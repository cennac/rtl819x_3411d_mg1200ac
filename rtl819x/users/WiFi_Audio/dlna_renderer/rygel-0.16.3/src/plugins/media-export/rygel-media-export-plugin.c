/* rygel-media-export-plugin.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-media-export-plugin.vala, do not modify */

/*
 * Copyright (C) 2008-2009 Jens Georg <mail@jensge.org>.
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
#include <stdlib.h>
#include <string.h>
#include <rygel-core.h>
#include <rygel-server.h>
#include <gee.h>


#define RYGEL_MEDIA_EXPORT_TYPE_PLUGIN (rygel_media_export_plugin_get_type ())
#define RYGEL_MEDIA_EXPORT_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_PLUGIN, RygelMediaExportPlugin))
#define RYGEL_MEDIA_EXPORT_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_PLUGIN, RygelMediaExportPluginClass))
#define RYGEL_MEDIA_EXPORT_IS_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_PLUGIN))
#define RYGEL_MEDIA_EXPORT_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_PLUGIN))
#define RYGEL_MEDIA_EXPORT_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_PLUGIN, RygelMediaExportPluginClass))

typedef struct _RygelMediaExportPlugin RygelMediaExportPlugin;
typedef struct _RygelMediaExportPluginClass RygelMediaExportPluginClass;
typedef struct _Block1Data Block1Data;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
typedef struct _Block2Data Block2Data;

#define RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER (rygel_media_export_db_container_get_type ())
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainer))
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_DB_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_DB_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER))
#define RYGEL_MEDIA_EXPORT_DB_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_DB_CONTAINER, RygelMediaExportDBContainerClass))

typedef struct _RygelMediaExportDBContainer RygelMediaExportDBContainer;
typedef struct _RygelMediaExportDBContainerClass RygelMediaExportDBContainerClass;

#define RYGEL_MEDIA_EXPORT_TYPE_ROOT_CONTAINER (rygel_media_export_root_container_get_type ())
#define RYGEL_MEDIA_EXPORT_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_ROOT_CONTAINER, RygelMediaExportRootContainer))
#define RYGEL_MEDIA_EXPORT_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_ROOT_CONTAINER, RygelMediaExportRootContainerClass))
#define RYGEL_MEDIA_EXPORT_IS_ROOT_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_ROOT_CONTAINER))
#define RYGEL_MEDIA_EXPORT_IS_ROOT_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_ROOT_CONTAINER))
#define RYGEL_MEDIA_EXPORT_ROOT_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_ROOT_CONTAINER, RygelMediaExportRootContainerClass))

typedef struct _RygelMediaExportRootContainer RygelMediaExportRootContainer;
typedef struct _RygelMediaExportRootContainerClass RygelMediaExportRootContainerClass;
typedef struct _RygelMediaExportPluginPrivate RygelMediaExportPluginPrivate;

struct _Block1Data {
	int _ref_count_;
	RygelMediaExportPlugin* plugin;
	RygelPluginLoader* loader;
};

struct _Block2Data {
	int _ref_count_;
	RygelPlugin* plugin;
	RygelPlugin* our_plugin;
};

struct _RygelMediaExportPlugin {
	RygelMediaServerPlugin parent_instance;
	RygelMediaExportPluginPrivate * priv;
};

struct _RygelMediaExportPluginClass {
	RygelMediaServerPluginClass parent_class;
};


static gpointer rygel_media_export_plugin_parent_class = NULL;

#define TRACKER_PLUGIN "Tracker"
void module_init (RygelPluginLoader* loader);
GType rygel_media_export_plugin_get_type (void) G_GNUC_CONST;
static Block1Data* block1_data_ref (Block1Data* _data1_);
static void block1_data_unref (void * _userdata_);
#define RYGEL_MEDIA_EXPORT_PLUGIN_NAME "MediaExport"
RygelMediaExportPlugin* rygel_media_export_plugin_new (GError** error);
RygelMediaExportPlugin* rygel_media_export_plugin_construct (GType object_type, GError** error);
static gboolean __lambda6_ (Block1Data* _data1_);
void on_plugin_available (RygelPlugin* plugin, RygelPlugin* our_plugin);
static void __lambda8_ (Block1Data* _data1_, RygelPlugin* new_plugin);
static void ___lambda8__rygel_plugin_loader_plugin_available (RygelPluginLoader* _sender, RygelPlugin* plugin, gpointer self);
static gboolean ___lambda6__gsource_func (gpointer self);
static Block2Data* block2_data_ref (Block2Data* _data2_);
static void block2_data_unref (void * _userdata_);
static void ____lambda7_ (Block2Data* _data2_);
void shutdown_media_export (void);
static void _____lambda7__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
RygelMediaContainer* rygel_media_export_root_container_get_instance (GError** error);
GType rygel_media_export_db_container_get_type (void) G_GNUC_CONST;
GType rygel_media_export_root_container_get_type (void) G_GNUC_CONST;
void rygel_media_export_root_container_shutdown (RygelMediaExportRootContainer* self);
enum  {
	RYGEL_MEDIA_EXPORT_PLUGIN_DUMMY_PROPERTY
};


/**
 * Simple plugin which exposes the media contents of a directory via UPnP.
 *
 */
