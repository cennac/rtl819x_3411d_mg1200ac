/* GStreamer
 * Copyright (C) <1999> Erik Walthinsen <omega@cse.ogi.edu>,
 *               <2006> Edward Hervey <bilboed@bilboed.com>
 *               <2006> Wim Taymans <wim@fluendo.com>
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#ifdef HAVE_FFMPEG_UNINSTALLED
#include <avformat.h>
#ifdef HAVE_AVI_H
#include <avi.h>
#endif
#else
#include <libavformat/avformat.h>
#ifdef HAVE_AVI_H
#include <ffmpeg/avi.h>
#endif
#endif
#include <stdio.h>
#include <gst/gst.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "gstffmpeg.h"
#include "gstffmpegcodecmap.h"
#include "gstffmpegutils.h"
#include "gstffmpegpipe.h"
#include "libavutil/mem.h"
#define MAX_STREAMS 20

typedef struct _GstFFMpegDemux GstFFMpegDemux;
typedef struct _GstFFStream GstFFStream;
typedef struct _GstFFMpegAPEContext GstFFMpegAPEContext;
struct _GstFFStream
{
  GstPad *pad;

  AVStream *avstream;

  gboolean unknown;
  GstClockTime last_ts;
  gboolean discont;
  gboolean eos;
  GstFlowReturn last_flow;

  GstTagList *tags;             /* stream tags */
};

struct _GstFFMpegDemux
{
  GstElement element;

  /* We need to keep track of our pads, so we do so here. */
  GstPad *sinkpad;

  AVFormatContext *context;
  gboolean opened;

  GstFFStream *streams[MAX_STREAMS];

  gint videopads, audiopads;

  GstClockTime start_time;
  GstClockTime duration;

  /* TRUE if working in pull-mode */
  gboolean seekable;

  /* TRUE if the avformat demuxer can reliably handle streaming mode */
  gboolean can_push;

  gboolean flushing;

  /* segment stuff */
  GstSegment segment;
  gboolean running;

  /* cached seek in READY */
  GstEvent *seek_event;

  /* cached upstream events */
  GList *cached_events;

  /* push mode data */
  GstFFMpegPipe ffpipe;
  GstTask *task;
  GStaticRecMutex *task_lock;
  unsigned int inPushMode;
  unsigned int audio_frame_idx;
  unsigned int IsinSeeking;
  uint32_t isPauseCauseReadEnd;
  uint32_t isAPESeekable;
};

typedef struct _GstFFMpegDemuxClass GstFFMpegDemuxClass;

struct _GstFFMpegDemuxClass
{
  GstElementClass parent_class;

  AVInputFormat *in_plugin;
  GstPadTemplate *sinktempl;
  GstPadTemplate *videosrctempl;
  GstPadTemplate *audiosrctempl;
};

struct _GstFFMpegAPEFrame 
{
    int64_t pos;
    int nblocks;
    int size;
    int skip;
    int64_t pts;
     int64_t duration;
};

struct _GstFFMpegAPEContext
{
    /* Derived fields */
    uint32_t junklength;
    uint32_t firstframe;
    uint32_t totalsamples;
    int currentframe;
    struct _GstFFMpegAPEFrame *frames;

    /* Info from Descriptor Block */
    char magic[4];
    int16_t fileversion;
    int16_t padding1;
    uint32_t descriptorlength;
    uint32_t headerlength;
    uint32_t seektablelength;
    uint32_t wavheaderlength;
    uint32_t audiodatalength;
    uint32_t audiodatalength_high;
    uint32_t wavtaillength;
    uint8_t md5[16];

    /* Info from Header Block */
    uint16_t compressiontype;
    uint16_t formatflags;
    uint32_t blocksperframe;
    uint32_t finalframeblocks;
    uint32_t totalframes;
    uint16_t bps;
    uint16_t channels;
    uint32_t samplerate;

    /* Seektable */
    uint32_t *seektable;
    uint32_t inPushMode;
    uint32_t isAPESeekable;
};

/* A number of function prototypes are given so we can refer to them later. */
static void gst_ffmpegdemux_class_init (GstFFMpegDemuxClass * klass);
static void gst_ffmpegdemux_base_init (GstFFMpegDemuxClass * klass);
static void gst_ffmpegdemux_init (GstFFMpegDemux * demux);
static void gst_ffmpegdemux_finalize (GObject * object);

static gboolean gst_ffmpegdemux_sink_event (GstPad * sinkpad, GstEvent * event);
static GstFlowReturn gst_ffmpegdemux_chain (GstPad * sinkpad, GstBuffer * buf);

static void gst_ffmpegdemux_loop (GstFFMpegDemux * demux);
static gboolean gst_ffmpegdemux_sink_activate (GstPad * sinkpad);
static gboolean
gst_ffmpegdemux_sink_activate_pull (GstPad * sinkpad, gboolean active);
static gboolean
gst_ffmpegdemux_sink_activate_push (GstPad * sinkpad, gboolean active);

#if 0
static gboolean
gst_ffmpegdemux_src_convert (GstPad * pad,
    GstFormat src_fmt,
    gint64 src_value, GstFormat * dest_fmt, gint64 * dest_value);
#endif
static gboolean
gst_ffmpegdemux_send_event (GstElement * element, GstEvent * event);
static GstStateChangeReturn
gst_ffmpegdemux_change_state (GstElement * element, GstStateChange transition);

#define GST_FFDEMUX_PARAMS_QDATA g_quark_from_static_string("ffdemux-params")

static GstElementClass *parent_class = NULL;
GstFFMpegAPEContext *CurrentAPEContext=NULL;
unsigned char *LocalRing=NULL;
unsigned int  LocalRing_Pos=0;
#define LOCAL_RING_MAX 2048*1024
gint64 export_Current_Demux_ts=-1;
static const gchar *
gst_ffmpegdemux_averror (gint av_errno)
{
  const gchar *message = NULL;

  switch (av_errno) {
    case AVERROR (EINVAL):
      message = "Unknown error";
      break;
    case AVERROR (EIO):
      message = "Input/output error";
      break;
    case AVERROR (EDOM):
      message = "Number syntax expected in filename";
      break;
    case AVERROR (ENOMEM):
      message = "Not enough memory";
      break;
    case AVERROR (EILSEQ):
      message = "Unknown format";
      break;
    case AVERROR (ENOSYS):
      message = "Operation not supported";
      break;
    default:
      message = "Unhandled error code received";
      break;
  }

  return message;
}

static void
gst_ffmpegdemux_base_init (GstFFMpegDemuxClass * klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  AVInputFormat *in_plugin;
  gchar *p, *name;
  GstCaps *sinkcaps;
  GstPadTemplate *sinktempl, *audiosrctempl, *videosrctempl;
  gchar *longname, *description;

  in_plugin = (AVInputFormat *)
      g_type_get_qdata (G_OBJECT_CLASS_TYPE (klass), GST_FFDEMUX_PARAMS_QDATA);
  g_assert (in_plugin != NULL);

  p = name = g_strdup (in_plugin->name);
  while (*p) {
    if (*p == '.' || *p == ',')
      *p = '_';
    p++;
  }

  /* construct the element details struct */
  longname = g_strdup_printf ("FFmpeg %s demuxer", in_plugin->long_name);
  description = g_strdup_printf ("FFmpeg %s demuxer", in_plugin->long_name);
  gst_element_class_set_details_simple (element_class, longname,
      "Codec/Demuxer", description,
      "Wim Taymans <wim@fluendo.com>, "
      "Ronald Bultje <rbultje@ronald.bitfreak.net>, "
      "Edward Hervey <bilboed@bilboed.com>");
  g_free (longname);
  g_free (description);

  /* pad templates */
  sinkcaps = gst_ffmpeg_formatid_to_caps (name);
  sinktempl = gst_pad_template_new ("sink",
      GST_PAD_SINK, GST_PAD_ALWAYS, sinkcaps);
  videosrctempl = gst_pad_template_new ("video_%02d",
      GST_PAD_SRC, GST_PAD_SOMETIMES, GST_CAPS_ANY);
  audiosrctempl = gst_pad_template_new ("audio_%02d",
      GST_PAD_SRC, GST_PAD_SOMETIMES, GST_CAPS_ANY);

  gst_element_class_add_pad_template (element_class, videosrctempl);
  gst_element_class_add_pad_template (element_class, audiosrctempl);
  gst_element_class_add_pad_template (element_class, sinktempl);

  klass->in_plugin = in_plugin;
  klass->videosrctempl = videosrctempl;
  klass->audiosrctempl = audiosrctempl;
  klass->sinktempl = sinktempl;
}

static void
gst_ffmpegdemux_class_init (GstFFMpegDemuxClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->finalize = GST_DEBUG_FUNCPTR (gst_ffmpegdemux_finalize);

  gstelement_class->change_state = gst_ffmpegdemux_change_state;
  gstelement_class->send_event = gst_ffmpegdemux_send_event;
}

static void
gst_ffmpegdemux_init (GstFFMpegDemux * demux)
{
  GstFFMpegDemuxClass *oclass =
      (GstFFMpegDemuxClass *) (G_OBJECT_GET_CLASS (demux));
  gint n;

  demux->sinkpad = gst_pad_new_from_template (oclass->sinktempl, "sink");
  gst_pad_set_activate_function (demux->sinkpad,
      GST_DEBUG_FUNCPTR (gst_ffmpegdemux_sink_activate));
  gst_pad_set_activatepull_function (demux->sinkpad,
      GST_DEBUG_FUNCPTR (gst_ffmpegdemux_sink_activate_pull));
  gst_pad_set_activatepush_function (demux->sinkpad,
      GST_DEBUG_FUNCPTR (gst_ffmpegdemux_sink_activate_push));
  gst_element_add_pad (GST_ELEMENT (demux), demux->sinkpad);

  /* push based setup */
  /* the following are not used in pull-based mode, so safe to set anyway */
  gst_pad_set_event_function (demux->sinkpad,
      GST_DEBUG_FUNCPTR (gst_ffmpegdemux_sink_event));
  gst_pad_set_chain_function (demux->sinkpad,
      GST_DEBUG_FUNCPTR (gst_ffmpegdemux_chain));
  /* task for driving ffmpeg in loop function */
  demux->task = gst_task_create ((GstTaskFunction) gst_ffmpegdemux_loop, demux);
  demux->task_lock = g_new (GStaticRecMutex, 1);
  g_static_rec_mutex_init (demux->task_lock);
  gst_task_set_lock (demux->task, demux->task_lock);

  demux->opened = FALSE;
  demux->context = NULL;

  for (n = 0; n < MAX_STREAMS; n++) {
    demux->streams[n] = NULL;
  }
  demux->videopads = 0;
  demux->audiopads = 0;

  demux->seek_event = NULL;
  gst_segment_init (&demux->segment, GST_FORMAT_TIME);

  /* push based data */
  demux->ffpipe.tlock = g_mutex_new ();
  demux->ffpipe.cond = g_cond_new ();
  demux->ffpipe.adapter = gst_adapter_new ();
demux->audio_frame_idx = 0;
demux->inPushMode =0;
demux->IsinSeeking = 0;
  /* blacklist unreliable push-based demuxers */
#if 0  
  if (strcmp (oclass->in_plugin->name, "ape"))
    demux->can_push = TRUE;
  else
    demux->can_push = FALSE;
#endif    
    
    demux->can_push = TRUE;
	if (!strcmp (oclass->in_plugin->name, "ape"))
	{
		//g_print("%s, %d init CurrentAPEContext size=%d\n", __FUNCTION__, __LINE__,sizeof(GstFFMpegAPEContext));
		CurrentAPEContext =(GstFFMpegAPEContext *)av_mallocz(sizeof(GstFFMpegAPEContext));
		if(!CurrentAPEContext){
			g_debug("%s, %d init CurrentAPEContext Fail\n", __FUNCTION__, __LINE__);
		}else{
			LocalRing  = (unsigned char *)av_mallocz(LOCAL_RING_MAX);
			if(!LocalRing){
				g_debug("%s, %d init LocalRing Fail\n", __FUNCTION__, __LINE__);
			}
			CurrentAPEContext->inPushMode=0;
		}
		
	}

}

