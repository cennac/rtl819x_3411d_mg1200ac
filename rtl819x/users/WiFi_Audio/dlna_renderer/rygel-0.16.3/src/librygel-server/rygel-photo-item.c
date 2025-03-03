/* rygel-photo-item.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-photo-item.vala, do not modify */

/*
 * Copyright (C) 2008 Zeeshan Ali <zeenix@gmail.com>.
 * Copyright (C) 2010 Nokia Corporation.
 *
 * Author: Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
 *                               <zeeshan.ali@nokia.com>
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
#include <libgupnp-av/gupnp-av.h>
#include <stdlib.h>
#include <string.h>
#include <gee.h>
#include <gst/gst.h>
#include <rygel-core.h>


#define RYGEL_TYPE_MEDIA_OBJECT (rygel_media_object_get_type ())
#define RYGEL_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObject))
#define RYGEL_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))
#define RYGEL_IS_MEDIA_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_IS_MEDIA_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_OBJECT))
#define RYGEL_MEDIA_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_OBJECT, RygelMediaObjectClass))

typedef struct _RygelMediaObject RygelMediaObject;
typedef struct _RygelMediaObjectClass RygelMediaObjectClass;
typedef struct _RygelMediaObjectPrivate RygelMediaObjectPrivate;

#define RYGEL_TYPE_TRANSCODE_MANAGER (rygel_transcode_manager_get_type ())
#define RYGEL_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManager))
#define RYGEL_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))
#define RYGEL_IS_TRANSCODE_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_IS_TRANSCODE_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_TRANSCODE_MANAGER))
#define RYGEL_TRANSCODE_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_TRANSCODE_MANAGER, RygelTranscodeManagerClass))

typedef struct _RygelTranscodeManager RygelTranscodeManager;
typedef struct _RygelTranscodeManagerClass RygelTranscodeManagerClass;

#define RYGEL_TYPE_HTTP_SERVER (rygel_http_server_get_type ())
#define RYGEL_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServer))
#define RYGEL_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))
#define RYGEL_IS_HTTP_SERVER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_IS_HTTP_SERVER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_HTTP_SERVER))
#define RYGEL_HTTP_SERVER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_HTTP_SERVER, RygelHTTPServerClass))

typedef struct _RygelHTTPServer RygelHTTPServer;
typedef struct _RygelHTTPServerClass RygelHTTPServerClass;

#define RYGEL_TYPE_MEDIA_CONTAINER (rygel_media_container_get_type ())
#define RYGEL_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainer))
#define RYGEL_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))
#define RYGEL_IS_MEDIA_CONTAINER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_IS_MEDIA_CONTAINER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_CONTAINER))
#define RYGEL_MEDIA_CONTAINER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_CONTAINER, RygelMediaContainerClass))

typedef struct _RygelMediaContainer RygelMediaContainer;
typedef struct _RygelMediaContainerClass RygelMediaContainerClass;

#define RYGEL_TYPE_MEDIA_ITEM (rygel_media_item_get_type ())
#define RYGEL_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItem))
#define RYGEL_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))
#define RYGEL_IS_MEDIA_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_IS_MEDIA_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_MEDIA_ITEM))
#define RYGEL_MEDIA_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_MEDIA_ITEM, RygelMediaItemClass))

typedef struct _RygelMediaItem RygelMediaItem;
typedef struct _RygelMediaItemClass RygelMediaItemClass;
typedef struct _RygelMediaItemPrivate RygelMediaItemPrivate;

#define RYGEL_TYPE_VISUAL_ITEM (rygel_visual_item_get_type ())
#define RYGEL_VISUAL_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_VISUAL_ITEM, RygelVisualItem))
#define RYGEL_IS_VISUAL_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_VISUAL_ITEM))
#define RYGEL_VISUAL_ITEM_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_VISUAL_ITEM, RygelVisualItemIface))

typedef struct _RygelVisualItem RygelVisualItem;
typedef struct _RygelVisualItemIface RygelVisualItemIface;

#define RYGEL_TYPE_THUMBNAIL (rygel_thumbnail_get_type ())
#define RYGEL_THUMBNAIL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_THUMBNAIL, RygelThumbnail))
#define RYGEL_THUMBNAIL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_THUMBNAIL, RygelThumbnailClass))
#define RYGEL_IS_THUMBNAIL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_THUMBNAIL))
#define RYGEL_IS_THUMBNAIL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_THUMBNAIL))
#define RYGEL_THUMBNAIL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_THUMBNAIL, RygelThumbnailClass))

typedef struct _RygelThumbnail RygelThumbnail;
typedef struct _RygelThumbnailClass RygelThumbnailClass;

#define RYGEL_TYPE_IMAGE_ITEM (rygel_image_item_get_type ())
#define RYGEL_IMAGE_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_IMAGE_ITEM, RygelImageItem))
#define RYGEL_IMAGE_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_IMAGE_ITEM, RygelImageItemClass))
#define RYGEL_IS_IMAGE_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_IMAGE_ITEM))
#define RYGEL_IS_IMAGE_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_IMAGE_ITEM))
#define RYGEL_IMAGE_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_IMAGE_ITEM, RygelImageItemClass))

typedef struct _RygelImageItem RygelImageItem;
typedef struct _RygelImageItemClass RygelImageItemClass;
typedef struct _RygelImageItemPrivate RygelImageItemPrivate;

#define RYGEL_TYPE_PHOTO_ITEM (rygel_photo_item_get_type ())
#define RYGEL_PHOTO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_PHOTO_ITEM, RygelPhotoItem))
#define RYGEL_PHOTO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TYPE_PHOTO_ITEM, RygelPhotoItemClass))
#define RYGEL_IS_PHOTO_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_PHOTO_ITEM))
#define RYGEL_IS_PHOTO_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TYPE_PHOTO_ITEM))
#define RYGEL_PHOTO_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TYPE_PHOTO_ITEM, RygelPhotoItemClass))

typedef struct _RygelPhotoItem RygelPhotoItem;
typedef struct _RygelPhotoItemClass RygelPhotoItemClass;
typedef struct _RygelPhotoItemPrivate RygelPhotoItemPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _RygelMediaObject {
	GObject parent_instance;
	RygelMediaObjectPrivate * priv;
	gchar* id;
	gchar* ref_id;
	gchar* upnp_class;
	guint64 modified;
	GeeArrayList* uris;
	RygelMediaContainer* parent;
};

struct _RygelMediaObjectClass {
	GObjectClass parent_class;
	GUPnPDIDLLiteObject* (*serialize) (RygelMediaObject* self, GUPnPDIDLLiteWriter* writer, RygelHTTPServer* http_server, GError** error);
	gint (*compare_by_property) (RygelMediaObject* self, RygelMediaObject* media_object, const gchar* property);
	GUPnPOCMFlags (*get_ocm_flags) (RygelMediaObject* self);
};

struct _RygelMediaItem {
	RygelMediaObject parent_instance;
	RygelMediaItemPrivate * priv;
	gchar* date;
	gchar* mime_type;
	gchar* dlna_profile;
	GRegex* address_regex;
};

struct _RygelMediaItemClass {
	RygelMediaObjectClass parent_class;
	GstElement* (*create_stream_source) (RygelMediaItem* self, const gchar* host_ip);
	gboolean (*streamable) (RygelMediaItem* self);
	void (*add_uri) (RygelMediaItem* self, const gchar* uri);
	GUPnPDIDLLiteResource* (*add_resource) (RygelMediaItem* self, GUPnPDIDLLiteItem* didl_item, const gchar* uri, const gchar* protocol, const gchar* import_uri, GError** error);
	void (*add_proxy_resources) (RygelMediaItem* self, RygelHTTPServer* server, GUPnPDIDLLiteItem* didl_item, GError** error);
	GUPnPProtocolInfo* (*get_protocol_info) (RygelMediaItem* self, const gchar* uri, const gchar* protocol);
	void (*add_resources) (RygelMediaItem* self, GUPnPDIDLLiteItem* didl_item, gboolean allow_internal, GError** error);
};

struct _RygelVisualItemIface {
	GTypeInterface parent_iface;
	gint (*get_width) (RygelVisualItem* self);
	void (*set_width) (RygelVisualItem* self, gint value);
	gint (*get_height) (RygelVisualItem* self);
	void (*set_height) (RygelVisualItem* self, gint value);
	gint (*get_pixel_width) (RygelVisualItem* self);
	void (*set_pixel_width) (RygelVisualItem* self, gint value);
	gint (*get_pixel_height) (RygelVisualItem* self);
	void (*set_pixel_height) (RygelVisualItem* self, gint value);
	gint (*get_color_depth) (RygelVisualItem* self);
	void (*set_color_depth) (RygelVisualItem* self, gint value);
	GeeArrayList* (*get_thumbnails) (RygelVisualItem* self);
	void (*set_thumbnails) (RygelVisualItem* self, GeeArrayList* value);
};

struct _RygelImageItem {
	RygelMediaItem parent_instance;
	RygelImageItemPrivate * priv;
};

struct _RygelImageItemClass {
	RygelMediaItemClass parent_class;
};

struct _RygelPhotoItem {
	RygelImageItem parent_instance;
	RygelPhotoItemPrivate * priv;
	gchar* creator;
};

struct _RygelPhotoItemClass {
	RygelImageItemClass parent_class;
};


static gpointer rygel_photo_item_parent_class = NULL;

GType rygel_media_object_get_type (void) G_GNUC_CONST;
GType rygel_transcode_manager_get_type (void) G_GNUC_CONST;
GType rygel_http_server_get_type (void) G_GNUC_CONST;
GType rygel_media_container_get_type (void) G_GNUC_CONST;
GType rygel_media_item_get_type (void) G_GNUC_CONST;
GType rygel_thumbnail_get_type (void) G_GNUC_CONST;
GType rygel_visual_item_get_type (void) G_GNUC_CONST;
GType rygel_image_item_get_type (void) G_GNUC_CONST;
GType rygel_photo_item_get_type (void) G_GNUC_CONST;
enum  {
	RYGEL_PHOTO_ITEM_DUMMY_PROPERTY
};
#define RYGEL_PHOTO_ITEM_UPNP_CLASS "object.item.imageItem.photo"
RygelPhotoItem* rygel_photo_item_new (const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class);
RygelPhotoItem* rygel_photo_item_construct (GType object_type, const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class);
RygelImageItem* rygel_image_item_new (const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class);
RygelImageItem* rygel_image_item_construct (GType object_type, const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class);
static gint rygel_photo_item_real_compare_by_property (RygelMediaObject* base, RygelMediaObject* media_object, const gchar* property);
gint rygel_media_object_compare_string_props (RygelMediaObject* self, const gchar* prop1, const gchar* prop2);
gint rygel_media_object_compare_by_property (RygelMediaObject* self, RygelMediaObject* media_object, const gchar* property);
static GUPnPDIDLLiteObject* rygel_photo_item_real_serialize (RygelMediaObject* base, GUPnPDIDLLiteWriter* writer, RygelHTTPServer* http_server, GError** error);
GUPnPDIDLLiteObject* rygel_media_object_serialize (RygelMediaObject* self, GUPnPDIDLLiteWriter* writer, RygelHTTPServer* http_server, GError** error);
static void rygel_photo_item_finalize (GObject* obj);


RygelPhotoItem* rygel_photo_item_construct (GType object_type, const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class) {
	RygelPhotoItem * self = NULL;
	const gchar* _tmp0_;
	RygelMediaContainer* _tmp1_;
	const gchar* _tmp2_;
	const gchar* _tmp3_;
	g_return_val_if_fail (id != NULL, NULL);
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (upnp_class != NULL, NULL);
	_tmp0_ = id;
	_tmp1_ = parent;
	_tmp2_ = title;
	_tmp3_ = upnp_class;
	self = (RygelPhotoItem*) rygel_image_item_construct (object_type, _tmp0_, _tmp1_, _tmp2_, _tmp3_);
	return self;
}


RygelPhotoItem* rygel_photo_item_new (const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class) {
	return rygel_photo_item_construct (RYGEL_TYPE_PHOTO_ITEM, id, parent, title, upnp_class);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static gint rygel_photo_item_real_compare_by_property (RygelMediaObject* base, RygelMediaObject* media_object, const gchar* property) {
	RygelPhotoItem * self;
	gint result = 0;
	RygelMediaObject* _tmp0_;
	RygelMediaObject* _tmp1_;
	RygelPhotoItem* _tmp2_;
	RygelPhotoItem* item;
	const gchar* _tmp3_;
	const gchar* _tmp4_;
	GQuark _tmp6_ = 0U;
	static GQuark _tmp5_label0 = 0;
	self = (RygelPhotoItem*) base;
	g_return_val_if_fail (media_object != NULL, 0);
	g_return_val_if_fail (property != NULL, 0);
	_tmp0_ = media_object;
	if (!RYGEL_IS_PHOTO_ITEM (_tmp0_)) {
		result = 1;
		return result;
	}
	_tmp1_ = media_object;
	_tmp2_ = _g_object_ref0 (RYGEL_IS_PHOTO_ITEM (_tmp1_) ? ((RygelPhotoItem*) _tmp1_) : NULL);
	item = _tmp2_;
	_tmp3_ = property;
	_tmp4_ = _tmp3_;
	_tmp6_ = (NULL == _tmp4_) ? 0 : g_quark_from_string (_tmp4_);
	if (_tmp6_ == ((0 != _tmp5_label0) ? _tmp5_label0 : (_tmp5_label0 = g_quark_from_static_string ("dc:creator")))) {
		switch (0) {
			default:
			{
				const gchar* _tmp7_;
				RygelPhotoItem* _tmp8_;
				const gchar* _tmp9_;
				gint _tmp10_ = 0;
				_tmp7_ = self->creator;
				_tmp8_ = item;
				_tmp9_ = _tmp8_->creator;
				_tmp10_ = rygel_media_object_compare_string_props ((RygelMediaObject*) self, _tmp7_, _tmp9_);
				result = _tmp10_;
				_g_object_unref0 (item);
				return result;
			}
		}
	} else {
		switch (0) {
			default:
			{
				RygelPhotoItem* _tmp11_;
				const gchar* _tmp12_;
				gint _tmp13_ = 0;
				_tmp11_ = item;
				_tmp12_ = property;
				_tmp13_ = RYGEL_MEDIA_OBJECT_CLASS (rygel_photo_item_parent_class)->compare_by_property ((RygelMediaObject*) RYGEL_IMAGE_ITEM (self), (RygelMediaObject*) _tmp11_, _tmp12_);
				result = _tmp13_;
				_g_object_unref0 (item);
				return result;
			}
		}
	}
	_g_object_unref0 (item);
}


static GUPnPDIDLLiteObject* rygel_photo_item_real_serialize (RygelMediaObject* base, GUPnPDIDLLiteWriter* writer, RygelHTTPServer* http_server, GError** error) {
	RygelPhotoItem * self;
	GUPnPDIDLLiteObject* result = NULL;
	GUPnPDIDLLiteWriter* _tmp0_;
	RygelHTTPServer* _tmp1_;
	GUPnPDIDLLiteObject* _tmp2_ = NULL;
	GUPnPDIDLLiteObject* didl_item;
	gboolean _tmp3_ = FALSE;
	const gchar* _tmp4_;
	gboolean _tmp6_;
	GError * _inner_error_ = NULL;
	self = (RygelPhotoItem*) base;
	g_return_val_if_fail (writer != NULL, NULL);
	g_return_val_if_fail (http_server != NULL, NULL);
	_tmp0_ = writer;
	_tmp1_ = http_server;
	_tmp2_ = RYGEL_MEDIA_OBJECT_CLASS (rygel_photo_item_parent_class)->serialize ((RygelMediaObject*) RYGEL_IMAGE_ITEM (self), _tmp0_, _tmp1_, &_inner_error_);
	didl_item = _tmp2_;
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return NULL;
	}
	_tmp4_ = self->creator;
	if (_tmp4_ != NULL) {
		const gchar* _tmp5_;
		_tmp5_ = self->creator;
		_tmp3_ = g_strcmp0 (_tmp5_, "") != 0;
	} else {
		_tmp3_ = FALSE;
	}
	_tmp6_ = _tmp3_;
	if (_tmp6_) {
		GUPnPDIDLLiteContributor* _tmp7_ = NULL;
		GUPnPDIDLLiteContributor* contributor;
		GUPnPDIDLLiteContributor* _tmp8_;
		const gchar* _tmp9_;
		_tmp7_ = gupnp_didl_lite_object_add_creator (didl_item);
		contributor = _tmp7_;
		_tmp8_ = contributor;
		_tmp9_ = self->creator;
		gupnp_didl_lite_contributor_set_name (_tmp8_, _tmp9_);
		_g_object_unref0 (contributor);
	}
	result = didl_item;
	return result;
}


static void rygel_photo_item_class_init (RygelPhotoItemClass * klass) {
	rygel_photo_item_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_OBJECT_CLASS (klass)->compare_by_property = rygel_photo_item_real_compare_by_property;
	RYGEL_MEDIA_OBJECT_CLASS (klass)->serialize = rygel_photo_item_real_serialize;
	G_OBJECT_CLASS (klass)->finalize = rygel_photo_item_finalize;
}


static void rygel_photo_item_instance_init (RygelPhotoItem * self) {
}


static void rygel_photo_item_finalize (GObject* obj) {
	RygelPhotoItem * self;
	self = RYGEL_PHOTO_ITEM (obj);
	_g_free0 (self->creator);
	G_OBJECT_CLASS (rygel_photo_item_parent_class)->finalize (obj);
}


/**
 * Represents a photo item.
 */
GType rygel_photo_item_get_type (void) {
	static volatile gsize rygel_photo_item_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_photo_item_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelPhotoItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_photo_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelPhotoItem), 0, (GInstanceInitFunc) rygel_photo_item_instance_init, NULL };
		GType rygel_photo_item_type_id;
		rygel_photo_item_type_id = g_type_register_static (RYGEL_TYPE_IMAGE_ITEM, "RygelPhotoItem", &g_define_type_info, 0);
		g_once_init_leave (&rygel_photo_item_type_id__volatile, rygel_photo_item_type_id);
	}
	return rygel_photo_item_type_id__volatile;
}



