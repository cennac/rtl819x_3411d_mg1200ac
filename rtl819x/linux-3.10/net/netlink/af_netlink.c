/*
 * NETLINK      Kernel-user communication protocol.
 *
 * 		Authors:	Alan Cox <alan@lxorguk.ukuu.org.uk>
 * 				Alexey Kuznetsov <kuznet@ms2.inr.ac.ru>
 * 				Patrick McHardy <kaber@trash.net>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 * Tue Jun 26 14:36:48 MEST 2001 Herbert "herp" Rosmanith
 *                               added netlink_proto_exit
 * Tue Jan 22 18:32:44 BRST 2002 Arnaldo C. de Melo <acme@conectiva.com.br>
 * 				 use nlk_sk, as sk->protinfo is on a diet 8)
 * Fri Jul 22 19:51:12 MEST 2005 Harald Welte <laforge@gnumonks.org>
 * 				 - inc module use count of module that owns
 * 				   the kernel socket in case userspace opens
 * 				   socket of same protocol
 * 				 - remove all module support, since netlink is
 * 				   mandatory if CONFIG_NET=y these days
 */

#include <linux/module.h>

#include <linux/capability.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/stat.h>
#include <linux/socket.h>
#include <linux/un.h>
#include <linux/fcntl.h>
#include <linux/termios.h>
#include <linux/sockios.h>
#include <linux/net.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/rtnetlink.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/notifier.h>
#include <linux/security.h>
#include <linux/jhash.h>
#include <linux/jiffies.h>
#include <linux/random.h>
#include <linux/bitops.h>
#include <linux/mm.h>
#include <linux/types.h>
#include <linux/audit.h>
#include <linux/mutex.h>
#include <linux/vmalloc.h>
#include <asm/cacheflush.h>

#include <net/net_namespace.h>
#include <net/sock.h>
#include <net/scm.h>
#include <net/netlink.h>

#include "af_netlink.h"

struct listeners {
	struct rcu_head		rcu;
	unsigned long		masks[0];
};

/* state bits */
#define NETLINK_CONGESTED	0x0

/* flags */
#define NETLINK_KERNEL_SOCKET	0x1
#define NETLINK_RECV_PKTINFO	0x2
#define NETLINK_BROADCAST_SEND_ERROR	0x4
#define NETLINK_RECV_NO_ENOBUFS	0x8

static inline int netlink_is_kernel(struct sock *sk)
{
	return nlk_sk(sk)->flags & NETLINK_KERNEL_SOCKET;
}

struct netlink_table *nl_table;
EXPORT_SYMBOL_GPL(nl_table);

static DECLARE_WAIT_QUEUE_HEAD(nl_table_wait);

static int netlink_dump(struct sock *sk);
static void netlink_skb_destructor(struct sk_buff *skb);

DEFINE_RWLOCK(nl_table_lock);
EXPORT_SYMBOL_GPL(nl_table_lock);
static atomic_t nl_table_users = ATOMIC_INIT(0);

#define nl_deref_protected(X) rcu_dereference_protected(X, lockdep_is_held(&nl_table_lock));

static ATOMIC_NOTIFIER_HEAD(netlink_chain);

static inline u32 netlink_group_mask(u32 group)
{
	return group ? 1 << (group - 1) : 0;
}

static inline struct hlist_head *nl_portid_hashfn(struct nl_portid_hash *hash, u32 portid)
{
	return &hash->table[jhash_1word(portid, hash->rnd) & hash->mask];
}

static void netlink_overrun(struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (!(nlk->flags & NETLINK_RECV_NO_ENOBUFS)) {
		if (!test_and_set_bit(NETLINK_CONGESTED, &nlk_sk(sk)->state)) {
			sk->sk_err = ENOBUFS;
			sk->sk_error_report(sk);
		}
	}
	atomic_inc(&sk->sk_drops);
}

static void netlink_rcv_wake(struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (skb_queue_empty(&sk->sk_receive_queue))
		clear_bit(NETLINK_CONGESTED, &nlk->state);
	if (!test_bit(NETLINK_CONGESTED, &nlk->state))
		wake_up_interruptible(&nlk->wait);
}

#ifdef CONFIG_NETLINK_MMAP
static bool netlink_skb_is_mmaped(const struct sk_buff *skb)
{
	return NETLINK_CB(skb).flags & NETLINK_SKB_MMAPED;
}

static bool netlink_rx_is_mmaped(struct sock *sk)
{
	return nlk_sk(sk)->rx_ring.pg_vec != NULL;
}

static bool netlink_tx_is_mmaped(struct sock *sk)
{
	return nlk_sk(sk)->tx_ring.pg_vec != NULL;
}

static __pure struct page *pgvec_to_page(const void *addr)
{
	if (is_vmalloc_addr(addr))
		return vmalloc_to_page(addr);
	else
		return virt_to_page(addr);
}

static void free_pg_vec(void **pg_vec, unsigned int order, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++) {
		if (pg_vec[i] != NULL) {
			if (is_vmalloc_addr(pg_vec[i]))
				vfree(pg_vec[i]);
			else
				free_pages((unsigned long)pg_vec[i], order);
		}
	}
	kfree(pg_vec);
}

static void *alloc_one_pg_vec_page(unsigned long order)
{
	void *buffer;
	gfp_t gfp_flags = GFP_KERNEL | __GFP_COMP | __GFP_ZERO |
			  __GFP_NOWARN | __GFP_NORETRY;

	buffer = (void *)__get_free_pages(gfp_flags, order);
	if (buffer != NULL)
		return buffer;

	buffer = vzalloc((1 << order) * PAGE_SIZE);
	if (buffer != NULL)
		return buffer;

	gfp_flags &= ~__GFP_NORETRY;
	return (void *)__get_free_pages(gfp_flags, order);
}

static void **alloc_pg_vec(struct netlink_sock *nlk,
			   struct nl_mmap_req *req, unsigned int order)
{
	unsigned int block_nr = req->nm_block_nr;
	unsigned int i;
	void **pg_vec, *ptr;

	pg_vec = kcalloc(block_nr, sizeof(void *), GFP_KERNEL);
	if (pg_vec == NULL)
		return NULL;

	for (i = 0; i < block_nr; i++) {
		pg_vec[i] = ptr = alloc_one_pg_vec_page(order);
		if (pg_vec[i] == NULL)
			goto err1;
	}

	return pg_vec;
err1:
	free_pg_vec(pg_vec, order, block_nr);
	return NULL;
}


static void
__netlink_set_ring(struct sock *sk, struct nl_mmap_req *req, bool tx_ring, void **pg_vec,
		   unsigned int order)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	struct sk_buff_head *queue;
	struct netlink_ring *ring;

	queue = tx_ring ? &sk->sk_write_queue : &sk->sk_receive_queue;
	ring  = tx_ring ? &nlk->tx_ring : &nlk->rx_ring;

	spin_lock_bh(&queue->lock);

	ring->frame_max		= req->nm_frame_nr - 1;
	ring->head		= 0;
	ring->frame_size	= req->nm_frame_size;
	ring->pg_vec_pages	= req->nm_block_size / PAGE_SIZE;

	swap(ring->pg_vec_len, req->nm_block_nr);
	swap(ring->pg_vec_order, order);
	swap(ring->pg_vec, pg_vec);

	__skb_queue_purge(queue);
	spin_unlock_bh(&queue->lock);

	WARN_ON(atomic_read(&nlk->mapped));

	if (pg_vec)
		free_pg_vec(pg_vec, order, req->nm_block_nr);
}

static int netlink_set_ring(struct sock *sk, struct nl_mmap_req *req,
			    bool tx_ring)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_ring *ring;
	void **pg_vec = NULL;
	unsigned int order = 0;

	ring  = tx_ring ? &nlk->tx_ring : &nlk->rx_ring;

	if (atomic_read(&nlk->mapped))
		return -EBUSY;
	if (atomic_read(&ring->pending))
		return -EBUSY;

	if (req->nm_block_nr) {
		if (ring->pg_vec != NULL)
			return -EBUSY;

		if ((int)req->nm_block_size <= 0)
			return -EINVAL;
		if (!IS_ALIGNED(req->nm_block_size, PAGE_SIZE))
			return -EINVAL;
		if (req->nm_frame_size < NL_MMAP_HDRLEN)
			return -EINVAL;
		if (!IS_ALIGNED(req->nm_frame_size, NL_MMAP_MSG_ALIGNMENT))
			return -EINVAL;

		ring->frames_per_block = req->nm_block_size /
					 req->nm_frame_size;
		if (ring->frames_per_block == 0)
			return -EINVAL;
		if (ring->frames_per_block * req->nm_block_nr !=
		    req->nm_frame_nr)
			return -EINVAL;

		order = get_order(req->nm_block_size);
		pg_vec = alloc_pg_vec(nlk, req, order);
		if (pg_vec == NULL)
			return -ENOMEM;
	} else {
		if (req->nm_frame_nr)
			return -EINVAL;
	}

	mutex_lock(&nlk->pg_vec_lock);
	if (atomic_read(&nlk->mapped) == 0) {
		__netlink_set_ring(sk, req, tx_ring, pg_vec, order);
		mutex_unlock(&nlk->pg_vec_lock);
		return 0;
	}

	mutex_unlock(&nlk->pg_vec_lock);

	if (pg_vec)
		free_pg_vec(pg_vec, order, req->nm_block_nr);

	return -EBUSY;
}

static void netlink_mm_open(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;
	struct socket *sock = file->private_data;
	struct sock *sk = sock->sk;

	if (sk)
		atomic_inc(&nlk_sk(sk)->mapped);
}

static void netlink_mm_close(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;
	struct socket *sock = file->private_data;
	struct sock *sk = sock->sk;

	if (sk)
		atomic_dec(&nlk_sk(sk)->mapped);
}

static const struct vm_operations_struct netlink_mmap_ops = {
	.open	= netlink_mm_open,
	.close	= netlink_mm_close,
};

static int netlink_mmap(struct file *file, struct socket *sock,
			struct vm_area_struct *vma)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_ring *ring;
	unsigned long start, size, expected;
	unsigned int i;
	int err = -EINVAL;

	if (vma->vm_pgoff)
		return -EINVAL;

	mutex_lock(&nlk->pg_vec_lock);

	expected = 0;
	for (ring = &nlk->rx_ring; ring <= &nlk->tx_ring; ring++) {
		if (ring->pg_vec == NULL)
			continue;
		expected += ring->pg_vec_len * ring->pg_vec_pages * PAGE_SIZE;
	}

	if (expected == 0)
		goto out;

	size = vma->vm_end - vma->vm_start;
	if (size != expected)
		goto out;

	start = vma->vm_start;
	for (ring = &nlk->rx_ring; ring <= &nlk->tx_ring; ring++) {
		if (ring->pg_vec == NULL)
			continue;

		for (i = 0; i < ring->pg_vec_len; i++) {
			struct page *page;
			void *kaddr = ring->pg_vec[i];
			unsigned int pg_num;

			for (pg_num = 0; pg_num < ring->pg_vec_pages; pg_num++) {
				page = pgvec_to_page(kaddr);
				err = vm_insert_page(vma, start, page);
				if (err < 0)
					goto out;
				start += PAGE_SIZE;
				kaddr += PAGE_SIZE;
			}
		}
	}

	atomic_inc(&nlk->mapped);
	vma->vm_ops = &netlink_mmap_ops;
	err = 0;
out:
	mutex_unlock(&nlk->pg_vec_lock);
	return err;
}

static void netlink_frame_flush_dcache(const struct nl_mmap_hdr *hdr, unsigned int nm_len)
{
#if ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	struct page *p_start, *p_end;

	/* First page is flushed through netlink_{get,set}_status */
	p_start = pgvec_to_page(hdr + PAGE_SIZE);
	p_end   = pgvec_to_page((void *)hdr + NL_MMAP_HDRLEN + nm_len - 1);
	while (p_start <= p_end) {
		flush_dcache_page(p_start);
		p_start++;
	}
#endif
}

static enum nl_mmap_status netlink_get_status(const struct nl_mmap_hdr *hdr)
{
	smp_rmb();
	flush_dcache_page(pgvec_to_page(hdr));
	return hdr->nm_status;
}

static void netlink_set_status(struct nl_mmap_hdr *hdr,
			       enum nl_mmap_status status)
{
	smp_mb();
	hdr->nm_status = status;
	flush_dcache_page(pgvec_to_page(hdr));
}