static void
gst_ffmpegdemux_finalize (GObject * object)
{
  GstFFMpegDemux *demux;

  demux = (GstFFMpegDemux *) object;

  g_mutex_free (demux->ffpipe.tlock);
  g_cond_free (demux->ffpipe.cond);
  gst_object_unref (demux->ffpipe.adapter);

  gst_object_unref (demux->task);
  g_static_rec_mutex_free (demux->task_lock);
  g_free (demux->task_lock);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gst_ffmpegdemux_close (GstFFMpegDemux * demux)
{
  gint n;
  GstEvent **event_p;

  if (!demux->opened)
    return;

  /* remove pads from ourselves */
  for (n = 0; n < MAX_STREAMS; n++) {
    GstFFStream *stream;

    stream = demux->streams[n];
    if (stream) {
      if (stream->pad)
        gst_element_remove_pad (GST_ELEMENT (demux), stream->pad);
      if (stream->tags)
        gst_tag_list_free (stream->tags);
      g_free (stream);
    }
    demux->streams[n] = NULL;
  }
  demux->videopads = 0;
  demux->audiopads = 0;
	demux->IsinSeeking=0;
  /* close demuxer context from ffmpeg */
  av_close_input_file (demux->context);
  demux->context = NULL;

  GST_OBJECT_LOCK (demux);
  demux->opened = FALSE;
  event_p = &demux->seek_event;
  gst_event_replace (event_p, NULL);
  GST_OBJECT_UNLOCK (demux);

  gst_segment_init (&demux->segment, GST_FORMAT_TIME);
  av_freep(&CurrentAPEContext->frames);
  av_freep(&CurrentAPEContext->seektable);
  memset(CurrentAPEContext, 0x00, sizeof(struct _GstFFMpegAPEContext));
  av_freep(&CurrentAPEContext);
  av_freep(&LocalRing);
  export_Current_Demux_ts=-1;
  unlink("/var/gstreamer-0.10/inPush");
  
}

/* send an event to all the source pads .
 * Takes ownership of the event.
 *
 * Returns FALSE if none of the source pads handled the event.
 */
static gboolean
gst_ffmpegdemux_push_event (GstFFMpegDemux * demux, GstEvent * event)
{
  gboolean res;
  gint n;

  res = TRUE;

  for (n = 0; n < MAX_STREAMS; n++) {
    GstFFStream *s = demux->streams[n];

    if (s && s->pad) {
      gst_event_ref (event);
      res &= gst_pad_push_event (s->pad, event);
    }
  }
  gst_event_unref (event);

  return res;
}

/* set flags on all streams */
static void
gst_ffmpegdemux_set_flags (GstFFMpegDemux * demux, gboolean discont,
    gboolean eos)
{
  GstFFStream *s;
  gint n;

  for (n = 0; n < MAX_STREAMS; n++) {
    if ((s = demux->streams[n])) {
      s->discont = discont;
      s->eos = eos;
    }
  }
}

/* check if all streams are eos */
static gboolean
gst_ffmpegdemux_is_eos (GstFFMpegDemux * demux)
{
  GstFFStream *s;
  gint n;

  for (n = 0; n < MAX_STREAMS; n++) {
    if ((s = demux->streams[n])) {
      GST_DEBUG ("stream %d %p eos:%d", n, s, s->eos);
      if (!s->eos)
        return FALSE;
    }
  }
  return TRUE;
}

/* Returns True if we at least outputted one buffer */
static gboolean
gst_ffmpegdemux_has_outputted (GstFFMpegDemux * demux)
{
  GstFFStream *s;
  gint n;

  for (n = 0; n < MAX_STREAMS; n++) {
    if ((s = demux->streams[n])) {
      if (GST_CLOCK_TIME_IS_VALID (s->last_ts))
        return TRUE;
    }
  }
  return FALSE;
}

static int do_ape_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    AVStream *st = s->streams[stream_index];
    GstFFMpegAPEContext *ape = s->priv_data;
    int index = av_index_search_timestamp(st, timestamp, flags);

    if (index < 0)
        return -1;
    return index;
}


static gboolean
gst_ffmpegdemux_do_seek (GstFFMpegDemux * demux, GstSegment * segment)
{
  gboolean ret;
  gint seekret;
  gint64 target;
  gint64 fftarget;
  AVStream *stream;
  gint index;

  /* find default index and fail if none is present */
  index = av_find_default_stream_index (demux->context);
  GST_LOG_OBJECT (demux, "default stream index %d", index);
  if (index < 0)
    return FALSE;

  ret = TRUE;

  /* get the stream for seeking */
  stream = demux->context->streams[index];
  /* initial seek position */
  target = segment->last_stop;
  /* convert target to ffmpeg time */
  fftarget = gst_ffmpeg_time_gst_to_ff (target, stream->time_base);

  GST_LOG_OBJECT (demux, "do seek to time %" GST_TIME_FORMAT,
      GST_TIME_ARGS (target));

  /* if we need to land on a keyframe, try to do so, we don't try to do a 
   * keyframe seek if we are not absolutely sure we have an index.*/
  if (segment->flags & GST_SEEK_FLAG_KEY_UNIT) {
    gint keyframeidx;

    GST_LOG_OBJECT (demux, "looking for keyframe in ffmpeg for time %"
        GST_TIME_FORMAT, GST_TIME_ARGS (target));

    /* search in the index for the previous keyframe */
    keyframeidx =
        av_index_search_timestamp (stream, fftarget, AVSEEK_FLAG_BACKWARD);

    GST_LOG_OBJECT (demux, "keyframeidx: %d", keyframeidx);

    if (keyframeidx >= 0) {
      fftarget = stream->index_entries[keyframeidx].timestamp;
      target = gst_ffmpeg_time_ff_to_gst (fftarget, stream->time_base);

      GST_LOG_OBJECT (demux,
          "Found a keyframe at ffmpeg idx: %d timestamp :%" GST_TIME_FORMAT,
          keyframeidx, GST_TIME_ARGS (target));
    }
  }

  GST_DEBUG_OBJECT (demux,
      "About to call av_seek_frame (context, %d, %" G_GINT64_FORMAT
      ", 0) for time %" GST_TIME_FORMAT, index, fftarget,
      GST_TIME_ARGS (target));

  if ((seekret =
          av_seek_frame (demux->context, index, fftarget,
              AVSEEK_FLAG_BACKWARD)) < 0)
    goto seek_failed;

  GST_DEBUG_OBJECT (demux, "seek success, returned %d", seekret);

  segment->last_stop = target;
  segment->time = target;
  segment->start = target;

  return ret;

  /* ERRORS */
seek_failed:
  {
    GST_WARNING_OBJECT (demux, "Call to av_seek_frame failed : %d", seekret);
    return FALSE;
  }
}

/* do a seek in push based mode */
static gboolean gst_ape_demux_handle_seek_push (GstFFMpegDemux * demux, GstEvent * event)
{
  gdouble rate;
  GstFormat format;
  GstSeekFlags flags;
  GstSeekType cur_type, stop_type;
  gint64 cur, stop;
  guint packet;
  gboolean res=FALSE;
  gint index;
  gint64 fftarget;
  gboolean update;
  gint seekret;
  GstSegment seeksegment;
	int ape_frame_index=0;
  gst_event_parse_seek (event, &rate, &format, &flags, &cur_type, &cur,&stop_type, &stop);

  stop_type = GST_SEEK_TYPE_NONE;
  stop = -1;

  GST_DEBUG_OBJECT (demux, "seeking to %" GST_TIME_FORMAT, GST_TIME_ARGS (cur));


	if(CurrentAPEContext != NULL && demux->isAPESeekable){
		 /* find default index and fail if none is present */
  		index = av_find_default_stream_index (demux->context);
  		 fftarget = cur/GST_SECOND;
  		 //g_debug ("%s %d seek to fftarget=%lld", __FUNCTION__, __LINE__,fftarget);
  		if ((seekret =av_seek_frame (demux->context, index, fftarget,AVSEEK_FLAG_BACKWARD)) < 0){
              		g_debug("%s, %d seek_failed\n", __FUNCTION__, __LINE__);
              		return FALSE;
		}
			ape_frame_index = do_ape_read_seek(demux->context, index, fftarget,AVSEEK_FLAG_BACKWARD);
				if(ape_frame_index != -1)
				{
						
						demux->audio_frame_idx = ape_frame_index;
						cur = CurrentAPEContext->frames[ape_frame_index].pos;
						export_Current_Demux_ts = (CurrentAPEContext->frames[demux->audio_frame_idx].pts)*GST_SECOND;
						/* Mark discont on all srcpads and remove eos */
  						gst_ffmpegdemux_set_flags (demux, TRUE, FALSE);
  						gst_adapter_flush (demux->ffpipe.adapter,demux->ffpipe.adapter->size);
				}
	
  GST_DEBUG_OBJECT (demux, "Pushing BYTE seek rate %g, "
      "start %" G_GINT64_FORMAT ", stop %" G_GINT64_FORMAT, rate, cur, stop);
  /* BYTE seek event */
  event = gst_event_new_seek (rate, GST_FORMAT_BYTES, flags, cur_type, cur, stop_type, stop);
  res = gst_pad_push_event (demux->sinkpad, event);
}
  return res;
}


