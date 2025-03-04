/* testdeque.c generated by valac 0.15.0.90-e9553, the Vala compiler
 * generated from testdeque.vala, do not modify */

/* testdeque.vala
 *
 * Copyright (C) 2009  Didier Villevalois
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
 * 	Didier 'Ptitjes' Villevalois <ptitjes@free.fr>
 */

#include <glib.h>
#include <glib-object.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>


#define GEE_TYPE_TEST_CASE (gee_test_case_get_type ())
#define GEE_TEST_CASE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_TEST_CASE, GeeTestCase))
#define GEE_TEST_CASE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_TEST_CASE, GeeTestCaseClass))
#define GEE_IS_TEST_CASE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_TEST_CASE))
#define GEE_IS_TEST_CASE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_TEST_CASE))
#define GEE_TEST_CASE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_TEST_CASE, GeeTestCaseClass))

typedef struct _GeeTestCase GeeTestCase;
typedef struct _GeeTestCaseClass GeeTestCaseClass;
typedef struct _GeeTestCasePrivate GeeTestCasePrivate;

#define TYPE_COLLECTION_TESTS (collection_tests_get_type ())
#define COLLECTION_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_COLLECTION_TESTS, CollectionTests))
#define COLLECTION_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_COLLECTION_TESTS, CollectionTestsClass))
#define IS_COLLECTION_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_COLLECTION_TESTS))
#define IS_COLLECTION_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_COLLECTION_TESTS))
#define COLLECTION_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_COLLECTION_TESTS, CollectionTestsClass))

typedef struct _CollectionTests CollectionTests;
typedef struct _CollectionTestsClass CollectionTestsClass;
typedef struct _CollectionTestsPrivate CollectionTestsPrivate;

#define TYPE_QUEUE_TESTS (queue_tests_get_type ())
#define QUEUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_QUEUE_TESTS, QueueTests))
#define QUEUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_QUEUE_TESTS, QueueTestsClass))
#define IS_QUEUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_QUEUE_TESTS))
#define IS_QUEUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_QUEUE_TESTS))
#define QUEUE_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_QUEUE_TESTS, QueueTestsClass))

typedef struct _QueueTests QueueTests;
typedef struct _QueueTestsClass QueueTestsClass;
typedef struct _QueueTestsPrivate QueueTestsPrivate;

#define TYPE_DEQUE_TESTS (deque_tests_get_type ())
#define DEQUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DEQUE_TESTS, DequeTests))
#define DEQUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DEQUE_TESTS, DequeTestsClass))
#define IS_DEQUE_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DEQUE_TESTS))
#define IS_DEQUE_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DEQUE_TESTS))
#define DEQUE_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DEQUE_TESTS, DequeTestsClass))

typedef struct _DequeTests DequeTests;
typedef struct _DequeTestsClass DequeTestsClass;
typedef struct _DequeTestsPrivate DequeTestsPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _GeeTestCase {
	GObject parent_instance;
	GeeTestCasePrivate * priv;
};

struct _GeeTestCaseClass {
	GObjectClass parent_class;
	void (*set_up) (GeeTestCase* self);
	void (*tear_down) (GeeTestCase* self);
};

struct _CollectionTests {
	GeeTestCase parent_instance;
	CollectionTestsPrivate * priv;
	GeeCollection* test_collection;
};

struct _CollectionTestsClass {
	GeeTestCaseClass parent_class;
};

struct _QueueTests {
	CollectionTests parent_instance;
	QueueTestsPrivate * priv;
};

struct _QueueTestsClass {
	CollectionTestsClass parent_class;
};

struct _DequeTests {
	QueueTests parent_instance;
	DequeTestsPrivate * priv;
};

struct _DequeTestsClass {
	QueueTestsClass parent_class;
};

typedef void (*GeeTestCaseTestMethod) (void* user_data);

static gpointer deque_tests_parent_class = NULL;

