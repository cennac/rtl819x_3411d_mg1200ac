/* rygel-media-export-query-container-factory.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-media-export-query-container-factory.vala, do not modify */

/*
 * Copyright (C) 2011 Jens Georg <mail@jensge.org>.
 *
 * This file is part of Rygel.
 *
 * Rygel is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Rygel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <glib.h>
#include <glib-object.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>
#include <rygel-server.h>
#include <libgupnp-av/gupnp-av.h>


#define RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY (rygel_media_export_query_container_factory_get_type ())
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY, RygelMediaExportQueryContainerFactory))
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY, RygelMediaExportQueryContainerFactoryClass))
#define RYGEL_MEDIA_EXPORT_IS_QUERY_CONTAINER_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY))
#define RYGEL_MEDIA_EXPORT_IS_QUERY_CONTAINER_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY))
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY, RygelMediaExportQueryContainerFactoryClass))

typedef struct _RygelMediaExportQueryContainerFactory RygelMediaExportQueryContainerFactory;
typedef struct _RygelMediaExportQueryContainerFactoryClass RygelMediaExportQueryContainerFactoryClass;
typedef struct _RygelMediaExportQueryContainerFactoryPrivate RygelMediaExportQueryContainerFactoryPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_regex_unref0(var) ((var == NULL) ? NULL : (var = (g_regex_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

#define RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE (rygel_media_export_media_cache_get_type ())
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE, RygelMediaExportMediaCache))
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE, RygelMediaExportMediaCacheClass))
#define RYGEL_MEDIA_EXPORT_IS_MEDIA_CACHE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE))
#define RYGEL_MEDIA_EXPORT_IS_MEDIA_CACHE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE))
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE, RygelMediaExportMediaCacheClass))

typedef struct _RygelMediaExportMediaCache RygelMediaExportMediaCache;
typedef struct _RygelMediaExportMediaCacheClass RygelMediaExportMediaCacheClass;

#define RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER (rygel_media_export_db_container_get_type ())
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainer))
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_DB_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_DB_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER))
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainerClass))

typedef struct _RygelMediaExportDBContainer RygelMediaExportDBContainer;
typedef struct _RygelMediaExportDBContainerClass RygelMediaExportDBContainerClass;

#define RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER (rygel_media_export_query_container_get_type ())
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER, RygelMediaExportQueryContainer))
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER, RygelMediaExportQueryContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER, RygelMediaExportQueryContainerClass))

typedef struct _RygelMediaExportQueryContainer RygelMediaExportQueryContainer;
typedef struct _RygelMediaExportQueryContainerClass RygelMediaExportQueryContainerClass;

#define RYGEL_MEDIA_EXPORT_TYPE_LEAF_QUERY_CONTAINER (rygel_media_export_leaf_query_container_get_type ())
#define RYGEL_MEDIA_EXPORT_LEAF_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_LEAF_QUERY_CONTAINER, RygelMediaExportLeafQueryContainer))
#define RYGEL_MEDIA_EXPORT_LEAF_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_LEAF_QUERY_CONTAINER, RygelMediaExportLeafQueryContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_LEAF_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_LEAF_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_LEAF_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_LEAF_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_LEAF_QUERY_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_LEAF_QUERY_CONTAINER, RygelMediaExportLeafQueryContainerClass))

typedef struct _RygelMediaExportLeafQueryContainer RygelMediaExportLeafQueryContainer;
typedef struct _RygelMediaExportLeafQueryContainerClass RygelMediaExportLeafQueryContainerClass;

#define RYGEL_MEDIA_EXPORT_TYPE_NODE_QUERY_CONTAINER (rygel_media_export_node_query_container_get_type ())
#define RYGEL_MEDIA_EXPORT_NODE_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_NODE_QUERY_CONTAINER, RygelMediaExportNodeQueryContainer))
#define RYGEL_MEDIA_EXPORT_NODE_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_NODE_QUERY_CONTAINER, RygelMediaExportNodeQueryContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_NODE_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_NODE_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_NODE_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_NODE_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_NODE_QUERY_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_NODE_QUERY_CONTAINER, RygelMediaExportNodeQueryContainerClass))

typedef struct _RygelMediaExportNodeQueryContainer RygelMediaExportNodeQueryContainer;
typedef struct _RygelMediaExportNodeQueryContainerClass RygelMediaExportNodeQueryContainerClass;
#define _rygel_search_expression_unref0(var) ((var == NULL) ? NULL : (var = (rygel_search_expression_unref (var), NULL)))

struct _RygelMediaExportQueryContainerFactory {
	GObject parent_instance;
	RygelMediaExportQueryContainerFactoryPrivate * priv;
};

struct _RygelMediaExportQueryContainerFactoryClass {
	GObjectClass parent_class;
};

struct _RygelMediaExportQueryContainerFactoryPrivate {
	GeeHashMap* virtual_container_map;
};


static gpointer rygel_media_export_query_container_factory_parent_class = NULL;
static RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_instance;
static RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_instance = NULL;

GType rygel_media_export_query_container_factory_get_type (void) G_GNUC_CONST;
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY, RygelMediaExportQueryContainerFactoryPrivate))
enum  {
	RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY_DUMMY_PROPERTY
};
RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_get_default (void);
static RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_new (void);
static RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_construct (GType object_type);
void rygel_media_export_query_container_factory_register_id (RygelMediaExportQueryContainerFactory* self, gchar** id);
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_PREFIX "virtual-container:"
gchar* rygel_media_export_query_container_factory_get_virtual_container_definition (RygelMediaExportQueryContainerFactory* self, const gchar* hash);
GType rygel_media_export_media_cache_get_type (void) G_GNUC_CONST;
GType rygel_media_export_db_container_get_type (void) G_GNUC_CONST;
GType rygel_media_export_query_container_get_type (void) G_GNUC_CONST;
RygelMediaExportQueryContainer* rygel_media_export_query_container_factory_create_from_id (RygelMediaExportQueryContainerFactory* self, RygelMediaExportMediaCache* cache, const gchar* id, const gchar* name);
RygelMediaExportQueryContainer* rygel_media_export_query_container_factory_create_from_description (RygelMediaExportQueryContainerFactory* self, RygelMediaExportMediaCache* cache, const gchar* definition, const gchar* name);
static RygelSearchExpression* rygel_media_export_query_container_factory_parse_description (RygelMediaExportQueryContainerFactory* self, const gchar* description, gchar** pattern, gchar** attribute, gchar** upnp_class, gchar** name);
RygelMediaExportLeafQueryContainer* rygel_media_export_leaf_query_container_new (RygelMediaExportMediaCache* cache, RygelSearchExpression* expression, const gchar* id, const gchar* name);
RygelMediaExportLeafQueryContainer* rygel_media_export_leaf_query_container_construct (GType object_type, RygelMediaExportMediaCache* cache, RygelSearchExpression* expression, const gchar* id, const gchar* name);
GType rygel_media_export_leaf_query_container_get_type (void) G_GNUC_CONST;
RygelMediaExportNodeQueryContainer* rygel_media_export_node_query_container_new (RygelMediaExportMediaCache* cache, RygelSearchExpression* expression, const gchar* id, const gchar* name, const gchar* template, const gchar* attribute);
RygelMediaExportNodeQueryContainer* rygel_media_export_node_query_container_construct (GType object_type, RygelMediaExportMediaCache* cache, RygelSearchExpression* expression, const gchar* id, const gchar* name, const gchar* template, const gchar* attribute);
GType rygel_media_export_node_query_container_get_type (void) G_GNUC_CONST;
static gchar* rygel_media_export_query_container_factory_map_upnp_class (RygelMediaExportQueryContainerFactory* self, const gchar* attribute);
static void rygel_media_export_query_container_factory_update_search_expression (RygelMediaExportQueryContainerFactory* self, RygelSearchExpression** expression, const gchar* key, const gchar* value);
static void rygel_media_export_query_container_factory_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_get_default (void) {
	RygelMediaExportQueryContainerFactory* result = NULL;
	RygelMediaExportQueryContainerFactory* _tmp0_;
	gboolean _tmp1_ = FALSE;
	RygelMediaExportQueryContainerFactory* _tmp3_;
	RygelMediaExportQueryContainerFactory* _tmp4_;
	_tmp0_ = rygel_media_export_query_container_factory_instance;
	_tmp1_ = G_UNLIKELY (_tmp0_ == NULL);
	if (_tmp1_) {
		RygelMediaExportQueryContainerFactory* _tmp2_;
		_tmp2_ = rygel_media_export_query_container_factory_new ();
		_g_object_unref0 (rygel_media_export_query_container_factory_instance);
		rygel_media_export_query_container_factory_instance = _tmp2_;
	}
	_tmp3_ = rygel_media_export_query_container_factory_instance;
	_tmp4_ = _g_object_ref0 (_tmp3_);
	result = _tmp4_;
	return result;
}


static RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_construct (GType object_type) {
	RygelMediaExportQueryContainerFactory * self = NULL;
	GeeHashMap* _tmp0_;
	self = (RygelMediaExportQueryContainerFactory*) g_object_new (object_type, NULL);
	_tmp0_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL, NULL);
	_g_object_unref0 (self->priv->virtual_container_map);
	self->priv->virtual_container_map = _tmp0_;
	return self;
}


static RygelMediaExportQueryContainerFactory* rygel_media_export_query_container_factory_new (void) {
	return rygel_media_export_query_container_factory_construct (RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER_FACTORY);
}


/**
     * Register a plaintext description for a query container. The passed
     * string will be modified to the checksum id of the container.
     *
     * @param id Originally contains the plaintext id which is replaced with
     *           the hashed id on return.
     */