static gboolean
gst_ffmpegdemux_perform_seek (GstFFMpegDemux * demux, GstEvent * event)
{
  gboolean res;
  gdouble rate;
  GstFormat format;
  GstSeekFlags flags;
  GstSeekType cur_type, stop_type;
  gint64 cur, stop;
  gboolean flush;
  gboolean update;
  GstSegment seeksegment;
	int n_streams=0;
	AVCodecContext *ctx=NULL;
	n_streams = demux->context->nb_streams;
		if(n_streams == 1){
			ctx = demux->context->streams[0]->codec;
		}

  if (!demux->seekable) {
  	if(ctx && ctx->codec_id == CODEC_ID_APE){
		if(!demux->isAPESeekable){
			GST_DEBUG_OBJECT (demux, "in push mode; ignoring seek");
	    		g_debug("%s, %d in push mode; ignoring seek", __FUNCTION__, __LINE__);
	    		return FALSE;
		}
	}else{
    GST_DEBUG_OBJECT (demux, "in push mode; ignoring seek");
	    g_debug("%s, %d in push mode; ignoring seek", __FUNCTION__, __LINE__);
    return FALSE;
  }
  }

  GST_DEBUG_OBJECT (demux, "starting seek");

	demux->IsinSeeking=1;
  if (event) {
    gst_event_parse_seek (event, &rate, &format, &flags,
        &cur_type, &cur, &stop_type, &stop);

    /* we have to have a format as the segment format. Try to convert
     * if not. */
	if(ctx && ctx->codec_id == CODEC_ID_APE && demux->inPushMode){     
	    /* we can (re)construct the start later on, but not the end */
	    if (stop_type != GST_SEEK_TYPE_NONE) {
	      
	      return FALSE;
	    }
	    gst_event_ref (event);
	    
		if (!gst_pad_push_event (demux->sinkpad, event)){
			return gst_ape_demux_handle_seek_push (demux, event);
	    }else
	    	{
	    		return FALSE;
	    	}
	}     
     
    if (demux->segment.format != format) {
      GstFormat fmt;

      fmt = demux->segment.format;
      res = TRUE;
      /* FIXME, use source pad */
      if (cur_type != GST_SEEK_TYPE_NONE && cur != -1)
        res = gst_pad_query_convert (demux->sinkpad, format, cur, &fmt, &cur);
      if (res && stop_type != GST_SEEK_TYPE_NONE && stop != -1)
        res = gst_pad_query_convert (demux->sinkpad, format, stop, &fmt, &stop);
      if (!res)
        goto no_format;

      format = fmt;
    }
  } else {
    flags = 0;
  }

  flush = flags & GST_SEEK_FLAG_FLUSH;

  /* send flush start */
  if (flush) {
    /* mark flushing so that the streaming thread can react on it */
    GST_OBJECT_LOCK (demux);
    demux->flushing = TRUE;
    GST_OBJECT_UNLOCK (demux);
    gst_pad_push_event (demux->sinkpad, gst_event_new_flush_start ());
    gst_ffmpegdemux_push_event (demux, gst_event_new_flush_start ());
  } else {
    gst_pad_pause_task (demux->sinkpad);
  }

  /* grab streaming lock, this should eventually be possible, either
   * because the task is paused or our streaming thread stopped
   * because our peer is flushing. */
  GST_PAD_STREAM_LOCK (demux->sinkpad);

  /* make copy into temp structure, we can only update the main one
   * when we actually could do the seek. */
  memcpy (&seeksegment, &demux->segment, sizeof (GstSegment));

  /* now configure the seek segment */
  if (event) {
    gst_segment_set_seek (&seeksegment, rate, format, flags,
        cur_type, cur, stop_type, stop, &update);
  }

  GST_DEBUG_OBJECT (demux, "segment configured from %" G_GINT64_FORMAT
      " to %" G_GINT64_FORMAT ", position %" G_GINT64_FORMAT,
      seeksegment.start, seeksegment.stop, seeksegment.last_stop);

  /* make the sinkpad available for data passing since we might need
   * it when doing the seek */
  if (flush) {
    GST_OBJECT_LOCK (demux);
    demux->flushing = FALSE;
    GST_OBJECT_UNLOCK (demux);
    gst_pad_push_event (demux->sinkpad, gst_event_new_flush_stop ());
  }

  /* do the seek, segment.last_stop contains new position. */
  res = gst_ffmpegdemux_do_seek (demux, &seeksegment);

  /* and prepare to continue streaming */
  if (flush) {
    gint n;

    /* send flush stop, peer will accept data and events again. We
     * are not yet providing data as we still have the STREAM_LOCK. */
    gst_ffmpegdemux_push_event (demux, gst_event_new_flush_stop ());
    for (n = 0; n < MAX_STREAMS; ++n) {
      if (demux->streams[n])
        demux->streams[n]->last_flow = GST_FLOW_OK;
    }
  } else if (res && demux->running) {
    /* we are running the current segment and doing a non-flushing seek,
     * close the segment first based on the last_stop. */
    GST_DEBUG_OBJECT (demux, "closing running segment %" G_GINT64_FORMAT
        " to %" G_GINT64_FORMAT, demux->segment.start,
        demux->segment.last_stop);

    gst_ffmpegdemux_push_event (demux,
        gst_event_new_new_segment (TRUE,
            demux->segment.rate, demux->segment.format,
            demux->segment.start, demux->segment.last_stop,
            demux->segment.time));
  }
  /* if successfull seek, we update our real segment and push
   * out the new segment. */
  if (res) {
    memcpy (&demux->segment, &seeksegment, sizeof (GstSegment));

    if (demux->segment.flags & GST_SEEK_FLAG_SEGMENT) {
      gst_element_post_message (GST_ELEMENT (demux),
          gst_message_new_segment_start (GST_OBJECT (demux),
              demux->segment.format, demux->segment.last_stop));
    }

    /* now send the newsegment */
    GST_DEBUG_OBJECT (demux, "Sending newsegment from %" G_GINT64_FORMAT
        " to %" G_GINT64_FORMAT, demux->segment.last_stop, demux->segment.stop);

    gst_ffmpegdemux_push_event (demux,
        gst_event_new_new_segment (FALSE,
            demux->segment.rate, demux->segment.format,
            demux->segment.last_stop, demux->segment.stop,
            demux->segment.time));
  }

  /* Mark discont on all srcpads and remove eos */
  gst_ffmpegdemux_set_flags (demux, TRUE, FALSE);

  /* and restart the task in case it got paused explicitely or by
   * the FLUSH_START event we pushed out. */
  demux->running = TRUE;
  gst_pad_start_task (demux->sinkpad, (GstTaskFunction) gst_ffmpegdemux_loop,
      demux->sinkpad);

  /* and release the lock again so we can continue streaming */
  GST_PAD_STREAM_UNLOCK (demux->sinkpad);

  return res;

  /* ERROR */
no_format:
  {
    GST_DEBUG_OBJECT (demux, "undefined format given, seek aborted.");
    return FALSE;
  }
}

static gboolean
gst_ffmpegdemux_src_event (GstPad * pad, GstEvent * event)
{
  GstFFMpegDemux *demux;
  GstFFStream *stream;
  gboolean res = TRUE;

  if (!(stream = gst_pad_get_element_private (pad)))
    return FALSE;

  demux = (GstFFMpegDemux *) gst_pad_get_parent (pad);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
      res = gst_ffmpegdemux_perform_seek (demux, event);
      gst_event_unref (event);
      break;
    case GST_EVENT_LATENCY:
      res = gst_pad_push_event (demux->sinkpad, event);
      break;
    case GST_EVENT_NAVIGATION:
    case GST_EVENT_QOS:
    default:
      res = FALSE;
      gst_event_unref (event);
      break;
  }

  gst_object_unref (demux);

  return res;
}

static const GstQueryType *
gst_ffmpegdemux_src_query_list (GstPad * pad)
{
  static const GstQueryType src_types[] = {
    GST_QUERY_DURATION,
    GST_QUERY_POSITION,
    GST_QUERY_SEEKING,
    0
  };

  return src_types;
}

static gboolean
gst_ffmpegdemux_send_event (GstElement * element, GstEvent * event)
{
  GstFFMpegDemux *demux = (GstFFMpegDemux *) (element);
  gboolean res;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
      GST_OBJECT_LOCK (demux);
      if (!demux->opened) {
        GstEvent **event_p;

        GST_DEBUG_OBJECT (demux, "caching seek event");
        event_p = &demux->seek_event;
        gst_event_replace (event_p, event);
        GST_OBJECT_UNLOCK (demux);

        res = TRUE;
      } else {
        GST_OBJECT_UNLOCK (demux);
        res = gst_ffmpegdemux_perform_seek (demux, event);
        gst_event_unref (event);
      }
      break;
    default:
      res = FALSE;
      break;
  }

  return res;
}

static gboolean
gst_ffmpegdemux_src_query (GstPad * pad, GstQuery * query)
{
  GstFFMpegDemux *demux;
  GstFFStream *stream;
  AVStream *avstream;
  gboolean res = FALSE;
AVCodecContext *ctx=NULL;
int n_streams=0;
  if (!(stream = gst_pad_get_element_private (pad)))
    return FALSE;

  avstream = stream->avstream;

  demux = (GstFFMpegDemux *) GST_PAD_PARENT (pad);

	n_streams = demux->context->nb_streams;
		if(n_streams == 1){
			ctx = demux->context->streams[0]->codec;
		}
			


  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_POSITION:
    {
      GstFormat format;
      gint64 timeposition;

      gst_query_parse_position (query, &format, NULL);

      timeposition = stream->last_ts;
      if (!(GST_CLOCK_TIME_IS_VALID (timeposition)))
        break;

      switch (format) {
        case GST_FORMAT_TIME:
          gst_query_set_position (query, GST_FORMAT_TIME, timeposition);
          res = TRUE;
          break;
        case GST_FORMAT_DEFAULT:
          gst_query_set_position (query, GST_FORMAT_DEFAULT,
              gst_util_uint64_scale (timeposition, avstream->r_frame_rate.num,
                  GST_SECOND * avstream->r_frame_rate.den));
          res = TRUE;
          break;
        case GST_FORMAT_BYTES:
          if (demux->videopads + demux->audiopads == 1 &&
              GST_PAD_PEER (demux->sinkpad) != NULL)
            res = gst_pad_query_default (pad, query);
          break;
        default:
          break;
      }
    }
      break;
    case GST_QUERY_DURATION:
    {
      GstFormat format;
      gint64 timeduration;

      gst_query_parse_duration (query, &format, NULL);

      timeduration =
          gst_ffmpeg_time_ff_to_gst (avstream->duration, avstream->time_base);
      if (!(GST_CLOCK_TIME_IS_VALID (timeduration))) {
        /* use duration of complete file if the stream duration is not known */
        timeduration = demux->duration;
        if (!(GST_CLOCK_TIME_IS_VALID (timeduration)))
          break;
      }
  timeduration = demux->duration;
      switch (format) {
        case GST_FORMAT_TIME:
        	if(ctx && ctx->codec_id == CODEC_ID_APE){
        		gst_query_set_duration (query, GST_FORMAT_TIME, demux->duration);
        	}else
          	gst_query_set_duration (query, GST_FORMAT_TIME, timeduration);
          res = TRUE;
          break;
        case GST_FORMAT_DEFAULT:
          gst_query_set_duration (query, GST_FORMAT_DEFAULT,
              gst_util_uint64_scale (timeduration, avstream->r_frame_rate.num,
                  GST_SECOND * avstream->r_frame_rate.den));
          res = TRUE;
          break;
        case GST_FORMAT_BYTES:
          if (demux->videopads + demux->audiopads == 1 &&
              GST_PAD_PEER (demux->sinkpad) != NULL)
            res = gst_pad_query_default (pad, query);
          break;
        default:
          break;
      }
    }
      break;
    case GST_QUERY_SEEKING:{
      GstFormat format;
      gboolean seekable;
      gint64 dur = -1;

      gst_query_parse_seeking (query, &format, NULL, NULL, NULL);
      seekable = demux->seekable;
      if(ctx && ctx->codec_id == CODEC_ID_APE){
      	
      	if(demux->isAPESeekable==0){
      		seekable = FALSE;
		}else{
			seekable = TRUE;
		}
      }
      if (!gst_pad_query_duration (pad, &format, &dur)) {
        /* unlikely that we don't know duration but can seek */
        seekable = FALSE;
        dur = -1;
      }
      gst_query_set_seeking (query, format, seekable, 0, dur);
      res = TRUE;
      break;
    }
    default:
      /* FIXME : ADD GST_QUERY_CONVERT */
      res = gst_pad_query_default (pad, query);
      break;
  }

  return res;
}

