/* set.c generated by valac 0.15.0.90-e9553, the Vala compiler
 * generated from set.vala, do not modify */

/* set.vala
 *
 * Copyright (C) 2007  Jürg Billeter
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * Author:
 * 	Jürg Billeter <j@bitron.ch>
 */

#include <glib.h>
#include <glib-object.h>


#define GEE_TYPE_ITERABLE (gee_iterable_get_type ())
#define GEE_ITERABLE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_ITERABLE, GeeIterable))
#define GEE_IS_ITERABLE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_ITERABLE))
#define GEE_ITERABLE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_ITERABLE, GeeIterableIface))

typedef struct _GeeIterable GeeIterable;
typedef struct _GeeIterableIface GeeIterableIface;

#define GEE_TYPE_ITERATOR (gee_iterator_get_type ())
#define GEE_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_ITERATOR, GeeIterator))
#define GEE_IS_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_ITERATOR))
#define GEE_ITERATOR_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_ITERATOR, GeeIteratorIface))

typedef struct _GeeIterator GeeIterator;
typedef struct _GeeIteratorIface GeeIteratorIface;

#define GEE_TYPE_COLLECTION (gee_collection_get_type ())
#define GEE_COLLECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_COLLECTION, GeeCollection))
#define GEE_IS_COLLECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_COLLECTION))
#define GEE_COLLECTION_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_COLLECTION, GeeCollectionIface))

typedef struct _GeeCollection GeeCollection;
typedef struct _GeeCollectionIface GeeCollectionIface;

#define GEE_TYPE_SET (gee_set_get_type ())
#define GEE_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_SET, GeeSet))
#define GEE_IS_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_SET))
#define GEE_SET_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_SET, GeeSetIface))

typedef struct _GeeSet GeeSet;
typedef struct _GeeSetIface GeeSetIface;

#define GEE_TYPE_ABSTRACT_COLLECTION (gee_abstract_collection_get_type ())
#define GEE_ABSTRACT_COLLECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_ABSTRACT_COLLECTION, GeeAbstractCollection))
#define GEE_ABSTRACT_COLLECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_ABSTRACT_COLLECTION, GeeAbstractCollectionClass))
#define GEE_IS_ABSTRACT_COLLECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_ABSTRACT_COLLECTION))
#define GEE_IS_ABSTRACT_COLLECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_ABSTRACT_COLLECTION))
#define GEE_ABSTRACT_COLLECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_ABSTRACT_COLLECTION, GeeAbstractCollectionClass))

typedef struct _GeeAbstractCollection GeeAbstractCollection;
typedef struct _GeeAbstractCollectionClass GeeAbstractCollectionClass;

#define GEE_TYPE_ABSTRACT_SET (gee_abstract_set_get_type ())
#define GEE_ABSTRACT_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_ABSTRACT_SET, GeeAbstractSet))
#define GEE_ABSTRACT_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_ABSTRACT_SET, GeeAbstractSetClass))
#define GEE_IS_ABSTRACT_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_ABSTRACT_SET))
#define GEE_IS_ABSTRACT_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_ABSTRACT_SET))
#define GEE_ABSTRACT_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_ABSTRACT_SET, GeeAbstractSetClass))

typedef struct _GeeAbstractSet GeeAbstractSet;
typedef struct _GeeAbstractSetClass GeeAbstractSetClass;

#define GEE_TYPE_HASH_SET (gee_hash_set_get_type ())
#define GEE_HASH_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_HASH_SET, GeeHashSet))
#define GEE_HASH_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_HASH_SET, GeeHashSetClass))
#define GEE_IS_HASH_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_HASH_SET))
#define GEE_IS_HASH_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_HASH_SET))
#define GEE_HASH_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_HASH_SET, GeeHashSetClass))

typedef struct _GeeHashSet GeeHashSet;
typedef struct _GeeHashSetClass GeeHashSetClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _GeeIteratorIface {
	GTypeInterface parent_iface;
	gboolean (*next) (GeeIterator* self);
	gboolean (*has_next) (GeeIterator* self);
	gboolean (*first) (GeeIterator* self);
	gpointer (*get) (GeeIterator* self);
	void (*remove) (GeeIterator* self);
};

