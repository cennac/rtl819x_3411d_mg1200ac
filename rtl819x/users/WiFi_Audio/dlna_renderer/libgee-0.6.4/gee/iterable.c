/* iterable.c generated by valac 0.15.0.90-e9553, the Vala compiler
 * generated from iterable.vala, do not modify */

/* iterable.vala
 *
 * Copyright (C) 2007-2008  Jürg Billeter
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



GType gee_iterator_get_type (void) G_GNUC_CONST;
GType gee_iterable_get_type (void) G_GNUC_CONST;
GeeIterator* gee_iterable_iterator (GeeIterable* self);
GType gee_iterable_get_element_type (GeeIterable* self);


/**
 * Returns a {@link Iterator} that can be used for simple iteration over a
 * collection.
 *
 * @return a {@link Iterator} that can be used for simple iteration over a
 *         collection
 */
GeeIterator* gee_iterable_iterator (GeeIterable* self) {
	g_return_val_if_fail (self != NULL, NULL);
	return GEE_ITERABLE_GET_INTERFACE (self)->iterator (self);
}


GType gee_iterable_get_element_type (GeeIterable* self) {
	g_return_val_if_fail (self != NULL, 0UL);
	return GEE_ITERABLE_GET_INTERFACE (self)->get_element_type (self);
}


static void gee_iterable_base_init (GeeIterableIface * iface) {
	static gboolean initialized = FALSE;
	if (!initialized) {
		initialized = TRUE;
		/**
		 * The type of the elements in this collection.
		 */
		g_object_interface_install_property (iface, g_param_spec_gtype ("element-type", "element-type", "element-type", G_TYPE_NONE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	}
}


/**
 * An object that can provide an {@link Iterator}.
 */
GType gee_iterable_get_type (void) {
	static volatile gsize gee_iterable_type_id__volatile = 0;
	if (g_once_init_enter (&gee_iterable_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GeeIterableIface), (GBaseInitFunc) gee_iterable_base_init, (GBaseFinalizeFunc) NULL, (GClassInitFunc) NULL, (GClassFinalizeFunc) NULL, NULL, 0, 0, (GInstanceInitFunc) NULL, NULL };
		GType gee_iterable_type_id;
		gee_iterable_type_id = g_type_register_static (G_TYPE_INTERFACE, "GeeIterable", &g_define_type_info, 0);
		g_type_interface_add_prerequisite (gee_iterable_type_id, G_TYPE_OBJECT);
		g_once_init_leave (&gee_iterable_type_id__volatile, gee_iterable_type_id);
	}
	return gee_iterable_type_id__volatile;
}