#if 0
/* FIXME, reenable me */
static gboolean
gst_ffmpegdemux_src_convert (GstPad * pad,
    GstFormat src_fmt,
    gint64 src_value, GstFormat * dest_fmt, gint64 * dest_value)
{
  GstFFStream *stream;
  gboolean res = TRUE;
  AVStream *avstream;

  if (!(stream = gst_pad_get_element_private (pad)))
    return FALSE;

  avstream = stream->avstream;
  if (avstream->codec->codec_type != AVMEDIA_TYPE_VIDEO)
    return FALSE;

  switch (src_fmt) {
    case GST_FORMAT_TIME:
      switch (*dest_fmt) {
        case GST_FORMAT_DEFAULT:
          *dest_value = gst_util_uint64_scale (src_value,
              avstream->r_frame_rate.num,
              GST_SECOND * avstream->r_frame_rate.den);
          break;
        default:
          res = FALSE;
          break;
      }
      break;
    case GST_FORMAT_DEFAULT:
      switch (*dest_fmt) {
        case GST_FORMAT_TIME:
          *dest_value = gst_util_uint64_scale (src_value,
              GST_SECOND * avstream->r_frame_rate.num,
              avstream->r_frame_rate.den);
          break;
        default:
          res = FALSE;
          break;
      }
      break;
    default:
      res = FALSE;
      break;
  }

  return res;
}
#endif

static GstFlowReturn
gst_ffmpegdemux_aggregated_flow (GstFFMpegDemux * demux)
{
  gint n;
  GstFlowReturn res = GST_FLOW_OK;
  gboolean have_ok = FALSE;

  for (n = 0; n < MAX_STREAMS; n++) {
    GstFFStream *s = demux->streams[n];

    if (s) {
      res = MIN (res, s->last_flow);

      if (s->last_flow == GST_FLOW_OK)
        have_ok = TRUE;
    }
  }

  /* NOT_LINKED is OK, if at least one pad is linked */
  if (res == GST_FLOW_NOT_LINKED && have_ok)
    res = GST_FLOW_OK;

  GST_DEBUG_OBJECT (demux, "Returning aggregated value of %s",
      gst_flow_get_name (res));

  return res;
}

static gchar *
gst_ffmpegdemux_create_padname (const gchar * templ, gint n)
{
  GString *string;

  string = g_string_new (templ);
  g_string_truncate (string, string->len - 4);
  g_string_append_printf (string, "%02d", n);

  return g_string_free (string, FALSE);
}

static GstFFStream *
gst_ffmpegdemux_get_stream (GstFFMpegDemux * demux, AVStream * avstream)
{
  GstFFMpegDemuxClass *oclass;
  GstPadTemplate *templ = NULL;
  GstPad *pad;
  GstCaps *caps;
  gint num;
  gchar *padname;
  const gchar *codec;
  AVCodecContext *ctx;
  GstFFStream *stream;

  ctx = avstream->codec;

  oclass = (GstFFMpegDemuxClass *) G_OBJECT_GET_CLASS (demux);

  if (demux->streams[avstream->index] != NULL)
    goto exists;

  /* create new stream */
  stream = g_new0 (GstFFStream, 1);
  demux->streams[avstream->index] = stream;

  /* mark stream as unknown */
  stream->unknown = TRUE;
  stream->discont = TRUE;
  stream->avstream = avstream;
  stream->last_ts = GST_CLOCK_TIME_NONE;
  stream->last_flow = GST_FLOW_OK;
  stream->tags = NULL;

  switch (ctx->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
      templ = oclass->videosrctempl;
      num = demux->videopads++;
      break;
    case AVMEDIA_TYPE_AUDIO:
      templ = oclass->audiosrctempl;
      num = demux->audiopads++;
      break;
    default:
      goto unknown_type;
  }

  /* get caps that belongs to this stream */
  caps = gst_ffmpeg_codecid_to_caps (ctx->codec_id, ctx, TRUE);
  if (caps == NULL)
    goto unknown_caps;

  /* stream is known now */
  stream->unknown = FALSE;

  /* create new pad for this stream */
  padname =
      gst_ffmpegdemux_create_padname (GST_PAD_TEMPLATE_NAME_TEMPLATE (templ),
      num);
  pad = gst_pad_new_from_template (templ, padname);
  g_free (padname);

  gst_pad_use_fixed_caps (pad);
  gst_pad_set_caps (pad, caps);
  gst_caps_unref (caps);

  gst_pad_set_query_type_function (pad, gst_ffmpegdemux_src_query_list);
  gst_pad_set_query_function (pad, gst_ffmpegdemux_src_query);
  gst_pad_set_event_function (pad, gst_ffmpegdemux_src_event);

  /* store pad internally */
  stream->pad = pad;
  gst_pad_set_element_private (pad, stream);

  /* transform some useful info to GstClockTime and remember */
  {
    GstClockTime tmp;

    /* FIXME, actually use the start_time in some way */
    tmp = gst_ffmpeg_time_ff_to_gst (avstream->start_time, avstream->time_base);
    GST_DEBUG_OBJECT (demux, "stream %d: start time: %" GST_TIME_FORMAT,
        avstream->index, GST_TIME_ARGS (tmp));

    tmp = gst_ffmpeg_time_ff_to_gst (avstream->duration, avstream->time_base);
    GST_DEBUG_OBJECT (demux, "stream %d: duration: %" GST_TIME_FORMAT,
        avstream->index, GST_TIME_ARGS (tmp));
  }

  demux->streams[avstream->index] = stream;

  /* activate and add */
  gst_pad_set_active (pad, TRUE);
  gst_element_add_pad (GST_ELEMENT (demux), pad);

  /* metadata */
  if ((codec = gst_ffmpeg_get_codecid_longname (ctx->codec_id))) {
    stream->tags = gst_tag_list_new ();

    gst_tag_list_add (stream->tags, GST_TAG_MERGE_REPLACE,
        (ctx->codec_type == AVMEDIA_TYPE_VIDEO) ?
        GST_TAG_VIDEO_CODEC : GST_TAG_AUDIO_CODEC, codec, NULL);
  }

  return stream;

  /* ERRORS */
exists:
  {
    GST_DEBUG_OBJECT (demux, "Pad existed (stream %d)", avstream->index);
    return demux->streams[avstream->index];
  }
unknown_type:
  {
    GST_WARNING_OBJECT (demux, "Unknown pad type %d", ctx->codec_type);
    return stream;
  }
unknown_caps:
  {
    GST_WARNING_OBJECT (demux, "Unknown caps for codec %d", ctx->codec_id);
    return stream;
  }
}

#if 0
    /* Re-enable once converted to new AVMetaData API
     * See #566605
     */
static gchar *
my_safe_copy (gchar * input)
{
  gchar *output;

  if (!(g_utf8_validate (input, -1, NULL))) {
    output = g_convert (input, strlen (input),
        "UTF-8", "ISO-8859-1", NULL, NULL, NULL);
  } else {
    output = g_strdup (input);
  }

  return output;
}

static GstTagList *
gst_ffmpegdemux_read_tags (GstFFMpegDemux * demux)
{
  GstTagList *tlist;
  gboolean hastag = FALSE;

  tlist = gst_tag_list_new ();

  if (*demux->context->title) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_TITLE, my_safe_copy (demux->context->title), NULL);
    hastag = TRUE;
  }
  if (*demux->context->author) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_ARTIST, my_safe_copy (demux->context->author), NULL);
    hastag = TRUE;
  }
  if (*demux->context->copyright) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_COPYRIGHT, my_safe_copy (demux->context->copyright), NULL);
    hastag = TRUE;
  }
  if (*demux->context->comment) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_COMMENT, my_safe_copy (demux->context->comment), NULL);
    hastag = TRUE;
  }
  if (*demux->context->album) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_ALBUM, my_safe_copy (demux->context->album), NULL);
    hastag = TRUE;
  }
  if (demux->context->track) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_TRACK_NUMBER, demux->context->track, NULL);
    hastag = TRUE;
  }
  if (*demux->context->genre) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_GENRE, my_safe_copy (demux->context->genre), NULL);
    hastag = TRUE;
  }
  if (demux->context->year) {
    gst_tag_list_add (tlist, GST_TAG_MERGE_REPLACE,
        GST_TAG_DATE, g_date_new_dmy (1, 1, demux->context->year), NULL);
    hastag = TRUE;
  }

  if (!hastag) {
    gst_tag_list_free (tlist);
    tlist = NULL;
  }
  return tlist;
}
#endif

static void gstffmpegape_dumpinfo( struct _GstFFMpegAPEContext * ape_ctx)
{
#if 1
    g_debug("fileversion          = %"PRId16"\n", ape_ctx->fileversion);
    g_debug( "compressiontype      = %"PRIu16"\n", ape_ctx->compressiontype);
#else
	int i;
    g_debug("Descriptor Block:\n\n");
    g_debug("magic                = \"%c%c%c%c\"\n", ape_ctx->magic[0], ape_ctx->magic[1], ape_ctx->magic[2], ape_ctx->magic[3]);
    g_debug("fileversion          = %"PRId16"\n", ape_ctx->fileversion);
    g_debug("descriptorlength     = %"PRIu32"\n", ape_ctx->descriptorlength);
    g_debug("headerlength         = %"PRIu32"\n", ape_ctx->headerlength);
    g_debug( "seektablelength      = %"PRIu32"\n", ape_ctx->seektablelength);
    g_debug( "wavheaderlength      = %"PRIu32"\n", ape_ctx->wavheaderlength);
    g_debug( "audiodatalength      = %"PRIu32"\n", ape_ctx->audiodatalength);
    g_debug( "audiodatalength_high = %"PRIu32"\n", ape_ctx->audiodatalength_high);
    g_debug( "wavtaillength        = %"PRIu32"\n", ape_ctx->wavtaillength);
    g_debug( "md5                  = ");
    for (i = 0; i < 16; i++)
         g_debug("%02x", ape_ctx->md5[i]);
    g_debug("\n");

    g_debug("\nHeader Block:\n\n");

    g_debug( "compressiontype      = %"PRIu16"\n", ape_ctx->compressiontype);
    g_debug( "formatflags          = %"PRIu16"\n", ape_ctx->formatflags);
    g_debug( "blocksperframe       = %"PRIu32"\n", ape_ctx->blocksperframe);
    g_debug( "finalframeblocks     = %"PRIu32"\n", ape_ctx->finalframeblocks);
    g_debug( "totalframes          = %"PRIu32"\n", ape_ctx->totalframes);
    g_debug( "bps                  = %"PRIu16"\n", ape_ctx->bps);
    g_debug("channels             = %"PRIu16"\n", ape_ctx->channels);
    g_debug( "samplerate           = %"PRIu32"\n", ape_ctx->samplerate);

    g_debug("\nSeektable\n\n");
    if ((ape_ctx->seektablelength / sizeof(uint32_t)) != ape_ctx->totalframes) {
        g_debug("No seektable\n");
    } else {
        for (i = 0; i < ape_ctx->seektablelength / sizeof(uint32_t); i++) {
            if (i < ape_ctx->totalframes - 1) {
               g_debug("%8d   %"PRIu32" (%"PRIu32" bytes)\n",
                       i, ape_ctx->seektable[i],
                       ape_ctx->seektable[i + 1] - ape_ctx->seektable[i]);
            } else {
                g_debug("%8d   %"PRIu32"\n", i, ape_ctx->seektable[i]);
            }
        }
    }

   g_debug("\nFrames\n\n");
    for (i = 0; i < ape_ctx->totalframes; i++){
        g_debug("%8d   %8llX %8X (%d samples), skip=%d\n", i,ape_ctx->frames[i].pos, ape_ctx->frames[i].size,ape_ctx->frames[i].nblocks,ape_ctx->frames[i].skip);
	}
    g_debug("\nCalculated information:\n\n");
    g_debug( "junklength           = %"PRIu32"\n", ape_ctx->junklength);
    g_debug("firstframe           = %"PRIu32"\n", ape_ctx->firstframe);
    g_debug( "totalsamples         = %"PRIu32"\n", ape_ctx->totalsamples);
#endif
}






