/* abstractmultiset.c generated by valac 0.15.0.90-e9553, the Vala compiler
 * generated from abstractmultiset.vala, do not modify */

/* abstractmultiset.vala
 *
 * Copyright (C) 2009  Ali Sabil
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
 * 	Ali Sabil <ali.sabil@gmail.com>
 * 	Didier 'Ptitjes Villevalois <ptitjes@free.fr>
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

#define GEE_TYPE_ABSTRACT_COLLECTION (gee_abstract_collection_get_type ())
#define GEE_ABSTRACT_COLLECTION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_ABSTRACT_COLLECTION, GeeAbstractCollection))
#define GEE_ABSTRACT_COLLECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_ABSTRACT_COLLECTION, GeeAbstractCollectionClass))
#define GEE_IS_ABSTRACT_COLLECTION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_ABSTRACT_COLLECTION))
#define GEE_IS_ABSTRACT_COLLECTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_ABSTRACT_COLLECTION))
#define GEE_ABSTRACT_COLLECTION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_ABSTRACT_COLLECTION, GeeAbstractCollectionClass))

typedef struct _GeeAbstractCollection GeeAbstractCollection;
typedef struct _GeeAbstractCollectionClass GeeAbstractCollectionClass;
typedef struct _GeeAbstractCollectionPrivate GeeAbstractCollectionPrivate;

#define GEE_TYPE_MULTI_SET (gee_multi_set_get_type ())
#define GEE_MULTI_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_MULTI_SET, GeeMultiSet))
#define GEE_IS_MULTI_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_MULTI_SET))
#define GEE_MULTI_SET_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_MULTI_SET, GeeMultiSetIface))

typedef struct _GeeMultiSet GeeMultiSet;
typedef struct _GeeMultiSetIface GeeMultiSetIface;

#define GEE_TYPE_ABSTRACT_MULTI_SET (gee_abstract_multi_set_get_type ())
#define GEE_ABSTRACT_MULTI_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_ABSTRACT_MULTI_SET, GeeAbstractMultiSet))
#define GEE_ABSTRACT_MULTI_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_TYPE_ABSTRACT_MULTI_SET, GeeAbstractMultiSetClass))
#define GEE_IS_ABSTRACT_MULTI_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_ABSTRACT_MULTI_SET))
#define GEE_IS_ABSTRACT_MULTI_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_TYPE_ABSTRACT_MULTI_SET))
#define GEE_ABSTRACT_MULTI_SET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_TYPE_ABSTRACT_MULTI_SET, GeeAbstractMultiSetClass))

typedef struct _GeeAbstractMultiSet GeeAbstractMultiSet;
typedef struct _GeeAbstractMultiSetClass GeeAbstractMultiSetClass;
typedef struct _GeeAbstractMultiSetPrivate GeeAbstractMultiSetPrivate;

#define GEE_TYPE_MAP (gee_map_get_type ())
#define GEE_MAP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_MAP, GeeMap))
#define GEE_IS_MAP(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_MAP))
#define GEE_MAP_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_MAP, GeeMapIface))

typedef struct _GeeMap GeeMap;
typedef struct _GeeMapIface GeeMapIface;

#define GEE_TYPE_MAP_ITERATOR (gee_map_iterator_get_type ())
#define GEE_MAP_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_MAP_ITERATOR, GeeMapIterator))
#define GEE_IS_MAP_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_MAP_ITERATOR))
#define GEE_MAP_ITERATOR_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_MAP_ITERATOR, GeeMapIteratorIface))

typedef struct _GeeMapIterator GeeMapIterator;
typedef struct _GeeMapIteratorIface GeeMapIteratorIface;

#define GEE_TYPE_SET (gee_set_get_type ())
#define GEE_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_TYPE_SET, GeeSet))
#define GEE_IS_SET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_TYPE_SET))
#define GEE_SET_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GEE_TYPE_SET, GeeSetIface))

typedef struct _GeeSet GeeSet;
typedef struct _GeeSetIface GeeSetIface;

#define GEE_MAP_TYPE_ENTRY (gee_map_entry_get_type ())
#define GEE_MAP_ENTRY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_MAP_TYPE_ENTRY, GeeMapEntry))
#define GEE_MAP_ENTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_MAP_TYPE_ENTRY, GeeMapEntryClass))
#define GEE_MAP_IS_ENTRY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_MAP_TYPE_ENTRY))
#define GEE_MAP_IS_ENTRY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_MAP_TYPE_ENTRY))
#define GEE_MAP_ENTRY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_MAP_TYPE_ENTRY, GeeMapEntryClass))

typedef struct _GeeMapEntry GeeMapEntry;
typedef struct _GeeMapEntryClass GeeMapEntryClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR (gee_abstract_multi_set_iterator_get_type ())
#define GEE_ABSTRACT_MULTI_SET_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR, GeeAbstractMultiSetIterator))
#define GEE_ABSTRACT_MULTI_SET_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR, GeeAbstractMultiSetIteratorClass))
#define GEE_ABSTRACT_MULTI_SET_IS_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR))
#define GEE_ABSTRACT_MULTI_SET_IS_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR))
#define GEE_ABSTRACT_MULTI_SET_ITERATOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR, GeeAbstractMultiSetIteratorClass))

typedef struct _GeeAbstractMultiSetIterator GeeAbstractMultiSetIterator;
typedef struct _GeeAbstractMultiSetIteratorClass GeeAbstractMultiSetIteratorClass;
typedef struct _GeeAbstractMultiSetIteratorPrivate GeeAbstractMultiSetIteratorPrivate;

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

struct _GeeAbstractCollection {
	GObject parent_instance;
	GeeAbstractCollectionPrivate * priv;
};

struct _GeeAbstractCollectionClass {
	GObjectClass parent_class;
	gboolean (*contains) (GeeAbstractCollection* self, gconstpointer item);
	gboolean (*add) (GeeAbstractCollection* self, gconstpointer item);
	gboolean (*remove) (GeeAbstractCollection* self, gconstpointer item);
	void (*clear) (GeeAbstractCollection* self);
	gpointer* (*to_array) (GeeAbstractCollection* self, int* result_length1);
	gboolean (*add_all) (GeeAbstractCollection* self, GeeCollection* collection);
	gboolean (*contains_all) (GeeAbstractCollection* self, GeeCollection* collection);
	gboolean (*remove_all) (GeeAbstractCollection* self, GeeCollection* collection);
	gboolean (*retain_all) (GeeAbstractCollection* self, GeeCollection* collection);
	GeeIterator* (*iterator) (GeeAbstractCollection* self);
	gint (*get_size) (GeeAbstractCollection* self);
	gboolean (*get_is_empty) (GeeAbstractCollection* self);
	GeeCollection* (*get_read_only_view) (GeeAbstractCollection* self);
};

struct _GeeMultiSetIface {
	GTypeInterface parent_iface;
	gint (*count) (GeeMultiSet* self, gconstpointer item);
};

struct _GeeMapIteratorIface {
	GTypeInterface parent_iface;
	gboolean (*next) (GeeMapIterator* self);
	gboolean (*has_next) (GeeMapIterator* self);
	gboolean (*first) (GeeMapIterator* self);
	gpointer (*get_key) (GeeMapIterator* self);
	gpointer (*get_value) (GeeMapIterator* self);
	void (*set_value) (GeeMapIterator* self, gconstpointer value);
	void (*unset) (GeeMapIterator* self);
};

struct _GeeSetIface {
	GTypeInterface parent_iface;
	GeeSet* (*get_read_only_view) (GeeSet* self);
};

struct _GeeMapIface {
	GTypeInterface parent_iface;
	gboolean (*has_key) (GeeMap* self, gconstpointer key);
	gboolean (*contains) (GeeMap* self, gconstpointer key);
	gboolean (*has) (GeeMap* self, gconstpointer key, gconstpointer value);
	gpointer (*get) (GeeMap* self, gconstpointer key);
	void (*set) (GeeMap* self, gconstpointer key, gconstpointer value);
	gboolean (*unset) (GeeMap* self, gconstpointer key, gpointer* value);
	gboolean (*remove) (GeeMap* self, gconstpointer key, gpointer* value);
	void (*clear) (GeeMap* self);
	GeeMapIterator* (*map_iterator) (GeeMap* self);
	void (*set_all) (GeeMap* self, GeeMap* map);
	gboolean (*unset_all) (GeeMap* self, GeeMap* map);
	gboolean (*remove_all) (GeeMap* self, GeeMap* map);
	gboolean (*has_all) (GeeMap* self, GeeMap* map);
	gboolean (*contains_all) (GeeMap* self, GeeMap* map);
	gint (*get_size) (GeeMap* self);
	gboolean (*get_is_empty) (GeeMap* self);
	GeeSet* (*get_keys) (GeeMap* self);
	GeeCollection* (*get_values) (GeeMap* self);
	GeeSet* (*get_entries) (GeeMap* self);
	GeeMap* (*get_read_only_view) (GeeMap* self);
	GType (*get_key_type) (GeeMap* self);
	GType (*get_value_type) (GeeMap* self);
};

struct _GeeAbstractMultiSet {
	GeeAbstractCollection parent_instance;
	GeeAbstractMultiSetPrivate * priv;
	GeeMap* _storage_map;
};

struct _GeeAbstractMultiSetClass {
	GeeAbstractCollectionClass parent_class;
};

struct _GeeAbstractMultiSetPrivate {
	GType g_type;
	GBoxedCopyFunc g_dup_func;
	GDestroyNotify g_destroy_func;
	gint _nitems;
};

struct _GeeAbstractMultiSetIterator {
	GObject parent_instance;
	GeeAbstractMultiSetIteratorPrivate * priv;
};

struct _GeeAbstractMultiSetIteratorClass {
	GObjectClass parent_class;
};

struct _GeeAbstractMultiSetIteratorPrivate {
	GType g_type;
	GBoxedCopyFunc g_dup_func;
	GDestroyNotify g_destroy_func;
	GeeAbstractMultiSet* _set;
	GeeMapIterator* _iter;
	gint _pending;
	gboolean _removed;
};


static gpointer gee_abstract_multi_set_parent_class = NULL;
static gpointer gee_abstract_multi_set_iterator_parent_class = NULL;
static GeeIteratorIface* gee_abstract_multi_set_iterator_gee_iterator_parent_iface = NULL;
static GeeMultiSetIface* gee_abstract_multi_set_gee_multi_set_parent_iface = NULL;

GType gee_iterator_get_type (void) G_GNUC_CONST;
GType gee_iterable_get_type (void) G_GNUC_CONST;
GType gee_collection_get_type (void) G_GNUC_CONST;
GType gee_abstract_collection_get_type (void) G_GNUC_CONST;
GType gee_multi_set_get_type (void) G_GNUC_CONST;
GType gee_abstract_multi_set_get_type (void) G_GNUC_CONST;
GType gee_map_iterator_get_type (void) G_GNUC_CONST;
GType gee_set_get_type (void) G_GNUC_CONST;
GType gee_map_entry_get_type (void) G_GNUC_CONST;
GType gee_map_get_type (void) G_GNUC_CONST;
#define GEE_ABSTRACT_MULTI_SET_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEE_TYPE_ABSTRACT_MULTI_SET, GeeAbstractMultiSetPrivate))
enum  {
	GEE_ABSTRACT_MULTI_SET_DUMMY_PROPERTY,
	GEE_ABSTRACT_MULTI_SET_G_TYPE,
	GEE_ABSTRACT_MULTI_SET_G_DUP_FUNC,
	GEE_ABSTRACT_MULTI_SET_G_DESTROY_FUNC,
	GEE_ABSTRACT_MULTI_SET_SIZE
};
GeeAbstractMultiSet* gee_abstract_multi_set_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeMap* storage_map);
GeeAbstractCollection* gee_abstract_collection_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func);
static gint gee_abstract_multi_set_real_count (GeeMultiSet* base, gconstpointer item);
gboolean gee_map_has_key (GeeMap* self, gconstpointer key);
gpointer gee_map_get (GeeMap* self, gconstpointer key);
static gboolean gee_abstract_multi_set_real_contains (GeeAbstractCollection* base, gconstpointer item);
static GeeIterator* gee_abstract_multi_set_real_iterator (GeeAbstractCollection* base);
static GeeAbstractMultiSetIterator* gee_abstract_multi_set_iterator_new (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeAbstractMultiSet* set);
static GeeAbstractMultiSetIterator* gee_abstract_multi_set_iterator_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeAbstractMultiSet* set);
static GType gee_abstract_multi_set_iterator_get_type (void) G_GNUC_CONST G_GNUC_UNUSED;
static gboolean gee_abstract_multi_set_real_add (GeeAbstractCollection* base, gconstpointer item);
void gee_map_set (GeeMap* self, gconstpointer key, gconstpointer value);
static gboolean gee_abstract_multi_set_real_remove (GeeAbstractCollection* base, gconstpointer item);
gboolean gee_map_unset (GeeMap* self, gconstpointer key, gpointer* value);
static void gee_abstract_multi_set_real_clear (GeeAbstractCollection* base);
void gee_map_clear (GeeMap* self);
#define GEE_ABSTRACT_MULTI_SET_ITERATOR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR, GeeAbstractMultiSetIteratorPrivate))
enum  {
	GEE_ABSTRACT_MULTI_SET_ITERATOR_DUMMY_PROPERTY,
	GEE_ABSTRACT_MULTI_SET_ITERATOR_G_TYPE,
	GEE_ABSTRACT_MULTI_SET_ITERATOR_G_DUP_FUNC,
	GEE_ABSTRACT_MULTI_SET_ITERATOR_G_DESTROY_FUNC
};
GeeMapIterator* gee_map_map_iterator (GeeMap* self);
static gboolean gee_abstract_multi_set_iterator_real_next (GeeIterator* base);
gboolean gee_map_iterator_next (GeeMapIterator* self);
gpointer gee_map_iterator_get_value (GeeMapIterator* self);
static gboolean gee_abstract_multi_set_iterator_real_has_next (GeeIterator* base);
gboolean gee_map_iterator_has_next (GeeMapIterator* self);
static gboolean gee_abstract_multi_set_iterator_real_first (GeeIterator* base);
gboolean gee_map_iterator_first (GeeMapIterator* self);
static gpointer gee_abstract_multi_set_iterator_real_get (GeeIterator* base);
gpointer gee_map_iterator_get_key (GeeMapIterator* self);
static void gee_abstract_multi_set_iterator_real_remove (GeeIterator* base);
void gee_map_iterator_set_value (GeeMapIterator* self, gconstpointer value);
void gee_map_iterator_unset (GeeMapIterator* self);
static void gee_abstract_multi_set_iterator_finalize (GObject* obj);
static void _vala_gee_abstract_multi_set_iterator_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_gee_abstract_multi_set_iterator_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void gee_abstract_multi_set_finalize (GObject* obj);
gint gee_abstract_collection_get_size (GeeAbstractCollection* self);
static void _vala_gee_abstract_multi_set_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_gee_abstract_multi_set_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


/**
 * Constructs a new, empty abstract multi set.
 */
