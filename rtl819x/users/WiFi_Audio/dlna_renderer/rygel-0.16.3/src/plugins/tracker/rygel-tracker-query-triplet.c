/* rygel-tracker-query-triplet.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-tracker-query-triplet.vala, do not modify */

/*
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Author: Zeeshan Ali <zeenix@gmail.com>
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
#include <gobject/gvaluecollector.h>


#define RYGEL_TRACKER_TYPE_QUERY_TRIPLET (rygel_tracker_query_triplet_get_type ())
#define RYGEL_TRACKER_QUERY_TRIPLET(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_TRACKER_TYPE_QUERY_TRIPLET, RygelTrackerQueryTriplet))
#define RYGEL_TRACKER_QUERY_TRIPLET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_TRACKER_TYPE_QUERY_TRIPLET, RygelTrackerQueryTripletClass))
#define RYGEL_TRACKER_IS_QUERY_TRIPLET(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_TRACKER_TYPE_QUERY_TRIPLET))
#define RYGEL_TRACKER_IS_QUERY_TRIPLET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_TRACKER_TYPE_QUERY_TRIPLET))
#define RYGEL_TRACKER_QUERY_TRIPLET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_TRACKER_TYPE_QUERY_TRIPLET, RygelTrackerQueryTripletClass))

typedef struct _RygelTrackerQueryTriplet RygelTrackerQueryTriplet;
typedef struct _RygelTrackerQueryTripletClass RygelTrackerQueryTripletClass;
typedef struct _RygelTrackerQueryTripletPrivate RygelTrackerQueryTripletPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _rygel_tracker_query_triplet_unref0(var) ((var == NULL) ? NULL : (var = (rygel_tracker_query_triplet_unref (var), NULL)))
typedef struct _RygelTrackerParamSpecQueryTriplet RygelTrackerParamSpecQueryTriplet;

struct _RygelTrackerQueryTriplet {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelTrackerQueryTripletPrivate * priv;
	gchar* graph;
	gchar* subject;
	gchar* predicate;
	gchar* obj;
	RygelTrackerQueryTriplet* next;
};

struct _RygelTrackerQueryTripletClass {
	GTypeClass parent_class;
	void (*finalize) (RygelTrackerQueryTriplet *self);
};

struct _RygelTrackerParamSpecQueryTriplet {
	GParamSpec parent_instance;
};


static gpointer rygel_tracker_query_triplet_parent_class = NULL;

gpointer rygel_tracker_query_triplet_ref (gpointer instance);
void rygel_tracker_query_triplet_unref (gpointer instance);
GParamSpec* rygel_tracker_param_spec_query_triplet (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_tracker_value_set_query_triplet (GValue* value, gpointer v_object);
void rygel_tracker_value_take_query_triplet (GValue* value, gpointer v_object);
gpointer rygel_tracker_value_get_query_triplet (const GValue* value);
GType rygel_tracker_query_triplet_get_type (void) G_GNUC_CONST;
enum  {
	RYGEL_TRACKER_QUERY_TRIPLET_DUMMY_PROPERTY
};
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new (const gchar* subject, const gchar* predicate, const gchar* obj);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct (GType object_type, const gchar* subject, const gchar* predicate, const gchar* obj);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new_with_graph (const gchar* graph, const gchar* subject, const gchar* predicate, const gchar* object);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct_with_graph (GType object_type, const gchar* graph, const gchar* subject, const gchar* predicate, const gchar* object);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new_chain (const gchar* subject, const gchar* predicate, RygelTrackerQueryTriplet* next);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct_chain (GType object_type, const gchar* subject, const gchar* predicate, RygelTrackerQueryTriplet* next);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new_clone (RygelTrackerQueryTriplet* triplet);
RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct_clone (GType object_type, RygelTrackerQueryTriplet* triplet);
gboolean rygel_tracker_query_triplet_equal_func (RygelTrackerQueryTriplet* a, RygelTrackerQueryTriplet* b);
gchar* rygel_tracker_query_triplet_to_string (RygelTrackerQueryTriplet* self, gboolean include_subject);
static void rygel_tracker_query_triplet_finalize (RygelTrackerQueryTriplet* obj);


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct (GType object_type, const gchar* subject, const gchar* predicate, const gchar* obj) {
	RygelTrackerQueryTriplet* self = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_;
	const gchar* _tmp2_;
	gchar* _tmp3_;
	const gchar* _tmp4_;
	gchar* _tmp5_;
	g_return_val_if_fail (subject != NULL, NULL);
	g_return_val_if_fail (predicate != NULL, NULL);
	g_return_val_if_fail (obj != NULL, NULL);
	self = (RygelTrackerQueryTriplet*) g_type_create_instance (object_type);
	_g_free0 (self->graph);
	self->graph = NULL;
	_tmp0_ = subject;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->subject);
	self->subject = _tmp1_;
	_tmp2_ = predicate;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->predicate);
	self->predicate = _tmp3_;
	_tmp4_ = obj;
	_tmp5_ = g_strdup (_tmp4_);
	_g_free0 (self->obj);
	self->obj = _tmp5_;
	return self;
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new (const gchar* subject, const gchar* predicate, const gchar* obj) {
	return rygel_tracker_query_triplet_construct (RYGEL_TRACKER_TYPE_QUERY_TRIPLET, subject, predicate, obj);
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct_with_graph (GType object_type, const gchar* graph, const gchar* subject, const gchar* predicate, const gchar* object) {
	RygelTrackerQueryTriplet* self = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_;
	const gchar* _tmp2_;
	gchar* _tmp3_;
	const gchar* _tmp4_;
	gchar* _tmp5_;
	const gchar* _tmp6_;
	gchar* _tmp7_;
	g_return_val_if_fail (graph != NULL, NULL);
	g_return_val_if_fail (subject != NULL, NULL);
	g_return_val_if_fail (predicate != NULL, NULL);
	g_return_val_if_fail (object != NULL, NULL);
	self = (RygelTrackerQueryTriplet*) g_type_create_instance (object_type);
	_tmp0_ = graph;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->graph);
	self->graph = _tmp1_;
	_tmp2_ = subject;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->subject);
	self->subject = _tmp3_;
	_tmp4_ = predicate;
	_tmp5_ = g_strdup (_tmp4_);
	_g_free0 (self->predicate);
	self->predicate = _tmp5_;
	_tmp6_ = object;
	_tmp7_ = g_strdup (_tmp6_);
	_g_free0 (self->obj);
	self->obj = _tmp7_;
	return self;
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new_with_graph (const gchar* graph, const gchar* subject, const gchar* predicate, const gchar* object) {
	return rygel_tracker_query_triplet_construct_with_graph (RYGEL_TRACKER_TYPE_QUERY_TRIPLET, graph, subject, predicate, object);
}


static gpointer _rygel_tracker_query_triplet_ref0 (gpointer self) {
	return self ? rygel_tracker_query_triplet_ref (self) : NULL;
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct_chain (GType object_type, const gchar* subject, const gchar* predicate, RygelTrackerQueryTriplet* next) {
	RygelTrackerQueryTriplet* self = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_;
	const gchar* _tmp2_;
	gchar* _tmp3_;
	RygelTrackerQueryTriplet* _tmp4_;
	RygelTrackerQueryTriplet* _tmp5_;
	g_return_val_if_fail (subject != NULL, NULL);
	g_return_val_if_fail (predicate != NULL, NULL);
	g_return_val_if_fail (next != NULL, NULL);
	self = (RygelTrackerQueryTriplet*) g_type_create_instance (object_type);
	_tmp0_ = subject;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->subject);
	self->subject = _tmp1_;
	_tmp2_ = predicate;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->predicate);
	self->predicate = _tmp3_;
	_tmp4_ = next;
	_tmp5_ = _rygel_tracker_query_triplet_ref0 (_tmp4_);
	_rygel_tracker_query_triplet_unref0 (self->next);
	self->next = _tmp5_;
	return self;
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new_chain (const gchar* subject, const gchar* predicate, RygelTrackerQueryTriplet* next) {
	return rygel_tracker_query_triplet_construct_chain (RYGEL_TRACKER_TYPE_QUERY_TRIPLET, subject, predicate, next);
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_construct_clone (GType object_type, RygelTrackerQueryTriplet* triplet) {
	RygelTrackerQueryTriplet* self = NULL;
	RygelTrackerQueryTriplet* _tmp0_;
	const gchar* _tmp1_;
	gchar* _tmp2_;
	RygelTrackerQueryTriplet* _tmp3_;
	const gchar* _tmp4_;
	gchar* _tmp5_;
	RygelTrackerQueryTriplet* _tmp6_;
	const gchar* _tmp7_;
	gchar* _tmp8_;
	RygelTrackerQueryTriplet* _tmp9_;
	RygelTrackerQueryTriplet* _tmp10_;
	g_return_val_if_fail (triplet != NULL, NULL);
	self = (RygelTrackerQueryTriplet*) g_type_create_instance (object_type);
	_tmp0_ = triplet;
	_tmp1_ = _tmp0_->graph;
	_tmp2_ = g_strdup (_tmp1_);
	_g_free0 (self->graph);
	self->graph = _tmp2_;
	_tmp3_ = triplet;
	_tmp4_ = _tmp3_->subject;
	_tmp5_ = g_strdup (_tmp4_);
	_g_free0 (self->subject);
	self->subject = _tmp5_;
	_tmp6_ = triplet;
	_tmp7_ = _tmp6_->predicate;
	_tmp8_ = g_strdup (_tmp7_);
	_g_free0 (self->predicate);
	self->predicate = _tmp8_;
	_tmp9_ = triplet;
	_tmp10_ = _tmp9_->next;
	if (_tmp10_ != NULL) {
		RygelTrackerQueryTriplet* _tmp11_;
		RygelTrackerQueryTriplet* _tmp12_;
		RygelTrackerQueryTriplet* _tmp13_;
		_tmp11_ = triplet;
		_tmp12_ = _tmp11_->next;
		_tmp13_ = _rygel_tracker_query_triplet_ref0 (_tmp12_);
		_rygel_tracker_query_triplet_unref0 (self->next);
		self->next = _tmp13_;
	} else {
		RygelTrackerQueryTriplet* _tmp14_;
		const gchar* _tmp15_;
		gchar* _tmp16_;
		_tmp14_ = triplet;
		_tmp15_ = _tmp14_->obj;
		_tmp16_ = g_strdup (_tmp15_);
		_g_free0 (self->obj);
		self->obj = _tmp16_;
	}
	return self;
}


RygelTrackerQueryTriplet* rygel_tracker_query_triplet_new_clone (RygelTrackerQueryTriplet* triplet) {
	return rygel_tracker_query_triplet_construct_clone (RYGEL_TRACKER_TYPE_QUERY_TRIPLET, triplet);
}


gboolean rygel_tracker_query_triplet_equal_func (RygelTrackerQueryTriplet* a, RygelTrackerQueryTriplet* b) {
	gboolean result = FALSE;
	gboolean chain_equal = FALSE;
	gboolean _tmp0_ = FALSE;
	RygelTrackerQueryTriplet* _tmp1_;
	RygelTrackerQueryTriplet* _tmp2_;
	gboolean _tmp5_;
	gboolean _tmp15_ = FALSE;
	gboolean _tmp16_ = FALSE;
	gboolean _tmp17_ = FALSE;
	gboolean _tmp18_ = FALSE;
	RygelTrackerQueryTriplet* _tmp19_;
	const gchar* _tmp20_;
	RygelTrackerQueryTriplet* _tmp21_;
	const gchar* _tmp22_;
	gboolean _tmp27_;
	gboolean _tmp32_;
	gboolean _tmp37_;
	gboolean _tmp39_;
	g_return_val_if_fail (a != NULL, FALSE);
	g_return_val_if_fail (b != NULL, FALSE);
	_tmp1_ = a;
	_tmp2_ = _tmp1_->next;
	if (_tmp2_ != NULL) {
		RygelTrackerQueryTriplet* _tmp3_;
		RygelTrackerQueryTriplet* _tmp4_;
		_tmp3_ = b;
		_tmp4_ = _tmp3_->next;
		_tmp0_ = _tmp4_ != NULL;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	if (_tmp5_) {
		RygelTrackerQueryTriplet* _tmp6_;
		RygelTrackerQueryTriplet* _tmp7_;
		RygelTrackerQueryTriplet* _tmp8_;
		RygelTrackerQueryTriplet* _tmp9_;
		gboolean _tmp10_ = FALSE;
		_tmp6_ = a;
		_tmp7_ = _tmp6_->next;
		_tmp8_ = b;
		_tmp9_ = _tmp8_->next;
		_tmp10_ = rygel_tracker_query_triplet_equal_func (_tmp7_, _tmp9_);
		chain_equal = _tmp10_;
	} else {
		RygelTrackerQueryTriplet* _tmp11_;
		RygelTrackerQueryTriplet* _tmp12_;
		RygelTrackerQueryTriplet* _tmp13_;
		RygelTrackerQueryTriplet* _tmp14_;
		_tmp11_ = a;
		_tmp12_ = _tmp11_->next;
		_tmp13_ = b;
		_tmp14_ = _tmp13_->next;
		chain_equal = _tmp12_ == _tmp14_;
	}
	_tmp19_ = a;
	_tmp20_ = _tmp19_->graph;
	_tmp21_ = b;
	_tmp22_ = _tmp21_->graph;
	if (g_strcmp0 (_tmp20_, _tmp22_) == 0) {
		RygelTrackerQueryTriplet* _tmp23_;
		const gchar* _tmp24_;
		RygelTrackerQueryTriplet* _tmp25_;
		const gchar* _tmp26_;
		_tmp23_ = a;
		_tmp24_ = _tmp23_->subject;
		_tmp25_ = b;
		_tmp26_ = _tmp25_->subject;
		_tmp18_ = g_strcmp0 (_tmp24_, _tmp26_) == 0;
	} else {
		_tmp18_ = FALSE;
	}
	_tmp27_ = _tmp18_;
	if (_tmp27_) {
		RygelTrackerQueryTriplet* _tmp28_;
		const gchar* _tmp29_;
		RygelTrackerQueryTriplet* _tmp30_;
		const gchar* _tmp31_;
		_tmp28_ = a;
		_tmp29_ = _tmp28_->obj;
		_tmp30_ = b;
		_tmp31_ = _tmp30_->obj;
		_tmp17_ = g_strcmp0 (_tmp29_, _tmp31_) == 0;
	} else {
		_tmp17_ = FALSE;
	}
	_tmp32_ = _tmp17_;
	if (_tmp32_) {
		RygelTrackerQueryTriplet* _tmp33_;
		const gchar* _tmp34_;
		RygelTrackerQueryTriplet* _tmp35_;
		const gchar* _tmp36_;
		_tmp33_ = a;
		_tmp34_ = _tmp33_->predicate;
		_tmp35_ = b;
		_tmp36_ = _tmp35_->predicate;
		_tmp16_ = g_strcmp0 (_tmp34_, _tmp36_) == 0;
	} else {
		_tmp16_ = FALSE;
	}
	_tmp37_ = _tmp16_;
	if (_tmp37_) {
		gboolean _tmp38_;
		_tmp38_ = chain_equal;
		_tmp15_ = _tmp38_;
	} else {
		_tmp15_ = FALSE;
	}
	_tmp39_ = _tmp15_;
	result = _tmp39_;
	return result;
}


gchar* rygel_tracker_query_triplet_to_string (RygelTrackerQueryTriplet* self, gboolean include_subject) {
	gchar* result = NULL;
	gchar* _tmp0_;
	gchar* str;
	gboolean _tmp1_;
	const gchar* _tmp7_;
	const gchar* _tmp8_;
	gchar* _tmp9_;
	gchar* _tmp10_;
	gchar* _tmp11_;
	RygelTrackerQueryTriplet* _tmp12_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = g_strdup ("");
	str = _tmp0_;
	_tmp1_ = include_subject;
	if (_tmp1_) {
		const gchar* _tmp2_;
		const gchar* _tmp3_;
		gchar* _tmp4_;
		gchar* _tmp5_;
		gchar* _tmp6_;
		_tmp2_ = str;
		_tmp3_ = self->subject;
		_tmp4_ = g_strconcat (" ", _tmp3_, NULL);
		_tmp5_ = _tmp4_;
		_tmp6_ = g_strconcat (_tmp2_, _tmp5_, NULL);
		_g_free0 (str);
		str = _tmp6_;
		_g_free0 (_tmp5_);
	}
	_tmp7_ = str;
	_tmp8_ = self->predicate;
	_tmp9_ = g_strconcat (" ", _tmp8_, NULL);
	_tmp10_ = _tmp9_;
	_tmp11_ = g_strconcat (_tmp7_, _tmp10_, NULL);
	_g_free0 (str);
	str = _tmp11_;
	_g_free0 (_tmp10_);
	_tmp12_ = self->next;
	if (_tmp12_ != NULL) {
		const gchar* _tmp13_;
		RygelTrackerQueryTriplet* _tmp14_;
		gchar* _tmp15_ = NULL;
		gchar* _tmp16_;
		gchar* _tmp17_;
		gchar* _tmp18_;
		gchar* _tmp19_;
		gchar* _tmp20_;
		gchar* _tmp21_;
		_tmp13_ = str;
		_tmp14_ = self->next;
		_tmp15_ = rygel_tracker_query_triplet_to_string (_tmp14_, TRUE);
		_tmp16_ = _tmp15_;
		_tmp17_ = g_strconcat (" [ ", _tmp16_, NULL);
		_tmp18_ = _tmp17_;
		_tmp19_ = g_strconcat (_tmp18_, " ] ", NULL);
		_tmp20_ = _tmp19_;
		_tmp21_ = g_strconcat (_tmp13_, _tmp20_, NULL);
		_g_free0 (str);
		str = _tmp21_;
		_g_free0 (_tmp20_);
		_g_free0 (_tmp18_);
		_g_free0 (_tmp16_);
	} else {
		const gchar* _tmp22_;
		const gchar* _tmp23_;
		gchar* _tmp24_;
		gchar* _tmp25_;
		gchar* _tmp26_;
		_tmp22_ = str;
		_tmp23_ = self->obj;
		_tmp24_ = g_strconcat (" ", _tmp23_, NULL);
		_tmp25_ = _tmp24_;
		_tmp26_ = g_strconcat (_tmp22_, _tmp25_, NULL);
		_g_free0 (str);
		str = _tmp26_;
		_g_free0 (_tmp25_);
	}
	result = str;
	return result;
}


static void rygel_tracker_value_query_triplet_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void rygel_tracker_value_query_triplet_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		rygel_tracker_query_triplet_unref (value->data[0].v_pointer);
	}
}


static void rygel_tracker_value_query_triplet_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = rygel_tracker_query_triplet_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer rygel_tracker_value_query_triplet_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* rygel_tracker_value_query_triplet_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		RygelTrackerQueryTriplet* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = rygel_tracker_query_triplet_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* rygel_tracker_value_query_triplet_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	RygelTrackerQueryTriplet** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = rygel_tracker_query_triplet_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* rygel_tracker_param_spec_query_triplet (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	RygelTrackerParamSpecQueryTriplet* spec;
	g_return_val_if_fail (g_type_is_a (object_type, RYGEL_TRACKER_TYPE_QUERY_TRIPLET), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer rygel_tracker_value_get_query_triplet (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TRACKER_TYPE_QUERY_TRIPLET), NULL);
	return value->data[0].v_pointer;
}


void rygel_tracker_value_set_query_triplet (GValue* value, gpointer v_object) {
	RygelTrackerQueryTriplet* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TRACKER_TYPE_QUERY_TRIPLET));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, RYGEL_TRACKER_TYPE_QUERY_TRIPLET));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		rygel_tracker_query_triplet_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		rygel_tracker_query_triplet_unref (old);
	}
}


void rygel_tracker_value_take_query_triplet (GValue* value, gpointer v_object) {
	RygelTrackerQueryTriplet* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_TRACKER_TYPE_QUERY_TRIPLET));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, RYGEL_TRACKER_TYPE_QUERY_TRIPLET));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		rygel_tracker_query_triplet_unref (old);
	}
}


static void rygel_tracker_query_triplet_class_init (RygelTrackerQueryTripletClass * klass) {
	rygel_tracker_query_triplet_parent_class = g_type_class_peek_parent (klass);
	RYGEL_TRACKER_QUERY_TRIPLET_CLASS (klass)->finalize = rygel_tracker_query_triplet_finalize;
}


static void rygel_tracker_query_triplet_instance_init (RygelTrackerQueryTriplet * self) {
	self->ref_count = 1;
}


static void rygel_tracker_query_triplet_finalize (RygelTrackerQueryTriplet* obj) {
	RygelTrackerQueryTriplet * self;
	self = RYGEL_TRACKER_QUERY_TRIPLET (obj);
	_g_free0 (self->graph);
	_g_free0 (self->subject);
	_g_free0 (self->predicate);
	_g_free0 (self->obj);
	_rygel_tracker_query_triplet_unref0 (self->next);
}


/**
 * Represents SPARQL Triplet
 */