static gboolean
gst_ffmpegdemux_open (GstFFMpegDemux * demux)
{
  GstFFMpegDemuxClass *oclass =
      (GstFFMpegDemuxClass *) G_OBJECT_GET_CLASS (demux);
  gchar *location;
  gint res, n_streams, i;
  AVCodecContext *ctx;
#if 0
  /* Re-enable once converted to new AVMetaData API
   * See #566605
   */
  GstTagList *tags;
#endif
  GstEvent *event;
  GList *cached_events;

  /* to be sure... */
  gst_ffmpegdemux_close (demux);

  /* open via our input protocol hack */
  if (demux->seekable)
    location = g_strdup_printf ("gstreamer://%p", demux->sinkpad);
  else
    location = g_strdup_printf ("gstpipe://%p", &demux->ffpipe);
  GST_DEBUG_OBJECT (demux, "about to call av_open_input_file %s", location);

  res = av_open_input_file (&demux->context, location,
      oclass->in_plugin, 0, NULL);

  g_free (location);
  GST_DEBUG_OBJECT (demux, "av_open_input returned %d", res);
  if (res < 0)
    goto open_failed;

  res = gst_ffmpeg_av_find_stream_info (demux->context);
  GST_DEBUG_OBJECT (demux, "av_find_stream_info returned %d", res);
  if (res < 0)
    goto no_info;

  n_streams = demux->context->nb_streams;
  GST_DEBUG_OBJECT (demux, "we have %d streams", n_streams);

  /* open_input_file() automatically reads the header. We can now map each
   * created AVStream to a GstPad to make GStreamer handle it. */
  for (i = 0; i < n_streams; i++) {
    gst_ffmpegdemux_get_stream (demux, demux->context->streams[i]);
  }
	if(n_streams > 0 && n_streams ==1){
  	
		ctx = demux->context->streams[0]->codec;
		if(ctx->codec_id == CODEC_ID_APE){
			struct _GstFFMpegAPEContext *ape=demux->context->priv_data;
    			memcpy(CurrentAPEContext, ape, sizeof(struct _GstFFMpegAPEContext));
    			//g_print("%s, %d init APE frame size=%d\n", __FUNCTION__, __LINE__,(CurrentAPEContext->totalframes * sizeof(struct _GstFFMpegAPEFrame)));
    			CurrentAPEContext->frames= av_malloc(CurrentAPEContext->totalframes * sizeof(struct _GstFFMpegAPEFrame));
    			if(!CurrentAPEContext->frames){
    				g_print("%s, %d Not enough memory\n", __FUNCTION__, __LINE__);
    				av_freep(&CurrentAPEContext);
    				goto open_failed;
    			}
    			if (CurrentAPEContext->seektablelength > 0) {
    				//g_print("%s, %d APE seektable size=%d\n", __FUNCTION__, __LINE__,(CurrentAPEContext->seektablelength));
        				CurrentAPEContext->seektable = av_malloc(CurrentAPEContext->seektablelength);
				        if (!CurrentAPEContext->seektable){
				            	g_print("%s, %d Not enough memory\n", __FUNCTION__, __LINE__);
				            	av_freep(&CurrentAPEContext);
    							goto open_failed;
				          }
				        for (i = 0; i < ape->seektablelength / sizeof(uint32_t);i++)
				            CurrentAPEContext->seektable[i] = ape->seektable[i];
			}
    			for (i = 0; i < ape->totalframes; i++) {
        				CurrentAPEContext->frames[i].pos  = ape->frames[i].pos;
        				CurrentAPEContext->frames[i].nblocks = ape->frames[i].nblocks;
        				CurrentAPEContext->frames[i].size  = ape->frames[i].size;
        				CurrentAPEContext->frames[i].skip = ape->frames[i].skip;
        				CurrentAPEContext->frames[i].pts = ape->frames[i].pts;
    			}
    			
			if ((CurrentAPEContext->seektablelength / sizeof(uint32_t)) != CurrentAPEContext->totalframes) {
        				//g_debug("No Seektable\n");
        				demux->isAPESeekable =0;
			} else {
					//g_debug("Include Seektable\n");
					demux->isAPESeekable =1;
    			}
    			if(demux->inPushMode ==1){
    				//g_debug("Include Push Mode\n");
    				ape->inPushMode = 1;
    			}else{
    				//g_debug("NOT Include Push Mode\n");
    				ape->inPushMode = 0;
    			}
    			gstffmpegape_dumpinfo(CurrentAPEContext);
		}
	}

  gst_element_no_more_pads (GST_ELEMENT (demux));

  /* transform some useful info to GstClockTime and remember */
  demux->start_time = gst_util_uint64_scale_int (demux->context->start_time,
      GST_SECOND, AV_TIME_BASE);
  GST_DEBUG_OBJECT (demux, "start time: %" GST_TIME_FORMAT,
      GST_TIME_ARGS (demux->start_time));
  if (demux->context->duration > 0)
    demux->duration = gst_util_uint64_scale_int (demux->context->duration,
        GST_SECOND, AV_TIME_BASE);
  else
    demux->duration = GST_CLOCK_TIME_NONE;

  GST_DEBUG_OBJECT (demux, "duration: %" GST_TIME_FORMAT,
      GST_TIME_ARGS (demux->duration));

  /* store duration in the segment as well */
  gst_segment_set_duration (&demux->segment, GST_FORMAT_TIME, demux->duration);

  GST_OBJECT_LOCK (demux);
  demux->opened = TRUE;
  event = demux->seek_event;
  demux->seek_event = NULL;
  cached_events = demux->cached_events;
  demux->cached_events = NULL;
  GST_OBJECT_UNLOCK (demux);

  if (event) {
    gst_ffmpegdemux_perform_seek (demux, event);
    gst_event_unref (event);
  } else {
    gst_ffmpegdemux_push_event (demux,
        gst_event_new_new_segment (FALSE,
            demux->segment.rate, demux->segment.format,
            demux->segment.start, demux->segment.stop, demux->segment.time));
  }

  while (cached_events) {
    event = cached_events->data;
    GST_INFO_OBJECT (demux, "pushing cached %s event: %" GST_PTR_FORMAT,
        GST_EVENT_TYPE_NAME (event), event->structure);
    gst_ffmpegdemux_push_event (demux, event);
    cached_events = g_list_delete_link (cached_events, cached_events);
  }

#if 0
  /* Re-enable once converted to new AVMetaData API
   * See #566605
   */
  /* grab the global tags */
  tags = gst_ffmpegdemux_read_tags (demux);
  if (tags) {
    GST_INFO_OBJECT (demux, "global tags: %" GST_PTR_FORMAT, tags);
    gst_element_found_tags (GST_ELEMENT (demux), tags);
  }
#endif

  /* now handle the stream tags */
  for (i = 0; i < n_streams; i++) {
    GstFFStream *stream;

    stream = gst_ffmpegdemux_get_stream (demux, demux->context->streams[i]);
    if (stream->tags != NULL && stream->pad != NULL) {
      GST_INFO_OBJECT (stream->pad, "stream tags: %" GST_PTR_FORMAT,
          stream->tags);
      gst_element_found_tags_for_pad (GST_ELEMENT (demux), stream->pad,
          gst_tag_list_copy (stream->tags));
    }
  }

  return TRUE;

  /* ERRORS */
open_failed:
  {
    GST_ELEMENT_ERROR (demux, LIBRARY, FAILED, (NULL),
        ("%s", gst_ffmpegdemux_averror (res)));
    return FALSE;
  }
no_info:
  {
    GST_ELEMENT_ERROR (demux, LIBRARY, FAILED, (NULL),
        ("%s", gst_ffmpegdemux_averror (res)));
    return FALSE;
  }
}

#define GST_FFMPEG_TYPE_FIND_SIZE 4096
#define GST_FFMPEG_TYPE_FIND_MIN_SIZE 256

static void
gst_ffmpegdemux_type_find (GstTypeFind * tf, gpointer priv)
{
  guint8 *data;
  AVInputFormat *in_plugin = (AVInputFormat *) priv;
  gint res = 0;
  guint64 length;
  GstCaps *sinkcaps;

  /* We want GST_FFMPEG_TYPE_FIND_SIZE bytes, but if the file is shorter than
   * that we'll give it a try... */
  length = gst_type_find_get_length (tf);
  if (length == 0 || length > GST_FFMPEG_TYPE_FIND_SIZE)
    length = GST_FFMPEG_TYPE_FIND_SIZE;

  /* The ffmpeg typefinders assume there's a certain minimum amount of data
   * and will happily do invalid memory access if there isn't, so let's just
   * skip the ffmpeg typefinders if the data available is too short
   * (in which case it's unlikely to be a media file anyway) */
  if (length < GST_FFMPEG_TYPE_FIND_MIN_SIZE) {
    GST_LOG ("not typefinding %" G_GUINT64_FORMAT " bytes, too short", length);
    return;
  }

  GST_LOG ("typefinding %" G_GUINT64_FORMAT " bytes", length);
  if (in_plugin->read_probe &&
      (data = gst_type_find_peek (tf, 0, length)) != NULL) {
    AVProbeData probe_data;

    probe_data.filename = "";
    probe_data.buf = data;
    probe_data.buf_size = length;

    res = in_plugin->read_probe (&probe_data);
    if (res > 0) {
      res = MAX (1, res * GST_TYPE_FIND_MAXIMUM / AVPROBE_SCORE_MAX);
      /* Restrict the probability for MPEG-TS streams, because there is
       * probably a better version in plugins-base, if the user has a recent
       * plugins-base (in fact we shouldn't even get here for ffmpeg mpegts or
       * mpegtsraw typefinders, since we blacklist them) */
      if (g_str_has_prefix (in_plugin->name, "mpegts"))
        res = MIN (res, GST_TYPE_FIND_POSSIBLE);

      sinkcaps = gst_ffmpeg_formatid_to_caps (in_plugin->name);

      GST_LOG ("ffmpeg typefinder '%s' suggests %" GST_PTR_FORMAT ", p=%u%%",
          in_plugin->name, sinkcaps, res);

      gst_type_find_suggest (tf, res, sinkcaps);
    }
  }
}