static struct nl_mmap_hdr *
__netlink_lookup_frame(const struct netlink_ring *ring, unsigned int pos)
{
	unsigned int pg_vec_pos, frame_off;

	pg_vec_pos = pos / ring->frames_per_block;
	frame_off  = pos % ring->frames_per_block;

	return ring->pg_vec[pg_vec_pos] + (frame_off * ring->frame_size);
}

static struct nl_mmap_hdr *
netlink_lookup_frame(const struct netlink_ring *ring, unsigned int pos,
		     enum nl_mmap_status status)
{
	struct nl_mmap_hdr *hdr;

	hdr = __netlink_lookup_frame(ring, pos);
	if (netlink_get_status(hdr) != status)
		return NULL;

	return hdr;
}

static struct nl_mmap_hdr *
netlink_current_frame(const struct netlink_ring *ring,
		      enum nl_mmap_status status)
{
	return netlink_lookup_frame(ring, ring->head, status);
}

static struct nl_mmap_hdr *
netlink_previous_frame(const struct netlink_ring *ring,
		       enum nl_mmap_status status)
{
	unsigned int prev;

	prev = ring->head ? ring->head - 1 : ring->frame_max;
	return netlink_lookup_frame(ring, prev, status);
}

static void netlink_increment_head(struct netlink_ring *ring)
{
	ring->head = ring->head != ring->frame_max ? ring->head + 1 : 0;
}

static void netlink_forward_ring(struct netlink_ring *ring)
{
	unsigned int head = ring->head, pos = head;
	const struct nl_mmap_hdr *hdr;

	do {
		hdr = __netlink_lookup_frame(ring, pos);
		if (hdr->nm_status == NL_MMAP_STATUS_UNUSED)
			break;
		if (hdr->nm_status != NL_MMAP_STATUS_SKIP)
			break;
		netlink_increment_head(ring);
	} while (ring->head != head);
}

static bool netlink_dump_space(struct netlink_sock *nlk)
{
	struct netlink_ring *ring = &nlk->rx_ring;
	struct nl_mmap_hdr *hdr;
	unsigned int n;

	hdr = netlink_current_frame(ring, NL_MMAP_STATUS_UNUSED);
	if (hdr == NULL)
		return false;

	n = ring->head + ring->frame_max / 2;
	if (n > ring->frame_max)
		n -= ring->frame_max;

	hdr = __netlink_lookup_frame(ring, n);

	return hdr->nm_status == NL_MMAP_STATUS_UNUSED;
}

static unsigned int netlink_poll(struct file *file, struct socket *sock,
				 poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	unsigned int mask;
	int err;

	if (nlk->rx_ring.pg_vec != NULL) {
		/* Memory mapped sockets don't call recvmsg(), so flow control
		 * for dumps is performed here. A dump is allowed to continue
		 * if at least half the ring is unused.
		 */
		while (nlk->cb_running && netlink_dump_space(nlk)) {
			err = netlink_dump(sk);
			if (err < 0) {
				sk->sk_err = -err;
				sk->sk_error_report(sk);
				break;
			}
		}
		netlink_rcv_wake(sk);
	}

	mask = datagram_poll(file, sock, wait);

	spin_lock_bh(&sk->sk_receive_queue.lock);
	if (nlk->rx_ring.pg_vec) {
		netlink_forward_ring(&nlk->rx_ring);
		if (!netlink_previous_frame(&nlk->rx_ring, NL_MMAP_STATUS_UNUSED))
			mask |= POLLIN | POLLRDNORM;
	}
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	spin_lock_bh(&sk->sk_write_queue.lock);
	if (nlk->tx_ring.pg_vec) {
		if (netlink_current_frame(&nlk->tx_ring, NL_MMAP_STATUS_UNUSED))
			mask |= POLLOUT | POLLWRNORM;
	}
	spin_unlock_bh(&sk->sk_write_queue.lock);

	return mask;
}

static struct nl_mmap_hdr *netlink_mmap_hdr(struct sk_buff *skb)
{
	return (struct nl_mmap_hdr *)(skb->head - NL_MMAP_HDRLEN);
}

static void netlink_ring_setup_skb(struct sk_buff *skb, struct sock *sk,
				   struct netlink_ring *ring,
				   struct nl_mmap_hdr *hdr)
{
	unsigned int size;
	void *data;

	size = ring->frame_size - NL_MMAP_HDRLEN;
	data = (void *)hdr + NL_MMAP_HDRLEN;

	skb->head	= data;
	skb->data	= data;
	skb_reset_tail_pointer(skb);
	skb->end	= skb->tail + size;
	skb->len	= 0;

	skb->destructor	= netlink_skb_destructor;
	NETLINK_CB(skb).flags |= NETLINK_SKB_MMAPED;
	NETLINK_CB(skb).sk = sk;
}

static int netlink_mmap_sendmsg(struct sock *sk, struct msghdr *msg,
				u32 dst_portid, u32 dst_group,
				struct sock_iocb *siocb)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_ring *ring;
	struct nl_mmap_hdr *hdr;
	struct sk_buff *skb;
	unsigned int maxlen;
	int err = 0, len = 0;

	mutex_lock(&nlk->pg_vec_lock);

	ring   = &nlk->tx_ring;
	maxlen = ring->frame_size - NL_MMAP_HDRLEN;

	do {
		unsigned int nm_len;

		hdr = netlink_current_frame(ring, NL_MMAP_STATUS_VALID);
		if (hdr == NULL) {
			if (!(msg->msg_flags & MSG_DONTWAIT) &&
			    atomic_read(&nlk->tx_ring.pending))
				schedule();
			continue;
		}

		nm_len = ACCESS_ONCE(hdr->nm_len);
		if (nm_len > maxlen) {
			err = -EINVAL;
			goto out;
		}

		netlink_frame_flush_dcache(hdr, nm_len);

		skb = alloc_skb(nm_len, GFP_KERNEL);
		if (skb == NULL) {
			err = -ENOBUFS;
			goto out;
		}
		__skb_put(skb, nm_len);
		memcpy(skb->data, (void *)hdr + NL_MMAP_HDRLEN, nm_len);
		netlink_set_status(hdr, NL_MMAP_STATUS_UNUSED);

		netlink_increment_head(ring);

		NETLINK_CB(skb).portid	  = nlk->portid;
		NETLINK_CB(skb).dst_group = dst_group;
		NETLINK_CB(skb).creds	  = siocb->scm->creds;

		err = security_netlink_send(sk, skb);
		if (err) {
			kfree_skb(skb);
			goto out;
		}

		if (unlikely(dst_group)) {
			atomic_inc(&skb->users);
			netlink_broadcast(sk, skb, dst_portid, dst_group,
					  GFP_KERNEL);
		}
		err = netlink_unicast(sk, skb, dst_portid,
				      msg->msg_flags & MSG_DONTWAIT);
		if (err < 0)
			goto out;
		len += err;

	} while (hdr != NULL ||
		 (!(msg->msg_flags & MSG_DONTWAIT) &&
		  atomic_read(&nlk->tx_ring.pending)));

	if (len > 0)
		err = len;
out:
	mutex_unlock(&nlk->pg_vec_lock);
	return err;
}

static void netlink_queue_mmaped_skb(struct sock *sk, struct sk_buff *skb)
{
	struct nl_mmap_hdr *hdr;

	hdr = netlink_mmap_hdr(skb);
	hdr->nm_len	= skb->len;
	hdr->nm_group	= NETLINK_CB(skb).dst_group;
	hdr->nm_pid	= NETLINK_CB(skb).creds.pid;
	hdr->nm_uid	= from_kuid(sk_user_ns(sk), NETLINK_CB(skb).creds.uid);
	hdr->nm_gid	= from_kgid(sk_user_ns(sk), NETLINK_CB(skb).creds.gid);
	netlink_frame_flush_dcache(hdr, hdr->nm_len);
	netlink_set_status(hdr, NL_MMAP_STATUS_VALID);

	NETLINK_CB(skb).flags |= NETLINK_SKB_DELIVERED;
	kfree_skb(skb);
}

static void netlink_ring_set_copied(struct sock *sk, struct sk_buff *skb)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_ring *ring = &nlk->rx_ring;
	struct nl_mmap_hdr *hdr;

	spin_lock_bh(&sk->sk_receive_queue.lock);
	hdr = netlink_current_frame(ring, NL_MMAP_STATUS_UNUSED);
	if (hdr == NULL) {
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		kfree_skb(skb);
		netlink_overrun(sk);
		return;
	}
	netlink_increment_head(ring);
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	hdr->nm_len	= skb->len;
	hdr->nm_group	= NETLINK_CB(skb).dst_group;
	hdr->nm_pid	= NETLINK_CB(skb).creds.pid;
	hdr->nm_uid	= from_kuid(sk_user_ns(sk), NETLINK_CB(skb).creds.uid);
	hdr->nm_gid	= from_kgid(sk_user_ns(sk), NETLINK_CB(skb).creds.gid);
	netlink_set_status(hdr, NL_MMAP_STATUS_COPY);
}

#else /* CONFIG_NETLINK_MMAP */
#define netlink_skb_is_mmaped(skb)	false
#define netlink_rx_is_mmaped(sk)	false
#define netlink_tx_is_mmaped(sk)	false
#define netlink_mmap			sock_no_mmap
#define netlink_poll			datagram_poll
#define netlink_mmap_sendmsg(sk, msg, dst_portid, dst_group, siocb)	0
#endif /* CONFIG_NETLINK_MMAP */

static void netlink_skb_destructor(struct sk_buff *skb)
{
#ifdef CONFIG_NETLINK_MMAP
	struct nl_mmap_hdr *hdr;
	struct netlink_ring *ring;
	struct sock *sk;

	/* If a packet from the kernel to userspace was freed because of an
	 * error without being delivered to userspace, the kernel must reset
	 * the status. In the direction userspace to kernel, the status is
	 * always reset here after the packet was processed and freed.
	 */
	if (netlink_skb_is_mmaped(skb)) {
		hdr = netlink_mmap_hdr(skb);
		sk = NETLINK_CB(skb).sk;

		if (NETLINK_CB(skb).flags & NETLINK_SKB_TX) {
			netlink_set_status(hdr, NL_MMAP_STATUS_UNUSED);
			ring = &nlk_sk(sk)->tx_ring;
		} else {
			if (!(NETLINK_CB(skb).flags & NETLINK_SKB_DELIVERED)) {
				hdr->nm_len = 0;
				netlink_set_status(hdr, NL_MMAP_STATUS_VALID);
			}
			ring = &nlk_sk(sk)->rx_ring;
		}

		WARN_ON(atomic_read(&ring->pending) == 0);
		atomic_dec(&ring->pending);
		sock_put(sk);

		skb->head = NULL;
	}
#endif
	if (skb->sk != NULL)
		sock_rfree(skb);
}

static void netlink_skb_set_owner_r(struct sk_buff *skb, struct sock *sk)
{
	WARN_ON(skb->sk != NULL);
	skb->sk = sk;
	skb->destructor = netlink_skb_destructor;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	sk_mem_charge(sk, skb->truesize);
}

static void netlink_sock_destruct(struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (nlk->cb_running) {
		if (nlk->cb.done)
			nlk->cb.done(&nlk->cb);

		module_put(nlk->cb.module);
		kfree_skb(nlk->cb.skb);
	}

	skb_queue_purge(&sk->sk_receive_queue);
#ifdef CONFIG_NETLINK_MMAP
	if (1) {
		struct nl_mmap_req req;

		memset(&req, 0, sizeof(req));
		if (nlk->rx_ring.pg_vec)
			__netlink_set_ring(sk, &req, false, NULL, 0);
		memset(&req, 0, sizeof(req));
		if (nlk->tx_ring.pg_vec)
			__netlink_set_ring(sk, &req, true, NULL, 0);
	}
#endif /* CONFIG_NETLINK_MMAP */

	if (!sock_flag(sk, SOCK_DEAD)) {
		printk(KERN_ERR "Freeing alive netlink socket %p\n", sk);
		return;
	}

	WARN_ON(atomic_read(&sk->sk_rmem_alloc));
	WARN_ON(atomic_read(&sk->sk_wmem_alloc));
	WARN_ON(nlk_sk(sk)->groups);
}

/* This lock without WQ_FLAG_EXCLUSIVE is good on UP and it is _very_ bad on
 * SMP. Look, when several writers sleep and reader wakes them up, all but one
 * immediately hit write lock and grab all the cpus. Exclusive sleep solves
 * this, _but_ remember, it adds useless work on UP machines.
 */

