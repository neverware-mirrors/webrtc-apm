# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

module_audio_processing_CXX_OBJECTS = \
	modules/audio_processing/aec/aec_resampler.o \
	modules/audio_processing/aec/echo_cancellation.o \
	modules/audio_processing/agc/agc.o \
	modules/audio_processing/agc/agc_manager_direct.o \
	modules/audio_processing/agc/loudness_histogram.o \
	modules/audio_processing/agc/utility.o \
	modules/audio_processing/audio_buffer.o \
	modules/audio_processing/audio_processing_impl.o \
	modules/audio_processing/echo_cancellation_impl.o \
	modules/audio_processing/echo_control_mobile_impl.o \
	modules/audio_processing/echo_detector/circular_buffer.o \
	modules/audio_processing/echo_detector/mean_variance_estimator.o \
	modules/audio_processing/echo_detector/moving_max.o \
	modules/audio_processing/echo_detector/normalized_covariance_estimator.o \
	modules/audio_processing/gain_control_for_experimental_agc.o \
	modules/audio_processing/gain_control_impl.o \
	modules/audio_processing/gain_controller2.o \
	modules/audio_processing/include/audio_processing.o \
	modules/audio_processing/include/config.o \
	modules/audio_processing/level_estimator_impl.o \
	modules/audio_processing/low_cut_filter.o \
	modules/audio_processing/noise_suppression_impl.o \
	modules/audio_processing/noise_suppression_proxy.o \
	modules/audio_processing/residual_echo_detector.o \
	modules/audio_processing/rms_level.o \
	modules/audio_processing/splitting_filter.o \
	modules/audio_processing/three_band_filter_bank.o \
	modules/audio_processing/transient/moving_moments.o \
	modules/audio_processing/transient/transient_detector.o \
	modules/audio_processing/transient/transient_suppressor.o \
	modules/audio_processing/transient/wpd_node.o \
	modules/audio_processing/transient/wpd_tree.o \
	modules/audio_processing/typing_detection.o \
	modules/audio_processing/voice_detection_impl.o

audio_processing_statistics_CXX_OBJECTS = \
	modules/audio_processing/include/audio_processing_statistics.o

aec_dump_interface_CXX_OBJECTS = \
	modules/audio_processing/include/aec_dump.o

aec_dump_impl_CXX_OBJECTS = \
	modules/audio_processing/aec_dump/aec_dump_impl.o \
	modules/audio_processing/aec_dump/capture_stream_info.o \
	modules/audio_processing/aec_dump/write_to_file_task.o

apm_logging_CXX_OBJECTS = \
	modules/audio_processing/logging/apm_data_dumper.o

audio_processing_c_C_OBJECTS = \
	modules/audio_processing/agc/legacy/analog_agc.o \
	modules/audio_processing/agc/legacy/digital_agc.o \
	modules/audio_processing/ns/noise_suppression.o \
	modules/audio_processing/ns/ns_core.o

aec_core_CXX_OBJECTS = \
	modules/audio_processing/aec/aec_core.o \
	modules/audio_processing/aecm/aecm_core.o \
	modules/audio_processing/aecm/echo_control_mobile.o \
	modules/audio_processing/utility/block_mean_calculator.o \
	modules/audio_processing/utility/delay_estimator.o \
	modules/audio_processing/utility/delay_estimator_wrapper.o \
	modules/audio_processing/utility/ooura_fft.o \
	modules/audio_processing/aecm/aecm_core_c.o

ifeq (${USE_NEON},1)
aec_core_CXX_OBJECTS += \
	modules/audio_processing/aec/aec_core_neon.o \
	modules/audio_processing/aecm/aecm_core_neon.o \
	modules/audio_processing/utility/ooura_fft_neon.o
endif

ifeq (${USE_SSE2},1)
aec_core_CXX_OBJECTS += \
	modules/audio_processing/aec/aec_core_sse2.o \
	modules/audio_processing/utility/ooura_fft_sse2.o
endif

audio_frame_api_CXX_OBJECTS = \
	api/audio/audio_frame.o