/* Task */
static void
gst_ffmpegdemux_loop (GstFFMpegDemux * demux)
{
  GstFlowReturn ret;
  gint res;
  AVPacket pkt;
  GstPad *srcpad;
  GstFFStream *stream;
  AVStream *avstream;
  GstBuffer *outbuf = NULL;
  GstClockTime timestamp, duration;
  gint outsize;
  gboolean rawvideo;
uint8_t *ape_data;
AVCodecContext *ctx;
int n_streams=0;
unsigned int Correct_Last=0;
unsigned int LocalRing_Max=LOCAL_RING_MAX;
unsigned int NextLocalRing_Pos=0;
unsigned int LocalRing_Remainlen=0;
unsigned int CurrentFrameOffset=0;
unsigned int LastCurrentFrameOffset=0;
unsigned int LastNextLocalRing_Pos=0;
 uint32_t extra_size = 8;
 unsigned char *temp_buf=NULL;
  /* open file if we didn't so already */
  if (!demux->opened)
    if (!gst_ffmpegdemux_open (demux))
      goto open_failed;

  GST_DEBUG_OBJECT (demux, "about to read a frame");

  /* read a frame */
  res = av_read_frame (demux->context, &pkt);
  if (res < 0){
    goto read_failed;
}else
	demux->isPauseCauseReadEnd = 0;
  /* get the stream */
  stream =
      gst_ffmpegdemux_get_stream (demux,
      demux->context->streams[pkt.stream_index]);

  /* check if we know the stream */
  if (stream->unknown)
    goto done;

  /* get more stuff belonging to this stream */
  avstream = stream->avstream;

  /* do timestamps, we do this first so that we can know when we
   * stepped over the segment stop position. */
  timestamp = gst_ffmpeg_time_ff_to_gst (pkt.pts, avstream->time_base);
  if (GST_CLOCK_TIME_IS_VALID (timestamp)) {
    stream->last_ts = timestamp;
  }
  duration = gst_ffmpeg_time_ff_to_gst (pkt.duration, avstream->time_base);
  if (G_UNLIKELY (!duration)) {
    GST_WARNING_OBJECT (demux, "invalid buffer duration, setting to NONE");
    duration = GST_CLOCK_TIME_NONE;
  }


  GST_DEBUG_OBJECT (demux,
      "pkt pts:%" GST_TIME_FORMAT
      " / size:%d / stream_index:%d / flags:%d / duration:%" GST_TIME_FORMAT
      " / pos:%" G_GINT64_FORMAT, GST_TIME_ARGS (timestamp), pkt.size,
      pkt.stream_index, pkt.flags, GST_TIME_ARGS (duration), (gint64) pkt.pos);

  /* check start_time */
  if (demux->start_time != -1 && demux->start_time > timestamp)
    goto drop;

  if (GST_CLOCK_TIME_IS_VALID (timestamp))
    timestamp -= demux->start_time;

  /* check if we ran outside of the segment */
  if (demux->segment.stop != -1 && timestamp > demux->segment.stop)
    goto drop;

  /* prepare to push packet to peer */
  srcpad = stream->pad;
if(demux->IsinSeeking ==1){
	ape_data  = pkt.data+extra_size;
		n_streams = demux->context->nb_streams;
		if(n_streams == 1){
			ctx = demux->context->streams[0]->codec;
			if(demux->inPushMode ==1 && ctx->codec_id == CODEC_ID_APE){
				if(LocalRing != NULL){
					unsigned int first_count=0;
					memset(LocalRing, 0x00, LOCAL_RING_MAX);
					memcpy(LocalRing,ape_data,pkt.size-extra_size);
					LocalRing_Pos = pkt.size-extra_size;
					CurrentFrameOffset = 0;
				}
			}
		}
	demux->IsinSeeking = 0;
	demux->audio_frame_idx++;
	goto done;
}
  rawvideo = (avstream->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
      avstream->codec->codec_id == CODEC_ID_RAWVIDEO);

  if (rawvideo)
    outsize = gst_ffmpeg_avpicture_get_size (avstream->codec->pix_fmt,
        avstream->codec->width, avstream->codec->height);
  else
    outsize = pkt.size;

		n_streams = demux->context->nb_streams;
		if(n_streams == 1){
			ctx = demux->context->streams[0]->codec;
			if(demux->inPushMode ==1 && ctx && ctx->codec_id == CODEC_ID_APE){
				if(demux->audio_frame_idx == (CurrentAPEContext->totalframes-1)){
					LastCurrentFrameOffset = (unsigned int)(CurrentAPEContext->frames[demux->audio_frame_idx].pos - CurrentAPEContext->frames[demux->audio_frame_idx-1].pos);
					LastNextLocalRing_Pos = (LocalRing_Pos+outsize-extra_size) -LastCurrentFrameOffset;
					Correct_Last= LastNextLocalRing_Pos+extra_size;
				}
			}
		}

	if(Correct_Last>0 ){
		stream->last_flow = gst_pad_alloc_buffer_and_set_caps (srcpad,GST_CLOCK_TIME_NONE, Correct_Last, GST_PAD_CAPS (srcpad), &outbuf);
		memset(GST_BUFFER_DATA (outbuf), 0x00,Correct_Last); 
	}else
	  stream->last_flow = gst_pad_alloc_buffer_and_set_caps (srcpad,
	      GST_CLOCK_TIME_NONE, outsize, GST_PAD_CAPS (srcpad), &outbuf);

  if ((ret = gst_ffmpegdemux_aggregated_flow (demux)) != GST_FLOW_OK)
    goto no_buffer;

  /* If the buffer allocation failed, don't try sending it ! */
  if (stream->last_flow != GST_FLOW_OK)
    goto done;

  /* copy the data from packet into the target buffer
   * and do conversions for raw video packets */
  if (rawvideo) {
    AVPicture src, dst;
    const gchar *plugin_name =
        ((GstFFMpegDemuxClass *) (G_OBJECT_GET_CLASS (demux)))->in_plugin->name;

    if (strcmp (plugin_name, "gif") == 0) {
      src.data[0] = pkt.data;
      src.data[1] = NULL;
      src.data[2] = NULL;
      src.linesize[0] = avstream->codec->width * 3;;
    } else {
      GST_WARNING ("Unknown demuxer %s, no idea what to do", plugin_name);
      gst_ffmpeg_avpicture_fill (&src, pkt.data,
          avstream->codec->pix_fmt, avstream->codec->width,
          avstream->codec->height);
    }

    gst_ffmpeg_avpicture_fill (&dst, GST_BUFFER_DATA (outbuf),
        avstream->codec->pix_fmt, avstream->codec->width,
        avstream->codec->height);

    av_picture_copy (&dst, &src, avstream->codec->pix_fmt,
        avstream->codec->width, avstream->codec->height);
  } else {
  	///wrapper for pos of each frame
  	ape_data  = pkt.data+extra_size;
		n_streams = demux->context->nb_streams;
		if(n_streams == 1){
			ctx = demux->context->streams[0]->codec;
			if(demux->inPushMode ==1 && ctx->codec_id == CODEC_ID_APE){
				timestamp = pkt.pts*GST_SECOND;
				if(LocalRing != NULL){
						if( demux->audio_frame_idx > 0){
						}
						if(demux->audio_frame_idx ==0){
							memcpy(LocalRing,ape_data,outsize-extra_size);
							LocalRing_Pos = outsize-extra_size;
							CurrentFrameOffset = 0;
						}else{
							memcpy(LocalRing+LocalRing_Pos,ape_data,outsize-extra_size);
							CurrentFrameOffset = (unsigned int)(CurrentAPEContext->frames[demux->audio_frame_idx].pos - CurrentAPEContext->frames[demux->audio_frame_idx-1].pos);
							NextLocalRing_Pos = (LocalRing_Pos+outsize-extra_size) -CurrentFrameOffset;
							temp_buf =(unsigned char *)av_mallocz(NextLocalRing_Pos);
							memcpy(temp_buf, LocalRing+CurrentFrameOffset,NextLocalRing_Pos); 
							LocalRing_Pos = 0;
						}
					if(demux->audio_frame_idx ==0){
					   	memcpy (GST_BUFFER_DATA (outbuf), pkt.data, outsize);
					}else if(demux->audio_frame_idx >0){
					 	memcpy (GST_BUFFER_DATA (outbuf), pkt.data, extra_size);
					 	if((demux->audio_frame_idx == (CurrentAPEContext->totalframes-1)) && Correct_Last > 0){
					 		g_debug("Last output CurrentFrameOffset=%d size=%d",CurrentFrameOffset,(Correct_Last-extra_size) );
					 		memcpy (GST_BUFFER_DATA (outbuf)+extra_size, LocalRing+CurrentFrameOffset, Correct_Last-extra_size);
					 	}else{
					  		memcpy (GST_BUFFER_DATA (outbuf)+extra_size, LocalRing+CurrentFrameOffset, outsize-extra_size);
					  	}
						memcpy(LocalRing+LocalRing_Pos,temp_buf,NextLocalRing_Pos);
						LocalRing_Pos= NextLocalRing_Pos;
					   	av_freep(&temp_buf);
					}
				}else
					memcpy (GST_BUFFER_DATA (outbuf), pkt.data, outsize);
  			}else
  				memcpy (GST_BUFFER_DATA (outbuf), pkt.data, outsize);
  		}else
    memcpy (GST_BUFFER_DATA (outbuf), pkt.data, outsize);
  }

  GST_BUFFER_TIMESTAMP (outbuf) = timestamp;
  GST_BUFFER_DURATION (outbuf) = duration;

  /* mark keyframes */
  if (!(pkt.flags & AV_PKT_FLAG_KEY)) {
    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_DELTA_UNIT);
  }

  /* Mark discont */
  if (stream->discont) {
    GST_DEBUG_OBJECT (demux, "marking DISCONT");
    GST_BUFFER_FLAG_SET (outbuf, GST_BUFFER_FLAG_DISCONT);
    stream->discont = FALSE;
  }

  GST_DEBUG_OBJECT (demux,
      "Sending out buffer time:%" GST_TIME_FORMAT " size:%d",
      GST_TIME_ARGS (timestamp), GST_BUFFER_SIZE (outbuf));

  ret = stream->last_flow = gst_pad_push (srcpad, outbuf);

  /* if a pad is in e.g. WRONG_STATE, we want to pause to unlock the STREAM_LOCK */
  if ((ret != GST_FLOW_OK)
      && ((ret = gst_ffmpegdemux_aggregated_flow (demux)) != GST_FLOW_OK)) {
    GST_WARNING_OBJECT (demux, "stream_movi flow: %s / %s",
        gst_flow_get_name (stream->last_flow), gst_flow_get_name (ret));
    goto pause;
  }
  else{
  	if(ctx && demux->inPushMode ==1  && ctx->codec_id == CODEC_ID_APE){
		demux->audio_frame_idx++;
	}
  }
  	