GType gee_test_case_get_type (void) G_GNUC_CONST;
GType collection_tests_get_type (void) G_GNUC_CONST;
GType queue_tests_get_type (void) G_GNUC_CONST;
GType deque_tests_get_type (void) G_GNUC_CONST;
enum  {
	DEQUE_TESTS_DUMMY_PROPERTY
};
DequeTests* deque_tests_construct (GType object_type, const gchar* name);
QueueTests* queue_tests_construct (GType object_type, const gchar* name);
void gee_test_case_add_test (GeeTestCase* self, const gchar* name, GeeTestCaseTestMethod test, void* test_target);
void deque_tests_test_queue_use (DequeTests* self);
static void _deque_tests_test_queue_use_gee_test_case_test_method (gpointer self);
void deque_tests_test_stack_use (DequeTests* self);
static void _deque_tests_test_stack_use_gee_test_case_test_method (gpointer self);
void deque_tests_test_reversed_stack_use (DequeTests* self);
static void _deque_tests_test_reversed_stack_use_gee_test_case_test_method (gpointer self);


static void _deque_tests_test_queue_use_gee_test_case_test_method (gpointer self) {
	deque_tests_test_queue_use (self);
}


static void _deque_tests_test_stack_use_gee_test_case_test_method (gpointer self) {
	deque_tests_test_stack_use (self);
}


static void _deque_tests_test_reversed_stack_use_gee_test_case_test_method (gpointer self) {
	deque_tests_test_reversed_stack_use (self);
}


