/* GStreamer
 * Copyright (C)  2005 Wim Taymans <wim@fluendo.com>
 *
 * gstalsasink.h: 
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


#ifndef __GST_ALSASINK_H__
#define __GST_ALSASINK_H__


#include <gst/gst.h>
#include <gst/audio/gstaudiosink.h>
#include <alsa/asoundlib.h>

#include <netinet/in.h>

#if defined(MULTI_ROOM_SUPPORT)
#include <stdbool.h>
#include "multiroom.h"
#endif



G_BEGIN_DECLS

#define GST_TYPE_ALSA_SINK            (gst_alsasink_get_type())
#define GST_ALSA_SINK(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_ALSA_SINK,GstAlsaSink))
#define GST_ALSA_SINK_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_ALSA_SINK,GstAlsaSinkClass))
#define GST_IS_ALSA_SINK(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_ALSA_SINK))
#define GST_IS_ALSA_SINK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_ALSA_SINK))
#define GST_ALSA_SINK_CAST(obj)       ((GstAlsaSink *) (obj))

typedef struct _GstAlsaSink GstAlsaSink;
typedef struct _GstAlsaSinkClass GstAlsaSinkClass;

#define GST_ALSA_SINK_GET_LOCK(obj)	    (GST_ALSA_SINK_CAST (obj)->alsa_lock)
#define GST_ALSA_SINK_LOCK(obj)	        (g_mutex_lock (GST_ALSA_SINK_GET_LOCK (obj)))
#define GST_ALSA_SINK_UNLOCK(obj)	    (g_mutex_unlock (GST_ALSA_SINK_GET_LOCK (obj)))

/**
 * GstAlsaSink:
 *
 * Opaque data structure
 */
struct _GstAlsaSink {
  GstAudioSink    sink;

  gchar                 *device;

  snd_pcm_t             *handle;
  snd_pcm_hw_params_t   *hwparams;
  snd_pcm_sw_params_t   *swparams;

  snd_pcm_access_t access;
  snd_pcm_format_t format;
  guint rate;
  guint channels;
  gint bytes_per_sample; // actually it is bytes_per_frame
  gboolean iec958;
  gboolean need_swap;

  guint buffer_time;
  guint period_time;
  snd_pcm_uframes_t buffer_size;
  snd_pcm_uframes_t period_size;

  GstCaps *cached_caps;

  GMutex *alsa_lock;


#if defined(MULTI_ROOM_SUPPORT)
    multiroom_userdata_t *mr_u;
#endif
	guint bypassalsa;
	guint inalsa_write;
	guint amz_announce_alsa_state;
};

struct _GstAlsaSinkClass {
  GstAudioSinkClass parent_class;
};

GType gst_alsasink_get_type(void);

G_END_DECLS

#endif /* __GST_ALSASINK_H__ */
