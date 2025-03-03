/* rygel-media-export-database-cursor.c generated by valac 0.16.1, the Vala compiler
 * generated from rygel-media-export-database-cursor.vala, do not modify */

/*
 * Copyright (C) 2011 Jens Georg <mail@jensge.org>.
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
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n-lib.h>
#include <gobject/gvaluecollector.h>


#define RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER (rygel_media_export_sqlite_wrapper_get_type ())
#define RYGEL_MEDIA_EXPORT_SQLITE_WRAPPER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER, RygelMediaExportSqliteWrapper))
#define RYGEL_MEDIA_EXPORT_SQLITE_WRAPPER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER, RygelMediaExportSqliteWrapperClass))
#define RYGEL_MEDIA_EXPORT_IS_SQLITE_WRAPPER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER))
#define RYGEL_MEDIA_EXPORT_IS_SQLITE_WRAPPER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER))
#define RYGEL_MEDIA_EXPORT_SQLITE_WRAPPER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER, RygelMediaExportSqliteWrapperClass))

typedef struct _RygelMediaExportSqliteWrapper RygelMediaExportSqliteWrapper;
typedef struct _RygelMediaExportSqliteWrapperClass RygelMediaExportSqliteWrapperClass;
typedef struct _RygelMediaExportSqliteWrapperPrivate RygelMediaExportSqliteWrapperPrivate;

#define RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR (rygel_media_export_database_cursor_get_type ())
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR, RygelMediaExportDatabaseCursor))
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR, RygelMediaExportDatabaseCursorClass))
#define RYGEL_MEDIA_EXPORT_IS_DATABASE_CURSOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR))
#define RYGEL_MEDIA_EXPORT_IS_DATABASE_CURSOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR))
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR, RygelMediaExportDatabaseCursorClass))

typedef struct _RygelMediaExportDatabaseCursor RygelMediaExportDatabaseCursor;
typedef struct _RygelMediaExportDatabaseCursorClass RygelMediaExportDatabaseCursorClass;
typedef struct _RygelMediaExportDatabaseCursorPrivate RygelMediaExportDatabaseCursorPrivate;
#define _sqlite3_finalize0(var) ((var == NULL) ? NULL : (var = (sqlite3_finalize (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR (rygel_media_export_database_cursor_iterator_get_type ())
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR, RygelMediaExportDatabaseCursorIterator))
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR, RygelMediaExportDatabaseCursorIteratorClass))
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_IS_ITERATOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR))
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_IS_ITERATOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR))
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR, RygelMediaExportDatabaseCursorIteratorClass))

typedef struct _RygelMediaExportDatabaseCursorIterator RygelMediaExportDatabaseCursorIterator;
typedef struct _RygelMediaExportDatabaseCursorIteratorClass RygelMediaExportDatabaseCursorIteratorClass;
typedef struct _RygelMediaExportDatabaseCursorIteratorPrivate RygelMediaExportDatabaseCursorIteratorPrivate;
typedef struct _RygelMediaExportDatabaseCursorParamSpecIterator RygelMediaExportDatabaseCursorParamSpecIterator;

struct _RygelMediaExportSqliteWrapper {
	GObject parent_instance;
	RygelMediaExportSqliteWrapperPrivate * priv;
};

struct _RygelMediaExportSqliteWrapperClass {
	GObjectClass parent_class;
};

struct _RygelMediaExportDatabaseCursor {
	RygelMediaExportSqliteWrapper parent_instance;
	RygelMediaExportDatabaseCursorPrivate * priv;
};

struct _RygelMediaExportDatabaseCursorClass {
	RygelMediaExportSqliteWrapperClass parent_class;
};

struct _RygelMediaExportDatabaseCursorPrivate {
	sqlite3_stmt* statement;
	gint current_state;
	gboolean dirty;
};

typedef enum  {
	RYGEL_MEDIA_EXPORT_DATABASE_ERROR_IO_ERROR,
	RYGEL_MEDIA_EXPORT_DATABASE_ERROR_SQLITE_ERROR
} RygelMediaExportDatabaseError;
#define RYGEL_MEDIA_EXPORT_DATABASE_ERROR rygel_media_export_database_error_quark ()
struct _RygelMediaExportDatabaseCursorIterator {
	GTypeInstance parent_instance;
	volatile int ref_count;
	RygelMediaExportDatabaseCursorIteratorPrivate * priv;
	RygelMediaExportDatabaseCursor* cursor;
};

struct _RygelMediaExportDatabaseCursorIteratorClass {
	GTypeClass parent_class;
	void (*finalize) (RygelMediaExportDatabaseCursorIterator *self);
};

struct _RygelMediaExportDatabaseCursorParamSpecIterator {
	GParamSpec parent_instance;
};


static gpointer rygel_media_export_database_cursor_parent_class = NULL;
static gpointer rygel_media_export_database_cursor_iterator_parent_class = NULL;

GType rygel_media_export_sqlite_wrapper_get_type (void) G_GNUC_CONST;
GType rygel_media_export_database_cursor_get_type (void) G_GNUC_CONST;
#define RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR, RygelMediaExportDatabaseCursorPrivate))
enum  {
	RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_DUMMY_PROPERTY
};
GQuark rygel_media_export_database_error_quark (void);
RygelMediaExportDatabaseCursor* rygel_media_export_database_cursor_new (sqlite3* db, const gchar* sql, GValue* arguments, int arguments_length1, GError** error);
RygelMediaExportDatabaseCursor* rygel_media_export_database_cursor_construct (GType object_type, sqlite3* db, const gchar* sql, GValue* arguments, int arguments_length1, GError** error);
RygelMediaExportSqliteWrapper* rygel_media_export_sqlite_wrapper_new_wrap (sqlite3* db);
RygelMediaExportSqliteWrapper* rygel_media_export_sqlite_wrapper_construct_wrap (GType object_type, sqlite3* db);
void rygel_media_export_sqlite_wrapper_throw_if_code_is_error (RygelMediaExportSqliteWrapper* self, gint sqlite_error, GError** error);
void rygel_media_export_sqlite_wrapper_throw_if_db_has_error (RygelMediaExportSqliteWrapper* self, GError** error);
gboolean rygel_media_export_database_cursor_has_next (RygelMediaExportDatabaseCursor* self);
sqlite3_stmt* rygel_media_export_database_cursor_next (RygelMediaExportDatabaseCursor* self, GError** error);
gpointer rygel_media_export_database_cursor_iterator_ref (gpointer instance);
void rygel_media_export_database_cursor_iterator_unref (gpointer instance);
GParamSpec* rygel_media_export_database_cursor_param_spec_iterator (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void rygel_media_export_database_cursor_value_set_iterator (GValue* value, gpointer v_object);
void rygel_media_export_database_cursor_value_take_iterator (GValue* value, gpointer v_object);
gpointer rygel_media_export_database_cursor_value_get_iterator (const GValue* value);
GType rygel_media_export_database_cursor_iterator_get_type (void) G_GNUC_CONST;
RygelMediaExportDatabaseCursorIterator* rygel_media_export_database_cursor_iterator (RygelMediaExportDatabaseCursor* self);
RygelMediaExportDatabaseCursorIterator* rygel_media_export_database_cursor_iterator_new (RygelMediaExportDatabaseCursor* cursor);
RygelMediaExportDatabaseCursorIterator* rygel_media_export_database_cursor_iterator_construct (GType object_type, RygelMediaExportDatabaseCursor* cursor);
enum  {
	RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR_DUMMY_PROPERTY
};
gboolean rygel_media_export_database_cursor_iterator_next (RygelMediaExportDatabaseCursorIterator* self);
sqlite3_stmt* rygel_media_export_database_cursor_iterator_get (RygelMediaExportDatabaseCursorIterator* self, GError** error);
static void rygel_media_export_database_cursor_iterator_finalize (RygelMediaExportDatabaseCursorIterator* obj);
static void rygel_media_export_database_cursor_finalize (GObject* obj);


/**
     * Prepare a SQLite statement from a SQL string
     *
     * This function uses the type of the GValue passed in values to determine
     * which _bind function to use.
     *
     * Supported types are: int, long, int64, uint64, string and pointer.
     * @note the only pointer supported is the null pointer as provided by
     * Database.@null. This is a special value to bind a column to NULL
     *
     * @param db SQLite database this cursor belongs to
     * @param sql statement to execute
     * @param values array of values to bind to the SQL statement or null if
     * none
     */