void netlink_table_grab(void)
	__acquires(nl_table_lock)
{
	might_sleep();

	write_lock_irq(&nl_table_lock);

	if (atomic_read(&nl_table_users)) {
		DECLARE_WAITQUEUE(wait, current);

		add_wait_queue_exclusive(&nl_table_wait, &wait);
		for (;;) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			if (atomic_read(&nl_table_users) == 0)
				break;
			write_unlock_irq(&nl_table_lock);
			schedule();
			write_lock_irq(&nl_table_lock);
		}

		__set_current_state(TASK_RUNNING);
		remove_wait_queue(&nl_table_wait, &wait);
	}
}

void netlink_table_ungrab(void)
	__releases(nl_table_lock)
{
	write_unlock_irq(&nl_table_lock);
	wake_up(&nl_table_wait);
}

static inline void
netlink_lock_table(void)
{
	/* read_lock() synchronizes us to netlink_table_grab */

	read_lock(&nl_table_lock);
	atomic_inc(&nl_table_users);
	read_unlock(&nl_table_lock);
}

static inline void
netlink_unlock_table(void)
{
	if (atomic_dec_and_test(&nl_table_users))
		wake_up(&nl_table_wait);
}

static struct sock *netlink_lookup(struct net *net, int protocol, u32 portid)
{
	struct nl_portid_hash *hash = &nl_table[protocol].hash;
	struct hlist_head *head;
	struct sock *sk;

	read_lock(&nl_table_lock);
	head = nl_portid_hashfn(hash, portid);
	sk_for_each(sk, head) {
		if (net_eq(sock_net(sk), net) && (nlk_sk(sk)->portid == portid)) {
			sock_hold(sk);
			goto found;
		}
	}
	sk = NULL;
found:
	read_unlock(&nl_table_lock);
	return sk;
}

static struct hlist_head *nl_portid_hash_zalloc(size_t size)
{
	if (size <= PAGE_SIZE)
		return kzalloc(size, GFP_ATOMIC);
	else
		return (struct hlist_head *)
			__get_free_pages(GFP_ATOMIC | __GFP_ZERO,
					 get_order(size));
}

static void nl_portid_hash_free(struct hlist_head *table, size_t size)
{
	if (size <= PAGE_SIZE)
		kfree(table);
	else
		free_pages((unsigned long)table, get_order(size));
}

static int nl_portid_hash_rehash(struct nl_portid_hash *hash, int grow)
{
	unsigned int omask, mask, shift;
	size_t osize, size;
	struct hlist_head *otable, *table;
	int i;

	omask = mask = hash->mask;
	osize = size = (mask + 1) * sizeof(*table);
	shift = hash->shift;

	if (grow) {
		if (++shift > hash->max_shift)
			return 0;
		mask = mask * 2 + 1;
		size *= 2;
	}

	table = nl_portid_hash_zalloc(size);
	if (!table)
		return 0;

	otable = hash->table;
	hash->table = table;
	hash->mask = mask;
	hash->shift = shift;
	get_random_bytes(&hash->rnd, sizeof(hash->rnd));

	for (i = 0; i <= omask; i++) {
		struct sock *sk;
		struct hlist_node *tmp;

		sk_for_each_safe(sk, tmp, &otable[i])
			__sk_add_node(sk, nl_portid_hashfn(hash, nlk_sk(sk)->portid));
	}

	nl_portid_hash_free(otable, osize);
	hash->rehash_time = jiffies + 10 * 60 * HZ;
	return 1;
}

static inline int nl_portid_hash_dilute(struct nl_portid_hash *hash, int len)
{
	int avg = hash->entries >> hash->shift;

	if (unlikely(avg > 1) && nl_portid_hash_rehash(hash, 1))
		return 1;

	if (unlikely(len > avg) && time_after(jiffies, hash->rehash_time)) {
		nl_portid_hash_rehash(hash, 0);
		return 1;
	}

	return 0;
}

static const struct proto_ops netlink_ops;

static void
netlink_update_listeners(struct sock *sk)
{
	struct netlink_table *tbl = &nl_table[sk->sk_protocol];
	unsigned long mask;
	unsigned int i;
	struct listeners *listeners;

	listeners = nl_deref_protected(tbl->listeners);
	if (!listeners)
		return;

	for (i = 0; i < NLGRPLONGS(tbl->groups); i++) {
		mask = 0;
		sk_for_each_bound(sk, &tbl->mc_list) {
			if (i < NLGRPLONGS(nlk_sk(sk)->ngroups))
				mask |= nlk_sk(sk)->groups[i];
		}
		listeners->masks[i] = mask;
	}
	/* this function is only called with the netlink table "grabbed", which
	 * makes sure updates are visible before bind or setsockopt return. */
}

static int netlink_insert(struct sock *sk, struct net *net, u32 portid)
{
	struct nl_portid_hash *hash = &nl_table[sk->sk_protocol].hash;
	struct hlist_head *head;
	int err = -EADDRINUSE;
	struct sock *osk;
	int len;

	netlink_table_grab();
	head = nl_portid_hashfn(hash, portid);
	len = 0;
	sk_for_each(osk, head) {
		if (net_eq(sock_net(osk), net) && (nlk_sk(osk)->portid == portid))
			break;
		len++;
	}
	if (osk)
		goto err;

	err = -EBUSY;
	if (nlk_sk(sk)->portid)
		goto err;

	err = -ENOMEM;
	if (BITS_PER_LONG > 32 && unlikely(hash->entries >= UINT_MAX))
		goto err;

	if (len && nl_portid_hash_dilute(hash, len))
		head = nl_portid_hashfn(hash, portid);
	hash->entries++;
	nlk_sk(sk)->portid = portid;
	sk_add_node(sk, head);
	err = 0;

err:
	netlink_table_ungrab();
	return err;
}

static void netlink_remove(struct sock *sk)
{
	netlink_table_grab();
	if (sk_del_node_init(sk))
		nl_table[sk->sk_protocol].hash.entries--;
	if (nlk_sk(sk)->subscriptions)
		__sk_del_bind_node(sk);
	netlink_table_ungrab();
}

static struct proto netlink_proto = {
	.name	  = "NETLINK",
	.owner	  = THIS_MODULE,
	.obj_size = sizeof(struct netlink_sock),
};

static int __netlink_create(struct net *net, struct socket *sock,
			    struct mutex *cb_mutex, int protocol)
{
	struct sock *sk;
	struct netlink_sock *nlk;

	sock->ops = &netlink_ops;

	sk = sk_alloc(net, PF_NETLINK, GFP_KERNEL, &netlink_proto);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);

	nlk = nlk_sk(sk);
	if (cb_mutex) {
		nlk->cb_mutex = cb_mutex;
	} else {
		nlk->cb_mutex = &nlk->cb_def_mutex;
		mutex_init(nlk->cb_mutex);
	}
	init_waitqueue_head(&nlk->wait);
#ifdef CONFIG_NETLINK_MMAP
	mutex_init(&nlk->pg_vec_lock);
#endif

	sk->sk_destruct = netlink_sock_destruct;
	sk->sk_protocol = protocol;
	return 0;
}

static int netlink_create(struct net *net, struct socket *sock, int protocol,
			  int kern)
{
	struct module *module = NULL;
	struct mutex *cb_mutex;
	struct netlink_sock *nlk;
	void (*bind)(int group);
	int err = 0;

	sock->state = SS_UNCONNECTED;

	if (sock->type != SOCK_RAW && sock->type != SOCK_DGRAM)
		return -ESOCKTNOSUPPORT;

	if (protocol < 0 || protocol >= MAX_LINKS)
		return -EPROTONOSUPPORT;

	netlink_lock_table();
#ifdef CONFIG_MODULES
	if (!nl_table[protocol].registered) {
		netlink_unlock_table();
		request_module("net-pf-%d-proto-%d", PF_NETLINK, protocol);
		netlink_lock_table();
	}
#endif
	if (nl_table[protocol].registered &&
	    try_module_get(nl_table[protocol].module))
		module = nl_table[protocol].module;
	else
		err = -EPROTONOSUPPORT;
	cb_mutex = nl_table[protocol].cb_mutex;
	bind = nl_table[protocol].bind;
	netlink_unlock_table();

	if (err < 0)
		goto out;

	err = __netlink_create(net, sock, cb_mutex, protocol);
	if (err < 0)
		goto out_module;

	local_bh_disable();
	sock_prot_inuse_add(net, &netlink_proto, 1);
	local_bh_enable();

	nlk = nlk_sk(sock->sk);
	nlk->module = module;
	nlk->netlink_bind = bind;
out:
	return err;

out_module:
	module_put(module);
	goto out;
}

static int netlink_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk;

	if (!sk)
		return 0;

	netlink_remove(sk);
	sock_orphan(sk);
	nlk = nlk_sk(sk);

	/*
	 * OK. Socket is unlinked, any packets that arrive now
	 * will be purged.
	 */

	sock->sk = NULL;
	wake_up_interruptible_all(&nlk->wait);

	skb_queue_purge(&sk->sk_write_queue);

	if (nlk->portid) {
		struct netlink_notify n = {
						.net = sock_net(sk),
						.protocol = sk->sk_protocol,
						.portid = nlk->portid,
					  };
		atomic_notifier_call_chain(&netlink_chain,
				NETLINK_URELEASE, &n);
	}

	module_put(nlk->module);

	netlink_table_grab();
	if (netlink_is_kernel(sk)) {
		BUG_ON(nl_table[sk->sk_protocol].registered == 0);
		if (--nl_table[sk->sk_protocol].registered == 0) {
			struct listeners *old;

			old = nl_deref_protected(nl_table[sk->sk_protocol].listeners);
			RCU_INIT_POINTER(nl_table[sk->sk_protocol].listeners, NULL);
			kfree_rcu(old, rcu);
			nl_table[sk->sk_protocol].module = NULL;
			nl_table[sk->sk_protocol].bind = NULL;
			nl_table[sk->sk_protocol].flags = 0;
			nl_table[sk->sk_protocol].registered = 0;
		}
	} else if (nlk->subscriptions) {
		netlink_update_listeners(sk);
	}
	netlink_table_ungrab();

	kfree(nlk->groups);
	nlk->groups = NULL;

	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), &netlink_proto, -1);
	local_bh_enable();
	sock_put(sk);
	return 0;
}

static int netlink_autobind(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct net *net = sock_net(sk);
	struct nl_portid_hash *hash = &nl_table[sk->sk_protocol].hash;
	struct hlist_head *head;
	struct sock *osk;
	s32 portid = task_tgid_vnr(current);
	int err;
	static s32 rover = -4097;

retry:
	cond_resched();
	netlink_table_grab();
	head = nl_portid_hashfn(hash, portid);
	sk_for_each(osk, head) {
		if (!net_eq(sock_net(osk), net))
			continue;
		if (nlk_sk(osk)->portid == portid) {
			/* Bind collision, search negative portid values. */
			portid = rover--;
			if (rover > -4097)
				rover = -4097;
			netlink_table_ungrab();
			goto retry;
		}
	}
	netlink_table_ungrab();

	err = netlink_insert(sk, net, portid);
	if (err == -EADDRINUSE)
		goto retry;

	/* If 2 threads race to autobind, that is fine.  */
	if (err == -EBUSY)
		err = 0;

	return err;
}

/**
 * __netlink_ns_capable - General netlink message capability test
 * @nsp: NETLINK_CB of the socket buffer holding a netlink command from userspace.
 * @user_ns: The user namespace of the capability to use
 * @cap: The capability to use
 *
 * Test to see if the opener of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has has the capability @cap in the user namespace @user_ns.
 */
bool __netlink_ns_capable(const struct netlink_skb_parms *nsp,
			struct user_namespace *user_ns, int cap)
{
	return ((nsp->flags & NETLINK_SKB_DST) ||
		file_ns_capable(nsp->sk->sk_socket->file, user_ns, cap)) &&
		ns_capable(user_ns, cap);
}
EXPORT_SYMBOL(__netlink_ns_capable);

/**
 * netlink_ns_capable - General netlink message capability test
 * @skb: socket buffer holding a netlink command from userspace
 * @user_ns: The user namespace of the capability to use
 * @cap: The capability to use
 *
 * Test to see if the opener of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has has the capability @cap in the user namespace @user_ns.
 */
bool netlink_ns_capable(const struct sk_buff *skb,
			struct user_namespace *user_ns, int cap)
{
	return __netlink_ns_capable(&NETLINK_CB(skb), user_ns, cap);
}
EXPORT_SYMBOL(netlink_ns_capable);

