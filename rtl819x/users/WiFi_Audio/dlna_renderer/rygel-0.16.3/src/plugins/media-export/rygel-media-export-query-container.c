/* rygel-media-export-query-container.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-media-export-query-container.vala, do not modify */

/*
 * Copyright (C) 2009,2010 Jens Georg <mail@jensge.org>.
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
#include <rygel-server.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>


#define RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER (rygel_media_export_db_container_get_type ())
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainer))
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_DB_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_DB_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER))
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainerClass))

typedef struct _RygelMediaExportDBContainer RygelMediaExportDBContainer;
typedef struct _RygelMediaExportDBContainerClass RygelMediaExportDBContainerClass;
typedef struct _RygelMediaExportDBContainerPrivate RygelMediaExportDBContainerPrivate;

#define RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE (rygel_media_export_media_cache_get_type ())
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE, RygelMediaExportMediaCache))
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE, RygelMediaExportMediaCacheClass))
#define RYGEL_MEDIA_EXPORT_IS_MEDIA_CACHE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE))
#define RYGEL_MEDIA_EXPORT_IS_MEDIA_CACHE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE))
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_MEDIA_CACHE, RygelMediaExportMediaCacheClass))

typedef struct _RygelMediaExportMediaCache RygelMediaExportMediaCache;
typedef struct _RygelMediaExportMediaCacheClass RygelMediaExportMediaCacheClass;

#define RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER (rygel_media_export_query_container_get_type ())
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER, RygelMediaExportQueryContainer))
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER, RygelMediaExportQueryContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_QUERY_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_QUERY_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER))
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_QUERY_CONTAINER, RygelMediaExportQueryContainerClass))

typedef struct _RygelMediaExportQueryContainer RygelMediaExportQueryContainer;
typedef struct _RygelMediaExportQueryContainerClass RygelMediaExportQueryContainerClass;
typedef struct _RygelMediaExportQueryContainerPrivate RygelMediaExportQueryContainerPrivate;
#define _rygel_search_expression_unref0(var) ((var == NULL) ? NULL : (var = (rygel_search_expression_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
typedef struct _RygelMediaExportQueryContainerSearchData RygelMediaExportQueryContainerSearchData;

struct _RygelMediaExportDBContainer {
	RygelMediaContainer parent_instance;
	RygelMediaExportDBContainerPrivate * priv;
	RygelMediaExportMediaCache* media_db;
};

struct _RygelMediaExportDBContainerClass {
	RygelMediaContainerClass parent_class;
	void (*search) (RygelMediaExportDBContainer* self, RygelSearchExpression* expression, guint offset, guint max_count, const gchar* sort_criteria, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
	RygelMediaObjects* (*search_finish) (RygelMediaExportDBContainer* self, GAsyncResult* _res_, guint* total_matches, GError** error);
};

struct _RygelMediaExportQueryContainer {
	RygelMediaExportDBContainer parent_instance;
	RygelMediaExportQueryContainerPrivate * priv;
	RygelSearchExpression* expression;
};

struct _RygelMediaExportQueryContainerClass {
	RygelMediaExportDBContainerClass parent_class;
	gint (*count_children) (RygelMediaExportQueryContainer* self, GError** error);
};

typedef enum  {
	RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR_SQLITE_ERROR,
	RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR_GENERAL_ERROR,
	RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR_INVALID_TYPE,
	RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR_UNSUPPORTED_SEARCH
} RygelMediaExportMediaCacheError;
#define RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR rygel_media_export_media_cache_error_quark ()
struct _RygelMediaExportQueryContainerSearchData {
	int _state_;
	GObject* _source_object_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	RygelMediaExportQueryContainer* self;
	RygelSearchExpression* expression;
	guint offset;
	guint max_count;
	guint total_matches;
	gchar* sort_criteria;
	GCancellable* cancellable;
	RygelMediaObjects* result;
	RygelMediaObjects* children;
	RygelSearchExpression* combined_expression;
	RygelSearchExpression* _tmp0_;
	RygelSearchExpression* _tmp1_;
	RygelSearchExpression* _tmp2_;
	RygelLogicalExpression* _tmp3_;
	RygelLogicalExpression* local_expression;
	RygelLogicalExpression* _tmp4_;
	RygelSearchExpression* _tmp5_;
	RygelSearchExpression* _tmp6_;
	RygelLogicalExpression* _tmp7_;
	RygelLogicalExpression* _tmp8_;
	RygelSearchExpression* _tmp9_;
	RygelSearchExpression* _tmp10_;
	RygelLogicalExpression* _tmp11_;
	RygelSearchExpression* _tmp12_;
	RygelMediaExportMediaCache* _tmp13_;
	RygelSearchExpression* _tmp14_;
	const gchar* _tmp15_;
	guint _tmp16_;
	guint _tmp17_;
	guint _tmp18_;
	RygelMediaObjects* _tmp19_;
	RygelMediaObjects* _tmp20_;
	GError* _error_;
	GError* _tmp21_;
	RygelMediaObjects* _tmp22_;
	GError* _tmp23_;
	GError* _tmp24_;
	GError * _inner_error_;
};


static gpointer rygel_media_export_query_container_parent_class = NULL;

GType rygel_media_export_db_container_get_type (void) G_GNUC_CONST;
GType rygel_media_export_media_cache_get_type (void) G_GNUC_CONST;
GType rygel_media_export_query_container_get_type (void) G_GNUC_CONST;
enum  {
	RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_DUMMY_PROPERTY
};
#define RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_PREFIX "virtual-container:"
RygelMediaExportQueryContainer* rygel_media_export_query_container_construct (GType object_type, RygelMediaExportMediaCache* cache, RygelSearchExpression* expression, const gchar* id, const gchar* name);
RygelMediaExportDBContainer* rygel_media_export_db_container_new (RygelMediaExportMediaCache* media_db, const gchar* id, const gchar* title);
RygelMediaExportDBContainer* rygel_media_export_db_container_construct (GType object_type, RygelMediaExportMediaCache* media_db, const gchar* id, const gchar* title);
gint rygel_media_export_query_container_count_children (RygelMediaExportQueryContainer* self, GError** error);
static void rygel_media_export_query_container_real_search_data_free (gpointer _data);
static void rygel_media_export_query_container_real_search (RygelMediaExportDBContainer* base, RygelSearchExpression* expression, guint offset, guint max_count, const gchar* sort_criteria, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_);
static gboolean rygel_media_export_query_container_real_search_co (RygelMediaExportQueryContainerSearchData* _data_);
RygelMediaObjects* rygel_media_export_media_cache_get_objects_by_search_expression (RygelMediaExportMediaCache* self, RygelSearchExpression* expression, const gchar* container_id, const gchar* sort_criteria, guint offset, guint max_count, guint* total_matches, GError** error);
GQuark rygel_media_export_media_cache_error_quark (void);
static gint rygel_media_export_query_container_real_count_children (RygelMediaExportQueryContainer* self, GError** error);
static void rygel_media_export_query_container_finalize (GObject* obj);


static gpointer _rygel_search_expression_ref0 (gpointer self) {
	return self ? rygel_search_expression_ref (self) : NULL;
}


RygelMediaExportQueryContainer* rygel_media_export_query_container_construct (GType object_type, RygelMediaExportMediaCache* cache, RygelSearchExpression* expression, const gchar* id, const gchar* name) {
	RygelMediaExportQueryContainer * self = NULL;
	RygelMediaExportMediaCache* _tmp0_;
	const gchar* _tmp1_;
	const gchar* _tmp2_;
	RygelSearchExpression* _tmp3_;
	RygelSearchExpression* _tmp4_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (cache != NULL, NULL);
	g_return_val_if_fail (expression != NULL, NULL);
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = cache;
	_tmp1_ = id;
	_tmp2_ = name;
	self = (RygelMediaExportQueryContainer*) rygel_media_export_db_container_construct (object_type, _tmp0_, _tmp1_, _tmp2_);
	_tmp3_ = expression;
	_tmp4_ = _rygel_search_expression_ref0 (_tmp3_);
	_rygel_search_expression_unref0 (self->expression);
	self->expression = _tmp4_;
	{
		gint _tmp5_ = 0;
		gint _tmp6_;
		_tmp5_ = rygel_media_export_query_container_count_children (self, &_inner_error_);
		_tmp6_ = _tmp5_;
		if (_inner_error_ != NULL) {
			goto __catch38_g_error;
		}
		((RygelMediaContainer*) self)->child_count = _tmp6_;
	}
	goto __finally38;
	__catch38_g_error:
	{
		GError* _error_ = NULL;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		((RygelMediaContainer*) self)->child_count = 0;
		_g_error_free0 (_error_);
	}
	__finally38:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	return self;
}


static void rygel_media_export_query_container_real_search_data_free (gpointer _data) {
	RygelMediaExportQueryContainerSearchData* _data_;
	_data_ = _data;
	_rygel_search_expression_unref0 (_data_->expression);
	_g_free0 (_data_->sort_criteria);
	_g_object_unref0 (_data_->cancellable);
	_g_object_unref0 (_data_->result);
	_g_object_unref0 (_data_->self);
	g_slice_free (RygelMediaExportQueryContainerSearchData, _data_);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void rygel_media_export_query_container_real_search (RygelMediaExportDBContainer* base, RygelSearchExpression* expression, guint offset, guint max_count, const gchar* sort_criteria, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	RygelMediaExportQueryContainer * self;
	RygelMediaExportQueryContainerSearchData* _data_;
	RygelMediaExportQueryContainer* _tmp0_;
	RygelSearchExpression* _tmp1_;
	RygelSearchExpression* _tmp2_;
	guint _tmp3_;
	guint _tmp4_;
	const gchar* _tmp5_;
	gchar* _tmp6_;
	GCancellable* _tmp7_;
	GCancellable* _tmp8_;
	self = (RygelMediaExportQueryContainer*) base;
	_data_ = g_slice_new0 (RygelMediaExportQueryContainerSearchData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, rygel_media_export_query_container_real_search);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, rygel_media_export_query_container_real_search_data_free);
	_tmp0_ = _g_object_ref0 (self);
	_data_->self = _tmp0_;
	_tmp1_ = expression;
	_tmp2_ = _rygel_search_expression_ref0 (_tmp1_);
	_data_->expression = _tmp2_;
	_tmp3_ = offset;
	_data_->offset = _tmp3_;
	_tmp4_ = max_count;
	_data_->max_count = _tmp4_;
	_tmp5_ = sort_criteria;
	_tmp6_ = g_strdup (_tmp5_);
	_data_->sort_criteria = _tmp6_;
	_tmp7_ = cancellable;
	_tmp8_ = _g_object_ref0 (_tmp7_);
	_data_->cancellable = _tmp8_;
	rygel_media_export_query_container_real_search_co (_data_);
}


static RygelMediaObjects* rygel_media_export_query_container_real_search_finish (RygelMediaExportDBContainer* base, GAsyncResult* _res_, guint* total_matches, GError** error) {
	RygelMediaObjects* result;
	RygelMediaExportQueryContainerSearchData* _data_;
	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (_res_), error)) {
		return NULL;
	}
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
	if (total_matches) {
		*total_matches = _data_->total_matches;
	}
	result = _data_->result;
	_data_->result = NULL;
	return result;
}


static gpointer _g_error_copy0 (gpointer self) {
	return self ? g_error_copy (self) : NULL;
}


static gboolean rygel_media_export_query_container_real_search_co (RygelMediaExportQueryContainerSearchData* _data_) {
	switch (_data_->_state_) {
		case 0:
		goto _state_0;
		default:
		g_assert_not_reached ();
	}
	_state_0:
	_data_->children = NULL;
	_data_->_tmp0_ = _data_->expression;
	if (_data_->_tmp0_ == NULL) {
		_data_->_tmp1_ = _data_->self->expression;
		_data_->_tmp2_ = _rygel_search_expression_ref0 (_data_->_tmp1_);
		_rygel_search_expression_unref0 (_data_->combined_expression);
		_data_->combined_expression = _data_->_tmp2_;
	} else {
		_data_->_tmp3_ = rygel_logical_expression_new ();
		_data_->local_expression = _data_->_tmp3_;
		_data_->_tmp4_ = _data_->local_expression;
		_data_->_tmp5_ = _data_->self->expression;
		_data_->_tmp6_ = _rygel_search_expression_ref0 (_data_->_tmp5_);
		_rygel_search_expression_unref0 (((RygelSearchExpression*) _data_->_tmp4_)->operand1);
		((RygelSearchExpression*) _data_->_tmp4_)->operand1 = _data_->_tmp6_;
		_data_->_tmp7_ = _data_->local_expression;
		((RygelSearchExpression*) _data_->_tmp7_)->op = GINT_TO_POINTER (RYGEL_LOGICAL_OPERATOR_AND);
		_data_->_tmp8_ = _data_->local_expression;
		_data_->_tmp9_ = _data_->expression;
		_data_->_tmp10_ = _rygel_search_expression_ref0 (_data_->_tmp9_);
		_rygel_search_expression_unref0 (((RygelSearchExpression*) _data_->_tmp8_)->operand2);
		((RygelSearchExpression*) _data_->_tmp8_)->operand2 = _data_->_tmp10_;
		_data_->_tmp11_ = _data_->local_expression;
		_data_->_tmp12_ = _rygel_search_expression_ref0 ((RygelSearchExpression*) _data_->_tmp11_);
		_rygel_search_expression_unref0 (_data_->combined_expression);
		_data_->combined_expression = _data_->_tmp12_;
		_rygel_search_expression_unref0 (_data_->local_expression);
	}
	{
		_data_->_tmp13_ = ((RygelMediaExportDBContainer*) _data_->self)->media_db;
		_data_->_tmp14_ = _data_->combined_expression;
		_data_->_tmp15_ = _data_->sort_criteria;
		_data_->_tmp16_ = _data_->offset;
		_data_->_tmp17_ = _data_->max_count;
		_data_->_tmp18_ = 0U;
		_data_->_tmp19_ = NULL;
		_data_->_tmp19_ = rygel_media_export_media_cache_get_objects_by_search_expression (_data_->_tmp13_, _data_->_tmp14_, NULL, _data_->_tmp15_, _data_->_tmp16_, _data_->_tmp17_, &_data_->_tmp18_, &_data_->_inner_error_);
		_data_->total_matches = _data_->_tmp18_;
		_data_->_tmp20_ = _data_->_tmp19_;
		if (_data_->_inner_error_ != NULL) {
			if (_data_->_inner_error_->domain == RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR) {
				goto __catch39_rygel_media_export_media_cache_error;
			}
			goto __finally39;
		}
		_g_object_unref0 (_data_->children);
		_data_->children = _data_->_tmp20_;
	}
	goto __finally39;
	__catch39_rygel_media_export_media_cache_error:
	{
		_data_->_error_ = _data_->_inner_error_;
		_data_->_inner_error_ = NULL;
		_data_->_tmp21_ = _data_->_error_;
		if (g_error_matches (_data_->_tmp21_, RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR, RYGEL_MEDIA_EXPORT_MEDIA_CACHE_ERROR_UNSUPPORTED_SEARCH)) {
			_data_->_tmp22_ = rygel_media_objects_new ();
			_g_object_unref0 (_data_->children);
			_data_->children = _data_->_tmp22_;
			_data_->total_matches = (guint) 0;
		} else {
			_data_->_tmp23_ = _data_->_error_;
			_data_->_tmp24_ = _g_error_copy0 (_data_->_tmp23_);
			_data_->_inner_error_ = _data_->_tmp24_;
			_g_error_free0 (_data_->_error_);
			goto __finally39;
		}
		_g_error_free0 (_data_->_error_);
	}
	__finally39:
	if (_data_->_inner_error_ != NULL) {
		g_simple_async_result_set_from_error (_data_->_async_result, _data_->_inner_error_);
		g_error_free (_data_->_inner_error_);
		_rygel_search_expression_unref0 (_data_->combined_expression);
		_g_object_unref0 (_data_->children);
		if (_data_->_state_ == 0) {
			g_simple_async_result_complete_in_idle (_data_->_async_result);
		} else {
			g_simple_async_result_complete (_data_->_async_result);
		}
		g_object_unref (_data_->_async_result);
		return FALSE;
	}
	_data_->result = _data_->children;
	_rygel_search_expression_unref0 (_data_->combined_expression);
	if (_data_->_state_ == 0) {
		g_simple_async_result_complete_in_idle (_data_->_async_result);
	} else {
		g_simple_async_result_complete (_data_->_async_result);
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
	_rygel_search_expression_unref0 (_data_->combined_expression);
	_g_object_unref0 (_data_->children);
	if (_data_->_state_ == 0) {
		g_simple_async_result_complete_in_idle (_data_->_async_result);
	} else {
		g_simple_async_result_complete (_data_->_async_result);
	}
	g_object_unref (_data_->_async_result);
	return FALSE;
}


static gint rygel_media_export_query_container_real_count_children (RygelMediaExportQueryContainer* self, GError** error) {
	g_critical ("Type `%s' does not implement abstract method `rygel_media_export_query_container_count_children'", g_type_name (G_TYPE_FROM_INSTANCE (self)));
	return 0;
}


gint rygel_media_export_query_container_count_children (RygelMediaExportQueryContainer* self, GError** error) {
	g_return_val_if_fail (self != NULL, 0);
	return RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_GET_CLASS (self)->count_children (self, error);
}


static void rygel_media_export_query_container_class_init (RygelMediaExportQueryContainerClass * klass) {
	rygel_media_export_query_container_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_EXPORT_DB_CONTAINER_CLASS (klass)->search = rygel_media_export_query_container_real_search;
	RYGEL_MEDIA_EXPORT_DB_CONTAINER_CLASS (klass)->search_finish = rygel_media_export_query_container_real_search_finish;
	RYGEL_MEDIA_EXPORT_QUERY_CONTAINER_CLASS (klass)->count_children = rygel_media_export_query_container_real_count_children;
	G_OBJECT_CLASS (klass)->finalize = rygel_media_export_query_container_finalize;
}


static void rygel_media_export_query_container_instance_init (RygelMediaExportQueryContainer * self) {
}


static void rygel_media_export_query_container_finalize (GObject* obj) {
	RygelMediaExportQueryContainer * self;
	self = RYGEL_MEDIA_EXPORT_QUERY_CONTAINER (obj);
	_rygel_search_expression_unref0 (self->expression);
	G_OBJECT_CLASS (rygel_media_export_query_container_parent_class)->finalize (obj);
}


GType rygel_media_export_query_container_get_type (void) {
	static volatile gsize rygel_media_export_query_container_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_media_export_query_container_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaExportQueryContainerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_export_query_container_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaExportQueryContainer), 0, (GInstanceInitFunc) rygel_media_export_query_container_instance_init, NULL };
		GType rygel_media_export_query_container_type_id;
		rygel_media_export_query_container_type_id = g_type_register_static (RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, "RygelMediaExportQueryContainer", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
		g_once_init_leave (&rygel_media_export_query_container_type_id__volatile, rygel_media_export_query_container_type_id);
	}
	return rygel_media_export_query_container_type_id__volatile;
}



