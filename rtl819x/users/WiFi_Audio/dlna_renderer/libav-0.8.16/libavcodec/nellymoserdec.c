/*
 * NellyMoser audio decoder
 * Copyright (c) 2007 a840bda5870ba11f19698ff6eb9581dfb0f95fa5,
 *                    539459aeb7d425140b62a3ec7dbf6dc8e408a306, and
 *                    520e17cd55896441042b14df2566a6eb610ed444
 * Copyright (c) 2007 Loic Minier <lool at dooz.org>
 *                    Benjamin Larsson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * @file
 * The 3 alphanumeric copyright notices are md5summed they are from the original
 * implementors. The original code is available from http://code.google.com/p/nelly2pcm/
 */

#include "nellymoser.h"
#include "libavutil/lfg.h"
#include "libavutil/random_seed.h"
#include "libavutil/audioconvert.h"
#include "avcodec.h"
#include "internal.h"
#include "dsputil.h"
#include "fft.h"
#include "fmtconvert.h"
#include "sinewin.h"

#define BITSTREAM_READER_LE
#include "get_bits.h"


typedef struct NellyMoserDecodeContext {
    AVCodecContext* avctx;
    AVFrame         frame;
    float          *float_buf;
    DECLARE_ALIGNED(16, float, state)[NELLY_BUF_LEN];
    AVLFG           random_state;
    GetBitContext   gb;
    float           scale_bias;
    DSPContext      dsp;
    FFTContext      imdct_ctx;
    FmtConvertContext fmt_conv;
    DECLARE_ALIGNED(32, float, imdct_out)[NELLY_BUF_LEN * 2];
} NellyMoserDecodeContext;

static void nelly_decode_block(NellyMoserDecodeContext *s,
                               const unsigned char block[NELLY_BLOCK_LEN],
                               float audio[NELLY_SAMPLES])
{
    int i,j;
    float buf[NELLY_FILL_LEN], pows[NELLY_FILL_LEN];
    float *aptr, *bptr, *pptr, val, pval;
    int bits[NELLY_BUF_LEN];
    unsigned char v;

    init_get_bits(&s->gb, block, NELLY_BLOCK_LEN * 8);

    bptr = buf;
    pptr = pows;
    val = ff_nelly_init_table[get_bits(&s->gb, 6)];
    for (i=0 ; i<NELLY_BANDS ; i++) {
        if (i > 0)
            val += ff_nelly_delta_table[get_bits(&s->gb, 5)];
        pval = -pow(2, val/2048) * s->scale_bias;
        for (j = 0; j < ff_nelly_band_sizes_table[i]; j++) {
            *bptr++ = val;
            *pptr++ = pval;
        }

    }

    ff_nelly_get_sample_bits(buf, bits);

    for (i = 0; i < 2; i++) {
        aptr = audio + i * NELLY_BUF_LEN;

        init_get_bits(&s->gb, block, NELLY_BLOCK_LEN * 8);
        skip_bits_long(&s->gb, NELLY_HEADER_BITS + i*NELLY_DETAIL_BITS);

        for (j = 0; j < NELLY_FILL_LEN; j++) {
            if (bits[j] <= 0) {
                aptr[j] = M_SQRT1_2*pows[j];
                if (av_lfg_get(&s->random_state) & 1)
                    aptr[j] *= -1.0;
            } else {
                v = get_bits(&s->gb, bits[j]);
                aptr[j] = ff_nelly_dequantization_table[(1<<bits[j])-1+v]*pows[j];
            }
        }
        memset(&aptr[NELLY_FILL_LEN], 0,
               (NELLY_BUF_LEN - NELLY_FILL_LEN) * sizeof(float));

        s->imdct_ctx.imdct_calc(&s->imdct_ctx, s->imdct_out, aptr);
        /* XXX: overlapping and windowing should be part of a more
           generic imdct function */
        s->dsp.vector_fmul_reverse(s->state, s->state, ff_sine_128, NELLY_BUF_LEN);
        s->dsp.vector_fmul_add(aptr, s->imdct_out, ff_sine_128, s->state, NELLY_BUF_LEN);
        memcpy(s->state, s->imdct_out + NELLY_BUF_LEN, sizeof(float)*NELLY_BUF_LEN);
    }
}