/**
 * netlink_capable - Netlink global message capability test
 * @skb: socket buffer holding a netlink command from userspace
 * @cap: The capability to use
 *
 * Test to see if the opener of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has has the capability @cap in all user namespaces.
 */
bool netlink_capable(const struct sk_buff *skb, int cap)
{
	return netlink_ns_capable(skb, &init_user_ns, cap);
}
EXPORT_SYMBOL(netlink_capable);

/**
 * netlink_net_capable - Netlink network namespace message capability test
 * @skb: socket buffer holding a netlink command from userspace
 * @cap: The capability to use
 *
 * Test to see if the opener of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has has the capability @cap over the network namespace of
 * the socket we received the message from.
 */
bool netlink_net_capable(const struct sk_buff *skb, int cap)
{
	return netlink_ns_capable(skb, sock_net(skb->sk)->user_ns, cap);
}
EXPORT_SYMBOL(netlink_net_capable);

static inline int netlink_allowed(const struct socket *sock, unsigned int flag)
{
	return (nl_table[sock->sk->sk_protocol].flags & flag) ||
		ns_capable(sock_net(sock->sk)->user_ns, CAP_NET_ADMIN);
}

static void
netlink_update_subscriptions(struct sock *sk, unsigned int subscriptions)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (nlk->subscriptions && !subscriptions)
		__sk_del_bind_node(sk);
	else if (!nlk->subscriptions && subscriptions)
		sk_add_bind_node(sk, &nl_table[sk->sk_protocol].mc_list);
	nlk->subscriptions = subscriptions;
}

static int netlink_realloc_groups(struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	unsigned int groups;
	unsigned long *new_groups;
	int err = 0;

	netlink_table_grab();

	groups = nl_table[sk->sk_protocol].groups;
	if (!nl_table[sk->sk_protocol].registered) {
		err = -ENOENT;
		goto out_unlock;
	}

	if (nlk->ngroups >= groups)
		goto out_unlock;

	new_groups = krealloc(nlk->groups, NLGRPSZ(groups), GFP_ATOMIC);
	if (new_groups == NULL) {
		err = -ENOMEM;
		goto out_unlock;
	}
	memset((char *)new_groups + NLGRPSZ(nlk->ngroups), 0,
	       NLGRPSZ(groups) - NLGRPSZ(nlk->ngroups));

	nlk->groups = new_groups;
	nlk->ngroups = groups;
 out_unlock:
	netlink_table_ungrab();
	return err;
}

static int netlink_bind(struct socket *sock, struct sockaddr *addr,
			int addr_len)
{
	struct sock *sk = sock->sk;
	struct net *net = sock_net(sk);
	struct netlink_sock *nlk = nlk_sk(sk);
	struct sockaddr_nl *nladdr = (struct sockaddr_nl *)addr;
	int err;

	if (addr_len < sizeof(struct sockaddr_nl))
		return -EINVAL;

	if (nladdr->nl_family != AF_NETLINK)
		return -EINVAL;

	/* Only superuser is allowed to listen multicasts */
	if (nladdr->nl_groups) {
		if (!netlink_allowed(sock, NL_CFG_F_NONROOT_RECV))
			return -EPERM;
		err = netlink_realloc_groups(sk);
		if (err)
			return err;
	}

	if (nlk->portid) {
		if (nladdr->nl_pid != nlk->portid)
			return -EINVAL;
	} else {
		err = nladdr->nl_pid ?
			netlink_insert(sk, net, nladdr->nl_pid) :
			netlink_autobind(sock);
		if (err)
			return err;
	}

	if (!nladdr->nl_groups && (nlk->groups == NULL || !(u32)nlk->groups[0]))
		return 0;

	netlink_table_grab();
	netlink_update_subscriptions(sk, nlk->subscriptions +
					 hweight32(nladdr->nl_groups) -
					 hweight32(nlk->groups[0]));
	nlk->groups[0] = (nlk->groups[0] & ~0xffffffffUL) | nladdr->nl_groups;
	netlink_update_listeners(sk);
	netlink_table_ungrab();

	if (nlk->netlink_bind && nlk->groups[0]) {
		int i;

		for (i=0; i<nlk->ngroups; i++) {
			if (test_bit(i, nlk->groups))
				nlk->netlink_bind(i);
		}
	}

	return 0;
}

static int netlink_connect(struct socket *sock, struct sockaddr *addr,
			   int alen, int flags)
{
	int err = 0;
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	struct sockaddr_nl *nladdr = (struct sockaddr_nl *)addr;

	if (alen < sizeof(addr->sa_family))
		return -EINVAL;

	if (addr->sa_family == AF_UNSPEC) {
		sk->sk_state	= NETLINK_UNCONNECTED;
		nlk->dst_portid	= 0;
		nlk->dst_group  = 0;
		return 0;
	}
	if (addr->sa_family != AF_NETLINK)
		return -EINVAL;

	/* Only superuser is allowed to send multicasts */
	if (nladdr->nl_groups && !netlink_allowed(sock, NL_CFG_F_NONROOT_SEND))
		return -EPERM;

	if (!nlk->portid)
		err = netlink_autobind(sock);

	if (err == 0) {
		sk->sk_state	= NETLINK_CONNECTED;
		nlk->dst_portid = nladdr->nl_pid;
		nlk->dst_group  = ffs(nladdr->nl_groups);
	}

	return err;
}

static int netlink_getname(struct socket *sock, struct sockaddr *addr,
			   int *addr_len, int peer)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	DECLARE_SOCKADDR(struct sockaddr_nl *, nladdr, addr);

	nladdr->nl_family = AF_NETLINK;
	nladdr->nl_pad = 0;
	*addr_len = sizeof(*nladdr);

	if (peer) {
		nladdr->nl_pid = nlk->dst_portid;
		nladdr->nl_groups = netlink_group_mask(nlk->dst_group);
	} else {
		nladdr->nl_pid = nlk->portid;
		nladdr->nl_groups = nlk->groups ? nlk->groups[0] : 0;
	}
	return 0;
}

static struct sock *netlink_getsockbyportid(struct sock *ssk, u32 portid)
{
	struct sock *sock;
	struct netlink_sock *nlk;

	sock = netlink_lookup(sock_net(ssk), ssk->sk_protocol, portid);
	if (!sock)
		return ERR_PTR(-ECONNREFUSED);

	/* Don't bother queuing skb if kernel socket has no input function */
	nlk = nlk_sk(sock);
	if (sock->sk_state == NETLINK_CONNECTED &&
	    nlk->dst_portid != nlk_sk(ssk)->portid) {
		sock_put(sock);
		return ERR_PTR(-ECONNREFUSED);
	}
	return sock;
}

struct sock *netlink_getsockbyfilp(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	struct sock *sock;

	if (!S_ISSOCK(inode->i_mode))
		return ERR_PTR(-ENOTSOCK);

	sock = SOCKET_I(inode)->sk;
	if (sock->sk_family != AF_NETLINK)
		return ERR_PTR(-EINVAL);

	sock_hold(sock);
	return sock;
}

/*
 * Attach a skb to a netlink socket.
 * The caller must hold a reference to the destination socket. On error, the
 * reference is dropped. The skb is not send to the destination, just all
 * all error checks are performed and memory in the queue is reserved.
 * Return values:
 * < 0: error. skb freed, reference to sock dropped.
 * 0: continue
 * 1: repeat lookup - reference dropped while waiting for socket memory.
 */
int netlink_attachskb(struct sock *sk, struct sk_buff *skb,
		      long *timeo, struct sock *ssk)
{
	struct netlink_sock *nlk;

	nlk = nlk_sk(sk);

	if ((atomic_read(&sk->sk_rmem_alloc) > sk->sk_rcvbuf ||
	     test_bit(NETLINK_CONGESTED, &nlk->state)) &&
	    !netlink_skb_is_mmaped(skb)) {
		DECLARE_WAITQUEUE(wait, current);
		if (!*timeo) {
			if (!ssk || netlink_is_kernel(ssk))
				netlink_overrun(sk);
			sock_put(sk);
			kfree_skb(skb);
			return -EAGAIN;
		}

		__set_current_state(TASK_INTERRUPTIBLE);
		add_wait_queue(&nlk->wait, &wait);

		if ((atomic_read(&sk->sk_rmem_alloc) > sk->sk_rcvbuf ||
		     test_bit(NETLINK_CONGESTED, &nlk->state)) &&
		    !sock_flag(sk, SOCK_DEAD))
			*timeo = schedule_timeout(*timeo);

		__set_current_state(TASK_RUNNING);
		remove_wait_queue(&nlk->wait, &wait);
		sock_put(sk);

		if (signal_pending(current)) {
			kfree_skb(skb);
			return sock_intr_errno(*timeo);
		}
		return 1;
	}
	netlink_skb_set_owner_r(skb, sk);
	return 0;
}

static int __netlink_sendskb(struct sock *sk, struct sk_buff *skb)
{
	int len = skb->len;

#ifdef CONFIG_NETLINK_MMAP
	if (netlink_skb_is_mmaped(skb))
		netlink_queue_mmaped_skb(sk, skb);
	else if (netlink_rx_is_mmaped(sk))
		netlink_ring_set_copied(sk, skb);
	else
#endif /* CONFIG_NETLINK_MMAP */
		skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk, len);
	return len;
}

int netlink_sendskb(struct sock *sk, struct sk_buff *skb)
{
	int len = __netlink_sendskb(sk, skb);

	sock_put(sk);
	return len;
}

void netlink_detachskb(struct sock *sk, struct sk_buff *skb)
{
	kfree_skb(skb);
	sock_put(sk);
}

static struct sk_buff *netlink_trim(struct sk_buff *skb, gfp_t allocation)
{
	int delta;

	WARN_ON(skb->sk != NULL);
	if (netlink_skb_is_mmaped(skb))
		return skb;

	delta = skb->end - skb->tail;
	if (delta * 2 < skb->truesize)
		return skb;

	if (skb_shared(skb)) {
		struct sk_buff *nskb = skb_clone(skb, allocation);
		if (!nskb)
			return skb;
		consume_skb(skb);
		skb = nskb;
	}

	if (!pskb_expand_head(skb, 0, -delta, allocation))
		skb->truesize -= delta;

	return skb;
}

static int netlink_unicast_kernel(struct sock *sk, struct sk_buff *skb,
				  struct sock *ssk)
{
	int ret;
	struct netlink_sock *nlk = nlk_sk(sk);

	ret = -ECONNREFUSED;
	if (nlk->netlink_rcv != NULL) {
		ret = skb->len;
		netlink_skb_set_owner_r(skb, sk);
		NETLINK_CB(skb).sk = ssk;
		nlk->netlink_rcv(skb);
		consume_skb(skb);
	} else {
		kfree_skb(skb);
	}
	sock_put(sk);
	return ret;
}

int netlink_unicast(struct sock *ssk, struct sk_buff *skb,
		    u32 portid, int nonblock)
{
	struct sock *sk;
	int err;
	long timeo;

	skb = netlink_trim(skb, gfp_any());

	timeo = sock_sndtimeo(ssk, nonblock);
retry:
	sk = netlink_getsockbyportid(ssk, portid);
	if (IS_ERR(sk)) {
		kfree_skb(skb);
		return PTR_ERR(sk);
	}
	if (netlink_is_kernel(sk))
		return netlink_unicast_kernel(sk, skb, ssk);

	if (sk_filter(sk, skb)) {
		err = skb->len;
		kfree_skb(skb);
		sock_put(sk);
		return err;
	}

	err = netlink_attachskb(sk, skb, &timeo, ssk);
	if (err == 1)
		goto retry;
	if (err)
		return err;

	return netlink_sendskb(sk, skb);
}
EXPORT_SYMBOL(netlink_unicast);