DequeTests* deque_tests_construct (GType object_type, const gchar* name) {
	DequeTests * self = NULL;
	const gchar* _tmp0_;
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = name;
	self = (DequeTests*) queue_tests_construct (object_type, _tmp0_);
	gee_test_case_add_test ((GeeTestCase*) self, "[Deque] queue use", _deque_tests_test_queue_use_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[Deque] stack use", _deque_tests_test_stack_use_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[Deque] reversed stack use", _deque_tests_test_reversed_stack_use_gee_test_case_test_method, self);
	return self;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void deque_tests_test_queue_use (DequeTests* self) {
	GeeCollection* _tmp0_;
	GeeDeque* _tmp1_;
	GeeDeque* test_deque;
	GeeArrayList* _tmp2_;
	GeeArrayList* recipient;
	gboolean _tmp3_ = FALSE;
	gint _tmp4_;
	gint _tmp5_;
	gboolean _tmp6_ = FALSE;
	gint _tmp7_;
	gint _tmp8_;
	gboolean _tmp9_ = FALSE;
	gint _tmp10_;
	gint _tmp11_;
	gboolean _tmp12_ = FALSE;
	gint _tmp13_;
	gint _tmp14_;
	gpointer _tmp15_ = NULL;
	gchar* _tmp16_;
	gpointer _tmp17_ = NULL;
	gchar* _tmp18_;
	gint _tmp19_;
	gint _tmp20_;
	gpointer _tmp21_ = NULL;
	gchar* _tmp22_;
	gpointer _tmp23_ = NULL;
	gchar* _tmp24_;
	gint _tmp25_;
	gint _tmp26_;
	gpointer _tmp27_ = NULL;
	gchar* _tmp28_;
	gpointer _tmp29_ = NULL;
	gchar* _tmp30_;
	gint _tmp31_;
	gint _tmp32_;
	gpointer _tmp33_ = NULL;
	gchar* _tmp34_;
	gpointer _tmp35_ = NULL;
	gchar* _tmp36_;
	gint _tmp37_;
	gint _tmp38_;
	gpointer _tmp39_ = NULL;
	gchar* _tmp40_;
	gpointer _tmp41_ = NULL;
	gchar* _tmp42_;
	gboolean _tmp43_ = FALSE;
	gboolean _tmp44_ = FALSE;
	gboolean _tmp45_ = FALSE;
	gboolean _tmp46_ = FALSE;
	gint _tmp47_;
	gint _tmp48_;
	gint _tmp49_ = 0;
	gint _tmp50_;
	gint _tmp51_;
	gint _tmp52_;
	gint _tmp53_;
	gpointer _tmp54_ = NULL;
	gchar* _tmp55_;
	gint _tmp56_ = 0;
	gint _tmp57_;
	gint _tmp58_;
	gint _tmp59_;
	gint _tmp60_;
	gpointer _tmp61_ = NULL;
	gchar* _tmp62_;
	gpointer _tmp63_ = NULL;
	gchar* _tmp64_;
	gpointer _tmp65_ = NULL;
	gchar* _tmp66_;
	gint _tmp67_ = 0;
	gint _tmp68_;
	gint _tmp69_;
	gint _tmp70_;
	gint _tmp71_;
	gint _tmp72_ = 0;
	gint _tmp73_;
	gint _tmp74_;
	gint _tmp75_;
	gint _tmp76_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_DEQUE (_tmp0_) ? ((GeeDeque*) _tmp0_) : NULL);
	test_deque = _tmp1_;
	_tmp2_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL);
	recipient = _tmp2_;
	g_assert (test_deque != NULL);
	_tmp3_ = gee_deque_offer_tail (test_deque, "one");
	g_assert (_tmp3_);
	_tmp4_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp5_ = _tmp4_;
	g_assert (_tmp5_ == 1);
	_tmp6_ = gee_deque_offer_tail (test_deque, "two");
	g_assert (_tmp6_);
	_tmp7_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp8_ = _tmp7_;
	g_assert (_tmp8_ == 2);
	_tmp9_ = gee_deque_offer_tail (test_deque, "three");
	g_assert (_tmp9_);
	_tmp10_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp11_ = _tmp10_;
	g_assert (_tmp11_ == 3);
	_tmp12_ = gee_deque_offer_tail (test_deque, "four");
	g_assert (_tmp12_);
	_tmp13_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp14_ = _tmp13_;
	g_assert (_tmp14_ == 4);
	_tmp15_ = gee_deque_peek_head (test_deque);
	_tmp16_ = (gchar*) _tmp15_;
	g_assert (g_strcmp0 (_tmp16_, "one") == 0);
	_g_free0 (_tmp16_);
	_tmp17_ = gee_deque_poll_head (test_deque);
	_tmp18_ = (gchar*) _tmp17_;
	g_assert (g_strcmp0 (_tmp18_, "one") == 0);
	_g_free0 (_tmp18_);
	_tmp19_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp20_ = _tmp19_;
	g_assert (_tmp20_ == 3);
	_tmp21_ = gee_deque_peek_head (test_deque);
	_tmp22_ = (gchar*) _tmp21_;
	g_assert (g_strcmp0 (_tmp22_, "two") == 0);
	_g_free0 (_tmp22_);
	_tmp23_ = gee_deque_poll_head (test_deque);
	_tmp24_ = (gchar*) _tmp23_;
	g_assert (g_strcmp0 (_tmp24_, "two") == 0);
	_g_free0 (_tmp24_);
	_tmp25_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp26_ = _tmp25_;
	g_assert (_tmp26_ == 2);
	_tmp27_ = gee_deque_peek_head (test_deque);
	_tmp28_ = (gchar*) _tmp27_;
	g_assert (g_strcmp0 (_tmp28_, "three") == 0);
	_g_free0 (_tmp28_);
	_tmp29_ = gee_deque_poll_head (test_deque);
	_tmp30_ = (gchar*) _tmp29_;
	g_assert (g_strcmp0 (_tmp30_, "three") == 0);
	_g_free0 (_tmp30_);
	_tmp31_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp32_ = _tmp31_;
	g_assert (_tmp32_ == 1);
	_tmp33_ = gee_deque_peek_head (test_deque);
	_tmp34_ = (gchar*) _tmp33_;
	g_assert (g_strcmp0 (_tmp34_, "four") == 0);
	_g_free0 (_tmp34_);
	_tmp35_ = gee_deque_poll_head (test_deque);
	_tmp36_ = (gchar*) _tmp35_;
	g_assert (g_strcmp0 (_tmp36_, "four") == 0);
	_g_free0 (_tmp36_);
	_tmp37_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp38_ = _tmp37_;
	g_assert (_tmp38_ == 0);
	_tmp39_ = gee_deque_peek_head (test_deque);
	_tmp40_ = (gchar*) _tmp39_;
	g_assert (_tmp40_ == NULL);
	_g_free0 (_tmp40_);
	_tmp41_ = gee_deque_poll_head (test_deque);
	_tmp42_ = (gchar*) _tmp41_;
	g_assert (_tmp42_ == NULL);
	_g_free0 (_tmp42_);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp43_ = gee_deque_offer_tail (test_deque, "one");
	g_assert (_tmp43_);
	_tmp44_ = gee_deque_offer_tail (test_deque, "two");
	g_assert (_tmp44_);
	_tmp45_ = gee_deque_offer_tail (test_deque, "three");
	g_assert (_tmp45_);
	_tmp46_ = gee_deque_offer_tail (test_deque, "four");
	g_assert (_tmp46_);
	_tmp47_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp48_ = _tmp47_;
	g_assert (_tmp48_ == 4);
	_tmp49_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, 1);
	g_assert (_tmp49_ == 1);
	_tmp50_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp51_ = _tmp50_;
	g_assert (_tmp51_ == 3);
	_tmp52_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp53_ = _tmp52_;
	g_assert (_tmp53_ == 1);
	_tmp54_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 0);
	_tmp55_ = (gchar*) _tmp54_;
	g_assert (g_strcmp0 (_tmp55_, "one") == 0);
	_g_free0 (_tmp55_);
	_tmp56_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, -1);
	g_assert (_tmp56_ == 3);
	_tmp57_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp58_ = _tmp57_;
	g_assert (_tmp58_ == 0);
	_tmp59_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp60_ = _tmp59_;
	g_assert (_tmp60_ == 4);
	_tmp61_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 1);
	_tmp62_ = (gchar*) _tmp61_;
	g_assert (g_strcmp0 (_tmp62_, "two") == 0);
	_g_free0 (_tmp62_);
	_tmp63_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 2);
	_tmp64_ = (gchar*) _tmp63_;
	g_assert (g_strcmp0 (_tmp64_, "three") == 0);
	_g_free0 (_tmp64_);
	_tmp65_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 3);
	_tmp66_ = (gchar*) _tmp65_;
	g_assert (g_strcmp0 (_tmp66_, "four") == 0);
	_g_free0 (_tmp66_);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp67_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, 1);
	g_assert (_tmp67_ == 0);
	_tmp68_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp69_ = _tmp68_;
	g_assert (_tmp69_ == 0);
	_tmp70_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp71_ = _tmp70_;
	g_assert (_tmp71_ == 0);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp72_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, -1);
	g_assert (_tmp72_ == 0);
	_tmp73_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp74_ = _tmp73_;
	g_assert (_tmp74_ == 0);
	_tmp75_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp76_ = _tmp75_;
	g_assert (_tmp76_ == 0);
	_g_object_unref0 (recipient);
	_g_object_unref0 (test_deque);
}