RygelMediaExportDatabaseCursor* rygel_media_export_database_cursor_construct (GType object_type, sqlite3* db, const gchar* sql, GValue* arguments, int arguments_length1, GError** error) {
	RygelMediaExportDatabaseCursor * self = NULL;
	sqlite3* _tmp0_;
	sqlite3* _tmp1_;
	const gchar* _tmp2_;
	sqlite3_stmt* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	GValue* _tmp5_;
	gint _tmp5__length1;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (db != NULL, NULL);
	g_return_val_if_fail (sql != NULL, NULL);
	_tmp0_ = db;
	self = (RygelMediaExportDatabaseCursor*) rygel_media_export_sqlite_wrapper_construct_wrap (object_type, _tmp0_);
	_tmp1_ = db;
	_tmp2_ = sql;
	_tmp4_ = sqlite3_prepare_v2 (_tmp1_, _tmp2_, -1, &_tmp3_, NULL);
	_sqlite3_finalize0 (self->priv->statement);
	self->priv->statement = _tmp3_;
	rygel_media_export_sqlite_wrapper_throw_if_code_is_error ((RygelMediaExportSqliteWrapper*) self, _tmp4_, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == RYGEL_MEDIA_EXPORT_DATABASE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp5_ = arguments;
	_tmp5__length1 = arguments_length1;
	if (_tmp5_ == NULL) {
		return self;
	}
	{
		gint i;
		i = 1;
		{
			gboolean _tmp6_;
			_tmp6_ = TRUE;
			while (TRUE) {
				gboolean _tmp7_;
				gint _tmp9_;
				GValue* _tmp10_;
				gint _tmp10__length1;
				GValue* _tmp11_;
				gint _tmp11__length1;
				gint _tmp12_;
				GValue _tmp13_;
				GValue current_value;
				gboolean _tmp14_ = FALSE;
				_tmp7_ = _tmp6_;
				if (!_tmp7_) {
					gint _tmp8_;
					_tmp8_ = i;
					i = _tmp8_ + 1;
				}
				_tmp6_ = FALSE;
				_tmp9_ = i;
				_tmp10_ = arguments;
				_tmp10__length1 = arguments_length1;
				if (!(_tmp9_ <= _tmp10__length1)) {
					break;
				}
				_tmp11_ = arguments;
				_tmp11__length1 = arguments_length1;
				_tmp12_ = i;
				_tmp13_ = _tmp11_[_tmp12_ - 1];
				current_value = _tmp13_;
				_tmp14_ = G_VALUE_HOLDS (&current_value, G_TYPE_INT);
				if (_tmp14_) {
					sqlite3_stmt* _tmp15_;
					gint _tmp16_;
					gint _tmp17_ = 0;
					_tmp15_ = self->priv->statement;
					_tmp16_ = i;
					_tmp17_ = g_value_get_int (&current_value);
					sqlite3_bind_int (_tmp15_, _tmp16_, _tmp17_);
				} else {
					gboolean _tmp18_ = FALSE;
					_tmp18_ = G_VALUE_HOLDS (&current_value, G_TYPE_INT64);
					if (_tmp18_) {
						sqlite3_stmt* _tmp19_;
						gint _tmp20_;
						gint64 _tmp21_ = 0LL;
						_tmp19_ = self->priv->statement;
						_tmp20_ = i;
						_tmp21_ = g_value_get_int64 (&current_value);
						sqlite3_bind_int64 (_tmp19_, _tmp20_, _tmp21_);
					} else {
						gboolean _tmp22_ = FALSE;
						_tmp22_ = G_VALUE_HOLDS (&current_value, G_TYPE_UINT64);
						if (_tmp22_) {
							sqlite3_stmt* _tmp23_;
							gint _tmp24_;
							guint64 _tmp25_ = 0ULL;
							_tmp23_ = self->priv->statement;
							_tmp24_ = i;
							_tmp25_ = g_value_get_uint64 (&current_value);
							sqlite3_bind_int64 (_tmp23_, _tmp24_, (gint64) _tmp25_);
						} else {
							gboolean _tmp26_ = FALSE;
							_tmp26_ = G_VALUE_HOLDS (&current_value, G_TYPE_LONG);
							if (_tmp26_) {
								sqlite3_stmt* _tmp27_;
								gint _tmp28_;
								glong _tmp29_ = 0L;
								_tmp27_ = self->priv->statement;
								_tmp28_ = i;
								_tmp29_ = g_value_get_long (&current_value);
								sqlite3_bind_int64 (_tmp27_, _tmp28_, (gint64) _tmp29_);
							} else {
								gboolean _tmp30_ = FALSE;
								_tmp30_ = G_VALUE_HOLDS (&current_value, G_TYPE_STRING);
								if (_tmp30_) {
									sqlite3_stmt* _tmp31_;
									gint _tmp32_;
									const gchar* _tmp33_ = NULL;
									gchar* _tmp34_;
									GDestroyNotify _tmp35_;
									_tmp31_ = self->priv->statement;
									_tmp32_ = i;
									_tmp33_ = g_value_get_string (&current_value);
									_tmp34_ = g_strdup (_tmp33_);
									_tmp35_ = g_free;
									sqlite3_bind_text (_tmp31_, _tmp32_, _tmp34_, -1, _tmp35_);
								} else {
									gboolean _tmp36_ = FALSE;
									_tmp36_ = G_VALUE_HOLDS (&current_value, G_TYPE_POINTER);
									if (_tmp36_) {
										void* _tmp37_ = NULL;
										_tmp37_ = g_value_peek_pointer (&current_value);
										if (_tmp37_ == NULL) {
											sqlite3_stmt* _tmp38_;
											gint _tmp39_;
											_tmp38_ = self->priv->statement;
											_tmp39_ = i;
											sqlite3_bind_null (_tmp38_, _tmp39_);
										} else {
											g_assert_not_reached ();
										}
									} else {
										GType _tmp40_ = 0UL;
										GType type;
										const gchar* _tmp41_ = NULL;
										const gchar* _tmp42_ = NULL;
										_tmp40_ = G_VALUE_TYPE (&current_value);
										type = _tmp40_;
										_tmp41_ = _ ("Unsupported type %s");
										_tmp42_ = g_type_name (type);
										g_warning (_tmp41_, _tmp42_);
										g_assert_not_reached ();
									}
								}
							}
						}
					}
				}
				rygel_media_export_sqlite_wrapper_throw_if_db_has_error ((RygelMediaExportSqliteWrapper*) self, &_inner_error_);
				if (_inner_error_ != NULL) {
					if (_inner_error_->domain == RYGEL_MEDIA_EXPORT_DATABASE_ERROR) {
						g_propagate_error (error, _inner_error_);
						_g_object_unref0 (self);
						return NULL;
					} else {
						g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
						g_clear_error (&_inner_error_);
						return NULL;
					}
				}
			}
		}
	}
	return self;
}


RygelMediaExportDatabaseCursor* rygel_media_export_database_cursor_new (sqlite3* db, const gchar* sql, GValue* arguments, int arguments_length1, GError** error) {
	return rygel_media_export_database_cursor_construct (RYGEL_MEDIA_EXPORT_TYPE_DATABASE_CURSOR, db, sql, arguments, arguments_length1, error);
}


/**
     * Check if the cursor has more rows left
     *
     * @return true if more rows left, false otherwise
     */
gboolean rygel_media_export_database_cursor_has_next (RygelMediaExportDatabaseCursor* self) {
	gboolean result = FALSE;
	gboolean _tmp0_;
	gboolean _tmp3_ = FALSE;
	gint _tmp4_;
	gboolean _tmp6_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->dirty;
	if (_tmp0_) {
		sqlite3_stmt* _tmp1_;
		gint _tmp2_ = 0;
		_tmp1_ = self->priv->statement;
		_tmp2_ = sqlite3_step (_tmp1_);
		self->priv->current_state = _tmp2_;
		self->priv->dirty = FALSE;
	}
	_tmp4_ = self->priv->current_state;
	if (_tmp4_ == SQLITE_ROW) {
		_tmp3_ = TRUE;
	} else {
		gint _tmp5_;
		_tmp5_ = self->priv->current_state;
		_tmp3_ = _tmp5_ == (-1);
	}
	_tmp6_ = _tmp3_;
	result = _tmp6_;
	return result;
}


/**
     * Get the next row of this cursor.
     *
     * This function uses pointers instead of unowned because var doesn't work
     * with unowned.
     *
     * @return a pointer to the current row
     */
sqlite3_stmt* rygel_media_export_database_cursor_next (RygelMediaExportDatabaseCursor* self, GError** error) {
	sqlite3_stmt* result = NULL;
	gint _tmp0_;
	sqlite3_stmt* _tmp1_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	rygel_media_export_database_cursor_has_next (self);
	_tmp0_ = self->priv->current_state;
	rygel_media_export_sqlite_wrapper_throw_if_code_is_error ((RygelMediaExportSqliteWrapper*) self, _tmp0_, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == RYGEL_MEDIA_EXPORT_DATABASE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->priv->dirty = TRUE;
	_tmp1_ = self->priv->statement;
	result = _tmp1_;
	return result;
}


/**
     * Return a iterator to the cursor to use with foreach
     *
     * @return an iterator wrapping the cursor
     */
RygelMediaExportDatabaseCursorIterator* rygel_media_export_database_cursor_iterator (RygelMediaExportDatabaseCursor* self) {
	RygelMediaExportDatabaseCursorIterator* result = NULL;
	RygelMediaExportDatabaseCursorIterator* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = rygel_media_export_database_cursor_iterator_new (self);
	result = _tmp0_;
	return result;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


RygelMediaExportDatabaseCursorIterator* rygel_media_export_database_cursor_iterator_construct (GType object_type, RygelMediaExportDatabaseCursor* cursor) {
	RygelMediaExportDatabaseCursorIterator* self = NULL;
	RygelMediaExportDatabaseCursor* _tmp0_;
	RygelMediaExportDatabaseCursor* _tmp1_;
	g_return_val_if_fail (cursor != NULL, NULL);
	self = (RygelMediaExportDatabaseCursorIterator*) g_type_create_instance (object_type);
	_tmp0_ = cursor;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->cursor);
	self->cursor = _tmp1_;
	return self;
}


RygelMediaExportDatabaseCursorIterator* rygel_media_export_database_cursor_iterator_new (RygelMediaExportDatabaseCursor* cursor) {
	return rygel_media_export_database_cursor_iterator_construct (RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR, cursor);
}


gboolean rygel_media_export_database_cursor_iterator_next (RygelMediaExportDatabaseCursorIterator* self) {
	gboolean result = FALSE;
	RygelMediaExportDatabaseCursor* _tmp0_;
	gboolean _tmp1_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->cursor;
	_tmp1_ = rygel_media_export_database_cursor_has_next (_tmp0_);
	result = _tmp1_;
	return result;
}


sqlite3_stmt* rygel_media_export_database_cursor_iterator_get (RygelMediaExportDatabaseCursorIterator* self, GError** error) {
	sqlite3_stmt* result = NULL;
	RygelMediaExportDatabaseCursor* _tmp0_;
	sqlite3_stmt* _tmp1_ = NULL;
	sqlite3_stmt* _tmp2_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->cursor;
	_tmp1_ = rygel_media_export_database_cursor_next (_tmp0_, &_inner_error_);
	_tmp2_ = _tmp1_;
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == RYGEL_MEDIA_EXPORT_DATABASE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	result = _tmp2_;
	return result;
}


static void rygel_media_export_database_cursor_value_iterator_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void rygel_media_export_database_cursor_value_iterator_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		rygel_media_export_database_cursor_iterator_unref (value->data[0].v_pointer);
	}
}