struct sk_buff *netlink_alloc_skb(struct sock *ssk, unsigned int size,
				  u32 dst_portid, gfp_t gfp_mask)
{
#ifdef CONFIG_NETLINK_MMAP
	struct sock *sk = NULL;
	struct sk_buff *skb;
	struct netlink_ring *ring;
	struct nl_mmap_hdr *hdr;
	unsigned int maxlen;

	sk = netlink_getsockbyportid(ssk, dst_portid);
	if (IS_ERR(sk))
		goto out;

	ring = &nlk_sk(sk)->rx_ring;
	/* fast-path without atomic ops for common case: non-mmaped receiver */
	if (ring->pg_vec == NULL)
		goto out_put;

	skb = alloc_skb_head(gfp_mask);
	if (skb == NULL)
		goto err1;

	spin_lock_bh(&sk->sk_receive_queue.lock);
	/* check again under lock */
	if (ring->pg_vec == NULL)
		goto out_free;

	maxlen = ring->frame_size - NL_MMAP_HDRLEN;
	if (maxlen < size)
		goto out_free;

	netlink_forward_ring(ring);
	hdr = netlink_current_frame(ring, NL_MMAP_STATUS_UNUSED);
	if (hdr == NULL)
		goto err2;
	netlink_ring_setup_skb(skb, sk, ring, hdr);
	netlink_set_status(hdr, NL_MMAP_STATUS_RESERVED);
	atomic_inc(&ring->pending);
	netlink_increment_head(ring);

	spin_unlock_bh(&sk->sk_receive_queue.lock);
	return skb;

err2:
	kfree_skb(skb);
	spin_unlock_bh(&sk->sk_receive_queue.lock);
	netlink_overrun(sk);
err1:
	sock_put(sk);
	return NULL;

out_free:
	kfree_skb(skb);
	spin_unlock_bh(&sk->sk_receive_queue.lock);
out_put:
	sock_put(sk);
out:
#endif
	return alloc_skb(size, gfp_mask);
}
EXPORT_SYMBOL_GPL(netlink_alloc_skb);

int netlink_has_listeners(struct sock *sk, unsigned int group)
{
	int res = 0;
	struct listeners *listeners;

	BUG_ON(!netlink_is_kernel(sk));

	rcu_read_lock();
	listeners = rcu_dereference(nl_table[sk->sk_protocol].listeners);

	if (listeners && group - 1 < nl_table[sk->sk_protocol].groups)
		res = test_bit(group - 1, listeners->masks);

	rcu_read_unlock();

	return res;
}
EXPORT_SYMBOL_GPL(netlink_has_listeners);

static int netlink_broadcast_deliver(struct sock *sk, struct sk_buff *skb)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf &&
	    !test_bit(NETLINK_CONGESTED, &nlk->state)) {
		netlink_skb_set_owner_r(skb, sk);
		__netlink_sendskb(sk, skb);
		return atomic_read(&sk->sk_rmem_alloc) > (sk->sk_rcvbuf >> 1);
	}
	return -1;
}

struct netlink_broadcast_data {
	struct sock *exclude_sk;
	struct net *net;
	u32 portid;
	u32 group;
	int failure;
	int delivery_failure;
	int congested;
	int delivered;
	gfp_t allocation;
	struct sk_buff *skb, *skb2;
	int (*tx_filter)(struct sock *dsk, struct sk_buff *skb, void *data);
	void *tx_data;
};

static int do_one_broadcast(struct sock *sk,
				   struct netlink_broadcast_data *p)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	int val;

	if (p->exclude_sk == sk)
		goto out;

	if (nlk->portid == p->portid || p->group - 1 >= nlk->ngroups ||
	    !test_bit(p->group - 1, nlk->groups))
		goto out;

	if (!net_eq(sock_net(sk), p->net))
		goto out;

	if (p->failure) {
		netlink_overrun(sk);
		goto out;
	}

	sock_hold(sk);
	if (p->skb2 == NULL) {
		if (skb_shared(p->skb)) {
			p->skb2 = skb_clone(p->skb, p->allocation);
		} else {
			p->skb2 = skb_get(p->skb);
			/*
			 * skb ownership may have been set when
			 * delivered to a previous socket.
			 */
			skb_orphan(p->skb2);
		}
	}
	if (p->skb2 == NULL) {
		netlink_overrun(sk);
		/* Clone failed. Notify ALL listeners. */
		p->failure = 1;
		if (nlk->flags & NETLINK_BROADCAST_SEND_ERROR)
			p->delivery_failure = 1;
	} else if (p->tx_filter && p->tx_filter(sk, p->skb2, p->tx_data)) {
		kfree_skb(p->skb2);
		p->skb2 = NULL;
	} else if (sk_filter(sk, p->skb2)) {
		kfree_skb(p->skb2);
		p->skb2 = NULL;
	} else if ((val = netlink_broadcast_deliver(sk, p->skb2)) < 0) {
		netlink_overrun(sk);
		if (nlk->flags & NETLINK_BROADCAST_SEND_ERROR)
			p->delivery_failure = 1;
	} else {
		p->congested |= val;
		p->delivered = 1;
		p->skb2 = NULL;
	}
	sock_put(sk);

out:
	return 0;
}

int netlink_broadcast_filtered(struct sock *ssk, struct sk_buff *skb, u32 portid,
	u32 group, gfp_t allocation,
	int (*filter)(struct sock *dsk, struct sk_buff *skb, void *data),
	void *filter_data)
{
	struct net *net = sock_net(ssk);
	struct netlink_broadcast_data info;
	struct sock *sk;

	skb = netlink_trim(skb, allocation);

	info.exclude_sk = ssk;
	info.net = net;
	info.portid = portid;
	info.group = group;
	info.failure = 0;
	info.delivery_failure = 0;
	info.congested = 0;
	info.delivered = 0;
	info.allocation = allocation;
	info.skb = skb;
	info.skb2 = NULL;
	info.tx_filter = filter;
	info.tx_data = filter_data;

	/* While we sleep in clone, do not allow to change socket list */

	netlink_lock_table();

	sk_for_each_bound(sk, &nl_table[ssk->sk_protocol].mc_list)
		do_one_broadcast(sk, &info);

	consume_skb(skb);

	netlink_unlock_table();

	if (info.delivery_failure) {
		kfree_skb(info.skb2);
		return -ENOBUFS;
	}
	consume_skb(info.skb2);

	if (info.delivered) {
		if (info.congested && (allocation & __GFP_WAIT))
			yield();
		return 0;
	}
	return -ESRCH;
}
EXPORT_SYMBOL(netlink_broadcast_filtered);

int netlink_broadcast(struct sock *ssk, struct sk_buff *skb, u32 portid,
		      u32 group, gfp_t allocation)
{
	return netlink_broadcast_filtered(ssk, skb, portid, group, allocation,
		NULL, NULL);
}
EXPORT_SYMBOL(netlink_broadcast);

struct netlink_set_err_data {
	struct sock *exclude_sk;
	u32 portid;
	u32 group;
	int code;
};

static int do_one_set_err(struct sock *sk, struct netlink_set_err_data *p)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	int ret = 0;

	if (sk == p->exclude_sk)
		goto out;

	if (!net_eq(sock_net(sk), sock_net(p->exclude_sk)))
		goto out;

	if (nlk->portid == p->portid || p->group - 1 >= nlk->ngroups ||
	    !test_bit(p->group - 1, nlk->groups))
		goto out;

	if (p->code == ENOBUFS && nlk->flags & NETLINK_RECV_NO_ENOBUFS) {
		ret = 1;
		goto out;
	}

	sk->sk_err = p->code;
	sk->sk_error_report(sk);
out:
	return ret;
}

/**
 * netlink_set_err - report error to broadcast listeners
 * @ssk: the kernel netlink socket, as returned by netlink_kernel_create()
 * @portid: the PORTID of a process that we want to skip (if any)
 * @groups: the broadcast group that will notice the error
 * @code: error code, must be negative (as usual in kernelspace)
 *
 * This function returns the number of broadcast listeners that have set the
 * NETLINK_RECV_NO_ENOBUFS socket option.
 */
int netlink_set_err(struct sock *ssk, u32 portid, u32 group, int code)
{
	struct netlink_set_err_data info;
	struct sock *sk;
	int ret = 0;

	info.exclude_sk = ssk;
	info.portid = portid;
	info.group = group;
	/* sk->sk_err wants a positive error value */
	info.code = -code;

	read_lock(&nl_table_lock);

	sk_for_each_bound(sk, &nl_table[ssk->sk_protocol].mc_list)
		ret += do_one_set_err(sk, &info);

	read_unlock(&nl_table_lock);
	return ret;
}
EXPORT_SYMBOL(netlink_set_err);

/* must be called with netlink table grabbed */
static void netlink_update_socket_mc(struct netlink_sock *nlk,
				     unsigned int group,
				     int is_new)
{
	int old, new = !!is_new, subscriptions;

	old = test_bit(group - 1, nlk->groups);
	subscriptions = nlk->subscriptions - old + new;
	if (new)
		__set_bit(group - 1, nlk->groups);
	else
		__clear_bit(group - 1, nlk->groups);
	netlink_update_subscriptions(&nlk->sk, subscriptions);
	netlink_update_listeners(&nlk->sk);
}

static int netlink_setsockopt(struct socket *sock, int level, int optname,
			      char __user *optval, unsigned int optlen)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	unsigned int val = 0;
	int err;

	if (level != SOL_NETLINK)
		return -ENOPROTOOPT;

	if (optname != NETLINK_RX_RING && optname != NETLINK_TX_RING &&
	    optlen >= sizeof(int) &&
	    get_user(val, (unsigned int __user *)optval))
		return -EFAULT;

	switch (optname) {
	case NETLINK_PKTINFO:
		if (val)
			nlk->flags |= NETLINK_RECV_PKTINFO;
		else
			nlk->flags &= ~NETLINK_RECV_PKTINFO;
		err = 0;
		break;
	case NETLINK_ADD_MEMBERSHIP:
	case NETLINK_DROP_MEMBERSHIP: {
		if (!netlink_allowed(sock, NL_CFG_F_NONROOT_RECV))
			return -EPERM;
		err = netlink_realloc_groups(sk);
		if (err)
			return err;
		if (!val || val - 1 >= nlk->ngroups)
			return -EINVAL;
		netlink_table_grab();
		netlink_update_socket_mc(nlk, val,
					 optname == NETLINK_ADD_MEMBERSHIP);
		netlink_table_ungrab();

		if (nlk->netlink_bind)
			nlk->netlink_bind(val);

		err = 0;
		break;
	}
	case NETLINK_BROADCAST_ERROR:
		if (val)
			nlk->flags |= NETLINK_BROADCAST_SEND_ERROR;
		else
			nlk->flags &= ~NETLINK_BROADCAST_SEND_ERROR;
		err = 0;
		break;
	case NETLINK_NO_ENOBUFS:
		if (val) {
			nlk->flags |= NETLINK_RECV_NO_ENOBUFS;
			clear_bit(NETLINK_CONGESTED, &nlk->state);
			wake_up_interruptible(&nlk->wait);
		} else {
			nlk->flags &= ~NETLINK_RECV_NO_ENOBUFS;
		}
		err = 0;
		break;
#ifdef CONFIG_NETLINK_MMAP
	case NETLINK_RX_RING:
	case NETLINK_TX_RING: {
		struct nl_mmap_req req;

		/* Rings might consume more memory than queue limits, require
		 * CAP_NET_ADMIN.
		 */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		if (optlen < sizeof(req))
			return -EINVAL;
		if (copy_from_user(&req, optval, sizeof(req)))
			return -EFAULT;
		err = netlink_set_ring(sk, &req,
				       optname == NETLINK_TX_RING);
		break;
	}
#endif /* CONFIG_NETLINK_MMAP */
	default:
		err = -ENOPROTOOPT;
	}
	return err;
}

static int netlink_getsockopt(struct socket *sock, int level, int optname,
			      char __user *optval, int __user *optlen)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	int len, val, err;

	if (level != SOL_NETLINK)
		return -ENOPROTOOPT;

	if (get_user(len, optlen))
		return -EFAULT;
	if (len < 0)
		return -EINVAL;

	switch (optname) {
	case NETLINK_PKTINFO:
		if (len < sizeof(int))
			return -EINVAL;
		len = sizeof(int);
		val = nlk->flags & NETLINK_RECV_PKTINFO ? 1 : 0;
		if (put_user(len, optlen) ||
		    put_user(val, optval))
			return -EFAULT;
		err = 0;
		break;
	case NETLINK_BROADCAST_ERROR:
		if (len < sizeof(int))
			return -EINVAL;
		len = sizeof(int);
		val = nlk->flags & NETLINK_BROADCAST_SEND_ERROR ? 1 : 0;
		if (put_user(len, optlen) ||
		    put_user(val, optval))
			return -EFAULT;
		err = 0;
		break;
	case NETLINK_NO_ENOBUFS:
		if (len < sizeof(int))
			return -EINVAL;
		len = sizeof(int);
		val = nlk->flags & NETLINK_RECV_NO_ENOBUFS ? 1 : 0;
		if (put_user(len, optlen) ||
		    put_user(val, optval))
			return -EFAULT;
		err = 0;
		break;
	default:
		err = -ENOPROTOOPT;
	}
	return err;
}