void rygel_media_export_query_container_factory_register_id (RygelMediaExportQueryContainerFactory* self, gchar** id) {
	const gchar* _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* md5;
	GeeHashMap* _tmp2_;
	const gchar* _tmp3_;
	gboolean _tmp4_ = FALSE;
	const gchar* _tmp10_;
	gchar* _tmp11_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (*id != NULL);
	_tmp0_ = *id;
	_tmp1_ = g_compute_checksum_for_string (G_CHECKSUM_MD5, _tmp0_, (gsize) (-1));
	md5 = _tmp1_;
	_tmp2_ = self->priv->virtual_container_map;
	_tmp3_ = md5;
	_tmp4_ = gee_abstract_map_has_key ((GeeAbstractMap*) _tmp2_, _tmp3_);
	if (!_tmp4_) {
		GeeHashMap* _tmp5_;
		const gchar* _tmp6_;
		const gchar* _tmp7_;
		const gchar* _tmp8_;
		const gchar* _tmp9_;
		_tmp5_ = self->priv->virtual_container_map;
		_tmp6_ = md5;
		_tmp7_ = *id;
		gee_abstract_map_set ((GeeAbstractMap*) _tmp5_, _tmp6_, _tmp7_);
		_tmp8_ = md5;
		_tmp9_ = *id;
		g_debug ("rygel-media-export-query-container-factory.vala:58: Registering %s for" \
" %s", _tmp8_, _tmp9_);
	}
	_tmp10_ = md5;
	_tmp11_ = g_strconcat (RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_PREFIX, _tmp10_, NULL);
	_g_free0 (*id);
	*id = _tmp11_;
	_g_free0 (md5);
}


