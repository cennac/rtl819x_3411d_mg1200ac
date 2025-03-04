/* rygel-state-machine_item-creator.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-state-machine_item-creator.vala, do not modify */

/*
 * Copyright (C) 2008, 2009 Nokia Corporation.
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
#include <gio/gio.h>


#define RYGEL_TYPE_STATE_MACHINE (rygel_state_machine_get_type ())
#define RYGEL_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachine))
#define RYGEL_IS_STATE_MACHINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TYPE_STATE_MACHINE))
#define RYGEL_STATE_MACHINE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), RYGEL_TYPE_STATE_MACHINE, RygelStateMachineIface))

typedef struct _RygelStateMachine RygelStateMachine;
typedef struct _RygelStateMachineIface RygelStateMachineIface;

struct _RygelStateMachineIface {
	GTypeInterface parent_iface;
	void (*run) (RygelStateMachine* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
	void (*run_finish) (RygelStateMachine* self, GAsyncResult* _res_);
	GCancellable* (*get_cancellable) (RygelStateMachine* self);
	void (*set_cancellable) (RygelStateMachine* self, GCancellable* value);
};



GType rygel_state_machine_get_type (void) G_GNUC_CONST;
void rygel_state_machine_run (RygelStateMachine* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
void rygel_state_machine_run_finish (RygelStateMachine* self, GAsyncResult* _res_);
GCancellable* rygel_state_machine_get_cancellable (RygelStateMachine* self);
void rygel_state_machine_set_cancellable (RygelStateMachine* self, GCancellable* value);


void rygel_state_machine_run (RygelStateMachine* self, GAsyncReadyCallback _callback_, gpointer _user_data_) {
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	RYGEL_STATE_MACHINE_GET_INTERFACE (self)->run (self, _callback_, _user_data_);
#line 61 "rygel-state-machine_item-creator.c"
}


void rygel_state_machine_run_finish (RygelStateMachine* self, GAsyncResult* _res_) {
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	RYGEL_STATE_MACHINE_GET_INTERFACE (self)->run_finish (self, _res_);
#line 68 "rygel-state-machine_item-creator.c"
}


GCancellable* rygel_state_machine_get_cancellable (RygelStateMachine* self) {
#line 32 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 32 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	return RYGEL_STATE_MACHINE_GET_INTERFACE (self)->get_cancellable (self);
#line 77 "rygel-state-machine_item-creator.c"
}


void rygel_state_machine_set_cancellable (RygelStateMachine* self, GCancellable* value) {
#line 32 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	g_return_if_fail (self != NULL);
#line 32 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	RYGEL_STATE_MACHINE_GET_INTERFACE (self)->set_cancellable (self, value);
#line 86 "rygel-state-machine_item-creator.c"
}


static void rygel_state_machine_base_init (RygelStateMachineIface * iface) {
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	static gboolean initialized = FALSE;
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
	if (!initialized) {
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
		initialized = TRUE;
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
		g_object_interface_install_property (iface, g_param_spec_object ("cancellable", "cancellable", "cancellable", G_TYPE_CANCELLABLE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
#line 27 "/home/jens/Source/rygel/tests/rygel-state-machine_item-creator.vala"
		g_signal_new ("completed", RYGEL_TYPE_STATE_MACHINE, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
#line 101 "rygel-state-machine_item-creator.c"
	}
}


/**
 * StateMachine interface.
 */
GType rygel_state_machine_get_type (void) {
	static volatile gsize rygel_state_machine_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_state_machine_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelStateMachineIface), (GBaseInitFunc) rygel_state_machine_base_init, (GBaseFinalizeFunc) NULL, (GClassInitFunc) NULL, (GClassFinalizeFunc) NULL, NULL, 0, 0, (GInstanceInitFunc) NULL, NULL };
		GType rygel_state_machine_type_id;
		rygel_state_machine_type_id = g_type_register_static (G_TYPE_INTERFACE, "RygelStateMachine", &g_define_type_info, 0);
		g_type_interface_add_prerequisite (rygel_state_machine_type_id, G_TYPE_OBJECT);
		g_once_init_leave (&rygel_state_machine_type_id__volatile, rygel_state_machine_type_id);
	}
	return rygel_state_machine_type_id__volatile;
}