void deque_tests_test_stack_use (DequeTests* self) {
	GeeCollection* _tmp0_;
	GeeDeque* _tmp1_;
	GeeDeque* test_deque;
	GeeArrayList* _tmp2_;
	GeeArrayList* recipient;
	gboolean _tmp3_ = FALSE;
	gint _tmp4_;
	gint _tmp5_;
	gboolean _tmp6_ = FALSE;
	gint _tmp7_;
	gint _tmp8_;
	gboolean _tmp9_ = FALSE;
	gint _tmp10_;
	gint _tmp11_;
	gboolean _tmp12_ = FALSE;
	gint _tmp13_;
	gint _tmp14_;
	gpointer _tmp15_ = NULL;
	gchar* _tmp16_;
	gpointer _tmp17_ = NULL;
	gchar* _tmp18_;
	gint _tmp19_;
	gint _tmp20_;
	gpointer _tmp21_ = NULL;
	gchar* _tmp22_;
	gpointer _tmp23_ = NULL;
	gchar* _tmp24_;
	gint _tmp25_;
	gint _tmp26_;
	gpointer _tmp27_ = NULL;
	gchar* _tmp28_;
	gpointer _tmp29_ = NULL;
	gchar* _tmp30_;
	gint _tmp31_;
	gint _tmp32_;
	gpointer _tmp33_ = NULL;
	gchar* _tmp34_;
	gpointer _tmp35_ = NULL;
	gchar* _tmp36_;
	gint _tmp37_;
	gint _tmp38_;
	gpointer _tmp39_ = NULL;
	gchar* _tmp40_;
	gpointer _tmp41_ = NULL;
	gchar* _tmp42_;
	gboolean _tmp43_ = FALSE;
	gboolean _tmp44_ = FALSE;
	gboolean _tmp45_ = FALSE;
	gboolean _tmp46_ = FALSE;
	gint _tmp47_;
	gint _tmp48_;
	gint _tmp49_ = 0;
	gint _tmp50_;
	gint _tmp51_;
	gint _tmp52_;
	gint _tmp53_;
	gpointer _tmp54_ = NULL;
	gchar* _tmp55_;
	gint _tmp56_ = 0;
	gint _tmp57_;
	gint _tmp58_;
	gint _tmp59_;
	gint _tmp60_;
	gpointer _tmp61_ = NULL;
	gchar* _tmp62_;
	gpointer _tmp63_ = NULL;
	gchar* _tmp64_;
	gpointer _tmp65_ = NULL;
	gchar* _tmp66_;
	gint _tmp67_ = 0;
	gint _tmp68_;
	gint _tmp69_;
	gint _tmp70_;
	gint _tmp71_;
	gint _tmp72_ = 0;
	gint _tmp73_;
	gint _tmp74_;
	gint _tmp75_;
	gint _tmp76_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_DEQUE (_tmp0_) ? ((GeeDeque*) _tmp0_) : NULL);
	test_deque = _tmp1_;
	_tmp2_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL);
	recipient = _tmp2_;
	g_assert (test_deque != NULL);
	_tmp3_ = gee_deque_offer_head (test_deque, "one");
	g_assert (_tmp3_);
	_tmp4_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp5_ = _tmp4_;
	g_assert (_tmp5_ == 1);
	_tmp6_ = gee_deque_offer_head (test_deque, "two");
	g_assert (_tmp6_);
	_tmp7_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp8_ = _tmp7_;
	g_assert (_tmp8_ == 2);
	_tmp9_ = gee_deque_offer_head (test_deque, "three");
	g_assert (_tmp9_);
	_tmp10_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp11_ = _tmp10_;
	g_assert (_tmp11_ == 3);
	_tmp12_ = gee_deque_offer_head (test_deque, "four");
	g_assert (_tmp12_);
	_tmp13_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp14_ = _tmp13_;
	g_assert (_tmp14_ == 4);
	_tmp15_ = gee_deque_peek_head (test_deque);
	_tmp16_ = (gchar*) _tmp15_;
	g_assert (g_strcmp0 (_tmp16_, "four") == 0);
	_g_free0 (_tmp16_);
	_tmp17_ = gee_deque_poll_head (test_deque);
	_tmp18_ = (gchar*) _tmp17_;
	g_assert (g_strcmp0 (_tmp18_, "four") == 0);
	_g_free0 (_tmp18_);
	_tmp19_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp20_ = _tmp19_;
	g_assert (_tmp20_ == 3);
	_tmp21_ = gee_deque_peek_head (test_deque);
	_tmp22_ = (gchar*) _tmp21_;
	g_assert (g_strcmp0 (_tmp22_, "three") == 0);
	_g_free0 (_tmp22_);
	_tmp23_ = gee_deque_poll_head (test_deque);
	_tmp24_ = (gchar*) _tmp23_;
	g_assert (g_strcmp0 (_tmp24_, "three") == 0);
	_g_free0 (_tmp24_);
	_tmp25_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp26_ = _tmp25_;
	g_assert (_tmp26_ == 2);
	_tmp27_ = gee_deque_peek_head (test_deque);
	_tmp28_ = (gchar*) _tmp27_;
	g_assert (g_strcmp0 (_tmp28_, "two") == 0);
	_g_free0 (_tmp28_);
	_tmp29_ = gee_deque_poll_head (test_deque);
	_tmp30_ = (gchar*) _tmp29_;
	g_assert (g_strcmp0 (_tmp30_, "two") == 0);
	_g_free0 (_tmp30_);
	_tmp31_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp32_ = _tmp31_;
	g_assert (_tmp32_ == 1);
	_tmp33_ = gee_deque_peek_head (test_deque);
	_tmp34_ = (gchar*) _tmp33_;
	g_assert (g_strcmp0 (_tmp34_, "one") == 0);
	_g_free0 (_tmp34_);
	_tmp35_ = gee_deque_poll_head (test_deque);
	_tmp36_ = (gchar*) _tmp35_;
	g_assert (g_strcmp0 (_tmp36_, "one") == 0);
	_g_free0 (_tmp36_);
	_tmp37_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp38_ = _tmp37_;
	g_assert (_tmp38_ == 0);
	_tmp39_ = gee_deque_peek_head (test_deque);
	_tmp40_ = (gchar*) _tmp39_;
	g_assert (_tmp40_ == NULL);
	_g_free0 (_tmp40_);
	_tmp41_ = gee_deque_poll_head (test_deque);
	_tmp42_ = (gchar*) _tmp41_;
	g_assert (_tmp42_ == NULL);
	_g_free0 (_tmp42_);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp43_ = gee_deque_offer_head (test_deque, "one");
	g_assert (_tmp43_);
	_tmp44_ = gee_deque_offer_head (test_deque, "two");
	g_assert (_tmp44_);
	_tmp45_ = gee_deque_offer_head (test_deque, "three");
	g_assert (_tmp45_);
	_tmp46_ = gee_deque_offer_head (test_deque, "four");
	g_assert (_tmp46_);
	_tmp47_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp48_ = _tmp47_;
	g_assert (_tmp48_ == 4);
	_tmp49_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, 1);
	g_assert (_tmp49_ == 1);
	_tmp50_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp51_ = _tmp50_;
	g_assert (_tmp51_ == 3);
	_tmp52_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp53_ = _tmp52_;
	g_assert (_tmp53_ == 1);
	_tmp54_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 0);
	_tmp55_ = (gchar*) _tmp54_;
	g_assert (g_strcmp0 (_tmp55_, "four") == 0);
	_g_free0 (_tmp55_);
	_tmp56_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, -1);
	g_assert (_tmp56_ == 3);
	_tmp57_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp58_ = _tmp57_;
	g_assert (_tmp58_ == 0);
	_tmp59_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp60_ = _tmp59_;
	g_assert (_tmp60_ == 4);
	_tmp61_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 1);
	_tmp62_ = (gchar*) _tmp61_;
	g_assert (g_strcmp0 (_tmp62_, "three") == 0);
	_g_free0 (_tmp62_);
	_tmp63_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 2);
	_tmp64_ = (gchar*) _tmp63_;
	g_assert (g_strcmp0 (_tmp64_, "two") == 0);
	_g_free0 (_tmp64_);
	_tmp65_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 3);
	_tmp66_ = (gchar*) _tmp65_;
	g_assert (g_strcmp0 (_tmp66_, "one") == 0);
	_g_free0 (_tmp66_);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp67_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, 1);
	g_assert (_tmp67_ == 0);
	_tmp68_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp69_ = _tmp68_;
	g_assert (_tmp69_ == 0);
	_tmp70_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp71_ = _tmp70_;
	g_assert (_tmp71_ == 0);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp72_ = gee_deque_drain_head (test_deque, (GeeCollection*) recipient, -1);
	g_assert (_tmp72_ == 0);
	_tmp73_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp74_ = _tmp73_;
	g_assert (_tmp74_ == 0);
	_tmp75_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp76_ = _tmp75_;
	g_assert (_tmp76_ == 0);
	_g_object_unref0 (recipient);
	_g_object_unref0 (test_deque);
}


