/*
 * Copyright (C) 2010,2011 Jens Georg <mail@jensge.org>.
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

internal enum Rygel.MediaExport.DetailColumn {
    TYPE,
    TITLE,
    SIZE,
    MIME_TYPE,
    WIDTH,
    HEIGHT,
    CLASS,
    AUTHOR,
    ALBUM,
    DATE,
    BITRATE,
    SAMPLE_FREQ,
    BITS_PER_SAMPLE,
    CHANNELS,
    TRACK,
    COLOR_DEPTH,
    DURATION,
    ID,
    PARENT,
    TIMESTAMP,
    URI,
    DLNA_PROFILE,
    GENRE,
    DISC
}

internal enum Rygel.MediaExport.SQLString {
    SAVE_METADATA,
    INSERT,
    DELETE,
    GET_OBJECT,
    GET_CHILDREN,
    GET_OBJECTS_BY_FILTER,
    GET_OBJECTS_BY_FILTER_WITH_ANCESTOR,
    GET_OBJECT_COUNT_BY_FILTER,
    GET_OBJECT_COUNT_BY_FILTER_WITH_ANCESTOR,
    GET_META_DATA_COLUMN,
    CHILD_COUNT,
    EXISTS,
    CHILD_IDS,
    TABLE_METADATA,
    TABLE_CLOSURE,
    TRIGGER_CLOSURE,
    TRIGGER_COMMON,
    INDEX_COMMON,
    SCHEMA,
    EXISTS_CACHE,
    STATISTICS,
}

internal class Rygel.MediaExport.SQLFactory : Object {
    private const string SAVE_META_DATA_STRING =
    "INSERT OR REPLACE INTO meta_data " +
        "(size, mime_type, width, height, class, " +
         "author, album, date, bitrate, " +
         "sample_freq, bits_per_sample, channels, " +
         "track, color_depth, duration, object_fk, dlna_profile, genre, disc) VALUES " +
         "(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    private const string INSERT_OBJECT_STRING =
    "INSERT OR REPLACE INTO Object (upnp_id, title, type_fk, parent, timestamp, uri) " +
        "VALUES (?,?,?,?,?,?)";

    private const string DELETE_BY_ID_STRING =
    "DELETE FROM Object WHERE upnp_id IN " +
        "(SELECT descendant FROM closure WHERE ancestor = ?)";

    private const string ALL_DETAILS_STRING =
    "o.type_fk, o.title, m.size, m.mime_type, m.width, " +
    "m.height, m.class, m.author, m.album, m.date, m.bitrate, " +
    "m.sample_freq, m.bits_per_sample, m.channels, m.track, " +
    "m.color_depth, m.duration, o.upnp_id, o.parent, o.timestamp, " +
    "o.uri, m.dlna_profile, m.genre, m.disc ";

    private const string GET_OBJECT_WITH_PATH =
    "SELECT DISTINCT " + ALL_DETAILS_STRING +
    "FROM Object o " +
        "JOIN Closure c ON (o.upnp_id = c.ancestor) " +
        "LEFT OUTER JOIN meta_data m ON (o.upnp_id = m.object_fk) " +
            "WHERE c.descendant = ? ORDER BY c.depth DESC";

    /**
     * This is the database query used to retrieve the children for a
     * given object.
     *
     * Sorting is as follows:
     *   - by type: containers first, then items if both are present
     *   - by upnp_class: items are sorted according to their class
     *   - by track: sorted by track
     *   - and after that alphabetically
     */
    private const string GET_CHILDREN_STRING =
    "SELECT " + ALL_DETAILS_STRING +
    "FROM Object o " +
        "JOIN Closure c ON (o.upnp_id = c.descendant) " +
        "LEFT OUTER JOIN meta_data m " +
        "ON c.descendant = m.object_fk " +
    "WHERE c.ancestor = ? AND c.depth = 1 %s" +
    "LIMIT ?,?";

    private const string GET_OBJECTS_BY_FILTER_STRING_WITH_ANCESTOR =
    "SELECT DISTINCT " + ALL_DETAILS_STRING +
    "FROM Object o " +
        "JOIN Closure c ON o.upnp_id = c.descendant AND c.ancestor = ? " +
        "LEFT OUTER JOIN meta_data m " +
            "ON o.upnp_id = m.object_fk %s %s " +
    "LIMIT ?,?";

    private const string GET_OBJECTS_BY_FILTER_STRING =
    "SELECT DISTINCT " + ALL_DETAILS_STRING +
    "FROM Object o " +
        "LEFT OUTER JOIN meta_data m " +
            "ON o.upnp_id = m.object_fk %s %s " +
    "LIMIT ?,?";

    private const string GET_OBJECT_COUNT_BY_FILTER_STRING_WITH_ANCESTOR =
    "SELECT COUNT(o.type_fk) FROM Object o " +
        "JOIN Closure c ON o.upnp_id = c.descendant AND c.ancestor = ? " +
        "LEFT OUTER JOIN meta_data m " +
            "ON o.upnp_id = m.object_fk %s";

    private const string GET_OBJECT_COUNT_BY_FILTER_STRING =
    "SELECT COUNT(1) FROM meta_data m %s";

    private const string CHILDREN_COUNT_STRING =
    "SELECT COUNT(upnp_id) FROM Object WHERE Object.parent = ?";

    private const string OBJECT_EXISTS_STRING =
    "SELECT COUNT(1), timestamp, m.size FROM Object " +
        "JOIN meta_data m ON m.object_fk = upnp_id " +
        "WHERE Object.uri = ?";

    private const string GET_CHILD_ID_STRING =
    "SELECT upnp_id FROM OBJECT WHERE parent = ?";

    private const string GET_META_DATA_COLUMN_STRING =
    "SELECT DISTINCT %s AS _column FROM meta_data AS m " +
        "WHERE _column IS NOT NULL %s ORDER BY _column COLLATE CASEFOLD " +
    "LIMIT ?,?";

    internal const string schema_version = "11";
    internal const string CREATE_META_DATA_TABLE_STRING =
    "CREATE TABLE meta_data (size INTEGER NOT NULL, " +
                            "mime_type TEXT NOT NULL, " +
                            "dlna_profile TEXT, " +
                            "duration INTEGER, " +
                            "width INTEGER, " +
                            "height INTEGER, " +
                            "class TEXT NOT NULL, " +
                            "author TEXT, " +
                            "album TEXT, " +
                            "genre TEXT, " +
                            "date TEXT, " +
                            "bitrate INTEGER, " +
                            "sample_freq INTEGER, " +
                            "bits_per_sample INTEGER, " +
                            "channels INTEGER, " +
                            "track INTEGER, " +
                            "disc INTEGER, " +
                            "color_depth INTEGER, " +
                            "object_fk TEXT UNIQUE CONSTRAINT " +
                                "object_fk_id REFERENCES Object(upnp_id) " +
                                    "ON DELETE CASCADE);";

    private const string SCHEMA_STRING =
    "CREATE TABLE schema_info (version TEXT NOT NULL); " +
    CREATE_META_DATA_TABLE_STRING +
    "CREATE TABLE object (parent TEXT CONSTRAINT parent_fk_id " +
                                "REFERENCES Object(upnp_id), " +
                          "upnp_id TEXT PRIMARY KEY, " +
                          "type_fk INTEGER, " +
                          "title TEXT NOT NULL, " +
                          "timestamp INTEGER NOT NULL, " +
                          "uri TEXT, " +
                          "flags TEXT);" +
    "INSERT INTO schema_info (version) VALUES ('" +
    SQLFactory.schema_version + "'); ";

    private const string CREATE_CLOSURE_TABLE =
    "CREATE TABLE closure (ancestor TEXT, descendant TEXT, depth INTEGER)";

    private const string CREATE_CLOSURE_TRIGGER_STRING =
    "CREATE TRIGGER trgr_update_closure " +
    "AFTER INSERT ON Object " +
    "FOR EACH ROW BEGIN " +
        "SELECT RAISE(IGNORE) WHERE (SELECT COUNT(*) FROM Closure " +
            "WHERE ancestor = NEW.upnp_id " +
                  "AND descendant = NEW.upnp_id " +
                  "AND depth = 0) != 0;" +
        "INSERT INTO Closure (ancestor, descendant, depth) " +
            "VALUES (NEW.upnp_id, NEW.upnp_id, 0); " +
        "INSERT INTO Closure (ancestor, descendant, depth) " +
            "SELECT ancestor, NEW.upnp_id, depth + 1 FROM Closure " +
                "WHERE descendant = NEW.parent;" +
    "END;" +

    "CREATE TRIGGER trgr_delete_closure " +
    "AFTER DELETE ON Object " +
    "FOR EACH ROW BEGIN " +
        "DELETE FROM Closure WHERE descendant = OLD.upnp_id;" +
    "END;";

    // these triggers emulate ON DELETE CASCADE
    private const string CREATE_TRIGGER_STRING =
    "CREATE TRIGGER trgr_delete_metadata " +
    "BEFORE DELETE ON Object " +
    "FOR EACH ROW BEGIN " +
        "DELETE FROM meta_data WHERE meta_data.object_fk = OLD.upnp_id; "+
    "END;";

    private const string CREATE_INDICES_STRING =
    "CREATE INDEX IF NOT EXISTS idx_parent on Object(parent);" +
    "CREATE INDEX IF NOT EXISTS idx_object_upnp_id on Object(upnp_id);" +
    "CREATE INDEX IF NOT EXISTS idx_meta_data_fk on meta_data(object_fk);" +
    "CREATE INDEX IF NOT EXISTS idx_closure on Closure(descendant,depth);" +
    "CREATE INDEX IF NOT EXISTS idx_closure_descendant on Closure(descendant);" +
    "CREATE INDEX IF NOT EXISTS idx_closure_ancestor on Closure(ancestor);" +
    "CREATE INDEX IF NOT EXISTS idx_uri on Object(uri);" +
    "CREATE INDEX IF NOT EXISTS idx_meta_data_date on meta_data(date);" +
    "CREATE INDEX IF NOT EXISTS idx_meta_data_genre on meta_data(genre);" +
    "CREATE INDEX IF NOT EXISTS idx_meta_data_album on meta_data(album);" +
    "CREATE INDEX IF NOT EXISTS idx_meta_data_artist_album on " +
                                "meta_data(author, album);";



    private const string EXISTS_CACHE_STRING =
    "SELECT m.size, o.timestamp, o.uri FROM Object o " +
        "JOIN meta_data m ON o.upnp_id = m.object_fk";

    private const string STATISTICS_STRING =
    "SELECT class, count(1) FROM meta_data GROUP BY class";

    public unowned string make (SQLString query) {
        switch (query) {
            case SQLString.SAVE_METADATA:
                return SAVE_META_DATA_STRING;
            case SQLString.INSERT:
                return INSERT_OBJECT_STRING;
            case SQLString.DELETE:
                return DELETE_BY_ID_STRING;
            case SQLString.GET_OBJECT:
                return GET_OBJECT_WITH_PATH;
            case SQLString.GET_CHILDREN:
                return GET_CHILDREN_STRING;
            case SQLString.GET_OBJECTS_BY_FILTER:
                return GET_OBJECTS_BY_FILTER_STRING;
            case SQLString.GET_OBJECTS_BY_FILTER_WITH_ANCESTOR:
                return GET_OBJECTS_BY_FILTER_STRING_WITH_ANCESTOR;
            case SQLString.GET_OBJECT_COUNT_BY_FILTER:
                return GET_OBJECT_COUNT_BY_FILTER_STRING;
            case SQLString.GET_OBJECT_COUNT_BY_FILTER_WITH_ANCESTOR:
                return GET_OBJECT_COUNT_BY_FILTER_STRING_WITH_ANCESTOR;
            case SQLString.GET_META_DATA_COLUMN:
                return GET_META_DATA_COLUMN_STRING;
            case SQLString.CHILD_COUNT:
                return CHILDREN_COUNT_STRING;
            case SQLString.EXISTS:
                return OBJECT_EXISTS_STRING;
            case SQLString.CHILD_IDS:
                return GET_CHILD_ID_STRING;
            case SQLString.TABLE_METADATA:
                return CREATE_META_DATA_TABLE_STRING;
            case SQLString.TRIGGER_COMMON:
                return CREATE_TRIGGER_STRING;
            case SQLString.TRIGGER_CLOSURE:
                return CREATE_CLOSURE_TRIGGER_STRING;
            case SQLString.INDEX_COMMON:
                return CREATE_INDICES_STRING;
            case SQLString.SCHEMA:
                return SCHEMA_STRING;
            case SQLString.EXISTS_CACHE:
                return EXISTS_CACHE_STRING;
            case SQLString.TABLE_CLOSURE:
                return CREATE_CLOSURE_TABLE;
            case SQLString.STATISTICS:
                return STATISTICS_STRING;
            default:
                assert_not_reached ();
        }
    }
}