struct _GeeIterableIface {
	GTypeInterface parent_iface;
	GeeIterator* (*iterator) (GeeIterable* self);
	GType (*get_element_type) (GeeIterable* self);
};

struct _GeeCollectionIface {
	GTypeInterface parent_iface;
	gboolean (*contains) (GeeCollection* self, gconstpointer item);
	gboolean (*add) (GeeCollection* self, gconstpointer item);
	gboolean (*remove) (GeeCollection* self, gconstpointer item);
	void (*clear) (GeeCollection* self);
	gboolean (*add_all) (GeeCollection* self, GeeCollection* collection);
	gboolean (*contains_all) (GeeCollection* self, GeeCollection* collection);
	gboolean (*remove_all) (GeeCollection* self, GeeCollection* collection);
	gboolean (*retain_all) (GeeCollection* self, GeeCollection* collection);
	gpointer* (*to_array) (GeeCollection* self, int* result_length1);
	gint (*get_size) (GeeCollection* self);
	gboolean (*get_is_empty) (GeeCollection* self);
	GeeCollection* (*get_read_only_view) (GeeCollection* self);
};

struct _GeeSetIface {
	GTypeInterface parent_iface;
	GeeSet* (*get_read_only_view) (GeeSet* self);
};



GType gee_iterator_get_type (void) G_GNUC_CONST;
GType gee_iterable_get_type (void) G_GNUC_CONST;
GType gee_collection_get_type (void) G_GNUC_CONST;
GType gee_set_get_type (void) G_GNUC_CONST;
GeeSet* gee_set_empty (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func);
GeeHashSet* gee_hash_set_new (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GHashFunc hash_func, GEqualFunc equal_func);
GeeHashSet* gee_hash_set_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GHashFunc hash_func, GEqualFunc equal_func);
GType gee_abstract_collection_get_type (void) G_GNUC_CONST;
GType gee_abstract_set_get_type (void) G_GNUC_CONST;
GType gee_hash_set_get_type (void) G_GNUC_CONST;
GeeSet* gee_abstract_set_get_read_only_view (GeeAbstractSet* self);
GeeSet* gee_set_get_read_only_view (GeeSet* self);


/**
 * Returns an immutable empty set.
 *
 * @return an immutable empty set
 */
GeeSet* gee_set_empty (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func) {
	GeeSet* result = NULL;
	GeeHashSet* _tmp0_;
	GeeHashSet* _tmp1_;
	GeeSet* _tmp2_;
	GeeSet* _tmp3_;
	GeeSet* _tmp4_;
	_tmp0_ = gee_hash_set_new (g_type, (GBoxedCopyFunc) g_dup_func, g_destroy_func, NULL, NULL);
	_tmp1_ = _tmp0_;
	_tmp2_ = gee_abstract_set_get_read_only_view ((GeeAbstractSet*) _tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = _tmp3_;
	_g_object_unref0 (_tmp1_);
	result = _tmp4_;
	return result;
}


GeeSet* gee_set_get_read_only_view (GeeSet* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return GEE_SET_GET_INTERFACE (self)->get_read_only_view (self);
}


static void gee_set_base_init (GeeSetIface * iface) {
	static gboolean initialized = FALSE;
	if (!initialized) {
		initialized = TRUE;
		/**
		 * The read-only view of this set.
		 */
		g_object_interface_install_property (iface, g_param_spec_object ("read-only-view", "read-only-view", "read-only-view", GEE_TYPE_SET, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	}
}


/**
 * A collection without duplicate elements.
 */
GType gee_set_get_type (void) {
	static volatile gsize gee_set_type_id__volatile = 0;
	if (g_once_init_enter (&gee_set_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GeeSetIface), (GBaseInitFunc) gee_set_base_init, (GBaseFinalizeFunc) NULL, (GClassInitFunc) NULL, (GClassFinalizeFunc) NULL, NULL, 0, 0, (GInstanceInitFunc) NULL, NULL };
		GType gee_set_type_id;
		gee_set_type_id = g_type_register_static (G_TYPE_INTERFACE, "GeeSet", &g_define_type_info, 0);
		g_type_interface_add_prerequisite (gee_set_type_id, GEE_TYPE_COLLECTION);
		g_once_init_leave (&gee_set_type_id__volatile, gee_set_type_id);
	}
	return gee_set_type_id__volatile;
}