static void rygel_media_export_database_cursor_value_iterator_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = rygel_media_export_database_cursor_iterator_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer rygel_media_export_database_cursor_value_iterator_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* rygel_media_export_database_cursor_value_iterator_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		RygelMediaExportDatabaseCursorIterator* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = rygel_media_export_database_cursor_iterator_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* rygel_media_export_database_cursor_value_iterator_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	RygelMediaExportDatabaseCursorIterator** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags & G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = rygel_media_export_database_cursor_iterator_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* rygel_media_export_database_cursor_param_spec_iterator (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	RygelMediaExportDatabaseCursorParamSpecIterator* spec;
	g_return_val_if_fail (g_type_is_a (object_type, RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer rygel_media_export_database_cursor_value_get_iterator (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR), NULL);
	return value->data[0].v_pointer;
}


void rygel_media_export_database_cursor_value_set_iterator (GValue* value, gpointer v_object) {
	RygelMediaExportDatabaseCursorIterator* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		rygel_media_export_database_cursor_iterator_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		rygel_media_export_database_cursor_iterator_unref (old);
	}
}


void rygel_media_export_database_cursor_value_take_iterator (GValue* value, gpointer v_object) {
	RygelMediaExportDatabaseCursorIterator* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_TYPE_ITERATOR));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		rygel_media_export_database_cursor_iterator_unref (old);
	}
}