static av_cold int decode_init(AVCodecContext * avctx) {
    NellyMoserDecodeContext *s = avctx->priv_data;

    s->avctx = avctx;
    av_lfg_init(&s->random_state, 0);
    ff_mdct_init(&s->imdct_ctx, 8, 1, 1.0);

    dsputil_init(&s->dsp, avctx);

    if (avctx->request_sample_fmt == AV_SAMPLE_FMT_FLT) {
        s->scale_bias = 1.0/(32768*8);
        avctx->sample_fmt = AV_SAMPLE_FMT_FLT;
    } else {
        s->scale_bias = 1.0/(1*8);
        avctx->sample_fmt = AV_SAMPLE_FMT_S16;
        ff_fmt_convert_init(&s->fmt_conv, avctx);
        s->float_buf = av_mallocz(NELLY_SAMPLES * sizeof(*s->float_buf));
        if (!s->float_buf) {
            av_log(avctx, AV_LOG_ERROR, "error allocating float buffer\n");
            return AVERROR(ENOMEM);
        }
    }

    /* Generate overlap window */
    if (!ff_sine_128[127])
        ff_init_ff_sine_windows(7);

    avctx->channel_layout = AV_CH_LAYOUT_MONO;

    avcodec_get_frame_defaults(&s->frame);
    avctx->coded_frame = &s->frame;

    return 0;
}

static int decode_tag(AVCodecContext *avctx, void *data,
                      int *got_frame_ptr, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    NellyMoserDecodeContext *s = avctx->priv_data;
    int blocks, i, ret;
    int16_t *samples_s16;
    float   *samples_flt;

    blocks     = buf_size / NELLY_BLOCK_LEN;
    if (blocks <= 0) {
        av_log(avctx, AV_LOG_ERROR, "Packet is too small\n");
        return AVERROR_INVALIDDATA;
    }
    if (buf_size % NELLY_BLOCK_LEN) {
        av_log(avctx, AV_LOG_WARNING, "Leftover bytes: %d.\n",
               buf_size % NELLY_BLOCK_LEN);
    }
    /* Normal numbers of blocks for sample rates:
     *  8000 Hz - 1
     * 11025 Hz - 2
     * 16000 Hz - 3
     * 22050 Hz - 4
     * 44100 Hz - 8
     */

    /* get output buffer */
    s->frame.nb_samples = NELLY_SAMPLES * blocks;
    if ((ret = ff_get_buffer(avctx, &s->frame)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return ret;
    }
    samples_s16 = (int16_t *)s->frame.data[0];
    samples_flt = (float   *)s->frame.data[0];

    for (i=0 ; i<blocks ; i++) {
        if (avctx->sample_fmt == AV_SAMPLE_FMT_FLT) {
            nelly_decode_block(s, buf, samples_flt);
            samples_flt += NELLY_SAMPLES;
        } else {
            nelly_decode_block(s, buf, s->float_buf);
            s->fmt_conv.float_to_int16(samples_s16, s->float_buf, NELLY_SAMPLES);
            samples_s16 += NELLY_SAMPLES;
        }
        buf += NELLY_BLOCK_LEN;
    }

    *got_frame_ptr   = 1;
    *(AVFrame *)data = s->frame;

    return buf_size;
}

static av_cold int decode_end(AVCodecContext * avctx) {
    NellyMoserDecodeContext *s = avctx->priv_data;

    av_freep(&s->float_buf);
    ff_mdct_end(&s->imdct_ctx);

    return 0;
}

AVCodec ff_nellymoser_decoder = {
    .name           = "nellymoser",
    .type           = AVMEDIA_TYPE_AUDIO,
    .id             = CODEC_ID_NELLYMOSER,
    .priv_data_size = sizeof(NellyMoserDecodeContext),
    .init           = decode_init,
    .close          = decode_end,
    .decode         = decode_tag,
    .capabilities   = CODEC_CAP_DR1 | CODEC_CAP_PARAM_CHANGE,
    .long_name = NULL_IF_CONFIG_SMALL("Nellymoser Asao"),
    .sample_fmts    = (const enum AVSampleFormat[]) { AV_SAMPLE_FMT_FLT,
                                                      AV_SAMPLE_FMT_S16,
                                                      AV_SAMPLE_FMT_NONE },
};