done:
  /* can destroy the packet now */
  av_free_packet (&pkt);

  return;

  /* ERRORS */
pause:
  {
  	gboolean isseekable = demux->seekable;
  	n_streams = demux->context->nb_streams;
		if(n_streams == 1){
			ctx = demux->context->streams[0]->codec;
		}
    GST_LOG_OBJECT (demux, "pausing task, reason %d (%s)", ret,
        gst_flow_get_name (ret));
    demux->running = FALSE;
    if(demux->inPushMode ==1 && ctx && ctx->codec_id == CODEC_ID_APE){
	    if(demux->isAPESeekable==0){
	      		isseekable = FALSE;
		}else{
				isseekable = TRUE;
		}
	}
	if(demux->inPushMode ==1 && ctx && ctx->codec_id == CODEC_ID_APE){
		 if (isseekable && demux->isPauseCauseReadEnd ==0){
      gst_pad_pause_task (demux->sinkpad);
    		}else {
      GstFFMpegPipe *ffpipe = &demux->ffpipe;
      GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
      /* pause task and make sure loop stops */
      gst_task_pause (demux->task);
      g_static_rec_mutex_lock (demux->task_lock);
      g_static_rec_mutex_unlock (demux->task_lock);
      demux->ffpipe.srcresult = ret;
      GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);
    }
	}else {
		if (isseekable){
		gst_pad_pause_task (demux->sinkpad);
		}else {
		GstFFMpegPipe *ffpipe = &demux->ffpipe;

	      GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
	      /* pause task and make sure loop stops */
	      gst_task_pause (demux->task);
	      g_static_rec_mutex_lock (demux->task_lock);
	      g_static_rec_mutex_unlock (demux->task_lock);
	      demux->ffpipe.srcresult = ret;
	      GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);
	    }
	}
    if (ret == GST_FLOW_UNEXPECTED) {
      if (demux->segment.flags & GST_SEEK_FLAG_SEGMENT) {
        gint64 stop;

        if ((stop = demux->segment.stop) == -1)
          stop = demux->segment.duration;

        GST_LOG_OBJECT (demux, "posting segment done");
        gst_element_post_message (GST_ELEMENT (demux),
            gst_message_new_segment_done (GST_OBJECT (demux),
                demux->segment.format, stop));
      } else {
        GST_LOG_OBJECT (demux, "pushing eos");
        gst_ffmpegdemux_push_event (demux, gst_event_new_eos ());
      }
    } else if (ret == GST_FLOW_NOT_LINKED || ret < GST_FLOW_UNEXPECTED) {
      GST_ELEMENT_ERROR (demux, STREAM, FAILED,
          ("Internal data stream error."),
          ("streaming stopped, reason %s", gst_flow_get_name (ret)));
      gst_ffmpegdemux_push_event (demux, gst_event_new_eos ());
    }
    return;
  }
open_failed:
  {
    ret = GST_FLOW_ERROR;
    goto pause;
  }
read_failed:
  {
    /* something went wrong... */
    GST_WARNING_OBJECT (demux, "av_read_frame returned %d", res);

    GST_OBJECT_LOCK (demux);
    /* pause appropriatly based on if we are flushing or not */
    if (demux->flushing)
      ret = GST_FLOW_WRONG_STATE;
    else if (gst_ffmpegdemux_has_outputted (demux)
        || gst_ffmpegdemux_is_eos (demux)) {
      GST_DEBUG_OBJECT (demux, "We are EOS");
      ret = GST_FLOW_UNEXPECTED;
    } else
      ret = GST_FLOW_ERROR;
    GST_OBJECT_UNLOCK (demux);
	demux->isPauseCauseReadEnd = 1;
    goto pause;
  }
drop:
  {
    GST_DEBUG_OBJECT (demux, "dropping buffer out of segment, stream eos");
    stream->eos = TRUE;
    if (gst_ffmpegdemux_is_eos (demux)) {
      av_free_packet (&pkt);
      GST_DEBUG_OBJECT (demux, "we are eos");
      ret = GST_FLOW_UNEXPECTED;
      goto pause;
    } else {
      GST_DEBUG_OBJECT (demux, "some streams are not yet eos");
      goto done;
    }
  }
no_buffer:
  {
    av_free_packet (&pkt);
    goto pause;
  }
}


static gboolean
gst_ffmpegdemux_sink_event (GstPad * sinkpad, GstEvent * event)
{
  GstFFMpegDemux *demux;
  GstFFMpegPipe *ffpipe;
  gboolean result = TRUE;

  demux = (GstFFMpegDemux *) (GST_PAD_PARENT (sinkpad));
  ffpipe = &(demux->ffpipe);

  GST_LOG_OBJECT (demux, "%s event: %" GST_PTR_FORMAT,
      GST_EVENT_TYPE_NAME (event), event->structure);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_FLUSH_START:
      /* forward event */
      gst_pad_event_default (sinkpad, event);

      /* now unblock the chain function */
      GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
      ffpipe->srcresult = GST_FLOW_WRONG_STATE;
      GST_FFMPEG_PIPE_SIGNAL (ffpipe);
      GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);

      /* loop might run into WRONG_STATE and end itself,
       * but may also be waiting in a ffmpeg read
       * trying to break that would make ffmpeg believe eos,
       * so no harm to have the loop 'pausing' there ... */
      goto done;
    case GST_EVENT_FLUSH_STOP:
      /* forward event */
      gst_pad_event_default (sinkpad, event);

      GST_OBJECT_LOCK (demux);
      g_list_foreach (demux->cached_events, (GFunc) gst_mini_object_unref,
          NULL);
      g_list_free (demux->cached_events);
      GST_OBJECT_UNLOCK (demux);
      GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
      gst_adapter_clear (ffpipe->adapter);
      ffpipe->srcresult = GST_FLOW_OK;
      /* loop may have decided to end itself as a result of flush WRONG_STATE */
      gst_task_start (demux->task);
      demux->running = TRUE;
      demux->flushing = FALSE;
      GST_LOG_OBJECT (demux, "loop started");
      GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);
      goto done;
    case GST_EVENT_EOS:
      /* inform the src task that it can stop now */
      GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
      ffpipe->eos = TRUE;
      GST_FFMPEG_PIPE_SIGNAL (ffpipe);
      GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);

      /* eat this event for now, task will send eos when finished */
      gst_event_unref (event);
      goto done;
    default:
      /* for a serialized event, wait until an earlier data is gone,
       * though this is no guarantee as to when task is done with it.
       *
       * If the demuxer isn't opened, push straight away, since we'll
       * be waiting against a cond that will never be signalled. */
      if (GST_EVENT_IS_SERIALIZED (event)) {
        if (demux->opened) {
          GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
          while (!ffpipe->needed)
            GST_FFMPEG_PIPE_WAIT (ffpipe);
          GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);
        } else {
          /* queue events and send them later (esp. tag events) */
          GST_OBJECT_LOCK (demux);
          demux->cached_events = g_list_append (demux->cached_events, event);
          GST_OBJECT_UNLOCK (demux);
          goto done;
        }
      }
      break;
  }

  result = gst_pad_event_default (sinkpad, event);

done:

  return result;
}

static GstFlowReturn
gst_ffmpegdemux_chain (GstPad * sinkpad, GstBuffer * buffer)
{
  GstFFMpegDemux *demux;
  GstFFMpegPipe *ffpipe;

  demux = (GstFFMpegDemux *) (GST_PAD_PARENT (sinkpad));
  ffpipe = &demux->ffpipe;

  GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);

  if (G_UNLIKELY (ffpipe->eos))
    goto eos;

  if (G_UNLIKELY (ffpipe->srcresult != GST_FLOW_OK))
    goto ignore;

  GST_DEBUG ("Giving a buffer of %d bytes", GST_BUFFER_SIZE (buffer));
  gst_adapter_push (ffpipe->adapter, buffer);
  buffer = NULL;
  while (gst_adapter_available (ffpipe->adapter) >= ffpipe->needed) {
    GST_DEBUG ("Adapter has more that requested (ffpipe->needed:%d)",
        ffpipe->needed);
    GST_FFMPEG_PIPE_SIGNAL (ffpipe);
    GST_FFMPEG_PIPE_WAIT (ffpipe);
    /* may have become flushing */
    if (G_UNLIKELY (ffpipe->srcresult != GST_FLOW_OK))
      goto ignore;
  }

  GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);

  return GST_FLOW_OK;

/* special cases */
eos:
  {
    GST_DEBUG_OBJECT (demux, "ignoring buffer at end-of-stream");
    GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);

    gst_buffer_unref (buffer);
    return GST_FLOW_UNEXPECTED;
  }
ignore:
  {
    GST_DEBUG_OBJECT (demux, "ignoring buffer because src task encountered %s",
        gst_flow_get_name (ffpipe->srcresult));
    GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);

    if (buffer)
      gst_buffer_unref (buffer);
    return GST_FLOW_WRONG_STATE;
  }
}

static gboolean
gst_ffmpegdemux_sink_activate (GstPad * sinkpad)
{
  GstFFMpegDemux *demux;
  gboolean res;

  demux = (GstFFMpegDemux *) (gst_pad_get_parent (sinkpad));

  res = FALSE;

  if (gst_pad_check_pull_range (sinkpad))
    res = gst_pad_activate_pull (sinkpad, TRUE);
  else {
    res = gst_pad_activate_push (sinkpad, TRUE);
  }
  gst_object_unref (demux);
  return res;
}

/* push mode:
 * - not seekable
 * - use gstpipe protocol, like ffmpeg's pipe protocol
 * - (independently managed) task driving ffmpeg
 */
static gboolean
gst_ffmpegdemux_sink_activate_push (GstPad * sinkpad, gboolean active)
{
  GstFFMpegDemux *demux;
  gboolean res = FALSE;

  demux = (GstFFMpegDemux *) (gst_pad_get_parent (sinkpad));

  if (active) {
    if (demux->can_push == FALSE) {
      GST_WARNING_OBJECT (demux, "Demuxer can't reliably operate in push-mode");
      goto beach;
    }
    demux->ffpipe.eos = FALSE;
    demux->ffpipe.srcresult = GST_FLOW_OK;
    demux->ffpipe.needed = 0;
    demux->running = TRUE;
    demux->seekable = FALSE;
    demux->inPushMode =1;
    g_debug("%s, %d active in PUSH",__FUNCTION__, __LINE__);
	if(CurrentAPEContext != NULL)
		CurrentAPEContext->inPushMode = 1;
		if (access("/var/gstreamer-0.10/inPush",R_OK) < 0)
		{
			unsigned char tmpbuf[32];
			int fh=0;
			fh = open("/var/gstreamer-0.10/inPush", O_RDWR|O_CREAT|O_TRUNC);
			if (fh < 0) {
				g_debug("Create %s error!\n", "/var/gstreamer-0.10/inPush");
			}else{
				sprintf(tmpbuf, "%s", "1");
				write(fh, tmpbuf, strlen(tmpbuf));
				close(fh);
			}
		}
			
    res = gst_task_start (demux->task);
  } else {
    GstFFMpegPipe *ffpipe = &demux->ffpipe;

    /* release chain and loop */
    GST_FFMPEG_PIPE_MUTEX_LOCK (ffpipe);
    demux->ffpipe.srcresult = GST_FLOW_WRONG_STATE;
    /* end streaming by making ffmpeg believe eos */
    demux->ffpipe.eos = TRUE;
    GST_FFMPEG_PIPE_SIGNAL (ffpipe);
    GST_FFMPEG_PIPE_MUTEX_UNLOCK (ffpipe);

    /* make sure streaming ends */
    gst_task_stop (demux->task);
    g_static_rec_mutex_lock (demux->task_lock);
    g_static_rec_mutex_unlock (demux->task_lock);
    res = gst_task_join (demux->task);
    demux->running = FALSE;
    demux->seekable = FALSE;
     demux->inPushMode=0;
     if(CurrentAPEContext != NULL)
		CurrentAPEContext->inPushMode = 0;
	if (access("/var/gstreamer-0.10/inPush",R_OK) == 0)
	{	
		unlink("/var/gstreamer-0.10/inPush");
	}
  }

beach:
  gst_object_unref (demux);

  return res;
}