/**
     * Get the plaintext definition from a hashed id.
     *
     * Inverse function of register_id().
     *
     * @param hash A hashed id
     * @return the plaintext defintion of the virtual folder
     */
static gchar* string_replace (const gchar* self, const gchar* old, const gchar* replacement) {
	gchar* result = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (old != NULL, NULL);
	g_return_val_if_fail (replacement != NULL, NULL);
	{
		const gchar* _tmp0_;
		gchar* _tmp1_ = NULL;
		gchar* _tmp2_;
		GRegex* _tmp3_;
		GRegex* _tmp4_;
		GRegex* regex;
		GRegex* _tmp5_;
		const gchar* _tmp6_;
		gchar* _tmp7_ = NULL;
		gchar* _tmp8_;
		_tmp0_ = old;
		_tmp1_ = g_regex_escape_string (_tmp0_, -1);
		_tmp2_ = _tmp1_;
		_tmp3_ = g_regex_new (_tmp2_, 0, 0, &_inner_error_);
		_tmp4_ = _tmp3_;
		_g_free0 (_tmp2_);
		regex = _tmp4_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch40_g_regex_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
		_tmp5_ = regex;
		_tmp6_ = replacement;
		_tmp7_ = g_regex_replace_literal (_tmp5_, self, (gssize) (-1), 0, _tmp6_, 0, &_inner_error_);
		_tmp8_ = _tmp7_;
		if (_inner_error_ != NULL) {
			_g_regex_unref0 (regex);
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch40_g_regex_error;
			}
			_g_regex_unref0 (regex);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
		result = _tmp8_;
		_g_regex_unref0 (regex);
		return result;
	}
	goto __finally40;
	__catch40_g_regex_error:
	{
		GError* e = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		g_assert_not_reached ();
		_g_error_free0 (e);
	}
	__finally40:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


gchar* rygel_media_export_query_container_factory_get_virtual_container_definition (RygelMediaExportQueryContainerFactory* self, const gchar* hash) {
	gchar* result = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* id;
	GeeHashMap* _tmp2_;
	gpointer _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (hash != NULL, NULL);
	_tmp0_ = hash;
	_tmp1_ = string_replace (_tmp0_, RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_PREFIX, "");
	id = _tmp1_;
	_tmp2_ = self->priv->virtual_container_map;
	_tmp3_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp2_, id);
	result = (gchar*) _tmp3_;
	_g_free0 (id);
	return result;
}