static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static Block1Data* block1_data_ref (Block1Data* _data1_) {
	g_atomic_int_inc (&_data1_->_ref_count_);
	return _data1_;
}


static void block1_data_unref (void * _userdata_) {
	Block1Data* _data1_;
	_data1_ = (Block1Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data1_->_ref_count_)) {
		_g_object_unref0 (_data1_->plugin);
		_g_object_unref0 (_data1_->loader);
		g_slice_free (Block1Data, _data1_);
	}
}


static void __lambda8_ (Block1Data* _data1_, RygelPlugin* new_plugin) {
	RygelPlugin* _tmp0_;
	RygelMediaExportPlugin* _tmp1_;
	g_return_if_fail (new_plugin != NULL);
	_tmp0_ = new_plugin;
	_tmp1_ = _data1_->plugin;
	on_plugin_available (_tmp0_, (RygelPlugin*) _tmp1_);
}


static void ___lambda8__rygel_plugin_loader_plugin_available (RygelPluginLoader* _sender, RygelPlugin* plugin, gpointer self) {
	__lambda8_ (self, plugin);
}


static gboolean __lambda6_ (Block1Data* _data1_) {
	gboolean result = FALSE;
	RygelPluginLoader* _tmp11_;
	{
		RygelPluginLoader* _tmp0_;
		GeeCollection* _tmp1_ = NULL;
		GeeCollection* _tmp2_;
		GeeIterator* _tmp3_ = NULL;
		GeeIterator* _tmp4_;
		GeeIterator* _loaded_plugin_it;
		_tmp0_ = _data1_->loader;
		_tmp1_ = rygel_plugin_loader_list_plugins (_tmp0_);
		_tmp2_ = _tmp1_;
		_tmp3_ = gee_iterable_iterator ((GeeIterable*) _tmp2_);
		_tmp4_ = _tmp3_;
		_g_object_unref0 (_tmp2_);
		_loaded_plugin_it = _tmp4_;
		while (TRUE) {
			GeeIterator* _tmp5_;
			gboolean _tmp6_ = FALSE;
			GeeIterator* _tmp7_;
			gpointer _tmp8_ = NULL;
			RygelPlugin* loaded_plugin;
			RygelPlugin* _tmp9_;
			RygelMediaExportPlugin* _tmp10_;
			_tmp5_ = _loaded_plugin_it;
			_tmp6_ = gee_iterator_next (_tmp5_);
			if (!_tmp6_) {
				break;
			}
			_tmp7_ = _loaded_plugin_it;
			_tmp8_ = gee_iterator_get (_tmp7_);
			loaded_plugin = (RygelPlugin*) _tmp8_;
			_tmp9_ = loaded_plugin;
			_tmp10_ = _data1_->plugin;
			on_plugin_available (_tmp9_, (RygelPlugin*) _tmp10_);
			_g_object_unref0 (loaded_plugin);
		}
		_g_object_unref0 (_loaded_plugin_it);
	}
	_tmp11_ = _data1_->loader;
	g_signal_connect_data (_tmp11_, "plugin-available", (GCallback) ___lambda8__rygel_plugin_loader_plugin_available, block1_data_ref (_data1_), (GClosureNotify) block1_data_unref, 0);
	result = FALSE;
	return result;
}


