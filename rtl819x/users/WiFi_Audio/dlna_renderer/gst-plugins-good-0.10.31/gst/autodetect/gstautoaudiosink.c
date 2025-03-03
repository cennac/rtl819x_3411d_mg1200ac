/* GStreamer
 * (c) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * (c) 2006 Jan Schmidt <thaytan@noraisin.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-autoaudiosink
 * @see_also: autovideosink, alsasink, osssink
 *
 * autoaudiosink is an audio sink that automatically detects an appropriate
 * audio sink to use.  It does so by scanning the registry for all elements
 * that have <quote>Sink</quote> and <quote>Audio</quote> in the class field
 * of their element information, and also have a non-zero autoplugging rank.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m audiotestsrc ! audioconvert ! audioresample ! autoaudiosink
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include "gstautoaudiosink.h"
#include "gstautodetect.h"

#define DEFAULT_SLAVE_VOLUME 1024

/* Properties */
enum
{
  PROP_0,
  PROP_CAPS,
  PROP_SLAVE_VOLUME,
  PROP_BYPASS_ALSA,
};

static GstStateChangeReturn
gst_auto_audio_sink_change_state (GstElement * element,
    GstStateChange transition);
static void gst_auto_audio_sink_dispose (GstAutoAudioSink * sink);
static void gst_auto_audio_sink_clear_kid (GstAutoAudioSink * sink);
static void gst_auto_audio_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_auto_audio_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

GST_BOILERPLATE (GstAutoAudioSink, gst_auto_audio_sink, GstBin, GST_TYPE_BIN);

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

static void
gst_auto_audio_sink_base_init (gpointer klass)
{
  GstElementClass *eklass = GST_ELEMENT_CLASS (klass);

  gst_element_class_add_static_pad_template (eklass, &sink_template);

  gst_element_class_set_details_simple (eklass, "Auto audio sink",
      "Sink/Audio",
      "Wrapper audio sink for automatically detected audio sink",
      "Jan Schmidt <thaytan@noraisin.net>");
}