aec3_CXX_OBJECTS = \
	modules/audio_processing/aec3/adaptive_fir_filter.o \
	modules/audio_processing/aec3/aec3_common.o \
	modules/audio_processing/aec3/aec3_fft.o \
	modules/audio_processing/aec3/aec_state.o \
	modules/audio_processing/aec3/api_call_jitter_metrics.o\
	modules/audio_processing/aec3/block_delay_buffer.o \
	modules/audio_processing/aec3/block_framer.o \
	modules/audio_processing/aec3/block_processor.o \
	modules/audio_processing/aec3/block_processor_metrics.o \
	modules/audio_processing/aec3/cascaded_biquad_filter.o \
	modules/audio_processing/aec3/clockdrift_detector.o \
	modules/audio_processing/aec3/comfort_noise_generator.o \
	modules/audio_processing/aec3/decimator.o \
	modules/audio_processing/aec3/downsampled_render_buffer.o \
	modules/audio_processing/aec3/echo_audibility.o \
	modules/audio_processing/aec3/echo_canceller3.o \
	modules/audio_processing/aec3/echo_path_delay_estimator.o \
	modules/audio_processing/aec3/echo_path_variability.o \
	modules/audio_processing/aec3/echo_remover.o \
	modules/audio_processing/aec3/echo_remover_metrics.o \
	modules/audio_processing/aec3/erl_estimator.o \
	modules/audio_processing/aec3/erle_estimator.o \
	modules/audio_processing/aec3/fft_buffer.o \
	modules/audio_processing/aec3/filter_analyzer.o \
	modules/audio_processing/aec3/frame_blocker.o \
	modules/audio_processing/aec3/fullband_erle_estimator.o \
	modules/audio_processing/aec3/main_filter_update_gain.o \
	modules/audio_processing/aec3/matched_filter.o \
	modules/audio_processing/aec3/matched_filter_lag_aggregator.o \
	modules/audio_processing/aec3/matrix_buffer.o \
	modules/audio_processing/aec3/moving_average.o \
	modules/audio_processing/aec3/render_buffer.o \
	modules/audio_processing/aec3/render_delay_buffer.o \
	modules/audio_processing/aec3/render_delay_controller.o \
	modules/audio_processing/aec3/render_delay_controller_metrics.o \
	modules/audio_processing/aec3/render_reverb_model.o \
	modules/audio_processing/aec3/render_signal_analyzer.o \
	modules/audio_processing/aec3/residual_echo_estimator.o \
	modules/audio_processing/aec3/reverb_decay_estimator.o \
	modules/audio_processing/aec3/reverb_frequency_response.o \
	modules/audio_processing/aec3/reverb_model.o \
	modules/audio_processing/aec3/reverb_model_estimator.o \
	modules/audio_processing/aec3/reverb_model_fallback.o \
	modules/audio_processing/aec3/shadow_filter_update_gain.o \
	modules/audio_processing/aec3/signal_dependent_erle_estimator.o \
	modules/audio_processing/aec3/skew_estimator.o \
	modules/audio_processing/aec3/stationarity_estimator.o \
	modules/audio_processing/aec3/subband_erle_estimator.o \
	modules/audio_processing/aec3/subtractor.o \
	modules/audio_processing/aec3/subtractor_output.o \
	modules/audio_processing/aec3/subtractor_output_analyzer.o \
	modules/audio_processing/aec3/suppression_filter.o \
	modules/audio_processing/aec3/suppression_gain.o \
	modules/audio_processing/aec3/vector_buffer.o

aec3_factory_CXX_OBJECTS = \
	api/audio/echo_canceller3_factory.o

aec3_config_CXX_OBJECTS = \
	api/audio/echo_canceller3_config.o

agc2_CXX_OBJECTS = \
	modules/audio_processing/agc2/adaptive_agc.o \
	modules/audio_processing/agc2/adaptive_digital_gain_applier.o \
	modules/audio_processing/agc2/adaptive_mode_level_estimator.o \
	modules/audio_processing/agc2/adaptive_mode_level_estimator_agc.o \
	modules/audio_processing/agc2/agc2_common.o \
	modules/audio_processing/agc2/biquad_filter.o \
	modules/audio_processing/agc2/compute_interpolated_gain_curve.o \
	modules/audio_processing/agc2/down_sampler.o \
	modules/audio_processing/agc2/fixed_digital_level_estimator.o \
	modules/audio_processing/agc2/gain_applier.o \
	modules/audio_processing/agc2/interpolated_gain_curve.o \
	modules/audio_processing/agc2/limiter.o \
	modules/audio_processing/agc2/limiter_db_gain_curve.o \
	modules/audio_processing/agc2/noise_level_estimator.o \
	modules/audio_processing/agc2/noise_spectrum_estimator.o \
	modules/audio_processing/agc2/saturation_protector.o \
	modules/audio_processing/agc2/signal_classifier.o \
	modules/audio_processing/agc2/vad_with_level.o \
	modules/audio_processing/agc2/vector_float_frame.o \
	modules/audio_processing/agc2/rnn_vad/features_extraction.o \
	modules/audio_processing/agc2/rnn_vad/fft_util.o \
	modules/audio_processing/agc2/rnn_vad/lp_residual.o \
	modules/audio_processing/agc2/rnn_vad/pitch_search.o \
	modules/audio_processing/agc2/rnn_vad/pitch_search_internal.o \
	modules/audio_processing/agc2/rnn_vad/rnn.o \
	modules/audio_processing/agc2/rnn_vad/spectral_features.o \
	modules/audio_processing/agc2/rnn_vad/spectral_features_internal.o \
	third_party/rnnoise/src/kiss_fft.o \
	third_party/rnnoise/src/rnn_vad_weights.o