void deque_tests_test_reversed_stack_use (DequeTests* self) {
	GeeCollection* _tmp0_;
	GeeDeque* _tmp1_;
	GeeDeque* test_deque;
	GeeArrayList* _tmp2_;
	GeeArrayList* recipient;
	gboolean _tmp3_ = FALSE;
	gint _tmp4_;
	gint _tmp5_;
	gboolean _tmp6_ = FALSE;
	gint _tmp7_;
	gint _tmp8_;
	gboolean _tmp9_ = FALSE;
	gint _tmp10_;
	gint _tmp11_;
	gboolean _tmp12_ = FALSE;
	gint _tmp13_;
	gint _tmp14_;
	gpointer _tmp15_ = NULL;
	gchar* _tmp16_;
	gpointer _tmp17_ = NULL;
	gchar* _tmp18_;
	gint _tmp19_;
	gint _tmp20_;
	gpointer _tmp21_ = NULL;
	gchar* _tmp22_;
	gpointer _tmp23_ = NULL;
	gchar* _tmp24_;
	gint _tmp25_;
	gint _tmp26_;
	gpointer _tmp27_ = NULL;
	gchar* _tmp28_;
	gpointer _tmp29_ = NULL;
	gchar* _tmp30_;
	gint _tmp31_;
	gint _tmp32_;
	gpointer _tmp33_ = NULL;
	gchar* _tmp34_;
	gpointer _tmp35_ = NULL;
	gchar* _tmp36_;
	gint _tmp37_;
	gint _tmp38_;
	gpointer _tmp39_ = NULL;
	gchar* _tmp40_;
	gpointer _tmp41_ = NULL;
	gchar* _tmp42_;
	gboolean _tmp43_ = FALSE;
	gboolean _tmp44_ = FALSE;
	gboolean _tmp45_ = FALSE;
	gboolean _tmp46_ = FALSE;
	gint _tmp47_;
	gint _tmp48_;
	gint _tmp49_ = 0;
	gint _tmp50_;
	gint _tmp51_;
	gint _tmp52_;
	gint _tmp53_;
	gpointer _tmp54_ = NULL;
	gchar* _tmp55_;
	gint _tmp56_ = 0;
	gint _tmp57_;
	gint _tmp58_;
	gint _tmp59_;
	gint _tmp60_;
	gpointer _tmp61_ = NULL;
	gchar* _tmp62_;
	gpointer _tmp63_ = NULL;
	gchar* _tmp64_;
	gpointer _tmp65_ = NULL;
	gchar* _tmp66_;
	gint _tmp67_ = 0;
	gint _tmp68_;
	gint _tmp69_;
	gint _tmp70_;
	gint _tmp71_;
	gint _tmp72_ = 0;
	gint _tmp73_;
	gint _tmp74_;
	gint _tmp75_;
	gint _tmp76_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_DEQUE (_tmp0_) ? ((GeeDeque*) _tmp0_) : NULL);
	test_deque = _tmp1_;
	_tmp2_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL);
	recipient = _tmp2_;
	g_assert (test_deque != NULL);
	_tmp3_ = gee_deque_offer_tail (test_deque, "one");
	g_assert (_tmp3_);
	_tmp4_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp5_ = _tmp4_;
	g_assert (_tmp5_ == 1);
	_tmp6_ = gee_deque_offer_tail (test_deque, "two");
	g_assert (_tmp6_);
	_tmp7_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp8_ = _tmp7_;
	g_assert (_tmp8_ == 2);
	_tmp9_ = gee_deque_offer_tail (test_deque, "three");
	g_assert (_tmp9_);
	_tmp10_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp11_ = _tmp10_;
	g_assert (_tmp11_ == 3);
	_tmp12_ = gee_deque_offer_tail (test_deque, "four");
	g_assert (_tmp12_);
	_tmp13_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp14_ = _tmp13_;
	g_assert (_tmp14_ == 4);
	_tmp15_ = gee_deque_peek_tail (test_deque);
	_tmp16_ = (gchar*) _tmp15_;
	g_assert (g_strcmp0 (_tmp16_, "four") == 0);
	_g_free0 (_tmp16_);
	_tmp17_ = gee_deque_poll_tail (test_deque);
	_tmp18_ = (gchar*) _tmp17_;
	g_assert (g_strcmp0 (_tmp18_, "four") == 0);
	_g_free0 (_tmp18_);
	_tmp19_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp20_ = _tmp19_;
	g_assert (_tmp20_ == 3);
	_tmp21_ = gee_deque_peek_tail (test_deque);
	_tmp22_ = (gchar*) _tmp21_;
	g_assert (g_strcmp0 (_tmp22_, "three") == 0);
	_g_free0 (_tmp22_);
	_tmp23_ = gee_deque_poll_tail (test_deque);
	_tmp24_ = (gchar*) _tmp23_;
	g_assert (g_strcmp0 (_tmp24_, "three") == 0);
	_g_free0 (_tmp24_);
	_tmp25_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp26_ = _tmp25_;
	g_assert (_tmp26_ == 2);
	_tmp27_ = gee_deque_peek_tail (test_deque);
	_tmp28_ = (gchar*) _tmp27_;
	g_assert (g_strcmp0 (_tmp28_, "two") == 0);
	_g_free0 (_tmp28_);
	_tmp29_ = gee_deque_poll_tail (test_deque);
	_tmp30_ = (gchar*) _tmp29_;
	g_assert (g_strcmp0 (_tmp30_, "two") == 0);
	_g_free0 (_tmp30_);
	_tmp31_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp32_ = _tmp31_;
	g_assert (_tmp32_ == 1);
	_tmp33_ = gee_deque_peek_tail (test_deque);
	_tmp34_ = (gchar*) _tmp33_;
	g_assert (g_strcmp0 (_tmp34_, "one") == 0);
	_g_free0 (_tmp34_);
	_tmp35_ = gee_deque_poll_tail (test_deque);
	_tmp36_ = (gchar*) _tmp35_;
	g_assert (g_strcmp0 (_tmp36_, "one") == 0);
	_g_free0 (_tmp36_);
	_tmp37_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp38_ = _tmp37_;
	g_assert (_tmp38_ == 0);
	_tmp39_ = gee_deque_peek_tail (test_deque);
	_tmp40_ = (gchar*) _tmp39_;
	g_assert (_tmp40_ == NULL);
	_g_free0 (_tmp40_);
	_tmp41_ = gee_deque_poll_tail (test_deque);
	_tmp42_ = (gchar*) _tmp41_;
	g_assert (_tmp42_ == NULL);
	_g_free0 (_tmp42_);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp43_ = gee_deque_offer_tail (test_deque, "one");
	g_assert (_tmp43_);
	_tmp44_ = gee_deque_offer_tail (test_deque, "two");
	g_assert (_tmp44_);
	_tmp45_ = gee_deque_offer_tail (test_deque, "three");
	g_assert (_tmp45_);
	_tmp46_ = gee_deque_offer_tail (test_deque, "four");
	g_assert (_tmp46_);
	_tmp47_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp48_ = _tmp47_;
	g_assert (_tmp48_ == 4);
	_tmp49_ = gee_deque_drain_tail (test_deque, (GeeCollection*) recipient, 1);
	g_assert (_tmp49_ == 1);
	_tmp50_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp51_ = _tmp50_;
	g_assert (_tmp51_ == 3);
	_tmp52_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp53_ = _tmp52_;
	g_assert (_tmp53_ == 1);
	_tmp54_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 0);
	_tmp55_ = (gchar*) _tmp54_;
	g_assert (g_strcmp0 (_tmp55_, "four") == 0);
	_g_free0 (_tmp55_);
	_tmp56_ = gee_deque_drain_tail (test_deque, (GeeCollection*) recipient, -1);
	g_assert (_tmp56_ == 3);
	_tmp57_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp58_ = _tmp57_;
	g_assert (_tmp58_ == 0);
	_tmp59_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp60_ = _tmp59_;
	g_assert (_tmp60_ == 4);
	_tmp61_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 1);
	_tmp62_ = (gchar*) _tmp61_;
	g_assert (g_strcmp0 (_tmp62_, "three") == 0);
	_g_free0 (_tmp62_);
	_tmp63_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 2);
	_tmp64_ = (gchar*) _tmp63_;
	g_assert (g_strcmp0 (_tmp64_, "two") == 0);
	_g_free0 (_tmp64_);
	_tmp65_ = gee_abstract_list_get ((GeeAbstractList*) recipient, 3);
	_tmp66_ = (gchar*) _tmp65_;
	g_assert (g_strcmp0 (_tmp66_, "one") == 0);
	_g_free0 (_tmp66_);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp67_ = gee_deque_drain_tail (test_deque, (GeeCollection*) recipient, 1);
	g_assert (_tmp67_ == 0);
	_tmp68_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp69_ = _tmp68_;
	g_assert (_tmp69_ == 0);
	_tmp70_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp71_ = _tmp70_;
	g_assert (_tmp71_ == 0);
	gee_abstract_collection_clear ((GeeAbstractCollection*) recipient);
	_tmp72_ = gee_deque_drain_tail (test_deque, (GeeCollection*) recipient, -1);
	g_assert (_tmp72_ == 0);
	_tmp73_ = gee_collection_get_size ((GeeCollection*) test_deque);
	_tmp74_ = _tmp73_;
	g_assert (_tmp74_ == 0);
	_tmp75_ = gee_collection_get_size ((GeeCollection*) recipient);
	_tmp76_ = _tmp75_;
	g_assert (_tmp76_ == 0);
	_g_object_unref0 (recipient);
	_g_object_unref0 (test_deque);
}


static void deque_tests_class_init (DequeTestsClass * klass) {
	deque_tests_parent_class = g_type_class_peek_parent (klass);
}


static void deque_tests_instance_init (DequeTests * self) {
}


GType deque_tests_get_type (void) {
	static volatile gsize deque_tests_type_id__volatile = 0;
	if (g_once_init_enter (&deque_tests_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (DequeTestsClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) deque_tests_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DequeTests), 0, (GInstanceInitFunc) deque_tests_instance_init, NULL };
		GType deque_tests_type_id;
		deque_tests_type_id = g_type_register_static (TYPE_QUEUE_TESTS, "DequeTests", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
		g_once_init_leave (&deque_tests_type_id__volatile, deque_tests_type_id);
	}
	return deque_tests_type_id__volatile;
}