static void netlink_cmsg_recv_pktinfo(struct msghdr *msg, struct sk_buff *skb)
{
	struct nl_pktinfo info;

	info.group = NETLINK_CB(skb).dst_group;
	put_cmsg(msg, SOL_NETLINK, NETLINK_PKTINFO, sizeof(info), &info);
}

static int netlink_sendmsg(struct kiocb *kiocb, struct socket *sock,
			   struct msghdr *msg, size_t len)
{
	struct sock_iocb *siocb = kiocb_to_siocb(kiocb);
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	struct sockaddr_nl *addr = msg->msg_name;
	u32 dst_portid;
	u32 dst_group;
	struct sk_buff *skb;
	int err;
	struct scm_cookie scm;
	u32 netlink_skb_flags = 0;

	if (msg->msg_flags&MSG_OOB)
		return -EOPNOTSUPP;

	if (NULL == siocb->scm)
		siocb->scm = &scm;

	err = scm_send(sock, msg, siocb->scm, true);
	if (err < 0)
		return err;

	if (msg->msg_namelen) {
		err = -EINVAL;
		if (addr->nl_family != AF_NETLINK)
			goto out;
		dst_portid = addr->nl_pid;
		dst_group = ffs(addr->nl_groups);
		err =  -EPERM;
		if ((dst_group || dst_portid) &&
		    !netlink_allowed(sock, NL_CFG_F_NONROOT_SEND))
			goto out;
		netlink_skb_flags |= NETLINK_SKB_DST;
	} else {
		dst_portid = nlk->dst_portid;
		dst_group = nlk->dst_group;
	}

	if (!nlk->portid) {
		err = netlink_autobind(sock);
		if (err)
			goto out;
	}

	if (netlink_tx_is_mmaped(sk) &&
	    msg->msg_iov->iov_base == NULL) {
		err = netlink_mmap_sendmsg(sk, msg, dst_portid, dst_group,
					   siocb);
		goto out;
	}

	err = -EMSGSIZE;
	if (len > sk->sk_sndbuf - 32)
		goto out;
	err = -ENOBUFS;
	skb = alloc_skb(len, GFP_KERNEL);
	if (skb == NULL)
		goto out;

	NETLINK_CB(skb).portid	= nlk->portid;
	NETLINK_CB(skb).dst_group = dst_group;
	NETLINK_CB(skb).creds	= siocb->scm->creds;
	NETLINK_CB(skb).flags	= netlink_skb_flags;

	err = -EFAULT;
	if (memcpy_fromiovec(skb_put(skb, len), msg->msg_iov, len)) {
		kfree_skb(skb);
		goto out;
	}

	err = security_netlink_send(sk, skb);
	if (err) {
		kfree_skb(skb);
		goto out;
	}

	if (dst_group) {
		atomic_inc(&skb->users);
		netlink_broadcast(sk, skb, dst_portid, dst_group, GFP_KERNEL);
	}
	err = netlink_unicast(sk, skb, dst_portid, msg->msg_flags&MSG_DONTWAIT);

out:
	scm_destroy(siocb->scm);
	return err;
}

static int netlink_recvmsg(struct kiocb *kiocb, struct socket *sock,
			   struct msghdr *msg, size_t len,
			   int flags)
{
	struct sock_iocb *siocb = kiocb_to_siocb(kiocb);
	struct scm_cookie scm;
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk = nlk_sk(sk);
	int noblock = flags&MSG_DONTWAIT;
	size_t copied;
	struct sk_buff *skb, *data_skb;
	int err, ret;

	if (flags&MSG_OOB)
		return -EOPNOTSUPP;

	copied = 0;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	if (skb == NULL)
		goto out;

	data_skb = skb;

#ifdef CONFIG_COMPAT_NETLINK_MESSAGES
	if (unlikely(skb_shinfo(skb)->frag_list)) {
		/*
		 * If this skb has a frag_list, then here that means that we
		 * will have to use the frag_list skb's data for compat tasks
		 * and the regular skb's data for normal (non-compat) tasks.
		 *
		 * If we need to send the compat skb, assign it to the
		 * 'data_skb' variable so that it will be used below for data
		 * copying. We keep 'skb' for everything else, including
		 * freeing both later.
		 */
		if (flags & MSG_CMSG_COMPAT)
			data_skb = skb_shinfo(skb)->frag_list;
	}
#endif

	/* Record the max length of recvmsg() calls for future allocations */
	nlk->max_recvmsg_len = max(nlk->max_recvmsg_len, len);
	nlk->max_recvmsg_len = min_t(size_t, nlk->max_recvmsg_len,
				     16384);

	copied = data_skb->len;
	if (len < copied) {
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	}

	skb_reset_transport_header(data_skb);
	err = skb_copy_datagram_iovec(data_skb, 0, msg->msg_iov, copied);

	if (msg->msg_name) {
		struct sockaddr_nl *addr = (struct sockaddr_nl *)msg->msg_name;
		addr->nl_family = AF_NETLINK;
		addr->nl_pad    = 0;
		addr->nl_pid	= NETLINK_CB(skb).portid;
		addr->nl_groups	= netlink_group_mask(NETLINK_CB(skb).dst_group);
		msg->msg_namelen = sizeof(*addr);
	}

	if (nlk->flags & NETLINK_RECV_PKTINFO)
		netlink_cmsg_recv_pktinfo(msg, skb);

	if (NULL == siocb->scm) {
		memset(&scm, 0, sizeof(scm));
		siocb->scm = &scm;
	}
	siocb->scm->creds = *NETLINK_CREDS(skb);
	if (flags & MSG_TRUNC)
		copied = data_skb->len;

	skb_free_datagram(sk, skb);

	if (nlk->cb_running &&
	    atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf / 2) {
		ret = netlink_dump(sk);
		if (ret) {
			sk->sk_err = -ret;
			sk->sk_error_report(sk);
		}
	}

	scm_recv(sock, msg, siocb->scm, flags);
out:
	netlink_rcv_wake(sk);
	return err ? : copied;
}

static void netlink_data_ready(struct sock *sk, int len)
{
	BUG();
}

/*
 *	We export these functions to other modules. They provide a
 *	complete set of kernel non-blocking support for message
 *	queueing.
 */

struct sock *
__netlink_kernel_create(struct net *net, int unit, struct module *module,
			struct netlink_kernel_cfg *cfg)
{
	struct socket *sock;
	struct sock *sk;
	struct netlink_sock *nlk;
	struct listeners *listeners = NULL;
	struct mutex *cb_mutex = cfg ? cfg->cb_mutex : NULL;
	unsigned int groups;

	BUG_ON(!nl_table);

	if (unit < 0 || unit >= MAX_LINKS)
		return NULL;

	if (sock_create_lite(PF_NETLINK, SOCK_DGRAM, unit, &sock))
		return NULL;

	/*
	 * We have to just have a reference on the net from sk, but don't
	 * get_net it. Besides, we cannot get and then put the net here.
	 * So we create one inside init_net and the move it to net.
	 */

	if (__netlink_create(&init_net, sock, cb_mutex, unit) < 0)
		goto out_sock_release_nosk;

	sk = sock->sk;
	sk_change_net(sk, net);

	if (!cfg || cfg->groups < 32)
		groups = 32;
	else
		groups = cfg->groups;

	listeners = kzalloc(sizeof(*listeners) + NLGRPSZ(groups), GFP_KERNEL);
	if (!listeners)
		goto out_sock_release;

	sk->sk_data_ready = netlink_data_ready;
	if (cfg && cfg->input)
		nlk_sk(sk)->netlink_rcv = cfg->input;

	if (netlink_insert(sk, net, 0))
		goto out_sock_release;

	nlk = nlk_sk(sk);
	nlk->flags |= NETLINK_KERNEL_SOCKET;

	netlink_table_grab();
	if (!nl_table[unit].registered) {
		nl_table[unit].groups = groups;
		rcu_assign_pointer(nl_table[unit].listeners, listeners);
		nl_table[unit].cb_mutex = cb_mutex;
		nl_table[unit].module = module;
		if (cfg) {
			nl_table[unit].bind = cfg->bind;
			nl_table[unit].flags = cfg->flags;
		}
		nl_table[unit].registered = 1;
	} else {
		kfree(listeners);
		nl_table[unit].registered++;
	}
	netlink_table_ungrab();
	return sk;

out_sock_release:
	kfree(listeners);
	netlink_kernel_release(sk);
	return NULL;

out_sock_release_nosk:
	sock_release(sock);
	return NULL;
}
EXPORT_SYMBOL(__netlink_kernel_create);

void
netlink_kernel_release(struct sock *sk)
{
	sk_release_kernel(sk);
}
EXPORT_SYMBOL(netlink_kernel_release);

int __netlink_change_ngroups(struct sock *sk, unsigned int groups)
{
	struct listeners *new, *old;
	struct netlink_table *tbl = &nl_table[sk->sk_protocol];

	if (groups < 32)
		groups = 32;

	if (NLGRPSZ(tbl->groups) < NLGRPSZ(groups)) {
		new = kzalloc(sizeof(*new) + NLGRPSZ(groups), GFP_ATOMIC);
		if (!new)
			return -ENOMEM;
		old = nl_deref_protected(tbl->listeners);
		memcpy(new->masks, old->masks, NLGRPSZ(tbl->groups));
		rcu_assign_pointer(tbl->listeners, new);

		kfree_rcu(old, rcu);
	}
	tbl->groups = groups;

	return 0;
}

/**
 * netlink_change_ngroups - change number of multicast groups
 *
 * This changes the number of multicast groups that are available
 * on a certain netlink family. Note that it is not possible to
 * change the number of groups to below 32. Also note that it does
 * not implicitly call netlink_clear_multicast_users() when the
 * number of groups is reduced.
 *
 * @sk: The kernel netlink socket, as returned by netlink_kernel_create().
 * @groups: The new number of groups.
 */
int netlink_change_ngroups(struct sock *sk, unsigned int groups)
{
	int err;

	netlink_table_grab();
	err = __netlink_change_ngroups(sk, groups);
	netlink_table_ungrab();

	return err;
}

void __netlink_clear_multicast_users(struct sock *ksk, unsigned int group)
{
	struct sock *sk;
	struct netlink_table *tbl = &nl_table[ksk->sk_protocol];

	sk_for_each_bound(sk, &tbl->mc_list)
		netlink_update_socket_mc(nlk_sk(sk), group, 0);
}

/**
 * netlink_clear_multicast_users - kick off multicast listeners
 *
 * This function removes all listeners from the given group.
 * @ksk: The kernel netlink socket, as returned by
 *	netlink_kernel_create().
 * @group: The multicast group to clear.
 */
void netlink_clear_multicast_users(struct sock *ksk, unsigned int group)
{
	netlink_table_grab();
	__netlink_clear_multicast_users(ksk, group);
	netlink_table_ungrab();
}

struct nlmsghdr *
__nlmsg_put(struct sk_buff *skb, u32 portid, u32 seq, int type, int len, int flags)
{
	struct nlmsghdr *nlh;
	int size = nlmsg_msg_size(len);

	nlh = (struct nlmsghdr*)skb_put(skb, NLMSG_ALIGN(size));
	nlh->nlmsg_type = type;
	nlh->nlmsg_len = size;
	nlh->nlmsg_flags = flags;
	nlh->nlmsg_pid = portid;
	nlh->nlmsg_seq = seq;
	if (!__builtin_constant_p(size) || NLMSG_ALIGN(size) - size != 0)
		memset(nlmsg_data(nlh) + len, 0, NLMSG_ALIGN(size) - size);
	return nlh;
}
EXPORT_SYMBOL(__nlmsg_put);

/*
 * It looks a bit ugly.
 * It would be better to create kernel thread.
 */