GType rygel_tracker_query_triplet_get_type (void) {
	static volatile gsize rygel_tracker_query_triplet_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_tracker_query_triplet_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { rygel_tracker_value_query_triplet_init, rygel_tracker_value_query_triplet_free_value, rygel_tracker_value_query_triplet_copy_value, rygel_tracker_value_query_triplet_peek_pointer, "p", rygel_tracker_value_query_triplet_collect_value, "p", rygel_tracker_value_query_triplet_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (RygelTrackerQueryTripletClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_tracker_query_triplet_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelTrackerQueryTriplet), 0, (GInstanceInitFunc) rygel_tracker_query_triplet_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType rygel_tracker_query_triplet_type_id;
		rygel_tracker_query_triplet_type_id = g_type_register_fundamental (g_type_fundamental_next (), "RygelTrackerQueryTriplet", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&rygel_tracker_query_triplet_type_id__volatile, rygel_tracker_query_triplet_type_id);
	}
	return rygel_tracker_query_triplet_type_id__volatile;
}


gpointer rygel_tracker_query_triplet_ref (gpointer instance) {
	RygelTrackerQueryTriplet* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void rygel_tracker_query_triplet_unref (gpointer instance) {
	RygelTrackerQueryTriplet* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		RYGEL_TRACKER_QUERY_TRIPLET_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}



