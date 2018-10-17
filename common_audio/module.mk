# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

common_audio_CXX_OBJECTS = \
	common_audio/audio_converter.o \
	common_audio/audio_util.o \
	common_audio/channel_buffer.o \
	common_audio/real_fourier.o \
	common_audio/real_fourier_ooura.o \
	common_audio/smoothing_filter.o \
	common_audio/sparse_fir_filter.o \
	common_audio/wav_file.o \
	common_audio/wav_header.o \
	common_audio/window_generator.o \
	common_audio/resampler/push_resampler.o \
	common_audio/resampler/push_sinc_resampler.o \
	common_audio/resampler/resampler.o \
	common_audio/resampler/sinc_resampler.o \
	common_audio/vad/vad.o

common_audio_cc_CXX_OBJECTS = \
	common_audio/signal_processing/dot_product_with_scale.o

# From common_audio_c.ninja
#
# TODO(hychao): figure out if common_audio/real_fourier_openmax.o
# is needed. Build it requires linking openmax dl library.
common_audio_c_C_OBJECTS = \
	common_audio/third_party/fft4g/fft4g.o \
	common_audio/ring_buffer.o \
	common_audio/signal_processing/auto_corr_to_refl_coef.o \
	common_audio/signal_processing/auto_correlation.o \
	common_audio/signal_processing/copy_set_operations.o \
	common_audio/signal_processing/cross_correlation.o \
	common_audio/signal_processing/division_operations.o \
	common_audio/signal_processing/downsample_fast.o \
	common_audio/signal_processing/energy.o \
	common_audio/signal_processing/filter_ar.o \
	common_audio/signal_processing/filter_ma_fast_q12.o \
	common_audio/signal_processing/get_hanning_window.o \
	common_audio/signal_processing/get_scaling_square.o \
	common_audio/signal_processing/ilbc_specific_functions.o \
	common_audio/signal_processing/levinson_durbin.o \
	common_audio/signal_processing/lpc_to_refl_coef.o \
	common_audio/signal_processing/min_max_operations.o \
	common_audio/signal_processing/randomization_functions.o \
	common_audio/signal_processing/real_fft.o \
	common_audio/signal_processing/refl_coef_to_lpc.o \
	common_audio/signal_processing/resample.o \
	common_audio/signal_processing/resample_48khz.o \
	common_audio/signal_processing/resample_by_2.o \
	common_audio/signal_processing/resample_by_2_internal.o \
	common_audio/signal_processing/resample_fractional.o \
	common_audio/signal_processing/spl_init.o \
	common_audio/signal_processing/spl_inl.o \
	common_audio/signal_processing/spl_sqrt.o \
	common_audio/signal_processing/splitting_filter.o \
	common_audio/signal_processing/sqrt_of_one_minus_x_squared.o \
	common_audio/signal_processing/vector_scaling_operations.o \
	common_audio/vad/vad_core.o \
	common_audio/vad/vad_filterbank.o \
	common_audio/vad/vad_gmm.o \
	common_audio/vad/vad_sp.o \
	common_audio/vad/webrtc_vad.o \
	common_audio/signal_processing/complex_fft.o \
	common_audio/signal_processing/complex_bit_reverse.o \
	common_audio/signal_processing/filter_ar_fast_q12.o \
	common_audio/third_party/spl_sqrt_floor/spl_sqrt_floor.o

ifeq (${USE_NEON},1)
common_audio_CXX_OBJECTS += \
	common_audio/fir_filter_neon.o \
	common_audio/resampler/sinc_resampler_neon.o
common_audio_c_C_OBJECTS += \
	common_audio/signal_processing/min_max_operations_neon.o \
	common_audio/signal_processing/cross_correlation_neon.o \
	common_audio/signal_processing/downsample_fast_neon.o
endif

ifeq (${USE_SSE2},1)
common_audio_CXX_OBJECTS += \
	common_audio/fir_filter_sse.o \
	common_audio/resampler/sinc_resampler_sse.o
endif

fir_filter_factory_CXX_OBJECTS = \
	common_audio/fir_filter_c.o \
	common_audio/fir_filter_factory.o

CXX_STATIC_LIBRARY(common_audio/libcommon_audio.pic.a): \
	CPPFLAGS += -DWEBRTC_POSIX
CXX_STATIC_LIBRARY(common_audio/libcommon_audio.pic.a): \
	$(common_audio_c_C_OBJECTS) \
	$(common_audio_cc_CXX_OBJECTS) \
	$(common_audio_CXX_OBJECTS) \
	$(fir_filter_factory_CXX_OBJECTS)

common_audio/libcommon_audio: CXX_STATIC_LIBRARY(common_audio/libcommon_audio.pic.a)

clean: CLEAN(common_audio/libcommon_audio.pic.a)

.PHONY: common_audio/libcommon_audio
