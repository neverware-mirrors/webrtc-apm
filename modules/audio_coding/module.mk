# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

isac_vad_c_OBJECTS = \
	modules/audio_coding/codecs/isac/main/source/filter_functions.o \
	modules/audio_coding/codecs/isac/main/source/isac_vad.o \
	modules/audio_coding/codecs/isac/main/source/pitch_estimator.o \
	modules/audio_coding/codecs/isac/main/source/pitch_filter.o

# From isac_c.ninja
isac_c_C_OBJECTS = \
	modules/audio_coding/codecs/isac/main/source/arith_routines.o \
	modules/audio_coding/codecs/isac/main/source/arith_routines_hist.o \
	modules/audio_coding/codecs/isac/main/source/arith_routines_logist.o \
	modules/audio_coding/codecs/isac/main/source/bandwidth_estimator.o \
	modules/audio_coding/codecs/isac/main/source/crc.o \
	modules/audio_coding/codecs/isac/main/source/decode.o \
	modules/audio_coding/codecs/isac/main/source/decode_bwe.o \
	modules/audio_coding/codecs/isac/main/source/encode.o \
	modules/audio_coding/codecs/isac/main/source/encode_lpc_swb.o \
	modules/audio_coding/codecs/isac/main/source/entropy_coding.o \
	modules/audio_coding/codecs/isac/main/source/filterbanks.o \
	modules/audio_coding/codecs/isac/main/source/intialize.o \
	modules/audio_coding/codecs/isac/main/source/isac.o \
	modules/audio_coding/codecs/isac/main/source/lattice.o \
	modules/audio_coding/codecs/isac/main/source/lpc_analysis.o \
	modules/audio_coding/codecs/isac/main/source/lpc_gain_swb_tables.o \
	modules/audio_coding/codecs/isac/main/source/lpc_shape_swb12_tables.o \
	modules/audio_coding/codecs/isac/main/source/lpc_shape_swb16_tables.o \
	modules/audio_coding/codecs/isac/main/source/lpc_tables.o \
	modules/audio_coding/codecs/isac/main/source/pitch_gain_tables.o \
	modules/audio_coding/codecs/isac/main/source/pitch_lag_tables.o \
	modules/audio_coding/codecs/isac/main/source/spectrum_ar_model_tables.o \
	modules/audio_coding/codecs/isac/main/source/transform.o \
	modules/third_party/fft/fft.o

CC_STATIC_LIBRARY(modules/audio_coding/libaudio_coding.pic.a): \
	$(isac_c_C_OBJECTS) $(isac_vad_c_OBJECTS)

modules/audio_coding/libaudio_coding: \
	CC_STATIC_LIBRARY(modules/audio_coding/libaudio_coding.pic.a)

clean: CLEAN(modules/audio_coding/libaudio_coding.pic.a)

.PHONY: modules/audio_coding/libaudio_coding