static gboolean ___lambda6__gsource_func (gpointer self) {
	gboolean result;
	result = __lambda6_ (self);
	return result;
}


void module_init (RygelPluginLoader* loader) {
	Block1Data* _data1_;
	RygelPluginLoader* _tmp0_;
	RygelPluginLoader* _tmp1_;
	RygelPluginLoader* _tmp2_;
	gboolean _tmp3_ = FALSE;
	RygelPluginLoader* _tmp8_;
	RygelMediaExportPlugin* _tmp9_;
	GError * _inner_error_ = NULL;
	g_return_if_fail (loader != NULL);
	_data1_ = g_slice_new0 (Block1Data);
	_data1_->_ref_count_ = 1;
	_tmp0_ = loader;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_data1_->loader = _tmp1_;
	_tmp2_ = _data1_->loader;
	_tmp3_ = rygel_plugin_loader_plugin_disabled (_tmp2_, RYGEL_MEDIA_EXPORT_PLUGIN_NAME);
	if (_tmp3_) {
		g_message ("rygel-media-export-plugin.vala:32: Plugin '%s' disabled by user, ignor" \
"ing..", RYGEL_MEDIA_EXPORT_PLUGIN_NAME);
		block1_data_unref (_data1_);
		_data1_ = NULL;
		return;
	}
	{
		RygelMediaExportPlugin* _tmp4_;
		RygelMediaExportPlugin* _tmp5_;
		_tmp4_ = rygel_media_export_plugin_new (&_inner_error_);
		_tmp5_ = _tmp4_;
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
		_g_object_unref0 (_data1_->plugin);
		_data1_->plugin = _tmp5_;
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError* _error_ = NULL;
		GError* _tmp6_;
		const gchar* _tmp7_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		_tmp6_ = _error_;
		_tmp7_ = _tmp6_->message;
		g_warning ("rygel-media-export-plugin.vala:43: Failed to initialize plugin '%s': %" \
"s. Ignoring..", RYGEL_MEDIA_EXPORT_PLUGIN_NAME, _tmp7_);
		_g_error_free0 (_error_);
		block1_data_unref (_data1_);
		_data1_ = NULL;
		return;
	}
	__finally0:
	if (_inner_error_ != NULL) {
		block1_data_unref (_data1_);
		_data1_ = NULL;
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, ___lambda6__gsource_func, block1_data_ref (_data1_), block1_data_unref);
	_tmp8_ = _data1_->loader;
	_tmp9_ = _data1_->plugin;
	rygel_plugin_loader_add_plugin (_tmp8_, (RygelPlugin*) _tmp9_);
	block1_data_unref (_data1_);
	_data1_ = NULL;
}


static Block2Data* block2_data_ref (Block2Data* _data2_) {
	g_atomic_int_inc (&_data2_->_ref_count_);
	return _data2_;
}


static void block2_data_unref (void * _userdata_) {
	Block2Data* _data2_;
	_data2_ = (Block2Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data2_->_ref_count_)) {
		_g_object_unref0 (_data2_->plugin);
		_g_object_unref0 (_data2_->our_plugin);
		g_slice_free (Block2Data, _data2_);
	}
}


static void ____lambda7_ (Block2Data* _data2_) {
	RygelPlugin* _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	_tmp0_ = _data2_->plugin;
	_tmp1_ = rygel_plugin_get_active (_tmp0_);
	_tmp2_ = _tmp1_;
	if (_tmp2_) {
		RygelPlugin* _tmp3_;
		RygelPlugin* _tmp4_;
		gboolean _tmp5_;
		gboolean _tmp6_;
		shutdown_media_export ();
		_tmp3_ = _data2_->our_plugin;
		_tmp4_ = _data2_->plugin;
		_tmp5_ = rygel_plugin_get_active (_tmp4_);
		_tmp6_ = _tmp5_;
		rygel_plugin_set_active (_tmp3_, !_tmp6_);
	}
}