static int netlink_dump(struct sock *sk)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	struct netlink_callback *cb;
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh;
	int len, err = -ENOBUFS;
	int alloc_min_size;
	int alloc_size;

	mutex_lock(nlk->cb_mutex);
	if (!nlk->cb_running) {
		err = -EINVAL;
		goto errout_skb;
	}

	if (!netlink_rx_is_mmaped(sk) &&
	    atomic_read(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		goto errout_skb;

	/* NLMSG_GOODSIZE is small to avoid high order allocations being
	 * required, but it makes sense to _attempt_ a 16K bytes allocation
	 * to reduce number of system calls on dump operations, if user
	 * ever provided a big enough buffer.
	 */
	cb = &nlk->cb;
	alloc_min_size = max_t(int, cb->min_dump_alloc, NLMSG_GOODSIZE);

	if (alloc_min_size < nlk->max_recvmsg_len) {
		alloc_size = nlk->max_recvmsg_len;
		skb = netlink_alloc_skb(sk, alloc_size, nlk->portid,
					GFP_KERNEL |
					__GFP_NOWARN |
					__GFP_NORETRY);
	}
	if (!skb) {
		alloc_size = alloc_min_size;
		skb = netlink_alloc_skb(sk, alloc_size, nlk->portid,
					GFP_KERNEL);
	}
	if (!skb)
		goto errout_skb;

	/* Trim skb to allocated size. User is expected to provide buffer as
	 * large as max(min_dump_alloc, 16KiB (mac_recvmsg_len capped at
	 * netlink_recvmsg())). dump will pack as many smaller messages as
	 * could fit within the allocated skb. skb is typically allocated
	 * with larger space than required (could be as much as near 2x the
	 * requested size with align to next power of 2 approach). Allowing
	 * dump to use the excess space makes it difficult for a user to have a
	 * reasonable static buffer based on the expected largest dump of a
	 * single netdev. The outcome is MSG_TRUNC error.
	 */
	skb_reserve(skb, skb_tailroom(skb) - alloc_size);
	netlink_skb_set_owner_r(skb, sk);

	len = cb->dump(skb, cb);

	if (len > 0) {
		mutex_unlock(nlk->cb_mutex);

		if (sk_filter(sk, skb))
			kfree_skb(skb);
		else
			__netlink_sendskb(sk, skb);
		return 0;
	}

	nlh = nlmsg_put_answer(skb, cb, NLMSG_DONE, sizeof(len), NLM_F_MULTI);
	if (!nlh)
		goto errout_skb;

	nl_dump_check_consistent(cb, nlh);

	memcpy(nlmsg_data(nlh), &len, sizeof(len));

	if (sk_filter(sk, skb))
		kfree_skb(skb);
	else
		__netlink_sendskb(sk, skb);

	if (cb->done)
		cb->done(cb);

	nlk->cb_running = false;
	mutex_unlock(nlk->cb_mutex);
	module_put(cb->module);
	consume_skb(cb->skb);
	return 0;

errout_skb:
	mutex_unlock(nlk->cb_mutex);
	kfree_skb(skb);
	return err;
}

int __netlink_dump_start(struct sock *ssk, struct sk_buff *skb,
			 const struct nlmsghdr *nlh,
			 struct netlink_dump_control *control)
{
	struct netlink_callback *cb;
	struct sock *sk;
	struct netlink_sock *nlk;
	int ret;

	/* Memory mapped dump requests need to be copied to avoid looping
	 * on the pending state in netlink_mmap_sendmsg() while the CB hold
	 * a reference to the skb.
	 */
	if (netlink_skb_is_mmaped(skb)) {
		skb = skb_copy(skb, GFP_KERNEL);
		if (skb == NULL)
			return -ENOBUFS;
	} else
		atomic_inc(&skb->users);

	sk = netlink_lookup(sock_net(ssk), ssk->sk_protocol, NETLINK_CB(skb).portid);
	if (sk == NULL) {
		ret = -ECONNREFUSED;
		goto error_free;
	}

	nlk = nlk_sk(sk);
	mutex_lock(nlk->cb_mutex);
	/* A dump is in progress... */
	if (nlk->cb_running) {
		ret = -EBUSY;
		goto error_unlock;
	}
	/* add reference of module which cb->dump belongs to */
	if (!try_module_get(control->module)) {
		ret = -EPROTONOSUPPORT;
		goto error_unlock;
	}

	cb = &nlk->cb;
	memset(cb, 0, sizeof(*cb));
	cb->dump = control->dump;
	cb->done = control->done;
	cb->nlh = nlh;
	cb->data = control->data;
	cb->module = control->module;
	cb->min_dump_alloc = control->min_dump_alloc;
	cb->skb = skb;

	nlk->cb_running = true;

	mutex_unlock(nlk->cb_mutex);

	ret = netlink_dump(sk);
	sock_put(sk);

	if (ret)
		return ret;

	/* We successfully started a dump, by returning -EINTR we
	 * signal not to send ACK even if it was requested.
	 */
	return -EINTR;

error_unlock:
	sock_put(sk);
	mutex_unlock(nlk->cb_mutex);
error_free:
	kfree_skb(skb);
	return ret;
}
EXPORT_SYMBOL(__netlink_dump_start);

void netlink_ack(struct sk_buff *in_skb, struct nlmsghdr *nlh, int err)
{
	struct sk_buff *skb;
	struct nlmsghdr *rep;
	struct nlmsgerr *errmsg;
	size_t payload = sizeof(*errmsg);

	/* error messages get the original request appened */
	if (err)
		payload += nlmsg_len(nlh);

	skb = netlink_alloc_skb(in_skb->sk, nlmsg_total_size(payload),
				NETLINK_CB(in_skb).portid, GFP_KERNEL);
	if (!skb) {
		struct sock *sk;

		sk = netlink_lookup(sock_net(in_skb->sk),
				    in_skb->sk->sk_protocol,
				    NETLINK_CB(in_skb).portid);
		if (sk) {
			sk->sk_err = ENOBUFS;
			sk->sk_error_report(sk);
			sock_put(sk);
		}
		return;
	}

	rep = __nlmsg_put(skb, NETLINK_CB(in_skb).portid, nlh->nlmsg_seq,
			  NLMSG_ERROR, payload, 0);
	errmsg = nlmsg_data(rep);
	errmsg->error = err;
	memcpy(&errmsg->msg, nlh, err ? nlh->nlmsg_len : sizeof(*nlh));
	netlink_unicast(in_skb->sk, skb, NETLINK_CB(in_skb).portid, MSG_DONTWAIT);
}
EXPORT_SYMBOL(netlink_ack);

int netlink_rcv_skb(struct sk_buff *skb, int (*cb)(struct sk_buff *,
						     struct nlmsghdr *))
{
	struct nlmsghdr *nlh;
	int err;

	while (skb->len >= nlmsg_total_size(0)) {
		int msglen;

		nlh = nlmsg_hdr(skb);
		err = 0;

		if (nlh->nlmsg_len < NLMSG_HDRLEN || skb->len < nlh->nlmsg_len)
			return 0;

		/* Only requests are handled by the kernel */
		if (!(nlh->nlmsg_flags & NLM_F_REQUEST))
			goto ack;

		/* Skip control messages */
		if (nlh->nlmsg_type < NLMSG_MIN_TYPE)
			goto ack;

		err = cb(skb, nlh);
		if (err == -EINTR)
			goto skip;

ack:
		if (nlh->nlmsg_flags & NLM_F_ACK || err)
			netlink_ack(skb, nlh, err);

skip:
		msglen = NLMSG_ALIGN(nlh->nlmsg_len);
		if (msglen > skb->len)
			msglen = skb->len;
		skb_pull(skb, msglen);
	}

	return 0;
}
EXPORT_SYMBOL(netlink_rcv_skb);

/**
 * nlmsg_notify - send a notification netlink message
 * @sk: netlink socket to use
 * @skb: notification message
 * @portid: destination netlink portid for reports or 0
 * @group: destination multicast group or 0
 * @report: 1 to report back, 0 to disable
 * @flags: allocation flags
 */
int nlmsg_notify(struct sock *sk, struct sk_buff *skb, u32 portid,
		 unsigned int group, int report, gfp_t flags)
{
	int err = 0;

	if (group) {
		int exclude_portid = 0;

		if (report) {
			atomic_inc(&skb->users);
			exclude_portid = portid;
		}

		/* errors reported via destination sk->sk_err, but propagate
		 * delivery errors if NETLINK_BROADCAST_ERROR flag is set */
		err = nlmsg_multicast(sk, skb, exclude_portid, group, flags);
	}

	if (report) {
		int err2;

		err2 = nlmsg_unicast(sk, skb, portid);
		if (!err || err == -ESRCH)
			err = err2;
	}

	return err;
}
EXPORT_SYMBOL(nlmsg_notify);

#ifdef CONFIG_PROC_FS
struct nl_seq_iter {
	struct seq_net_private p;
	int link;
	int hash_idx;
};

static struct sock *netlink_seq_socket_idx(struct seq_file *seq, loff_t pos)
{
	struct nl_seq_iter *iter = seq->private;
	int i, j;
	struct sock *s;
	loff_t off = 0;

	for (i = 0; i < MAX_LINKS; i++) {
		struct nl_portid_hash *hash = &nl_table[i].hash;

		for (j = 0; j <= hash->mask; j++) {
			sk_for_each(s, &hash->table[j]) {
				if (sock_net(s) != seq_file_net(seq))
					continue;
				if (off == pos) {
					iter->link = i;
					iter->hash_idx = j;
					return s;
				}
				++off;
			}
		}
	}
	return NULL;
}

static void *netlink_seq_start(struct seq_file *seq, loff_t *pos)
	__acquires(nl_table_lock)
{
	read_lock(&nl_table_lock);
	return *pos ? netlink_seq_socket_idx(seq, *pos - 1) : SEQ_START_TOKEN;
}

static void *netlink_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct sock *s;
	struct nl_seq_iter *iter;
	int i, j;

	++*pos;

	if (v == SEQ_START_TOKEN)
		return netlink_seq_socket_idx(seq, 0);

	iter = seq->private;
	s = v;
	do {
		s = sk_next(s);
	} while (s && sock_net(s) != seq_file_net(seq));
	if (s)
		return s;

	i = iter->link;
	j = iter->hash_idx + 1;

	do {
		struct nl_portid_hash *hash = &nl_table[i].hash;

		for (; j <= hash->mask; j++) {
			s = sk_head(&hash->table[j]);
			while (s && sock_net(s) != seq_file_net(seq))
				s = sk_next(s);
			if (s) {
				iter->link = i;
				iter->hash_idx = j;
				return s;
			}
		}

		j = 0;
	} while (++i < MAX_LINKS);

	return NULL;
}

static void netlink_seq_stop(struct seq_file *seq, void *v)
	__releases(nl_table_lock)
{
	read_unlock(&nl_table_lock);
}


static int netlink_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN) {
		seq_puts(seq,
			 "sk       Eth Pid    Groups   "
			 "Rmem     Wmem     Dump     Locks     Drops     Inode\n");
	} else {
		struct sock *s = v;
		struct netlink_sock *nlk = nlk_sk(s);

		seq_printf(seq, "%pK %-3d %-6u %08x %-8d %-8d %d %-8d %-8d %-8lu\n",
			   s,
			   s->sk_protocol,
			   nlk->portid,
			   nlk->groups ? (u32)nlk->groups[0] : 0,
			   sk_rmem_alloc_get(s),
			   sk_wmem_alloc_get(s),
			   nlk->cb_running,
			   atomic_read(&s->sk_refcnt),
			   atomic_read(&s->sk_drops),
			   sock_i_ino(s)
			);

	}
	return 0;
}

static const struct seq_operations netlink_seq_ops = {
	.start  = netlink_seq_start,
	.next   = netlink_seq_next,
	.stop   = netlink_seq_stop,
	.show   = netlink_seq_show,
};


static int netlink_seq_open(struct inode *inode, struct file *file)
{
	return seq_open_net(inode, file, &netlink_seq_ops,
				sizeof(struct nl_seq_iter));
}

static const struct file_operations netlink_seq_fops = {
	.owner		= THIS_MODULE,
	.open		= netlink_seq_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release_net,
};

#endif

int netlink_register_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&netlink_chain, nb);
}
EXPORT_SYMBOL(netlink_register_notifier);

int netlink_unregister_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&netlink_chain, nb);
}
EXPORT_SYMBOL(netlink_unregister_notifier);

static const struct proto_ops netlink_ops = {
	.family =	PF_NETLINK,
	.owner =	THIS_MODULE,
	.release =	netlink_release,
	.bind =		netlink_bind,
	.connect =	netlink_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	netlink_getname,
	.poll =		netlink_poll,
	.ioctl =	sock_no_ioctl,
	.listen =	sock_no_listen,
	.shutdown =	sock_no_shutdown,
	.setsockopt =	netlink_setsockopt,
	.getsockopt =	netlink_getsockopt,
	.sendmsg =	netlink_sendmsg,
	.recvmsg =	netlink_recvmsg,
	.mmap =		netlink_mmap,
	.sendpage =	sock_no_sendpage,
};

static const struct net_proto_family netlink_family_ops = {
	.family = PF_NETLINK,
	.create = netlink_create,
	.owner	= THIS_MODULE,	/* for consistency 8) */
};