static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


GeeAbstractMultiSet* gee_abstract_multi_set_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeMap* storage_map) {
	GeeAbstractMultiSet * self = NULL;
	GeeMap* _tmp0_;
	GeeMap* _tmp1_;
	g_return_val_if_fail (storage_map != NULL, NULL);
	self = (GeeAbstractMultiSet*) gee_abstract_collection_construct (object_type, g_type, (GBoxedCopyFunc) g_dup_func, g_destroy_func);
	self->priv->g_type = g_type;
	self->priv->g_dup_func = g_dup_func;
	self->priv->g_destroy_func = g_destroy_func;
	_tmp0_ = storage_map;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->_storage_map);
	self->_storage_map = _tmp1_;
	return self;
}


static gint gee_abstract_multi_set_real_count (GeeMultiSet* base, gconstpointer item) {
	GeeAbstractMultiSet * self;
	gint result = 0;
	gint _result_;
	GeeMap* _tmp0_;
	gconstpointer _tmp1_;
	gboolean _tmp2_ = FALSE;
	self = (GeeAbstractMultiSet*) base;
	_result_ = 0;
	_tmp0_ = self->_storage_map;
	_tmp1_ = item;
	_tmp2_ = gee_map_has_key (_tmp0_, _tmp1_);
	if (_tmp2_) {
		GeeMap* _tmp3_;
		gconstpointer _tmp4_;
		gpointer _tmp5_ = NULL;
		_tmp3_ = self->_storage_map;
		_tmp4_ = item;
		_tmp5_ = gee_map_get (_tmp3_, _tmp4_);
		_result_ = GPOINTER_TO_INT (_tmp5_);
	}
	result = _result_;
	return result;
}


