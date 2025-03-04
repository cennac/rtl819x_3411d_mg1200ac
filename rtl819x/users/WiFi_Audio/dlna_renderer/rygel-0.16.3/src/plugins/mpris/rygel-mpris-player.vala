/*
 * Copyright (C) 2008 OpenedHand Ltd.
 * Copyright (C) 2009 Nokia Corporation.
 *
 * Author: Jorn Baayen <jorn@openedhand.com>
 *         Zeeshan Ali (Khattak) <zeeshanak@gnome.org>
 *                               <zeeshan.ali@nokia.com>
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

using Rygel.MPRIS;
using Rygel.MPRIS.MediaPlayer;
using FreeDesktop;

public class Rygel.MPRIS.Player : GLib.Object, Rygel.MediaPlayer {
    private string[] protocols;
    private string[] mime_types;

    private PlayerProxy actual_player;

    public string playback_state {
        owned get {
            return this.mpris_to_upnp_state (actual_player.playback_status);
        }

        set {
            debug ("Changing playback state to %s..", value);

            /* FIXME: Do something about errors below */
            switch (value) {
            case "STOPPED":
                try {
                    this.actual_player.stop ();
                } catch (Error error) {}

                break;
            case "PAUSED_PLAYBACK":
                try {
                    this.actual_player.pause ();
                } catch (Error error) {}

                break;
            case "PLAYING":
                try {
                    this.actual_player.play ();
                } catch (Error error) {}

                break;
            default:
                assert_not_reached ();
            }
        }
    }

    public string? uri {
        owned get {
            var val = this.actual_player.metadata.lookup ("xesam:url");

            if (val != null) {
                return (string) val;
            } else {
                return null;
            }
        }

        set {
            try {
                this.actual_player.open_uri (value);
            } catch (Error error) {}
        }
    }

    public string? mime_type { owned get; set; }
    public string? metadata { owned get; set; }
    public string? content_features { owned get; set; }

    public double volume {
        get {
            return this.actual_player.volume;
        }

        set {
            this.actual_player.volume = value;
        }
    }

    public int64 duration {
        get {
            var val = this.actual_player.metadata.lookup ("mpris:length");
            int64 dur = 0;

            if (val != null) {
                dur = (int64) val * 1000;
            }

            return dur;
        }
    }

    public int64 position {
        get {
            return this.actual_player.position * 1000;
        }
    }

    public Player (Plugin plugin) {
        this.actual_player = plugin.actual_player;
        this.mime_types = plugin.mime_types;
        this.protocols = plugin.protocols;

        actual_player.g_properties_changed.connect (this.on_properties_changed);
    }

    public bool seek (Gst.ClockTime time) {
        var ret = false;

        try {
            this.actual_player.seek ((int64) (time / 1000));
            ret = true;
        } catch (Error error) {}

        return ret;
    }

    public string[] get_protocols () {
        return this.protocols;
    }

    public string[] get_mime_types () {
        return this.mime_types;
    }

    private string mpris_to_upnp_state (string state) {
        switch (state) {
        case "Stopped":
            return "STOPPED";
        case "Paused":
            return "PAUSED_PLAYBACK";
        case "Playing":
            return "PLAYING";
        default:
            assert_not_reached ();
        }
    }

    private void on_properties_changed (DBusProxy actual_player,
                                        Variant   changed,
                                        string[]  invalidated) {
        if (!changed.get_type().equal (VariantType.VARDICT)) {
            return;
        }

        foreach (var changed_prop in changed) {
            var key = (string) changed_prop.get_child_value (0);
            var value = changed_prop.get_child_value (1).get_child_value (0);

            switch (key) {
            case "PlaybackStatus":
                this.notify_property ("playback-state");

                break;
            case "Volume":
                this.notify_property ("volume");

                break;
            case "Metadata":
                this.on_properties_changed (actual_player,
                                            value,
                                            new string[0]);

                break;
            case "xesam:url":
                this.notify_property ("uri");

                break;
            case "mpris:length":
                this.notify_property ("duration");

                break;
            }
        }
    }
}