/**
     * Factory method.
     *
     * Create a QueryContainer directly from MD5 hashed id.
     *
     * @param cache An instance of the meta-data cache
     * @param id    The hashed id of the container
     * @param name  An the title of the container. If not supplied, it will
     *              be derived from the plain-text description of the
     *              container
     * @return A new instance of QueryContainer or null if id does not exist
     */
RygelMediaExportQueryContainer* rygel_media_export_query_container_factory_create_from_id (RygelMediaExportQueryContainerFactory* self, RygelMediaExportMediaCache* cache, const gchar* id, const gchar* name) {
	RygelMediaExportQueryContainer* result = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* definition;
	const gchar* _tmp2_;
	RygelMediaExportMediaCache* _tmp3_;
	const gchar* _tmp4_;
	const gchar* _tmp5_;
	RygelMediaExportQueryContainer* _tmp6_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (cache != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = id;
	_tmp1_ = rygel_media_export_query_container_factory_get_virtual_container_definition (self, _tmp0_);
	definition = _tmp1_;
	_tmp2_ = definition;
	if (_tmp2_ == NULL) {
		result = NULL;
		_g_free0 (definition);
		return result;
	}
	_tmp3_ = cache;
	_tmp4_ = definition;
	_tmp5_ = name;
	_tmp6_ = rygel_media_export_query_container_factory_create_from_description (self, _tmp3_, _tmp4_, _tmp5_);
	result = _tmp6_;
	_g_free0 (definition);
	return result;
}


/**
     * Factory method.
     *
     * Create a QueryContainer from a plain-text description string.
     *
     * @param cache      An instance of the meta-data cache
     * @param definition Plain-text defintion of the query-container
     * @param name       The title of the container. If not supplied, it
     *                   will be derived from the plain-text description of
     *                   the container
     * @return A new instance of QueryContainer
     */
RygelMediaExportQueryContainer* rygel_media_export_query_container_factory_create_from_description (RygelMediaExportQueryContainerFactory* self, RygelMediaExportMediaCache* cache, const gchar* definition, const gchar* name) {
	RygelMediaExportQueryContainer* result = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_;
	gchar* title;
	gchar* attribute;
	gchar* pattern;
	gchar* upnp_class;
	const gchar* _tmp2_;
	gchar* _tmp3_;
	gchar* id;
	RygelMediaExportQueryContainer* container = NULL;
	const gchar* _tmp4_;
	gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gchar* _tmp7_ = NULL;
	RygelSearchExpression* _tmp8_ = NULL;
	RygelSearchExpression* expression;
	gboolean _tmp9_ = FALSE;
	const gchar* _tmp10_;
	gboolean _tmp12_;
	const gchar* _tmp25_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (cache != NULL, NULL);
	g_return_val_if_fail (definition != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = name;
	_tmp1_ = g_strdup (_tmp0_);
	title = _tmp1_;
	attribute = NULL;
	pattern = NULL;
	upnp_class = NULL;
	_tmp2_ = definition;
	_tmp3_ = g_strdup (_tmp2_);
	id = _tmp3_;
	rygel_media_export_query_container_factory_register_id (self, &id);
	_tmp4_ = definition;
	_tmp8_ = rygel_media_export_query_container_factory_parse_description (self, _tmp4_, &_tmp5_, &_tmp6_, &_tmp7_, &title);
	_g_free0 (pattern);
	pattern = _tmp5_;
	_g_free0 (attribute);
	attribute = _tmp6_;
	_g_free0 (upnp_class);
	upnp_class = _tmp7_;
	expression = _tmp8_;
	_tmp10_ = pattern;
	if (_tmp10_ == NULL) {
		_tmp9_ = TRUE;
	} else {
		const gchar* _tmp11_;
		_tmp11_ = pattern;
		_tmp9_ = g_strcmp0 (_tmp11_, "") == 0;
	}
	_tmp12_ = _tmp9_;
	if (_tmp12_) {
		RygelMediaExportMediaCache* _tmp13_;
		RygelSearchExpression* _tmp14_;
		const gchar* _tmp15_;
		const gchar* _tmp16_;
		RygelMediaExportLeafQueryContainer* _tmp17_;
		_tmp13_ = cache;
		_tmp14_ = expression;
		_tmp15_ = id;
		_tmp16_ = title;
		_tmp17_ = rygel_media_export_leaf_query_container_new (_tmp13_, _tmp14_, _tmp15_, _tmp16_);
		_g_object_unref0 (container);
		container = (RygelMediaExportQueryContainer*) _tmp17_;
	} else {
		RygelMediaExportMediaCache* _tmp18_;
		RygelSearchExpression* _tmp19_;
		const gchar* _tmp20_;
		const gchar* _tmp21_;
		const gchar* _tmp22_;
		const gchar* _tmp23_;
		RygelMediaExportNodeQueryContainer* _tmp24_;
		_tmp18_ = cache;
		_tmp19_ = expression;
		_tmp20_ = id;
		_tmp21_ = title;
		_tmp22_ = pattern;
		_tmp23_ = attribute;
		_tmp24_ = rygel_media_export_node_query_container_new (_tmp18_, _tmp19_, _tmp20_, _tmp21_, _tmp22_, _tmp23_);
		_g_object_unref0 (container);
		container = (RygelMediaExportQueryContainer*) _tmp24_;
	}
	_tmp25_ = upnp_class;
	if (_tmp25_ != NULL) {
		RygelMediaExportQueryContainer* _tmp26_;
		const gchar* _tmp27_;
		gchar* _tmp28_;
		const gchar* _tmp29_;
		_tmp26_ = container;
		_tmp27_ = upnp_class;
		_tmp28_ = g_strdup (_tmp27_);
		_g_free0 (((RygelMediaObject*) _tmp26_)->upnp_class);
		((RygelMediaObject*) _tmp26_)->upnp_class = _tmp28_;
		_tmp29_ = upnp_class;
		if (g_strcmp0 (_tmp29_, RYGEL_MEDIA_CONTAINER_MUSIC_ALBUM) == 0) {
			RygelMediaExportQueryContainer* _tmp30_;
			_tmp30_ = container;
			rygel_media_container_set_sort_criteria ((RygelMediaContainer*) _tmp30_, RYGEL_MEDIA_CONTAINER_ALBUM_SORT_CRITERIA);
		}
	}
	result = container;
	_rygel_search_expression_unref0 (expression);
	_g_free0 (id);
	_g_free0 (upnp_class);
	_g_free0 (pattern);
	_g_free0 (attribute);
	_g_free0 (title);
	return result;
}


/**
     * Map a DIDL attribute to a UPnP container class.
     *
     * @return A matching UPnP class for the attribute or null if it can't be
     *         mapped.
     */
static gchar* rygel_media_export_query_container_factory_map_upnp_class (RygelMediaExportQueryContainerFactory* self, const gchar* attribute) {
	gchar* result = NULL;
	const gchar* _tmp0_;
	const gchar* _tmp1_;
	GQuark _tmp3_ = 0U;
	static GQuark _tmp2_label0 = 0;
	static GQuark _tmp2_label1 = 0;
	static GQuark _tmp2_label2 = 0;
	static GQuark _tmp2_label3 = 0;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (attribute != NULL, NULL);
	_tmp0_ = attribute;
	_tmp1_ = _tmp0_;
	_tmp3_ = (NULL == _tmp1_) ? 0 : g_quark_from_string (_tmp1_);
	if (_tmp3_ == ((0 != _tmp2_label0) ? _tmp2_label0 : (_tmp2_label0 = g_quark_from_static_string ("upnp:album")))) {
		switch (0) {
			default:
			{
				gchar* _tmp4_;
				_tmp4_ = g_strdup (RYGEL_MEDIA_CONTAINER_MUSIC_ALBUM);
				result = _tmp4_;
				return result;
			}
		}
	} else if ((_tmp3_ == ((0 != _tmp2_label1) ? _tmp2_label1 : (_tmp2_label1 = g_quark_from_static_string ("dc:creator")))) || (_tmp3_ == ((0 != _tmp2_label2) ? _tmp2_label2 : (_tmp2_label2 = g_quark_from_static_string ("upnp:artist"))))) {
		switch (0) {
			default:
			{
				gchar* _tmp5_;
				_tmp5_ = g_strdup (RYGEL_MEDIA_CONTAINER_MUSIC_ARTIST);
				result = _tmp5_;
				return result;
			}
		}
	} else if (_tmp3_ == ((0 != _tmp2_label3) ? _tmp2_label3 : (_tmp2_label3 = g_quark_from_static_string ("dc:genre")))) {
		switch (0) {
			default:
			{
				gchar* _tmp6_;
				_tmp6_ = g_strdup (RYGEL_MEDIA_CONTAINER_MUSIC_GENRE);
				result = _tmp6_;
				return result;
			}
		}
	} else {
		switch (0) {
			default:
			{
				result = NULL;
				return result;
			}
		}
	}
}


/**
     * Parse a plaintext container description into a search expression.
     *
     * Also generates a name for the container and other meta-data necessary
     * for node containers.
     *
     * @param description The plaintext container description
     * @param pattern     Contains the pattern used for child containers if
     *                    descrption is for a node container, null otherwise.
     * @param attribute   Contains the UPnP attribute the container describes.
     * @param name        If passed empty, name will be generated from the
     *                    description.
     * @return A SearchExpression corresponding to the non-variable part of
     *         the description.
     */
static gpointer _rygel_search_expression_ref0 (gpointer self) {
	return self ? rygel_search_expression_ref (self) : NULL;
}


static RygelSearchExpression* rygel_media_export_query_container_factory_parse_description (RygelMediaExportQueryContainerFactory* self, const gchar* description, gchar** pattern, gchar** attribute, gchar** upnp_class, gchar** name) {
	gchar* _vala_pattern = NULL;
	gchar* _vala_attribute = NULL;
	gchar* _vala_upnp_class = NULL;
	RygelSearchExpression* result = NULL;
	const gchar* _tmp0_;
	gchar** _tmp1_;
	gchar** _tmp2_ = NULL;
	gchar** args;
	gint args_length1;
	gint _args_size_;
	RygelSearchExpression* _tmp3_;
	RygelSearchExpression* expression;
	gint i;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (description != NULL, NULL);
	g_return_val_if_fail (*name != NULL, NULL);
	_tmp0_ = description;
	_tmp2_ = _tmp1_ = g_strsplit (_tmp0_, ",", 0);
	args = _tmp2_;
	args_length1 = _vala_array_length (_tmp1_);
	_args_size_ = args_length1;
	_tmp3_ = _rygel_search_expression_ref0 (RYGEL_IS_SEARCH_EXPRESSION (NULL) ? ((RygelSearchExpression*) NULL) : NULL);
	expression = _tmp3_;
	_g_free0 (_vala_pattern);
	_vala_pattern = NULL;
	_g_free0 (_vala_attribute);
	_vala_attribute = NULL;
	_g_free0 (_vala_upnp_class);
	_vala_upnp_class = NULL;
	i = 0;
	while (TRUE) {
		gint _tmp4_;
		gchar** _tmp5_;
		gint _tmp5__length1;
		const gchar* _tmp6_;
		gchar* _tmp7_;
		gchar* previous_attribute;
		gchar** _tmp8_;
		gint _tmp8__length1;
		gint _tmp9_;
		const gchar* _tmp10_;
		gchar* _tmp11_ = NULL;
		const gchar* _tmp12_;
		gchar* _tmp13_ = NULL;
		gchar** _tmp14_;
		gint _tmp14__length1;
		gint _tmp15_;
		const gchar* _tmp16_;
		gint _tmp43_;
		_tmp4_ = i;
		_tmp5_ = args;
		_tmp5__length1 = args_length1;
		if (!(_tmp4_ < _tmp5__length1)) {
			break;
		}
		_tmp6_ = _vala_attribute;
		_tmp7_ = g_strdup (_tmp6_);
		previous_attribute = _tmp7_;
		_tmp8_ = args;
		_tmp8__length1 = args_length1;
		_tmp9_ = i;
		_tmp10_ = _tmp8_[_tmp9_];
		_tmp11_ = string_replace (_tmp10_, RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_PREFIX, "");
		_g_free0 (_vala_attribute);
		_vala_attribute = _tmp11_;
		_tmp12_ = _vala_attribute;
		_tmp13_ = g_uri_unescape_string (_tmp12_, NULL);
		_g_free0 (_vala_attribute);
		_vala_attribute = _tmp13_;
		_tmp14_ = args;
		_tmp14__length1 = args_length1;
		_tmp15_ = i;
		_tmp16_ = _tmp14_[_tmp15_ + 1];
		if (g_strcmp0 (_tmp16_, "?") != 0) {
			gchar** _tmp17_;
			gint _tmp17__length1;
			gint _tmp18_;
			const gchar* _tmp19_;
			gchar** _tmp20_;
			gint _tmp20__length1;
			gint _tmp21_;
			const gchar* _tmp22_;
			gint _tmp23_;
			gchar** _tmp24_;
			gint _tmp24__length1;
			_tmp17_ = args;
			_tmp17__length1 = args_length1;
			_tmp18_ = i;
			_tmp19_ = _tmp17_[_tmp18_];
			_tmp20_ = args;
			_tmp20__length1 = args_length1;
			_tmp21_ = i;
			_tmp22_ = _tmp20_[_tmp21_ + 1];
			rygel_media_export_query_container_factory_update_search_expression (self, &expression, _tmp19_, _tmp22_);
			_tmp23_ = i;
			_tmp24_ = args;
			_tmp24__length1 = args_length1;
			if ((_tmp23_ + 2) == _tmp24__length1) {
				const gchar* _tmp25_;
				gchar* _tmp26_ = NULL;
				_tmp25_ = _vala_attribute;
				_tmp26_ = rygel_media_export_query_container_factory_map_upnp_class (self, _tmp25_);
				_g_free0 (_vala_upnp_class);
				_vala_upnp_class = _tmp26_;
			}
		} else {
			gchar** _tmp27_;
			gint _tmp27__length1;
			gint _tmp28_;
			gchar* _tmp29_;
			gchar* _tmp30_;
			gchar** _tmp31_;
			gint _tmp31__length1;
			gchar* _tmp32_ = NULL;
			const gchar* _tmp33_;
			gchar* _tmp34_ = NULL;
			gboolean _tmp35_ = FALSE;
			const gchar* _tmp36_;
			gboolean _tmp38_;
			_tmp27_ = args;
			_tmp27__length1 = args_length1;
			_tmp28_ = i;
			_tmp29_ = g_strdup ("%s");
			_g_free0 (_tmp27_[_tmp28_ + 1]);
			_tmp27_[_tmp28_ + 1] = _tmp29_;
			_tmp30_ = _tmp27_[_tmp28_ + 1];
			_tmp31_ = args;
			_tmp31__length1 = args_length1;
			_tmp32_ = g_strjoinv (",", _tmp31_);
			_g_free0 (_vala_pattern);
			_vala_pattern = _tmp32_;
			_tmp33_ = previous_attribute;
			_tmp34_ = rygel_media_export_query_container_factory_map_upnp_class (self, _tmp33_);
			_g_free0 (_vala_upnp_class);
			_vala_upnp_class = _tmp34_;
			_tmp36_ = *name;
			if (g_strcmp0 (_tmp36_, "") == 0) {
				gint _tmp37_;
				_tmp37_ = i;
				_tmp35_ = _tmp37_ > 0;
			} else {
				_tmp35_ = FALSE;
			}
			_tmp38_ = _tmp35_;
			if (_tmp38_) {
				gchar** _tmp39_;
				gint _tmp39__length1;
				gint _tmp40_;
				const gchar* _tmp41_;
				gchar* _tmp42_ = NULL;
				_tmp39_ = args;
				_tmp39__length1 = args_length1;
				_tmp40_ = i;
				_tmp41_ = _tmp39_[_tmp40_ - 1];
				_tmp42_ = g_uri_unescape_string (_tmp41_, NULL);
				_g_free0 (*name);
				*name = _tmp42_;
			}
			_g_free0 (previous_attribute);
			break;
		}
		_tmp43_ = i;
		i = _tmp43_ + 2;
		_g_free0 (previous_attribute);
	}
	result = expression;
	args = (_vala_array_free (args, args_length1, (GDestroyNotify) g_free), NULL);
	if (pattern) {
		*pattern = _vala_pattern;
	} else {
		_g_free0 (_vala_pattern);
	}
	if (attribute) {
		*attribute = _vala_attribute;
	} else {
		_g_free0 (_vala_attribute);
	}
	if (upnp_class) {
		*upnp_class = _vala_upnp_class;
	} else {
		_g_free0 (_vala_upnp_class);
	}
	return result;
}


/**
     * Update a SearchExpression with a new key = value condition.
     *
     * Will modifiy the passed expression to (expression AND (key = value))
     *
     * @param expression The expression to update or null to create a new one
     * @param key        Key of the key/value condition
     * @param value      Value of the key/value condition
     */
static void rygel_media_export_query_container_factory_update_search_expression (RygelMediaExportQueryContainerFactory* self, RygelSearchExpression** expression, const gchar* key, const gchar* value) {
	RygelRelationalExpression* _tmp0_;
	RygelRelationalExpression* subexpression;
	const gchar* _tmp1_;
	gchar* _tmp2_ = NULL;
	gchar* clean_key;
	RygelRelationalExpression* _tmp3_;
	const gchar* _tmp4_;
	gchar* _tmp5_ = NULL;
	RygelRelationalExpression* _tmp6_;
	RygelRelationalExpression* _tmp7_;
	const gchar* _tmp8_;
	gchar* _tmp9_ = NULL;
	RygelSearchExpression* _tmp10_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (key != NULL);
	g_return_if_fail (value != NULL);
	_tmp0_ = rygel_relational_expression_new ();
	subexpression = _tmp0_;
	_tmp1_ = key;
	_tmp2_ = string_replace (_tmp1_, RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_PREFIX, "");
	clean_key = _tmp2_;
	_tmp3_ = subexpression;
	_tmp4_ = clean_key;
	_tmp5_ = g_uri_unescape_string (_tmp4_, NULL);
	_g_free0 (((RygelSearchExpression*) _tmp3_)->operand1);
	((RygelSearchExpression*) _tmp3_)->operand1 = _tmp5_;
	_tmp6_ = subexpression;
	((RygelSearchExpression*) _tmp6_)->op = GINT_TO_POINTER (GUPNP_SEARCH_CRITERIA_OP_EQ);
	_tmp7_ = subexpression;
	_tmp8_ = value;
	_tmp9_ = g_uri_unescape_string (_tmp8_, NULL);
	_g_free0 (((RygelSearchExpression*) _tmp7_)->operand2);
	((RygelSearchExpression*) _tmp7_)->operand2 = _tmp9_;
	_tmp10_ = *expression;
	if (_tmp10_ != NULL) {
		RygelLogicalExpression* _tmp11_;
		RygelLogicalExpression* conjunction;
		RygelLogicalExpression* _tmp12_;
		RygelSearchExpression* _tmp13_;
		RygelSearchExpression* _tmp14_;
		RygelLogicalExpression* _tmp15_;
		RygelRelationalExpression* _tmp16_;
		RygelSearchExpression* _tmp17_;
		RygelLogicalExpression* _tmp18_;
		RygelLogicalExpression* _tmp19_;
		RygelSearchExpression* _tmp20_;
		_tmp11_ = rygel_logical_expression_new ();
		conjunction = _tmp11_;
		_tmp12_ = conjunction;
		_tmp13_ = *expression;
		_tmp14_ = _rygel_search_expression_ref0 (_tmp13_);
		_rygel_search_expression_unref0 (((RygelSearchExpression*) _tmp12_)->operand1);
		((RygelSearchExpression*) _tmp12_)->operand1 = _tmp14_;
		_tmp15_ = conjunction;
		_tmp16_ = subexpression;
		_tmp17_ = _rygel_search_expression_ref0 ((RygelSearchExpression*) _tmp16_);
		_rygel_search_expression_unref0 (((RygelSearchExpression*) _tmp15_)->operand2);
		((RygelSearchExpression*) _tmp15_)->operand2 = _tmp17_;
		_tmp18_ = conjunction;
		((RygelSearchExpression*) _tmp18_)->op = GINT_TO_POINTER (RYGEL_LOGICAL_OPERATOR_AND);
		_tmp19_ = conjunction;
		_tmp20_ = _rygel_search_expression_ref0 ((RygelSearchExpression*) _tmp19_);
		_rygel_search_expression_unref0 (*expression);
		*expression = _tmp20_;
		_rygel_search_expression_unref0 (conjunction);
	} else {
		RygelRelationalExpression* _tmp21_;
		RygelSearchExpression* _tmp22_;
		_tmp21_ = subexpression;
		_tmp22_ = _rygel_search_expression_ref0 ((RygelSearchExpression*) _tmp21_);
		_rygel_search_expression_unref0 (*expression);
		*expression = _tmp22_;
	}
	_g_free0 (clean_key);
	_rygel_search_expression_unref0 (subexpression);
}


static void rygel_media_export_query_container_factory_class_init (RygelMediaExportQueryContainerFactoryClass * klass) {
	rygel_media_export_query_container_factory_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediaExportQueryContainerFactoryPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_media_export_query_container_factory_finalize;
}


static void rygel_media_export_query_container_factory_instance_init (RygelMediaExportQueryContainerFactory * self) {
	self->priv = RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY_GET_PRIVATE (self);
}


static void rygel_media_export_query_container_factory_finalize (GObject* obj) {
	RygelMediaExportQueryContainerFactory * self;
	self = RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_FACTORY (obj);
	_g_object_unref0 (self->priv->virtual_container_map);
	G_OBJECT_CLASS (rygel_media_export_query_container_factory_parent_class)->finalize (obj);
}


GType rygel_media_export_query_container_factory_get_type (void) {
	static volatile gsize rygel_media_export_query_container_factory_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_media_export_query_container_factory_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaExportQueryContainerFactoryClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_export_query_container_factory_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaExportQueryContainerFactory), 0, (GInstanceInitFunc) rygel_media_export_query_container_factory_instance_init, NULL };
		GType rygel_media_export_query_container_factory_type_id;
		rygel_media_export_query_container_factory_type_id = g_type_register_static (G_TYPE_OBJECT, "RygelMediaExportQueryContainerFactory", &g_define_type_info, 0);
		g_once_init_leave (&rygel_media_export_query_container_factory_type_id__volatile, rygel_media_export_query_container_factory_type_id);
	}
	return rygel_media_export_query_container_factory_type_id__volatile;
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


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}