static gboolean gee_abstract_multi_set_real_contains (GeeAbstractCollection* base, gconstpointer item) {
	GeeAbstractMultiSet * self;
	gboolean result = FALSE;
	GeeMap* _tmp0_;
	gconstpointer _tmp1_;
	gboolean _tmp2_ = FALSE;
	self = (GeeAbstractMultiSet*) base;
	_tmp0_ = self->_storage_map;
	_tmp1_ = item;
	_tmp2_ = gee_map_has_key (_tmp0_, _tmp1_);
	result = _tmp2_;
	return result;
}


static GeeIterator* gee_abstract_multi_set_real_iterator (GeeAbstractCollection* base) {
	GeeAbstractMultiSet * self;
	GeeIterator* result = NULL;
	GeeAbstractMultiSetIterator* _tmp0_;
	self = (GeeAbstractMultiSet*) base;
	_tmp0_ = gee_abstract_multi_set_iterator_new (self->priv->g_type, (GBoxedCopyFunc) self->priv->g_dup_func, self->priv->g_destroy_func, self);
	result = (GeeIterator*) _tmp0_;
	return result;
}


static gboolean gee_abstract_multi_set_real_add (GeeAbstractCollection* base, gconstpointer item) {
	GeeAbstractMultiSet * self;
	gboolean result = FALSE;
	GeeMap* _tmp0_;
	gconstpointer _tmp1_;
	gboolean _tmp2_ = FALSE;
	gint _tmp11_;
	self = (GeeAbstractMultiSet*) base;
	_tmp0_ = self->_storage_map;
	_tmp1_ = item;
	_tmp2_ = gee_map_has_key (_tmp0_, _tmp1_);
	if (_tmp2_) {
		GeeMap* _tmp3_;
		gconstpointer _tmp4_;
		gpointer _tmp5_ = NULL;
		gint current_count;
		GeeMap* _tmp6_;
		gconstpointer _tmp7_;
		gint _tmp8_;
		_tmp3_ = self->_storage_map;
		_tmp4_ = item;
		_tmp5_ = gee_map_get (_tmp3_, _tmp4_);
		current_count = GPOINTER_TO_INT (_tmp5_);
		_tmp6_ = self->_storage_map;
		_tmp7_ = item;
		_tmp8_ = current_count;
		gee_map_set (_tmp6_, _tmp7_, GINT_TO_POINTER (_tmp8_ + 1));
	} else {
		GeeMap* _tmp9_;
		gconstpointer _tmp10_;
		_tmp9_ = self->_storage_map;
		_tmp10_ = item;
		gee_map_set (_tmp9_, _tmp10_, GINT_TO_POINTER (1));
	}
	_tmp11_ = self->priv->_nitems;
	self->priv->_nitems = _tmp11_ + 1;
	result = TRUE;
	return result;
}