static void
gst_auto_audio_sink_class_init (GstAutoAudioSinkClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *eklass;

  gobject_class = G_OBJECT_CLASS (klass);
  eklass = GST_ELEMENT_CLASS (klass);

  gobject_class->dispose = (GObjectFinalizeFunc) gst_auto_audio_sink_dispose;
  gobject_class->set_property = gst_auto_audio_sink_set_property;
  gobject_class->get_property = gst_auto_audio_sink_get_property;

  eklass->change_state = GST_DEBUG_FUNCPTR (gst_auto_audio_sink_change_state);

  /**
   * GstAutoAudioSink:filter-caps
   *
   * This property will filter out candidate sinks that can handle the specified
   * caps. By default only audio sinks that support raw floating point and
   * integer audio are selected.
   *
   * This property can only be set before the element goes to the READY state.
   *
   * Since: 0.10.7
   **/
  g_object_class_install_property (gobject_class, PROP_CAPS,
      g_param_spec_boxed ("filter-caps", "Filter caps",
          "Filter sink candidates using these caps.", GST_TYPE_CAPS,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, PROP_SLAVE_VOLUME,
          g_param_spec_int ("slave-volume", "Slave Audio Volume",
              "The audio volume of slave speakers", 0, 1024,
              DEFAULT_SLAVE_VOLUME,
              G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));
              
g_object_class_install_property (gobject_class, PROP_BYPASS_ALSA,
      g_param_spec_int ("bypass-alsa", "Bypass ALSA write",
          "skip alsa write while playing", 0, 3,
          0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));              
}

static void
gst_auto_audio_sink_dispose (GstAutoAudioSink * sink)
{
  gst_auto_audio_sink_clear_kid (sink);

  if (sink->filter_caps)
    gst_caps_unref (sink->filter_caps);
  sink->filter_caps = NULL;

  G_OBJECT_CLASS (parent_class)->dispose ((GObject *) sink);
}

static void
gst_auto_audio_sink_clear_kid (GstAutoAudioSink * sink)
{
  if (sink->kid) {
    gst_element_set_state (sink->kid, GST_STATE_NULL);
    gst_bin_remove (GST_BIN (sink), sink->kid);
    sink->kid = NULL;
    /* Don't lose the SINK flag */
    GST_OBJECT_FLAG_SET (sink, GST_ELEMENT_IS_SINK);
  }
}

/*
 * Hack to make initial linking work; ideally, this'd work even when
 * no target has been assigned to the ghostpad yet.
 */
static void
gst_auto_audio_sink_reset (GstAutoAudioSink * sink)
{
  GstPad *targetpad;

  gst_auto_audio_sink_clear_kid (sink);

  /* fakesink placeholder */
  sink->kid = gst_element_factory_make ("fakesink", "tempsink");
  gst_bin_add (GST_BIN (sink), sink->kid);

  /* pad */
  targetpad = gst_element_get_static_pad (sink->kid, "sink");
  gst_ghost_pad_set_target (GST_GHOST_PAD (sink->pad), targetpad);
  gst_object_unref (targetpad);
}

static GstStaticCaps raw_caps =
    GST_STATIC_CAPS ("audio/x-raw-int; audio/x-raw-float");

static void
gst_auto_audio_sink_init (GstAutoAudioSink * sink,
    GstAutoAudioSinkClass * g_class)
{
  sink->pad = gst_ghost_pad_new_no_target ("sink", GST_PAD_SINK);
  gst_element_add_pad (GST_ELEMENT (sink), sink->pad);

  gst_auto_audio_sink_reset (sink);

  /* set the default raw audio caps */
  sink->filter_caps = gst_static_caps_get (&raw_caps);

  /* mark as sink */
  GST_OBJECT_FLAG_SET (sink, GST_ELEMENT_IS_SINK);
}

static gboolean
gst_auto_audio_sink_factory_filter (GstPluginFeature * feature, gpointer data)
{
  guint rank;
  const gchar *klass;

  /* we only care about element factories */
  if (!GST_IS_ELEMENT_FACTORY (feature))
    return FALSE;

  /* audio sinks */
  klass = gst_element_factory_get_klass (GST_ELEMENT_FACTORY (feature));
  if (!(strstr (klass, "Sink") && strstr (klass, "Audio")))
    return FALSE;

  /* only select elements with autoplugging rank */
  rank = gst_plugin_feature_get_rank (feature);
  if (rank < GST_RANK_MARGINAL)
    return FALSE;

  return TRUE;
}

static gint
gst_auto_audio_sink_compare_ranks (GstPluginFeature * f1, GstPluginFeature * f2)
{
  gint diff;

  diff = gst_plugin_feature_get_rank (f2) - gst_plugin_feature_get_rank (f1);
  if (diff != 0)
    return diff;
  return strcmp (gst_plugin_feature_get_name (f2),
      gst_plugin_feature_get_name (f1));
}

static GstElement *
gst_auto_audio_sink_create_element_with_pretty_name (GstAutoAudioSink * sink,
    GstElementFactory * factory)
{
  GstElement *element;
  gchar *name, *marker;

  marker = g_strdup (GST_PLUGIN_FEATURE (factory)->name);
  if (g_str_has_suffix (marker, "sink"))
    marker[strlen (marker) - 4] = '\0';
  if (g_str_has_prefix (marker, "gst"))
    g_memmove (marker, marker + 3, strlen (marker + 3) + 1);
  name = g_strdup_printf ("%s-actual-sink-%s", GST_OBJECT_NAME (sink), marker);
  g_free (marker);

  element = gst_element_factory_create (factory, name);
  g_free (name);

  return element;
}

static GstElement *
gst_auto_audio_sink_find_best (GstAutoAudioSink * sink)
{
  GList *list, *item;
  GstElement *choice = NULL;
  GstMessage *message = NULL;
  GSList *errors = NULL;
  GstBus *bus = gst_bus_new ();
  GstPad *el_pad = NULL;
  GstCaps *el_caps = NULL;
  gboolean no_match = TRUE;

  list = gst_registry_feature_filter (gst_registry_get_default (),
      (GstPluginFeatureFilter) gst_auto_audio_sink_factory_filter, FALSE, sink);
  list = g_list_sort (list, (GCompareFunc) gst_auto_audio_sink_compare_ranks);

  /* We don't treat sound server sinks special. Our policy is that sound
   * server sinks that have a rank must not auto-spawn a daemon under any
   * circumstances, so there's nothing for us to worry about here */
  GST_LOG_OBJECT (sink, "Trying to find usable audio devices ...");

  for (item = list; item != NULL; item = item->next) {
    GstElementFactory *f = GST_ELEMENT_FACTORY (item->data);
    GstElement *el;

    if ((el = gst_auto_audio_sink_create_element_with_pretty_name (sink, f))) {
      GstStateChangeReturn ret;

      GST_DEBUG_OBJECT (sink, "Testing %s", GST_PLUGIN_FEATURE (f)->name);

      /* If autoaudiosink has been provided with filter caps,
       * accept only sinks that match with the filter caps */
      if (sink->filter_caps) {
        el_pad = gst_element_get_static_pad (GST_ELEMENT (el), "sink");
        el_caps = gst_pad_get_caps (el_pad);
        gst_object_unref (el_pad);
        GST_DEBUG_OBJECT (sink,
            "Checking caps: %" GST_PTR_FORMAT " vs. %" GST_PTR_FORMAT,
            sink->filter_caps, el_caps);
        no_match = !gst_caps_can_intersect (sink->filter_caps, el_caps);
        gst_caps_unref (el_caps);

        if (no_match) {
          GST_DEBUG_OBJECT (sink, "Incompatible caps");
          gst_object_unref (el);
          continue;
        } else {
          GST_DEBUG_OBJECT (sink, "Found compatible caps");
        }
      }

      gst_element_set_bus (el, bus);
      ret = gst_element_set_state (el, GST_STATE_READY);
      if (ret == GST_STATE_CHANGE_SUCCESS) {
        GST_DEBUG_OBJECT (sink, "This worked!");
        choice = el;
        break;
      }

      /* collect all error messages */
      while ((message = gst_bus_pop_filtered (bus, GST_MESSAGE_ERROR))) {
        GST_DEBUG_OBJECT (sink, "error message %" GST_PTR_FORMAT, message);
        errors = g_slist_append (errors, message);
      }

      gst_element_set_state (el, GST_STATE_NULL);
      gst_object_unref (el);
    }
  }

  GST_DEBUG_OBJECT (sink, "done trying");
  if (!choice) {
    if (errors) {
      /* FIXME: we forward the first error for now; but later on it might make
       * sense to actually analyse them */
      gst_message_ref (GST_MESSAGE (errors->data));
      GST_DEBUG_OBJECT (sink, "reposting message %p", errors->data);
      gst_element_post_message (GST_ELEMENT (sink), GST_MESSAGE (errors->data));
    } else {
      /* send warning message to application and use a fakesink */
      GST_ELEMENT_WARNING (sink, RESOURCE, NOT_FOUND, (NULL),
          ("Failed to find a usable audio sink"));
      choice = gst_element_factory_make ("fakesink", "fake-audio-sink");
      if (g_object_class_find_property (G_OBJECT_GET_CLASS (choice), "sync"))
        g_object_set (choice, "sync", TRUE, NULL);
      gst_element_set_state (choice, GST_STATE_READY);
    }
  }
  gst_object_unref (bus);
  gst_plugin_feature_list_free (list);
  g_slist_foreach (errors, (GFunc) gst_mini_object_unref, NULL);
  g_slist_free (errors);

  return choice;
}

static gboolean
gst_auto_audio_sink_detect (GstAutoAudioSink * sink)
{
  GstElement *esink;
  GstPad *targetpad;

  gst_auto_audio_sink_clear_kid (sink);

  /* find element */
  GST_DEBUG_OBJECT (sink, "Creating new kid");
  if (!(esink = gst_auto_audio_sink_find_best (sink)))
    goto no_sink;

  sink->kid = esink;
  /* Ensure the child is brought up to the right state to match the parent
   * although it's currently always in READY and 
   * we're always doing NULL->READY. */
  if (GST_STATE (sink->kid) < GST_STATE (sink))
    gst_element_set_state (sink->kid, GST_STATE (sink));

  gst_bin_add (GST_BIN (sink), esink);

  /* attach ghost pad */
  GST_DEBUG_OBJECT (sink, "Re-assigning ghostpad");
  targetpad = gst_element_get_static_pad (sink->kid, "sink");
  if (!gst_ghost_pad_set_target (GST_GHOST_PAD (sink->pad), targetpad))
    goto target_failed;

  gst_object_unref (targetpad);
  GST_DEBUG_OBJECT (sink, "done changing auto audio sink");

  return TRUE;

  /* ERRORS */
no_sink:
  {
    GST_ELEMENT_ERROR (sink, LIBRARY, INIT, (NULL),
        ("Failed to find a supported audio sink"));
    return FALSE;
  }
target_failed:
  {
    GST_ELEMENT_ERROR (sink, LIBRARY, INIT, (NULL),
        ("Failed to set target pad"));
    gst_object_unref (targetpad);
    return FALSE;
  }
}

static GstStateChangeReturn
gst_auto_audio_sink_change_state (GstElement * element,
    GstStateChange transition)
{
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
  GstAutoAudioSink *sink = GST_AUTO_AUDIO_SINK (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      if (!gst_auto_audio_sink_detect (sink))
        return GST_STATE_CHANGE_FAILURE;
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
  if (ret == GST_STATE_CHANGE_FAILURE)
    return ret;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_NULL:
      gst_auto_audio_sink_reset (sink);
      break;
    default:
      break;
  }

  return ret;
}

static void
gst_auto_audio_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstAutoAudioSink *sink = GST_AUTO_AUDIO_SINK (object);

  switch (prop_id) {
    case PROP_CAPS:
      if (sink->filter_caps)
        gst_caps_unref (sink->filter_caps);
      sink->filter_caps = gst_caps_copy (gst_value_get_caps (value));
      break;
    case PROP_SLAVE_VOLUME:
      if (sink->kid) {
          g_object_set (sink->kid, "slave-volume", g_value_get_int(value), NULL);
      }
      break;
        case PROP_BYPASS_ALSA:
      if (sink->kid) {
          g_object_set (sink->kid, "bypass-alsa", g_value_get_int(value), NULL);
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_auto_audio_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstAutoAudioSink *sink = GST_AUTO_AUDIO_SINK (object);
 gint int_temp;
  switch (prop_id) {
    case PROP_CAPS:{
      gst_value_set_caps (value, sink->filter_caps);
      break;
    }
    case PROP_BYPASS_ALSA:
    	 if (sink->kid) {
    	 	g_object_get(G_OBJECT(sink->kid), "bypass-alsa", &int_temp, NULL);
      		g_value_set_int (value, int_temp);
      	}
      break;
      
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