# Dependency of agc/agc.o
vad_CXX_OBJECTS = \
	modules/audio_processing/vad/gmm.o \
	modules/audio_processing/vad/pitch_based_vad.o \
	modules/audio_processing/vad/pitch_internal.o \
	modules/audio_processing/vad/pole_zero_filter.o \
	modules/audio_processing/vad/standalone_vad.o \
	modules/audio_processing/vad/vad_audio_proc.o \
	modules/audio_processing/vad/vad_circular_buffer.o \
	modules/audio_processing/vad/voice_activity_detector.o

# Dependency of vad objects
audio_frame_operations_CXX_OBJECTS = \
	audio/utility/audio_frame_operations.o

# TODO(hychao): WEBRTC_NS_FLOAT=0 for cases prefer fixed point operation
CXX_STATIC_LIBRARY(libaudio_processing.pic.a): \
	CPPFLAGS += -I. -DWEBRTC_POSIX \
		-DWEBRTC_APM_DEBUG_DUMP=0 \
		-DWEBRTC_INTELLIGIBILITY_ENHANCER=0 \
		-DWEBRTC_NS_FLOAT=1

CXX_STATIC_LIBRARY(libaudio_processing.pic.a): \
	$(module_audio_processing_CXX_OBJECTS) \
	$(audio_processing_statistics_CXX_OBJECTS) \
	$(aec_dump_interface_CXX_OBJECTS) \
	$(aec_dump_impl_CXX_OBJECTS) \
	$(apm_logging_CXX_OBJECTS) \
	$(audio_processing_c_C_OBJECTS) \
	$(aec_core_CXX_OBJECTS) \
	$(audio_frame_api_CXX_OBJECTS) \
	$(agc2_CXX_OBJECTS) \
	$(vad_CXX_OBJECTS) \
	$(audio_frame_api_CXX_OBJECTS) \
	$(aec3_CXX_OBJECTS) \
	$(aec3_factory_CXX_OBJECTS) \
	$(aec3_config_CXX_OBJECTS)

module/libaudio_processing: CXX_STATIC_LIBRARY(libaudio_processing.pic.a)

clean: CLEAN(libaudio_processing.pic.a)

.PHONY: module/libaudio_processing

PROTO_DIR = "modules/audio_processing"

$(PROTO_DIR)/debug.pb.cc \
$(PROTO_DIR)/debug.pb.h:
	protoc -I $(PROTO_DIR) --cpp_out=$(PROTO_DIR) $(PROTO_DIR)/debug.proto
clean: CLEAN($(PROTO_DIR)/debug.pb.h $(PROTO_DIR)/debug.pb.cc)
$(eval $(call add_object_rules,$(PROTO_DIR)/debug.pb.o,CXX,cc,CXXFLAGS))

modules/audio_processing/aec_dump/aec_dump_impl.o.depends \
modules/audio_processing/aec_dump/capture_stream_info.o.depends \
modules/audio_processing/aec_dump/write_to_file_task.o.depends: \
	$(PROTO_DIR)/debug.pb.h

audioproc_debug_proto_CXX_OBJECTS = \
	$(PROTO_DIR)/debug.pb.o

CXX_STATIC_LIBRARY(libaudioproc_debug_proto.pic.a): \
	$(audioproc_debug_proto_CXX_OBJECTS)

modules/audio_processing/libaudioproc_debug_proto: \
	CXX_STATIC_LIBRARY(libaudioproc_debug_proto.pic.a)

clean: CLEAN(libaudioproc_debug_proto.pic.a)

.PHONY: modules/audio_processing/libaudioproc_debug_proto