static void rygel_media_export_database_cursor_iterator_class_init (RygelMediaExportDatabaseCursorIteratorClass * klass) {
	rygel_media_export_database_cursor_iterator_parent_class = g_type_class_peek_parent (klass);
	RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR_CLASS (klass)->finalize = rygel_media_export_database_cursor_iterator_finalize;
}


static void rygel_media_export_database_cursor_iterator_instance_init (RygelMediaExportDatabaseCursorIterator * self) {
	self->ref_count = 1;
}


static void rygel_media_export_database_cursor_iterator_finalize (RygelMediaExportDatabaseCursorIterator* obj) {
	RygelMediaExportDatabaseCursorIterator * self;
	self = RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR (obj);
	_g_object_unref0 (self->cursor);
}


GType rygel_media_export_database_cursor_iterator_get_type (void) {
	static volatile gsize rygel_media_export_database_cursor_iterator_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_media_export_database_cursor_iterator_type_id__volatile)) {
		static const GTypeValueTable g_define_type_value_table = { rygel_media_export_database_cursor_value_iterator_init, rygel_media_export_database_cursor_value_iterator_free_value, rygel_media_export_database_cursor_value_iterator_copy_value, rygel_media_export_database_cursor_value_iterator_peek_pointer, "p", rygel_media_export_database_cursor_value_iterator_collect_value, "p", rygel_media_export_database_cursor_value_iterator_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaExportDatabaseCursorIteratorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_export_database_cursor_iterator_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaExportDatabaseCursorIterator), 0, (GInstanceInitFunc) rygel_media_export_database_cursor_iterator_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		GType rygel_media_export_database_cursor_iterator_type_id;
		rygel_media_export_database_cursor_iterator_type_id = g_type_register_fundamental (g_type_fundamental_next (), "RygelMediaExportDatabaseCursorIterator", &g_define_type_info, &g_define_type_fundamental_info, 0);
		g_once_init_leave (&rygel_media_export_database_cursor_iterator_type_id__volatile, rygel_media_export_database_cursor_iterator_type_id);
	}
	return rygel_media_export_database_cursor_iterator_type_id__volatile;
}