static gboolean gee_abstract_multi_set_real_remove (GeeAbstractCollection* base, gconstpointer item) {
	GeeAbstractMultiSet * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gint _tmp1_;
	gboolean _tmp5_;
	self = (GeeAbstractMultiSet*) base;
	_tmp1_ = self->priv->_nitems;
	if (_tmp1_ > 0) {
		GeeMap* _tmp2_;
		gconstpointer _tmp3_;
		gboolean _tmp4_ = FALSE;
		_tmp2_ = self->_storage_map;
		_tmp3_ = item;
		_tmp4_ = gee_map_has_key (_tmp2_, _tmp3_);
		_tmp0_ = _tmp4_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	if (_tmp5_) {
		GeeMap* _tmp6_;
		gconstpointer _tmp7_;
		gpointer _tmp8_ = NULL;
		gint current_count;
		gint _tmp9_;
		gint _tmp15_;
		_tmp6_ = self->_storage_map;
		_tmp7_ = item;
		_tmp8_ = gee_map_get (_tmp6_, _tmp7_);
		current_count = GPOINTER_TO_INT (_tmp8_);
		_tmp9_ = current_count;
		if (_tmp9_ <= 1) {
			GeeMap* _tmp10_;
			gconstpointer _tmp11_;
			_tmp10_ = self->_storage_map;
			_tmp11_ = item;
			gee_map_unset (_tmp10_, _tmp11_, NULL);
		} else {
			GeeMap* _tmp12_;
			gconstpointer _tmp13_;
			gint _tmp14_;
			_tmp12_ = self->_storage_map;
			_tmp13_ = item;
			_tmp14_ = current_count;
			gee_map_set (_tmp12_, _tmp13_, GINT_TO_POINTER (_tmp14_ - 1));
		}
		_tmp15_ = self->priv->_nitems;
		self->priv->_nitems = _tmp15_ - 1;
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


static void gee_abstract_multi_set_real_clear (GeeAbstractCollection* base) {
	GeeAbstractMultiSet * self;
	GeeMap* _tmp0_;
	self = (GeeAbstractMultiSet*) base;
	_tmp0_ = self->_storage_map;
	gee_map_clear (_tmp0_);
	self->priv->_nitems = 0;
}


static gint gee_abstract_multi_set_real_get_size (GeeAbstractCollection* base) {
	gint result;
	GeeAbstractMultiSet* self;
	gint _tmp0_;
	self = (GeeAbstractMultiSet*) base;
	_tmp0_ = self->priv->_nitems;
	result = _tmp0_;
	return result;
}


static GeeAbstractMultiSetIterator* gee_abstract_multi_set_iterator_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeAbstractMultiSet* set) {
	GeeAbstractMultiSetIterator * self = NULL;
	GeeAbstractMultiSet* _tmp0_;
	GeeAbstractMultiSet* _tmp1_;
	GeeAbstractMultiSet* _tmp2_;
	GeeMap* _tmp3_;
	GeeMapIterator* _tmp4_ = NULL;
	g_return_val_if_fail (set != NULL, NULL);
	self = (GeeAbstractMultiSetIterator*) g_object_new (object_type, NULL);
	self->priv->g_type = g_type;
	self->priv->g_dup_func = g_dup_func;
	self->priv->g_destroy_func = g_destroy_func;
	_tmp0_ = set;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->_set);
	self->priv->_set = _tmp1_;
	_tmp2_ = self->priv->_set;
	_tmp3_ = _tmp2_->_storage_map;
	_tmp4_ = gee_map_map_iterator (_tmp3_);
	_g_object_unref0 (self->priv->_iter);
	self->priv->_iter = _tmp4_;
	return self;
}


static GeeAbstractMultiSetIterator* gee_abstract_multi_set_iterator_new (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeAbstractMultiSet* set) {
	return gee_abstract_multi_set_iterator_construct (GEE_ABSTRACT_MULTI_SET_TYPE_ITERATOR, g_type, g_dup_func, g_destroy_func, set);
}


static gboolean gee_abstract_multi_set_iterator_real_next (GeeIterator* base) {
	GeeAbstractMultiSetIterator * self;
	gboolean result = FALSE;
	gint _tmp0_;
	self = (GeeAbstractMultiSetIterator*) base;
	self->priv->_removed = FALSE;
	_tmp0_ = self->priv->_pending;
	if (_tmp0_ == 0) {
		GeeMapIterator* _tmp1_;
		gboolean _tmp2_ = FALSE;
		_tmp1_ = self->priv->_iter;
		_tmp2_ = gee_map_iterator_next (_tmp1_);
		if (_tmp2_) {
			GeeMapIterator* _tmp3_;
			gpointer _tmp4_ = NULL;
			_tmp3_ = self->priv->_iter;
			_tmp4_ = gee_map_iterator_get_value (_tmp3_);
			self->priv->_pending = GPOINTER_TO_INT (_tmp4_) - 1;
			result = TRUE;
			return result;
		}
	} else {
		gint _tmp5_;
		_tmp5_ = self->priv->_pending;
		self->priv->_pending = _tmp5_ - 1;
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


static gboolean gee_abstract_multi_set_iterator_real_has_next (GeeIterator* base) {
	GeeAbstractMultiSetIterator * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gint _tmp1_;
	gboolean _tmp4_;
	self = (GeeAbstractMultiSetIterator*) base;
	_tmp1_ = self->priv->_pending;
	if (_tmp1_ > 0) {
		_tmp0_ = TRUE;
	} else {
		GeeMapIterator* _tmp2_;
		gboolean _tmp3_ = FALSE;
		_tmp2_ = self->priv->_iter;
		_tmp3_ = gee_map_iterator_has_next (_tmp2_);
		_tmp0_ = _tmp3_;
	}
	_tmp4_ = _tmp0_;
	result = _tmp4_;
	return result;
}


static gboolean gee_abstract_multi_set_iterator_real_first (GeeIterator* base) {
	GeeAbstractMultiSetIterator * self;
	gboolean result = FALSE;
	GeeAbstractMultiSet* _tmp0_;
	gint _tmp1_;
	GeeMapIterator* _tmp2_;
	gboolean _tmp3_ = FALSE;
	self = (GeeAbstractMultiSetIterator*) base;
	_tmp0_ = self->priv->_set;
	_tmp1_ = _tmp0_->priv->_nitems;
	if (_tmp1_ == 0) {
		result = FALSE;
		return result;
	}
	self->priv->_pending = 0;
	_tmp2_ = self->priv->_iter;
	_tmp3_ = gee_map_iterator_first (_tmp2_);
	if (_tmp3_) {
		GeeMapIterator* _tmp4_;
		gpointer _tmp5_ = NULL;
		_tmp4_ = self->priv->_iter;
		_tmp5_ = gee_map_iterator_get_value (_tmp4_);
		self->priv->_pending = GPOINTER_TO_INT (_tmp5_) - 1;
	}
	result = TRUE;
	return result;
}


static gpointer gee_abstract_multi_set_iterator_real_get (GeeIterator* base) {
	GeeAbstractMultiSetIterator * self;
	gpointer result = NULL;
	gboolean _tmp0_;
	GeeMapIterator* _tmp1_;
	gpointer _tmp2_ = NULL;
	self = (GeeAbstractMultiSetIterator*) base;
	_tmp0_ = self->priv->_removed;
	g_assert (!_tmp0_);
	_tmp1_ = self->priv->_iter;
	_tmp2_ = gee_map_iterator_get_key (_tmp1_);
	result = _tmp2_;
	return result;
}


static void gee_abstract_multi_set_iterator_real_remove (GeeIterator* base) {
	GeeAbstractMultiSetIterator * self;
	gboolean _tmp0_;
	GeeMapIterator* _tmp1_;
	GeeMapIterator* _tmp2_;
	gpointer _tmp3_ = NULL;
	gint _tmp4_;
	gint _tmp5_;
	GeeAbstractMultiSet* _tmp7_;
	gint _tmp8_;
	self = (GeeAbstractMultiSetIterator*) base;
	_tmp0_ = self->priv->_removed;
	g_assert (!_tmp0_);
	_tmp1_ = self->priv->_iter;
	_tmp2_ = self->priv->_iter;
	_tmp3_ = gee_map_iterator_get_value (_tmp2_);
	self->priv->_pending = GPOINTER_TO_INT (_tmp3_) - 1;
	_tmp4_ = self->priv->_pending;
	gee_map_iterator_set_value (_tmp1_, GINT_TO_POINTER (_tmp4_));
	_tmp5_ = self->priv->_pending;
	if (_tmp5_ == 0) {
		GeeMapIterator* _tmp6_;
		_tmp6_ = self->priv->_iter;
		gee_map_iterator_unset (_tmp6_);
	}
	_tmp7_ = self->priv->_set;
	_tmp8_ = _tmp7_->priv->_nitems;
	_tmp7_->priv->_nitems = _tmp8_ - 1;
	self->priv->_removed = TRUE;
}


static void gee_abstract_multi_set_iterator_class_init (GeeAbstractMultiSetIteratorClass * klass) {
	gee_abstract_multi_set_iterator_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GeeAbstractMultiSetIteratorPrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_gee_abstract_multi_set_iterator_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_gee_abstract_multi_set_iterator_set_property;
	G_OBJECT_CLASS (klass)->finalize = gee_abstract_multi_set_iterator_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_ITERATOR_G_TYPE, g_param_spec_gtype ("g-type", "type", "type", G_TYPE_NONE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_ITERATOR_G_DUP_FUNC, g_param_spec_pointer ("g-dup-func", "dup func", "dup func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_ITERATOR_G_DESTROY_FUNC, g_param_spec_pointer ("g-destroy-func", "destroy func", "destroy func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
}


static void gee_abstract_multi_set_iterator_gee_iterator_interface_init (GeeIteratorIface * iface) {
	gee_abstract_multi_set_iterator_gee_iterator_parent_iface = g_type_interface_peek_parent (iface);
	iface->next = (gboolean (*)(GeeIterator*)) gee_abstract_multi_set_iterator_real_next;
	iface->has_next = (gboolean (*)(GeeIterator*)) gee_abstract_multi_set_iterator_real_has_next;
	iface->first = (gboolean (*)(GeeIterator*)) gee_abstract_multi_set_iterator_real_first;
	iface->get = (gpointer (*)(GeeIterator*)) gee_abstract_multi_set_iterator_real_get;
	iface->remove = (void (*)(GeeIterator*)) gee_abstract_multi_set_iterator_real_remove;
}


static void gee_abstract_multi_set_iterator_instance_init (GeeAbstractMultiSetIterator * self) {
	self->priv = GEE_ABSTRACT_MULTI_SET_ITERATOR_GET_PRIVATE (self);
	self->priv->_pending = 0;
	self->priv->_removed = FALSE;
}


static void gee_abstract_multi_set_iterator_finalize (GObject* obj) {
	GeeAbstractMultiSetIterator * self;
	self = GEE_ABSTRACT_MULTI_SET_ITERATOR (obj);
	_g_object_unref0 (self->priv->_set);
	_g_object_unref0 (self->priv->_iter);
	G_OBJECT_CLASS (gee_abstract_multi_set_iterator_parent_class)->finalize (obj);
}


static GType gee_abstract_multi_set_iterator_get_type (void) {
	static volatile gsize gee_abstract_multi_set_iterator_type_id__volatile = 0;
	if (g_once_init_enter (&gee_abstract_multi_set_iterator_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GeeAbstractMultiSetIteratorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gee_abstract_multi_set_iterator_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GeeAbstractMultiSetIterator), 0, (GInstanceInitFunc) gee_abstract_multi_set_iterator_instance_init, NULL };
		static const GInterfaceInfo gee_iterator_info = { (GInterfaceInitFunc) gee_abstract_multi_set_iterator_gee_iterator_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		GType gee_abstract_multi_set_iterator_type_id;
		gee_abstract_multi_set_iterator_type_id = g_type_register_static (G_TYPE_OBJECT, "GeeAbstractMultiSetIterator", &g_define_type_info, 0);
		g_type_add_interface_static (gee_abstract_multi_set_iterator_type_id, GEE_TYPE_ITERATOR, &gee_iterator_info);
		g_once_init_leave (&gee_abstract_multi_set_iterator_type_id__volatile, gee_abstract_multi_set_iterator_type_id);
	}
	return gee_abstract_multi_set_iterator_type_id__volatile;
}


static void _vala_gee_abstract_multi_set_iterator_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GeeAbstractMultiSetIterator * self;
	self = GEE_ABSTRACT_MULTI_SET_ITERATOR (object);
	switch (property_id) {
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_gee_abstract_multi_set_iterator_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GeeAbstractMultiSetIterator * self;
	self = GEE_ABSTRACT_MULTI_SET_ITERATOR (object);
	switch (property_id) {
		case GEE_ABSTRACT_MULTI_SET_ITERATOR_G_TYPE:
		self->priv->g_type = g_value_get_gtype (value);
		break;
		case GEE_ABSTRACT_MULTI_SET_ITERATOR_G_DUP_FUNC:
		self->priv->g_dup_func = g_value_get_pointer (value);
		break;
		case GEE_ABSTRACT_MULTI_SET_ITERATOR_G_DESTROY_FUNC:
		self->priv->g_destroy_func = g_value_get_pointer (value);
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void gee_abstract_multi_set_class_init (GeeAbstractMultiSetClass * klass) {
	gee_abstract_multi_set_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GeeAbstractMultiSetPrivate));
	GEE_ABSTRACT_COLLECTION_CLASS (klass)->contains = gee_abstract_multi_set_real_contains;
	GEE_ABSTRACT_COLLECTION_CLASS (klass)->iterator = gee_abstract_multi_set_real_iterator;
	GEE_ABSTRACT_COLLECTION_CLASS (klass)->add = gee_abstract_multi_set_real_add;
	GEE_ABSTRACT_COLLECTION_CLASS (klass)->remove = gee_abstract_multi_set_real_remove;
	GEE_ABSTRACT_COLLECTION_CLASS (klass)->clear = gee_abstract_multi_set_real_clear;
	GEE_ABSTRACT_COLLECTION_CLASS (klass)->get_size = gee_abstract_multi_set_real_get_size;
	G_OBJECT_CLASS (klass)->get_property = _vala_gee_abstract_multi_set_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_gee_abstract_multi_set_set_property;
	G_OBJECT_CLASS (klass)->finalize = gee_abstract_multi_set_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_G_TYPE, g_param_spec_gtype ("g-type", "type", "type", G_TYPE_NONE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_G_DUP_FUNC, g_param_spec_pointer ("g-dup-func", "dup func", "dup func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_G_DESTROY_FUNC, g_param_spec_pointer ("g-destroy-func", "destroy func", "destroy func", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GEE_ABSTRACT_MULTI_SET_SIZE, g_param_spec_int ("size", "size", "size", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void gee_abstract_multi_set_gee_multi_set_interface_init (GeeMultiSetIface * iface) {
	gee_abstract_multi_set_gee_multi_set_parent_iface = g_type_interface_peek_parent (iface);
	iface->count = (gint (*)(GeeMultiSet*, gconstpointer)) gee_abstract_multi_set_real_count;
}


static void gee_abstract_multi_set_instance_init (GeeAbstractMultiSet * self) {
	self->priv = GEE_ABSTRACT_MULTI_SET_GET_PRIVATE (self);
	self->priv->_nitems = 0;
}


static void gee_abstract_multi_set_finalize (GObject* obj) {
	GeeAbstractMultiSet * self;
	self = GEE_ABSTRACT_MULTI_SET (obj);
	_g_object_unref0 (self->_storage_map);
	G_OBJECT_CLASS (gee_abstract_multi_set_parent_class)->finalize (obj);
}


/**
 * Skeletal implementation of the {@link MultiSet} interface.
 *
 * @see HashMultiSet
 * @see TreeMultiSet
 */
GType gee_abstract_multi_set_get_type (void) {
	static volatile gsize gee_abstract_multi_set_type_id__volatile = 0;
	if (g_once_init_enter (&gee_abstract_multi_set_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GeeAbstractMultiSetClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gee_abstract_multi_set_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GeeAbstractMultiSet), 0, (GInstanceInitFunc) gee_abstract_multi_set_instance_init, NULL };
		static const GInterfaceInfo gee_multi_set_info = { (GInterfaceInitFunc) gee_abstract_multi_set_gee_multi_set_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		GType gee_abstract_multi_set_type_id;
		gee_abstract_multi_set_type_id = g_type_register_static (GEE_TYPE_ABSTRACT_COLLECTION, "GeeAbstractMultiSet", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
		g_type_add_interface_static (gee_abstract_multi_set_type_id, GEE_TYPE_MULTI_SET, &gee_multi_set_info);
		g_once_init_leave (&gee_abstract_multi_set_type_id__volatile, gee_abstract_multi_set_type_id);
	}
	return gee_abstract_multi_set_type_id__volatile;
}


static void _vala_gee_abstract_multi_set_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GeeAbstractMultiSet * self;
	self = GEE_ABSTRACT_MULTI_SET (object);
	switch (property_id) {
		case GEE_ABSTRACT_MULTI_SET_SIZE:
		g_value_set_int (value, gee_abstract_collection_get_size ((GeeAbstractCollection*) self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_gee_abstract_multi_set_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GeeAbstractMultiSet * self;
	self = GEE_ABSTRACT_MULTI_SET (object);
	switch (property_id) {
		case GEE_ABSTRACT_MULTI_SET_G_TYPE:
		self->priv->g_type = g_value_get_gtype (value);
		break;
		case GEE_ABSTRACT_MULTI_SET_G_DUP_FUNC:
		self->priv->g_dup_func = g_value_get_pointer (value);
		break;
		case GEE_ABSTRACT_MULTI_SET_G_DESTROY_FUNC:
		self->priv->g_destroy_func = g_value_get_pointer (value);
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



