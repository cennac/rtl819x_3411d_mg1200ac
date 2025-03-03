/* testtreeset.c generated by valac 0.15.0.90-e9553, the Vala compiler
 * generated from testtreeset.vala, do not modify */

/* testtreeset.vala
 *
 * Copyright (C) 2009  Didier Villevalois, Julien Peeters
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
 * 	Julien Peeters <contact@julienpeeters.fr>
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

#define TYPE_SET_TESTS (set_tests_get_type ())
#define SET_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SET_TESTS, SetTests))
#define SET_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SET_TESTS, SetTestsClass))
#define IS_SET_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SET_TESTS))
#define IS_SET_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SET_TESTS))
#define SET_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SET_TESTS, SetTestsClass))

typedef struct _SetTests SetTests;
typedef struct _SetTestsClass SetTestsClass;
typedef struct _SetTestsPrivate SetTestsPrivate;

#define TYPE_SORTED_SET_TESTS (sorted_set_tests_get_type ())
#define SORTED_SET_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SORTED_SET_TESTS, SortedSetTests))
#define SORTED_SET_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SORTED_SET_TESTS, SortedSetTestsClass))
#define IS_SORTED_SET_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SORTED_SET_TESTS))
#define IS_SORTED_SET_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SORTED_SET_TESTS))
#define SORTED_SET_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SORTED_SET_TESTS, SortedSetTestsClass))

typedef struct _SortedSetTests SortedSetTests;
typedef struct _SortedSetTestsClass SortedSetTestsClass;
typedef struct _SortedSetTestsPrivate SortedSetTestsPrivate;

#define TYPE_TREE_SET_TESTS (tree_set_tests_get_type ())
#define TREE_SET_TESTS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TREE_SET_TESTS, TreeSetTests))
#define TREE_SET_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TREE_SET_TESTS, TreeSetTestsClass))
#define IS_TREE_SET_TESTS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TREE_SET_TESTS))
#define IS_TREE_SET_TESTS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TREE_SET_TESTS))
#define TREE_SET_TESTS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TREE_SET_TESTS, TreeSetTestsClass))

typedef struct _TreeSetTests TreeSetTests;
typedef struct _TreeSetTestsClass TreeSetTestsClass;
typedef struct _TreeSetTestsPrivate TreeSetTestsPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

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

struct _SetTests {
	CollectionTests parent_instance;
	SetTestsPrivate * priv;
};

struct _SetTestsClass {
	CollectionTestsClass parent_class;
	void (*test_duplicates_are_ignored) (SetTests* self);
};

struct _SortedSetTests {
	SetTests parent_instance;
	SortedSetTestsPrivate * priv;
};

struct _SortedSetTestsClass {
	SetTestsClass parent_class;
};

struct _TreeSetTests {
	SortedSetTests parent_instance;
	TreeSetTestsPrivate * priv;
};

struct _TreeSetTestsClass {
	SortedSetTestsClass parent_class;
};

typedef void (*GeeTestCaseTestMethod) (void* user_data);

static gpointer tree_set_tests_parent_class = NULL;

GType gee_test_case_get_type (void) G_GNUC_CONST;
GType collection_tests_get_type (void) G_GNUC_CONST;
GType set_tests_get_type (void) G_GNUC_CONST;
GType sorted_set_tests_get_type (void) G_GNUC_CONST;
GType tree_set_tests_get_type (void) G_GNUC_CONST;
enum  {
	TREE_SET_TESTS_DUMMY_PROPERTY
};
TreeSetTests* tree_set_tests_new (void);
TreeSetTests* tree_set_tests_construct (GType object_type);
SortedSetTests* sorted_set_tests_construct (GType object_type, const gchar* name);
void gee_test_case_add_test (GeeTestCase* self, const gchar* name, GeeTestCaseTestMethod test, void* test_target);
void tree_set_tests_test_selected_functions (TreeSetTests* self);
static void _tree_set_tests_test_selected_functions_gee_test_case_test_method (gpointer self);
void tree_set_tests_test_gobject_properties (TreeSetTests* self);
static void _tree_set_tests_test_gobject_properties_gee_test_case_test_method (gpointer self);
void tree_set_tests_test_add_remove (TreeSetTests* self);
static void _tree_set_tests_test_add_remove_gee_test_case_test_method (gpointer self);
static void tree_set_tests_real_set_up (GeeTestCase* base);
static void tree_set_tests_real_tear_down (GeeTestCase* base);
void collection_tests_test_remove_all (CollectionTests* self);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);


static void _tree_set_tests_test_selected_functions_gee_test_case_test_method (gpointer self) {
	tree_set_tests_test_selected_functions (self);
}


static void _tree_set_tests_test_gobject_properties_gee_test_case_test_method (gpointer self) {
	tree_set_tests_test_gobject_properties (self);
}


static void _tree_set_tests_test_add_remove_gee_test_case_test_method (gpointer self) {
	tree_set_tests_test_add_remove (self);
}


TreeSetTests* tree_set_tests_construct (GType object_type) {
	TreeSetTests * self = NULL;
	self = (TreeSetTests*) sorted_set_tests_construct (object_type, "TreeSet");
	gee_test_case_add_test ((GeeTestCase*) self, "[TreeSet] selected functions", _tree_set_tests_test_selected_functions_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[TreeSet] GObject properties", _tree_set_tests_test_gobject_properties_gee_test_case_test_method, self);
	gee_test_case_add_test ((GeeTestCase*) self, "[TreeSet] add and remove", _tree_set_tests_test_add_remove_gee_test_case_test_method, self);
	return self;
}


TreeSetTests* tree_set_tests_new (void) {
	return tree_set_tests_construct (TYPE_TREE_SET_TESTS);
}


static void tree_set_tests_real_set_up (GeeTestCase* base) {
	TreeSetTests * self;
	GeeTreeSet* _tmp0_;
	self = (TreeSetTests*) base;
	_tmp0_ = gee_tree_set_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL);
	_g_object_unref0 (((CollectionTests*) self)->test_collection);
	((CollectionTests*) self)->test_collection = (GeeCollection*) _tmp0_;
}


static void tree_set_tests_real_tear_down (GeeTestCase* base) {
	TreeSetTests * self;
	self = (TreeSetTests*) base;
	_g_object_unref0 (((CollectionTests*) self)->test_collection);
	((CollectionTests*) self)->test_collection = NULL;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void tree_set_tests_test_selected_functions (TreeSetTests* self) {
	GeeCollection* _tmp0_;
	GeeTreeSet* _tmp1_;
	GeeTreeSet* test_set;
	GCompareFunc _tmp2_;
	GCompareFunc _tmp3_;
	GCompareFunc _tmp4_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_TREE_SET (_tmp0_) ? ((GeeTreeSet*) _tmp0_) : NULL);
	test_set = _tmp1_;
	g_assert (test_set != NULL);
	_tmp2_ = gee_tree_set_get_compare_func (test_set);
	_tmp3_ = _tmp2_;
	_tmp4_ = g_strcmp0;
	g_assert (_tmp3_ == ((GCompareFunc) _tmp4_));
	_g_object_unref0 (test_set);
}


void tree_set_tests_test_gobject_properties (TreeSetTests* self) {
	GeeCollection* _tmp0_;
	GeeTreeSet* _tmp1_;
	GeeTreeSet* test_set;
	GValue value = {0};
	GValue _tmp2_ = {0};
	void* _tmp3_ = NULL;
	GCompareFunc _tmp4_;
	GCompareFunc _tmp5_;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_TREE_SET (_tmp0_) ? ((GeeTreeSet*) _tmp0_) : NULL);
	test_set = _tmp1_;
	g_assert (test_set != NULL);
	g_value_init (&_tmp2_, G_TYPE_POINTER);
	G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
	value = _tmp2_;
	g_object_get_property ((GObject*) test_set, "compare-func", &value);
	_tmp3_ = g_value_get_pointer (&value);
	_tmp4_ = gee_tree_set_get_compare_func (test_set);
	_tmp5_ = _tmp4_;
	g_assert (_tmp3_ == ((void*) _tmp5_));
	g_value_unset (&value);
	G_IS_VALUE (&value) ? (g_value_unset (&value), NULL) : NULL;
	_g_object_unref0 (test_set);
}


void tree_set_tests_test_add_remove (TreeSetTests* self) {
	GeeCollection* _tmp0_;
	GeeTreeSet* _tmp1_;
	GeeTreeSet* test_set;
	GeeTreeSet* _tmp2_;
	gchar* _tmp3_;
	gchar* _tmp4_;
	gchar* _tmp5_;
	gchar* _tmp6_;
	gchar* _tmp7_;
	gchar* _tmp8_;
	gchar* _tmp9_;
	gchar* _tmp10_;
	gchar* _tmp11_;
	gchar* _tmp12_;
	gchar* _tmp13_;
	gchar* _tmp14_;
	gchar* _tmp15_;
	gchar* _tmp16_;
	gchar* _tmp17_;
	gchar* _tmp18_;
	gchar** _tmp19_ = NULL;
	gchar** to_add;
	gint to_add_length1;
	gint _to_add_size_;
	gchar* _tmp20_;
	gchar* _tmp21_;
	gchar* _tmp22_;
	gchar* _tmp23_;
	gchar* _tmp24_;
	gchar* _tmp25_;
	gchar* _tmp26_;
	gchar* _tmp27_;
	gchar* _tmp28_;
	gchar* _tmp29_;
	gchar* _tmp30_;
	gchar* _tmp31_;
	gchar* _tmp32_;
	gchar* _tmp33_;
	gchar* _tmp34_;
	gchar* _tmp35_;
	gchar** _tmp36_ = NULL;
	gchar** to_remove;
	gint to_remove_length1;
	gint _to_remove_size_;
	gchar** _tmp37_;
	gint _tmp37__length1;
	gchar** _tmp48_;
	gint _tmp48__length1;
	gchar* _tmp59_;
	gchar* _tmp60_;
	gchar* _tmp61_;
	gchar* _tmp62_;
	gchar* _tmp63_;
	gchar* _tmp64_;
	gchar* _tmp65_;
	gchar* _tmp66_;
	gchar* _tmp67_;
	gchar* _tmp68_;
	gchar* _tmp69_;
	gchar* _tmp70_;
	gchar* _tmp71_;
	gchar* _tmp72_;
	gchar* _tmp73_;
	gchar* _tmp74_;
	gchar** _tmp75_ = NULL;
	gchar* _tmp76_;
	gchar* _tmp77_;
	gchar* _tmp78_;
	gchar* _tmp79_;
	gchar* _tmp80_;
	gchar* _tmp81_;
	gchar* _tmp82_;
	gchar* _tmp83_;
	gchar* _tmp84_;
	gchar* _tmp85_;
	gchar* _tmp86_;
	gchar* _tmp87_;
	gchar* _tmp88_;
	gchar* _tmp89_;
	gchar* _tmp90_;
	gchar* _tmp91_;
	gchar** _tmp92_ = NULL;
	gchar** _tmp93_;
	gint _tmp93__length1;
	gchar** _tmp104_;
	gint _tmp104__length1;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((CollectionTests*) self)->test_collection;
	_tmp1_ = _g_object_ref0 (GEE_IS_TREE_SET (_tmp0_) ? ((GeeTreeSet*) _tmp0_) : NULL);
	test_set = _tmp1_;
	_tmp2_ = test_set;
	g_assert (_tmp2_ != NULL);
	collection_tests_test_remove_all ((CollectionTests*) SORTED_SET_TESTS (self));
	_tmp3_ = g_strdup ("3");
	_tmp4_ = g_strdup ("10");
	_tmp5_ = g_strdup ("5");
	_tmp6_ = g_strdup ("6");
	_tmp7_ = g_strdup ("13");
	_tmp8_ = g_strdup ("8");
	_tmp9_ = g_strdup ("12");
	_tmp10_ = g_strdup ("11");
	_tmp11_ = g_strdup ("1");
	_tmp12_ = g_strdup ("0");
	_tmp13_ = g_strdup ("9");
	_tmp14_ = g_strdup ("2");
	_tmp15_ = g_strdup ("14");
	_tmp16_ = g_strdup ("7");
	_tmp17_ = g_strdup ("15");
	_tmp18_ = g_strdup ("4");
	_tmp19_ = g_new0 (gchar*, 16 + 1);
	_tmp19_[0] = _tmp3_;
	_tmp19_[1] = _tmp4_;
	_tmp19_[2] = _tmp5_;
	_tmp19_[3] = _tmp6_;
	_tmp19_[4] = _tmp7_;
	_tmp19_[5] = _tmp8_;
	_tmp19_[6] = _tmp9_;
	_tmp19_[7] = _tmp10_;
	_tmp19_[8] = _tmp11_;
	_tmp19_[9] = _tmp12_;
	_tmp19_[10] = _tmp13_;
	_tmp19_[11] = _tmp14_;
	_tmp19_[12] = _tmp15_;
	_tmp19_[13] = _tmp16_;
	_tmp19_[14] = _tmp17_;
	_tmp19_[15] = _tmp18_;
	to_add = _tmp19_;
	to_add_length1 = 16;
	_to_add_size_ = to_add_length1;
	_tmp20_ = g_strdup ("11");
	_tmp21_ = g_strdup ("13");
	_tmp22_ = g_strdup ("1");
	_tmp23_ = g_strdup ("12");
	_tmp24_ = g_strdup ("4");
	_tmp25_ = g_strdup ("0");
	_tmp26_ = g_strdup ("2");
	_tmp27_ = g_strdup ("5");
	_tmp28_ = g_strdup ("6");
	_tmp29_ = g_strdup ("3");
	_tmp30_ = g_strdup ("14");
	_tmp31_ = g_strdup ("10");
	_tmp32_ = g_strdup ("7");
	_tmp33_ = g_strdup ("15");
	_tmp34_ = g_strdup ("8");
	_tmp35_ = g_strdup ("9");
	_tmp36_ = g_new0 (gchar*, 16 + 1);
	_tmp36_[0] = _tmp20_;
	_tmp36_[1] = _tmp21_;
	_tmp36_[2] = _tmp22_;
	_tmp36_[3] = _tmp23_;
	_tmp36_[4] = _tmp24_;
	_tmp36_[5] = _tmp25_;
	_tmp36_[6] = _tmp26_;
	_tmp36_[7] = _tmp27_;
	_tmp36_[8] = _tmp28_;
	_tmp36_[9] = _tmp29_;
	_tmp36_[10] = _tmp30_;
	_tmp36_[11] = _tmp31_;
	_tmp36_[12] = _tmp32_;
	_tmp36_[13] = _tmp33_;
	_tmp36_[14] = _tmp34_;
	_tmp36_[15] = _tmp35_;
	to_remove = _tmp36_;
	to_remove_length1 = 16;
	_to_remove_size_ = to_remove_length1;
	_tmp37_ = to_add;
	_tmp37__length1 = to_add_length1;
	{
		gchar** s_collection = NULL;
		gint s_collection_length1 = 0;
		gint _s_collection_size_ = 0;
		gint s_it = 0;
		s_collection = _tmp37_;
		s_collection_length1 = _tmp37__length1;
		for (s_it = 0; s_it < _tmp37__length1; s_it = s_it + 1) {
			gchar* _tmp38_;
			gchar* s = NULL;
			_tmp38_ = g_strdup (s_collection[s_it]);
			s = _tmp38_;
			{
				GeeTreeSet* _tmp39_;
				const gchar* _tmp40_;
				gboolean _tmp41_ = FALSE;
				GeeTreeSet* _tmp42_;
				const gchar* _tmp43_;
				gboolean _tmp44_ = FALSE;
				GeeTreeSet* _tmp45_;
				const gchar* _tmp46_;
				gboolean _tmp47_ = FALSE;
				_tmp39_ = test_set;
				_tmp40_ = s;
				_tmp41_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp39_, _tmp40_);
				g_assert (!_tmp41_);
				_tmp42_ = test_set;
				_tmp43_ = s;
				_tmp44_ = gee_abstract_collection_add ((GeeAbstractCollection*) _tmp42_, _tmp43_);
				g_assert (_tmp44_);
				_tmp45_ = test_set;
				_tmp46_ = s;
				_tmp47_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp45_, _tmp46_);
				g_assert (_tmp47_);
				_g_free0 (s);
			}
		}
	}
	_tmp48_ = to_remove;
	_tmp48__length1 = to_remove_length1;
	{
		gchar** s_collection = NULL;
		gint s_collection_length1 = 0;
		gint _s_collection_size_ = 0;
		gint s_it = 0;
		s_collection = _tmp48_;
		s_collection_length1 = _tmp48__length1;
		for (s_it = 0; s_it < _tmp48__length1; s_it = s_it + 1) {
			gchar* _tmp49_;
			gchar* s = NULL;
			_tmp49_ = g_strdup (s_collection[s_it]);
			s = _tmp49_;
			{
				GeeTreeSet* _tmp50_;
				const gchar* _tmp51_;
				gboolean _tmp52_ = FALSE;
				GeeTreeSet* _tmp53_;
				const gchar* _tmp54_;
				gboolean _tmp55_ = FALSE;
				GeeTreeSet* _tmp56_;
				const gchar* _tmp57_;
				gboolean _tmp58_ = FALSE;
				_tmp50_ = test_set;
				_tmp51_ = s;
				_tmp52_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp50_, _tmp51_);
				g_assert (_tmp52_);
				_tmp53_ = test_set;
				_tmp54_ = s;
				_tmp55_ = gee_abstract_collection_remove ((GeeAbstractCollection*) _tmp53_, _tmp54_);
				g_assert (_tmp55_);
				_tmp56_ = test_set;
				_tmp57_ = s;
				_tmp58_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp56_, _tmp57_);
				g_assert (!_tmp58_);
				_g_free0 (s);
			}
		}
	}
	_tmp59_ = g_strdup ("2");
	_tmp60_ = g_strdup ("9");
	_tmp61_ = g_strdup ("13");
	_tmp62_ = g_strdup ("7");
	_tmp63_ = g_strdup ("12");
	_tmp64_ = g_strdup ("14");
	_tmp65_ = g_strdup ("8");
	_tmp66_ = g_strdup ("1");
	_tmp67_ = g_strdup ("5");
	_tmp68_ = g_strdup ("6");
	_tmp69_ = g_strdup ("11");
	_tmp70_ = g_strdup ("15");
	_tmp71_ = g_strdup ("3");
	_tmp72_ = g_strdup ("10");
	_tmp73_ = g_strdup ("0");
	_tmp74_ = g_strdup ("4");
	_tmp75_ = g_new0 (gchar*, 16 + 1);
	_tmp75_[0] = _tmp59_;
	_tmp75_[1] = _tmp60_;
	_tmp75_[2] = _tmp61_;
	_tmp75_[3] = _tmp62_;
	_tmp75_[4] = _tmp63_;
	_tmp75_[5] = _tmp64_;
	_tmp75_[6] = _tmp65_;
	_tmp75_[7] = _tmp66_;
	_tmp75_[8] = _tmp67_;
	_tmp75_[9] = _tmp68_;
	_tmp75_[10] = _tmp69_;
	_tmp75_[11] = _tmp70_;
	_tmp75_[12] = _tmp71_;
	_tmp75_[13] = _tmp72_;
	_tmp75_[14] = _tmp73_;
	_tmp75_[15] = _tmp74_;
	to_add = (_vala_array_free (to_add, to_add_length1, (GDestroyNotify) g_free), NULL);
	to_add = _tmp75_;
	to_add_length1 = 16;
	_to_add_size_ = to_add_length1;
	_tmp76_ = g_strdup ("11");
	_tmp77_ = g_strdup ("10");
	_tmp78_ = g_strdup ("14");
	_tmp79_ = g_strdup ("6");
	_tmp80_ = g_strdup ("13");
	_tmp81_ = g_strdup ("4");
	_tmp82_ = g_strdup ("3");
	_tmp83_ = g_strdup ("15");
	_tmp84_ = g_strdup ("8");
	_tmp85_ = g_strdup ("5");
	_tmp86_ = g_strdup ("7");
	_tmp87_ = g_strdup ("0");
	_tmp88_ = g_strdup ("12");
	_tmp89_ = g_strdup ("2");
	_tmp90_ = g_strdup ("9");
	_tmp91_ = g_strdup ("1");
	_tmp92_ = g_new0 (gchar*, 16 + 1);
	_tmp92_[0] = _tmp76_;
	_tmp92_[1] = _tmp77_;
	_tmp92_[2] = _tmp78_;
	_tmp92_[3] = _tmp79_;
	_tmp92_[4] = _tmp80_;
	_tmp92_[5] = _tmp81_;
	_tmp92_[6] = _tmp82_;
	_tmp92_[7] = _tmp83_;
	_tmp92_[8] = _tmp84_;
	_tmp92_[9] = _tmp85_;
	_tmp92_[10] = _tmp86_;
	_tmp92_[11] = _tmp87_;
	_tmp92_[12] = _tmp88_;
	_tmp92_[13] = _tmp89_;
	_tmp92_[14] = _tmp90_;
	_tmp92_[15] = _tmp91_;
	to_remove = (_vala_array_free (to_remove, to_remove_length1, (GDestroyNotify) g_free), NULL);
	to_remove = _tmp92_;
	to_remove_length1 = 16;
	_to_remove_size_ = to_remove_length1;
	_tmp93_ = to_add;
	_tmp93__length1 = to_add_length1;
	{
		gchar** s_collection = NULL;
		gint s_collection_length1 = 0;
		gint _s_collection_size_ = 0;
		gint s_it = 0;
		s_collection = _tmp93_;
		s_collection_length1 = _tmp93__length1;
		for (s_it = 0; s_it < _tmp93__length1; s_it = s_it + 1) {
			gchar* _tmp94_;
			gchar* s = NULL;
			_tmp94_ = g_strdup (s_collection[s_it]);
			s = _tmp94_;
			{
				GeeTreeSet* _tmp95_;
				const gchar* _tmp96_;
				gboolean _tmp97_ = FALSE;
				GeeTreeSet* _tmp98_;
				const gchar* _tmp99_;
				gboolean _tmp100_ = FALSE;
				GeeTreeSet* _tmp101_;
				const gchar* _tmp102_;
				gboolean _tmp103_ = FALSE;
				_tmp95_ = test_set;
				_tmp96_ = s;
				_tmp97_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp95_, _tmp96_);
				g_assert (!_tmp97_);
				_tmp98_ = test_set;
				_tmp99_ = s;
				_tmp100_ = gee_abstract_collection_add ((GeeAbstractCollection*) _tmp98_, _tmp99_);
				g_assert (_tmp100_);
				_tmp101_ = test_set;
				_tmp102_ = s;
				_tmp103_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp101_, _tmp102_);
				g_assert (_tmp103_);
				_g_free0 (s);
			}
		}
	}
	_tmp104_ = to_remove;
	_tmp104__length1 = to_remove_length1;
	{
		gchar** s_collection = NULL;
		gint s_collection_length1 = 0;
		gint _s_collection_size_ = 0;
		gint s_it = 0;
		s_collection = _tmp104_;
		s_collection_length1 = _tmp104__length1;
		for (s_it = 0; s_it < _tmp104__length1; s_it = s_it + 1) {
			gchar* _tmp105_;
			gchar* s = NULL;
			_tmp105_ = g_strdup (s_collection[s_it]);
			s = _tmp105_;
			{
				GeeTreeSet* _tmp106_;
				const gchar* _tmp107_;
				gboolean _tmp108_ = FALSE;
				GeeTreeSet* _tmp109_;
				const gchar* _tmp110_;
				gboolean _tmp111_ = FALSE;
				GeeTreeSet* _tmp112_;
				const gchar* _tmp113_;
				gboolean _tmp114_ = FALSE;
				_tmp106_ = test_set;
				_tmp107_ = s;
				_tmp108_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp106_, _tmp107_);
				g_assert (_tmp108_);
				_tmp109_ = test_set;
				_tmp110_ = s;
				_tmp111_ = gee_abstract_collection_remove ((GeeAbstractCollection*) _tmp109_, _tmp110_);
				g_assert (_tmp111_);
				_tmp112_ = test_set;
				_tmp113_ = s;
				_tmp114_ = gee_abstract_collection_contains ((GeeAbstractCollection*) _tmp112_, _tmp113_);
				g_assert (!_tmp114_);
				_g_free0 (s);
			}
		}
	}
	to_remove = (_vala_array_free (to_remove, to_remove_length1, (GDestroyNotify) g_free), NULL);
	to_add = (_vala_array_free (to_add, to_add_length1, (GDestroyNotify) g_free), NULL);
	_g_object_unref0 (test_set);
}


static void tree_set_tests_class_init (TreeSetTestsClass * klass) {
	tree_set_tests_parent_class = g_type_class_peek_parent (klass);
	GEE_TEST_CASE_CLASS (klass)->set_up = tree_set_tests_real_set_up;
	GEE_TEST_CASE_CLASS (klass)->tear_down = tree_set_tests_real_tear_down;
}


static void tree_set_tests_instance_init (TreeSetTests * self) {
}


GType tree_set_tests_get_type (void) {
	static volatile gsize tree_set_tests_type_id__volatile = 0;
	if (g_once_init_enter (&tree_set_tests_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (TreeSetTestsClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) tree_set_tests_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TreeSetTests), 0, (GInstanceInitFunc) tree_set_tests_instance_init, NULL };
		GType tree_set_tests_type_id;
		tree_set_tests_type_id = g_type_register_static (TYPE_SORTED_SET_TESTS, "TreeSetTests", &g_define_type_info, 0);
		g_once_init_leave (&tree_set_tests_type_id__volatile, tree_set_tests_type_id);
	}
	return tree_set_tests_type_id__volatile;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}