static int __net_init netlink_net_init(struct net *net)
{
#ifdef CONFIG_PROC_FS
	if (!proc_create("netlink", 0, net->proc_net, &netlink_seq_fops))
		return -ENOMEM;
#endif
	return 0;
}

static void __net_exit netlink_net_exit(struct net *net)
{
#ifdef CONFIG_PROC_FS
	remove_proc_entry("netlink", net->proc_net);
#endif
}

static void __init netlink_add_usersock_entry(void)
{
	struct listeners *listeners;
	int groups = 32;

	listeners = kzalloc(sizeof(*listeners) + NLGRPSZ(groups), GFP_KERNEL);
	if (!listeners)
		panic("netlink_add_usersock_entry: Cannot allocate listeners\n");

	netlink_table_grab();

	nl_table[NETLINK_USERSOCK].groups = groups;
	rcu_assign_pointer(nl_table[NETLINK_USERSOCK].listeners, listeners);
	nl_table[NETLINK_USERSOCK].module = THIS_MODULE;
	nl_table[NETLINK_USERSOCK].registered = 1;
	nl_table[NETLINK_USERSOCK].flags = NL_CFG_F_NONROOT_SEND;

	netlink_table_ungrab();
}

static struct pernet_operations __net_initdata netlink_net_ops = {
	.init = netlink_net_init,
	.exit = netlink_net_exit,
};

static int __init netlink_proto_init(void)
{
	int i;
	unsigned long limit;
	unsigned int order;
	int err = proto_register(&netlink_proto, 0);

	if (err != 0)
		goto out;

	BUILD_BUG_ON(sizeof(struct netlink_skb_parms) > FIELD_SIZEOF(struct sk_buff, cb));

	nl_table = kcalloc(MAX_LINKS, sizeof(*nl_table), GFP_KERNEL);
	if (!nl_table)
		goto panic;

	if (totalram_pages >= (128 * 1024))
		limit = totalram_pages >> (21 - PAGE_SHIFT);
	else
		limit = totalram_pages >> (23 - PAGE_SHIFT);

	order = get_bitmask_order(limit) - 1 + PAGE_SHIFT;
	limit = (1UL << order) / sizeof(struct hlist_head);
	order = get_bitmask_order(min(limit, (unsigned long)UINT_MAX)) - 1;

	for (i = 0; i < MAX_LINKS; i++) {
		struct nl_portid_hash *hash = &nl_table[i].hash;

		hash->table = nl_portid_hash_zalloc(1 * sizeof(*hash->table));
		if (!hash->table) {
			while (i-- > 0)
				nl_portid_hash_free(nl_table[i].hash.table,
						 1 * sizeof(*hash->table));
			kfree(nl_table);
			goto panic;
		}
		hash->max_shift = order;
		hash->shift = 0;
		hash->mask = 0;
		hash->rehash_time = jiffies;
	}

	netlink_add_usersock_entry();

	sock_register(&netlink_family_ops);
	register_pernet_subsys(&netlink_net_ops);
	/* The netlink device handler may be needed early. */
	rtnetlink_init();
out:
	return err;
panic:
	panic("netlink_init: Cannot allocate nl_table\n");
}

core_initcall(netlink_proto_init);

#if defined(CONFIG_RTL_819X)
int rtk_nlrecvmsg(struct sk_buff *skb,int _len, void *_recv_data)
{
	int pid;
//	struct sk_buff *skb;
  	struct nlmsghdr *nlh;
	
	pid=0;
//  	printk("net_link: data is ready to read.\n");
  	//skb = skb_get(_skb);
	
	if (skb->len >= NLMSG_SPACE(0)) {
    		nlh = nlmsg_hdr(skb);
		memcpy(_recv_data,NLMSG_DATA(nlh),_len);
    		pid = nlh->nlmsg_pid; /*pid of sending process */
//    		printk("net_link: pid is %d\n", pid);    		
		//kfree_skb(skb);	
		return pid;
  	}
	else
	{
		//kfree_skb(skb);	
		return -1;
	}
}
EXPORT_SYMBOL(rtk_nlrecvmsg);

int rtk_nlsendmsg (int _pid,struct sock *_nl_sk,int _len,void *_send_info) 
{
        struct nlmsghdr *nlh;
        struct sk_buff *skb;
        int rc;
        int len;

	 len = NLMSG_SPACE(_len+sizeof(struct nlmsghdr)+32);
 
        skb = alloc_skb(len, GFP_ATOMIC);
        if (!skb){
                printk(KERN_ERR "net_link: allocate failed.\n");
                return -1;
        }
        nlh = nlmsg_put(skb,0,0,0,len,0);
        NETLINK_CB(skb).portid = 0; /* from kernel */
 
        memcpy(NLMSG_DATA(nlh), _send_info, _len);
//        printk("net_link: going to send.\n");
        rc = netlink_unicast(_nl_sk, skb, _pid, MSG_DONTWAIT);
        if (rc < 0) {
                printk(KERN_ERR "net_link: can not unicast skb (%d)\n", rc);
        }
//        printk("net_link: send to %d is ok.\n",_pid);
        return 0;
}
EXPORT_SYMBOL(rtk_nlsendmsg);


#if defined(CONFIG_RTK_WLAN_EVENT_INDICATE) || defined (CONFIG_AUTO_DHCP_CHECK)
static int rtk_eventd_pid=0;
static struct sock * nl_eventd_sk=NULL;
#define MAX_PAYLOAD 1024

typedef struct __rtkEventHdr 
{
	int eventID;	
	char name[16];
	unsigned char data[0];
}rtkEventHdr;

#define RTK_EVENTD_HDR_LEN sizeof(rtkEventHdr)

void rtk_eventd_netlink_receive(struct sk_buff *puskb)
{
	//int		pid;
	rtkEventHdr * pEventdHdr=NULL;
	char msgBuf[1024];
	
	rtk_eventd_pid = rtk_nlrecvmsg(puskb, sizeof(msgBuf), msgBuf);
	if(rtk_eventd_pid<1)
	{
		return;
	}
	
	pEventdHdr=(rtkEventHdr *)msgBuf;
	
	//panic_printk("%s:%d##pid=%d\n",__FUNCTION__,__LINE__,rtk_eventd_pid);
	//panic_printk("%s:%d##eventID=%d\n",__FUNCTION__,__LINE__,pEventdHdr->eventID);
	//panic_printk("%s:%d##msg=%s\n",__FUNCTION__,__LINE__,pEventdHdr->data);
	
  	return;
}
EXPORT_SYMBOL(rtk_eventd_netlink_receive);

int get_nl_eventd_pid(void)
{
	return rtk_eventd_pid;
}
EXPORT_SYMBOL(get_nl_eventd_pid);

struct sock *get_nl_eventd_sk(void)
{
	return nl_eventd_sk;
}
EXPORT_SYMBOL(get_nl_eventd_sk);



void rtk_eventd_netlink_send(int pid, struct sock *nl_sk, int eventID, char *ifname, char *data, int data_len)
{
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	int rc, len;
	
	rtkEventHdr *pEventdHdr=NULL;
	char msgBuf[128];
	memset(msgBuf, 0, sizeof(msgBuf));
	pEventdHdr=(rtkEventHdr *)msgBuf;
	pEventdHdr->eventID=eventID;
	
	if(ifname!=NULL)
	{
		strcpy(pEventdHdr->name, ifname);
	}
	
	strcpy(pEventdHdr->data, data);	
	
	//if(data_len>MAX_OPENVPN_PAYLOAD)
	//{
	//	printk("%s:%d##date len is too long!\n",__FUNCTION__,__LINE__);
	//	return;
	//}
	
	if(data_len > MAX_PAYLOAD - RTK_EVENTD_HDR_LEN)
	{
		//panic_printk("%s:%d##date len is too long!\n",__FUNCTION__,__LINE__);
		printk("%s:%d##date len is too long!\n",__FUNCTION__,__LINE__);
		return;
	}
	
	len = NLMSG_SPACE(MAX_PAYLOAD-NLMSG_HDRLEN);
	//len = NLMSG_SPACE(MAX_PAYLOAD-RTK_EVENTD_HDR_LEN);

	skb = alloc_skb(len, GFP_ATOMIC);
	if(!skb)
	{
		printk(KERN_ERR "net_link: allocate failed.\n");
		return;
	}
	
	nlh = nlmsg_put(skb,0,0,0,len,0);

	if(nlh==NULL)
	{
		printk("data_len=%d len=%d nlh is NULL!\n\n", data_len, len);
	}
	
	NETLINK_CB(skb).portid = 0; /* from kernel */

	//memcpy(NLMSG_DATA(nlh), data, data_len);
	memcpy(NLMSG_DATA(nlh), pEventdHdr, data_len+sizeof(rtkEventHdr));
	
	nlh->nlmsg_len=data_len+sizeof(rtkEventHdr)+NLMSG_HDRLEN;
	
	rc = netlink_unicast(nl_sk, skb, pid, MSG_DONTWAIT);
	
	if (rc < 0)
	{
		printk(KERN_ERR "net_link: can not unicast skb (%d)\n", rc);
	}

	return;
}
EXPORT_SYMBOL(rtk_eventd_netlink_send);

void rtk_eventd_netlink_send_multicast(int pid, struct sock *nl_sk, int eventID, char *ifname, char *data, int data_len)
{
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	int rc, len;
	#define Rtk_Event_Netlink_Group (1<<0)
	
	rtkEventHdr *pEventdHdr=NULL;
	char msgBuf[128];
	memset(msgBuf, 0, sizeof(msgBuf));
	pEventdHdr=(rtkEventHdr *)msgBuf;
	pEventdHdr->eventID=eventID;

	//#define Rtk_Event_Netlink_Group (1<<8)
	
	if(ifname!=NULL)
	{
		strcpy(pEventdHdr->name, ifname);
	}
	
	strcpy(pEventdHdr->data, data);	
	
	//if(data_len>MAX_OPENVPN_PAYLOAD)
	//{
	//	printk("%s:%d##date len is too long!\n",__FUNCTION__,__LINE__);
	//	return;
	//}
	
	if(data_len > MAX_PAYLOAD - RTK_EVENTD_HDR_LEN)
	{
		//panic_printk("%s:%d##date len is too long!\n",__FUNCTION__,__LINE__);
		printk("%s:%d##date len is too long!\n",__FUNCTION__,__LINE__);
		return;
	}
	
	len = NLMSG_SPACE(MAX_PAYLOAD-NLMSG_HDRLEN);
	//len = NLMSG_SPACE(MAX_PAYLOAD-RTK_EVENTD_HDR_LEN);

	skb = alloc_skb(len, GFP_ATOMIC);
	if(!skb)
	{
		printk(KERN_ERR "net_link: allocate failed.\n");
		return;
	}
	
	nlh = nlmsg_put(skb,0,0,0,len,0);

	if(nlh==NULL)
	{
		printk("data_len=%d len=%d nlh is NULL!\n\n", data_len, len);
	}
	
	NETLINK_CB(skb).portid = 0; /* from kernel */
       /* to mcast group 1<<0 */  
       NETLINK_CB(skb).dst_group = Rtk_Event_Netlink_Group;

	//memcpy(NLMSG_DATA(nlh), data, data_len);
	memcpy(NLMSG_DATA(nlh), pEventdHdr, data_len+sizeof(rtkEventHdr));
	
	nlh->nlmsg_len=data_len+sizeof(rtkEventHdr)+NLMSG_HDRLEN;
	
	rc = netlink_broadcast(nl_sk, skb, 0, 1, GFP_KERNEL);
	
	if (rc < 0)
	{
		printk(KERN_ERR "net_link: can not multicast skb (%d)\n", rc);
	}

	return;
}
EXPORT_SYMBOL(rtk_eventd_netlink_send_multicast);

struct sock * rtk_eventd_netlink_init(void) 
{
	struct netlink_kernel_cfg cfg={
		.input=rtk_eventd_netlink_receive,
	};

	nl_eventd_sk = netlink_kernel_create(&init_net, NETLINK_RTK_EVENTD, &cfg);
  	//nl_eventd_sk = netlink_kernel_create(&init_net, NETLINK_RTK_EVENTD, 0, rtk_eventd_netlink_receive, NULL, THIS_MODULE);

  	if (!nl_eventd_sk) 
	{
    		//panic_printk(KERN_ERR "kernel create eventd netlink socket fail!\n");
    		printk(KERN_ERR "kernel create eventd netlink socket fail!\n");
  	}
  	return nl_eventd_sk;
}
EXPORT_SYMBOL(rtk_eventd_netlink_init);
#endif
#endif