static void _____lambda7__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	____lambda7_ (self);
}


void on_plugin_available (RygelPlugin* plugin, RygelPlugin* our_plugin) {
	Block2Data* _data2_;
	RygelPlugin* _tmp0_;
	RygelPlugin* _tmp1_;
	RygelPlugin* _tmp2_;
	RygelPlugin* _tmp3_;
	RygelPlugin* _tmp4_;
	const gchar* _tmp5_;
	g_return_if_fail (plugin != NULL);
	g_return_if_fail (our_plugin != NULL);
	_data2_ = g_slice_new0 (Block2Data);
	_data2_->_ref_count_ = 1;
	_tmp0_ = plugin;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_data2_->plugin = _tmp1_;
	_tmp2_ = our_plugin;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_data2_->our_plugin = _tmp3_;
	_tmp4_ = _data2_->plugin;
	_tmp5_ = _tmp4_->name;
	if (g_strcmp0 (_tmp5_, TRACKER_PLUGIN) == 0) {
		gboolean _tmp6_ = FALSE;
		RygelPlugin* _tmp7_;
		gboolean _tmp8_;
		gboolean _tmp9_;
		gboolean _tmp13_;
		_tmp7_ = _data2_->our_plugin;
		_tmp8_ = rygel_plugin_get_active (_tmp7_);
		_tmp9_ = _tmp8_;
		if (_tmp9_) {
			RygelPlugin* _tmp10_;
			gboolean _tmp11_;
			gboolean _tmp12_;
			_tmp10_ = _data2_->plugin;
			_tmp11_ = rygel_plugin_get_active (_tmp10_);
			_tmp12_ = _tmp11_;
			_tmp6_ = !_tmp12_;
		} else {
			_tmp6_ = FALSE;
		}
		_tmp13_ = _tmp6_;
		if (_tmp13_) {
			RygelPlugin* _tmp14_;
			_tmp14_ = _data2_->plugin;
			g_signal_connect_data ((GObject*) _tmp14_, "notify::active", (GCallback) _____lambda7__g_object_notify, block2_data_ref (_data2_), (GClosureNotify) block2_data_unref, 0);
		} else {
			RygelPlugin* _tmp15_;
			gboolean _tmp16_;
			gboolean _tmp17_;
			RygelPlugin* _tmp18_;
			gboolean _tmp19_;
			gboolean _tmp20_;
			_tmp15_ = _data2_->our_plugin;
			_tmp16_ = rygel_plugin_get_active (_tmp15_);
			_tmp17_ = _tmp16_;
			_tmp18_ = _data2_->plugin;
			_tmp19_ = rygel_plugin_get_active (_tmp18_);
			_tmp20_ = _tmp19_;
			if (_tmp17_ == _tmp20_) {
				RygelPlugin* _tmp21_;
				gboolean _tmp22_;
				gboolean _tmp23_;
				RygelPlugin* _tmp24_;
				RygelPlugin* _tmp25_;
				gboolean _tmp26_;
				gboolean _tmp27_;
				_tmp21_ = _data2_->plugin;
				_tmp22_ = rygel_plugin_get_active (_tmp21_);
				_tmp23_ = _tmp22_;
				if (_tmp23_) {
					shutdown_media_export ();
				} else {
					g_message ("rygel-media-export-plugin.vala:79: Plugin '%s' inactivate, activating " \
"'%s' plugin", TRACKER_PLUGIN, RYGEL_MEDIA_EXPORT_PLUGIN_NAME);
				}
				_tmp24_ = _data2_->our_plugin;
				_tmp25_ = _data2_->plugin;
				_tmp26_ = rygel_plugin_get_active (_tmp25_);
				_tmp27_ = _tmp26_;
				rygel_plugin_set_active (_tmp24_, !_tmp27_);
			}
		}
	}
	block2_data_unref (_data2_);
	_data2_ = NULL;
}