/* pull mode:
 * - seekable
 * - use gstreamer protocol, like ffmpeg's file protocol
 * - task driving ffmpeg based on sink pad
 */
static gboolean
gst_ffmpegdemux_sink_activate_pull (GstPad * sinkpad, gboolean active)
{
  GstFFMpegDemux *demux;
  gboolean res;

  demux = (GstFFMpegDemux *) (gst_pad_get_parent (sinkpad));

  if (active) {
    demux->running = TRUE;
    demux->seekable = TRUE;
    res = gst_pad_start_task (sinkpad, (GstTaskFunction) gst_ffmpegdemux_loop,
        demux);
  } else {
    demux->running = FALSE;
    res = gst_pad_stop_task (sinkpad);
    demux->seekable = FALSE;
  }
demux->inPushMode =0;
  gst_object_unref (demux);

 if(CurrentAPEContext != NULL)
		CurrentAPEContext->inPushMode = 0;
  return res;
}

static GstStateChangeReturn
gst_ffmpegdemux_change_state (GstElement * element, GstStateChange transition)
{
  GstFFMpegDemux *demux = (GstFFMpegDemux *) (element);
  GstStateChangeReturn ret;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
#if 0
      /* test seek in READY here */
      gst_element_send_event (element, gst_event_new_seek (1.0,
              GST_FORMAT_TIME, GST_SEEK_FLAG_NONE,
              GST_SEEK_TYPE_SET, 10 * GST_SECOND,
              GST_SEEK_TYPE_SET, 13 * GST_SECOND));
#endif
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_ffmpegdemux_close (demux);
      gst_adapter_clear (demux->ffpipe.adapter);
      g_list_foreach (demux->cached_events, (GFunc) gst_mini_object_unref,
          NULL);
      g_list_free (demux->cached_events);
      demux->cached_events = NULL;
      break;
    default:
      break;
  }

  return ret;
}

gboolean
gst_ffmpegdemux_register (GstPlugin * plugin)
{
  GType type;
  AVInputFormat *in_plugin;
  gchar **extensions;
  GTypeInfo typeinfo = {
    sizeof (GstFFMpegDemuxClass),
    (GBaseInitFunc) gst_ffmpegdemux_base_init,
    NULL,
    (GClassInitFunc) gst_ffmpegdemux_class_init,
    NULL,
    NULL,
    sizeof (GstFFMpegDemux),
    0,
    (GInstanceInitFunc) gst_ffmpegdemux_init,
  };

  in_plugin = av_iformat_next (NULL);

  GST_LOG ("Registering demuxers");

  while (in_plugin) {
    gchar *type_name, *typefind_name;
    gchar *p, *name = NULL;
    gint rank;
    gboolean register_typefind_func = TRUE;

    GST_LOG ("Attempting to handle ffmpeg demuxer plugin %s [%s]",
        in_plugin->name, in_plugin->long_name);

    /* no emulators */
    //if (!strncmp (in_plugin->long_name, "raw ", 4) ||
    //    !strncmp (in_plugin->long_name, "pcm ", 4) ||
    if(!strcmp (in_plugin->name, "audio_device") ||
        !strncmp (in_plugin->name, "image", 5) ||
        !strcmp (in_plugin->name, "mpegvideo") ||
        !strcmp (in_plugin->name, "mjpeg") ||
        !strcmp (in_plugin->name, "redir") ||
        !strncmp (in_plugin->name, "u8", 2) ||
        !strncmp (in_plugin->name, "u16", 3) ||
        !strncmp (in_plugin->name, "u24", 3) ||
        !strncmp (in_plugin->name, "u32", 3) ||
        !strncmp (in_plugin->name, "s8", 2) ||
        !strncmp (in_plugin->name, "s16", 3) ||
        !strncmp (in_plugin->name, "s24", 3) ||
        !strncmp (in_plugin->name, "s32", 3) ||
        !strncmp (in_plugin->name, "f32", 3) ||
        !strncmp (in_plugin->name, "f64", 3) ||
        !strcmp (in_plugin->name, "mulaw") || !strcmp (in_plugin->name, "alaw")
        )
      goto next;

    /* no network demuxers */
    if (!strcmp (in_plugin->name, "sdp") ||
        !strcmp (in_plugin->name, "rtsp") ||
        !strcmp (in_plugin->name, "applehttp")
        )
      goto next;

    /* these don't do what one would expect or
     * are only partially functional/useful */
    if (!strcmp (in_plugin->name, "aac") ||
        !strcmp (in_plugin->name, "wv") ||
        !strcmp (in_plugin->name, "ass") ||
        !strcmp (in_plugin->name, "ffmetadata"))
      goto next;

    /* Don't use the typefind functions of formats for which we already have
     * better typefind functions */
    if (!strcmp (in_plugin->name, "mov,mp4,m4a,3gp,3g2,mj2") ||
        !strcmp (in_plugin->name, "ass") ||
        !strcmp (in_plugin->name, "avi") ||
        !strcmp (in_plugin->name, "asf") ||
        !strcmp (in_plugin->name, "mpegvideo") ||
        !strcmp (in_plugin->name, "mp3") ||
        !strcmp (in_plugin->name, "matroska") ||
        !strcmp (in_plugin->name, "matroska_webm") ||
        !strcmp (in_plugin->name, "mpeg") ||
        !strcmp (in_plugin->name, "wav") ||
        !strcmp (in_plugin->name, "au") ||
        !strcmp (in_plugin->name, "tta") ||
        !strcmp (in_plugin->name, "rm") ||
        !strcmp (in_plugin->name, "amr") ||
        !strcmp (in_plugin->name, "ogg") ||
        !strcmp (in_plugin->name, "aiff") ||
        !strcmp (in_plugin->name, "ape") ||
        !strcmp (in_plugin->name, "dv") ||
        !strcmp (in_plugin->name, "flv") ||
        !strcmp (in_plugin->name, "mpc") ||
        !strcmp (in_plugin->name, "mpc8") ||
        !strcmp (in_plugin->name, "mpegts") ||
        !strcmp (in_plugin->name, "mpegtsraw") ||
        !strcmp (in_plugin->name, "mxf") ||
        !strcmp (in_plugin->name, "nuv") ||
        !strcmp (in_plugin->name, "swf") ||
        !strcmp (in_plugin->name, "voc") ||
        !strcmp (in_plugin->name, "gif") || !strcmp (in_plugin->name, "vc1test")
        )
      register_typefind_func = FALSE;

    /* Set the rank of demuxers know to work to MARGINAL.
     * Set demuxers for which we already have another implementation to NONE
     * Set All others to NONE*/
    if (!strcmp (in_plugin->name, "wsvqa") ||
        !strcmp (in_plugin->name, "wsaud") ||
        !strcmp (in_plugin->name, "wc3movie") ||
        !strcmp (in_plugin->name, "voc") ||
        !strcmp (in_plugin->name, "tta") ||
        !strcmp (in_plugin->name, "swf") ||
        !strcmp (in_plugin->name, "sol") ||
        !strcmp (in_plugin->name, "smk") ||
        !strcmp (in_plugin->name, "vmd") ||
        !strcmp (in_plugin->name, "film_cpk") ||
        !strcmp (in_plugin->name, "ingenient") ||
        !strcmp (in_plugin->name, "psxstr") ||
        !strcmp (in_plugin->name, "nuv") ||
        !strcmp (in_plugin->name, "nut") ||
        !strcmp (in_plugin->name, "nsv") ||
        !strcmp (in_plugin->name, "mxf") ||
        !strcmp (in_plugin->name, "mmf") ||
        !strcmp (in_plugin->name, "mm") ||
        !strcmp (in_plugin->name, "ipmovie") ||
        !strcmp (in_plugin->name, "ape") ||
        !strcmp (in_plugin->name, "RoQ") ||
        !strcmp (in_plugin->name, "idcin") ||
        !strcmp (in_plugin->name, "gxf") ||
        !strcmp (in_plugin->name, "ffm") ||
        !strcmp (in_plugin->name, "ea") ||
        !strcmp (in_plugin->name, "daud") ||
        !strcmp (in_plugin->name, "avs") ||
        !strcmp (in_plugin->name, "aiff") ||
        !strcmp (in_plugin->name, "4xm") ||
        !strcmp (in_plugin->name, "yuv4mpegpipe") ||
        !strcmp (in_plugin->name, "mpc") || !strcmp (in_plugin->name, "gif"))
      rank = GST_RANK_MARGINAL;
    else {
      GST_DEBUG ("ignoring %s", in_plugin->name);
      goto next;
    }

    p = name = g_strdup (in_plugin->name);
    while (*p) {
      if (*p == '.' || *p == ',')
        *p = '_';
      p++;
    }

    /* construct the type */
    type_name = g_strdup_printf ("ffdemux_%s", name);

    /* if it's already registered, drop it */
    if (g_type_from_name (type_name)) {
      g_free (type_name);
      goto next;
    }

    typefind_name = g_strdup_printf ("fftype_%s", name);

    /* create the type now */
    type = g_type_register_static (GST_TYPE_ELEMENT, type_name, &typeinfo, 0);
    g_type_set_qdata (type, GST_FFDEMUX_PARAMS_QDATA, (gpointer) in_plugin);

    if (in_plugin->extensions)
      extensions = g_strsplit (in_plugin->extensions, " ", 0);
    else
      extensions = NULL;

    if (!gst_element_register (plugin, type_name, rank, type) ||
        (register_typefind_func == TRUE &&
            !gst_type_find_register (plugin, typefind_name, rank,
                gst_ffmpegdemux_type_find, extensions, NULL, in_plugin,
                NULL))) {
      g_warning ("Register of type ffdemux_%s failed", name);
      g_free (type_name);
      g_free (typefind_name);
      return FALSE;
    }

    g_free (type_name);
    g_free (typefind_name);
    if (extensions)
      g_strfreev (extensions);

  next:
    g_free (name);
    in_plugin = av_iformat_next (in_plugin);
  }

  GST_LOG ("Finished registering demuxers");

  return TRUE;
}