gpointer rygel_media_export_database_cursor_iterator_ref (gpointer instance) {
	RygelMediaExportDatabaseCursorIterator* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void rygel_media_export_database_cursor_iterator_unref (gpointer instance) {
	RygelMediaExportDatabaseCursorIterator* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_ITERATOR_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}


static void rygel_media_export_database_cursor_class_init (RygelMediaExportDatabaseCursorClass * klass) {
	rygel_media_export_database_cursor_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RygelMediaExportDatabaseCursorPrivate));
	G_OBJECT_CLASS (klass)->finalize = rygel_media_export_database_cursor_finalize;
}


static void rygel_media_export_database_cursor_instance_init (RygelMediaExportDatabaseCursor * self) {
	self->priv = RYGEL_MEDIA_EXPORT_DATABASE_CURSOR_GET_PRIVATE (self);
	self->priv->current_state = -1;
	self->priv->dirty = TRUE;
}


static void rygel_media_export_database_cursor_finalize (GObject* obj) {
	RygelMediaExportDatabaseCursor * self;
	self = RYGEL_MEDIA_EXPORT_DATABASE_CURSOR (obj);
	_sqlite3_finalize0 (self->priv->statement);
	G_OBJECT_CLASS (rygel_media_export_database_cursor_parent_class)->finalize (obj);
}


GType rygel_media_export_database_cursor_get_type (void) {
	static volatile gsize rygel_media_export_database_cursor_type_id__volatile = 0;
	if (g_once_init_enter (&rygel_media_export_database_cursor_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RygelMediaExportDatabaseCursorClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) rygel_media_export_database_cursor_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RygelMediaExportDatabaseCursor), 0, (GInstanceInitFunc) rygel_media_export_database_cursor_instance_init, NULL };
		GType rygel_media_export_database_cursor_type_id;
		rygel_media_export_database_cursor_type_id = g_type_register_static (RYGEL_MEDIA_EXPORT_TYPE_SQLITE_WRAPPER, "RygelMediaExportDatabaseCursor", &g_define_type_info, 0);
		g_once_init_leave (&rygel_media_export_database_cursor_type_id__volatile, rygel_media_export_database_cursor_type_id);
	}
	return rygel_media_export_database_cursor_type_id__volatile;
}



