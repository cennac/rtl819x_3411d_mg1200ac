/* rygel-media-export-music-item.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-media-export-music-item.vala, do not modify */

/*
 * Copyright (C) 2012 Jens Georg <mail@jensge.org>.
 *
 * Author: Jens Georg <mail@jensge.org>
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
#include <stdlib.h>
#include <string.h>


#define RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM (rygel_media_export_music_item_get_type ())
#define RYGEL_MEDIA_EXPORT_MUSIC_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM, RygelMediaExportMusicItem))
#define RYGEL_MEDIA_EXPORT_MUSIC_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM, RygelMediaExportMusicItemClass))
#define RYGEL_MEDIA_EXPORT_IS_MUSIC_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM))
#define RYGEL_MEDIA_EXPORT_IS_MUSIC_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM))
#define RYGEL_MEDIA_EXPORT_MUSIC_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM, RygelMediaExportMusicItemClass))

typedef struct _RygelMediaExportMusicItem RygelMediaExportMusicItem;
typedef struct _RygelMediaExportMusicItemClass RygelMediaExportMusicItemClass;
typedef struct _RygelMediaExportMusicItemPrivate RygelMediaExportMusicItemPrivate;

struct _RygelMediaExportMusicItem {
	RygelMusicItem parent_instance;
	RygelMediaExportMusicItemPrivate * priv;
	gint disc;
};

struct _RygelMediaExportMusicItemClass {
	RygelMusicItemClass parent_class;
};


static gpointer rygel_media_export_music_item_parent_class = NULL;

GType rygel_media_export_music_item_get_type (void) G_GNUC_CONST;
enum  {
	RYGEL_MEDIA_EXPORT_MUSIC_ITEM_DUMMY_PROPERTY
};
RygelMediaExportMusicItem* rygel_media_export_music_item_new (const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class);
RygelMediaExportMusicItem* rygel_media_export_music_item_construct (GType object_type, const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class);
static void rygel_media_export_music_item_finalize (GObject* obj);


RygelMediaExportMusicItem* rygel_media_export_music_item_construct (GType object_type, const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class) {
	RygelMediaExportMusicItem * self = NULL;
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
	self = (RygelMediaExportMusicItem*) rygel_music_item_construct (object_type, _tmp0_, _tmp1_, _tmp2_, _tmp3_);
	return self;
}


RygelMediaExportMusicItem* rygel_media_export_music_item_new (const gchar* id, RygelMediaContainer* parent, const gchar* title, const gchar* upnp_class) {
	return rygel_media_export_music_item_construct (RYGEL_MEDIA_EXPORT_TYPE_MUSIC_ITEM, id, parent, title, upnp_class);
}


static void rygel_media_export_music_item_class_init (RygelMediaExportMusicItemClass * klass) {
	rygel_media_export_music_item_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = rygel_media_export_music_item_finalize;
}


static void rygel_media_export_music_item_instance_init (RygelMediaExportMusicItem * self) {
}


static void rygel_media_export_music_item_finalize (GObject* obj) {
	RygelMediaExportMusicItem * self;
	self = RYGEL_MEDIA_EXPORT_MUSIC_ITEM (obj);
	G_OBJECT_CLASS (rygel_media_export_music_item_parent_class)->finalize (obj);
}


/**
 * Own MusicItem class to provide disc number inside music item for sorting
 * and metadata extraction.
 */
GType rygel_media_export_music_item_get_type (void) {
	static volatile gsize rygel_media_export_music_item_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_media_export_music_item_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaExportMusicItemClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_export_music_item_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaExportMusicItem), 0, (GInstanceInitFunc) rygel_media_export_music_item_instance_init, NULL };
		GType rygel_media_export_music_item_type_id;
		rygel_media_export_music_item_type_id = g_type_register_static (RYGEL_TYPE_MUSIC_ITEM, "RygelMediaExportMusicItem", &g_define_type_info, 0);
		g_once_init_leave (&rygel_media_export_music_item_type_id__volatile, rygel_media_export_music_item_type_id);
	}
	return rygel_media_export_music_item_type_id__volatile;
}