void shutdown_media_export (void) {
	GError * _inner_error_ = NULL;
	g_message ("rygel-media-export-plugin.vala:89: Deactivating plugin '%s' in favor o" \
"f plugin '%s'", RYGEL_MEDIA_EXPORT_PLUGIN_NAME, TRACKER_PLUGIN);
	{
		RygelMetaConfig* _tmp0_ = NULL;
		RygelMetaConfig* config;
		RygelMetaConfig* _tmp1_;
		gboolean _tmp2_ = FALSE;
		gboolean enabled;
		gboolean _tmp3_;
		_tmp0_ = rygel_meta_config_get_default ();
		config = _tmp0_;
		_tmp1_ = config;
		_tmp2_ = rygel_configuration_get_bool ((RygelConfiguration*) _tmp1_, "MediaExport", "enabled", &_inner_error_);
		enabled = _tmp2_;
		if (_inner_error_ != NULL) {
			_g_object_unref0 (config);
			goto __catch1_g_error;
		}
		_tmp3_ = enabled;
		if (_tmp3_) {
			RygelMediaContainer* _tmp4_ = NULL;
			RygelMediaContainer* _tmp5_;
			RygelMediaExportRootContainer* root;
			RygelMediaExportRootContainer* _tmp6_;
			_tmp4_ = rygel_media_export_root_container_get_instance (&_inner_error_);
			_tmp5_ = _tmp4_;
			if (_inner_error_ != NULL) {
				_g_object_unref0 (config);
				goto __catch1_g_error;
			}
			root = RYGEL_MEDIA_EXPORT_IS_ROOT_CONTAINER (_tmp5_) ? ((RygelMediaExportRootContainer*) _tmp5_) : NULL;
			_tmp6_ = root;
			rygel_media_export_root_container_shutdown (_tmp6_);
			_g_object_unref0 (root);
		}
		_g_object_unref0 (config);
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError* _error_ = NULL;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		_g_error_free0 (_error_);
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


RygelMediaExportPlugin* rygel_media_export_plugin_construct (GType object_type, GError** error) {
	RygelMediaExportPlugin * self = NULL;
	RygelMediaContainer* _tmp0_ = NULL;
	RygelMediaContainer* _tmp1_;
	RygelMediaContainer* _tmp2_;
	GError * _inner_error_ = NULL;
	_tmp0_ = rygel_media_export_root_container_get_instance (&_inner_error_);
	_tmp1_ = _tmp0_;
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp2_ = _tmp1_;
	self = (RygelMediaExportPlugin*) rygel_media_server_plugin_construct (object_type, _tmp2_, RYGEL_MEDIA_EXPORT_PLUGIN_NAME, NULL);
	_g_object_unref0 (_tmp2_);
	return self;
}


RygelMediaExportPlugin* rygel_media_export_plugin_new (GError** error) {
	return rygel_media_export_plugin_construct (RYGEL_MEDIA_EXPORT_TYPE_PLUGIN, error);
}


static void rygel_media_export_plugin_class_init (RygelMediaExportPluginClass * klass) {
	rygel_media_export_plugin_parent_class = g_type_class_peek_parent (klass);
}


static void rygel_media_export_plugin_instance_init (RygelMediaExportPlugin * self) {
}


GType rygel_media_export_plugin_get_type (void) {
	static volatile gsize rygel_media_export_plugin_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_media_export_plugin_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaExportPluginClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_export_plugin_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaExportPlugin), 0, (GInstanceInitFunc) rygel_media_export_plugin_instance_init, NULL };
		GType rygel_media_export_plugin_type_id;
		rygel_media_export_plugin_type_id = g_type_register_static (RYGEL_TYPE_MEDIA_SERVER_PLUGIN, "RygelMediaExportPlugin", &g_define_type_info, 0);
		g_once_init_leave (&rygel_media_export_plugin_type_id__volatile, rygel_media_export_plugin_type_id);
	}
	return rygel_media_export_plugin_type_id__volatile;
}



