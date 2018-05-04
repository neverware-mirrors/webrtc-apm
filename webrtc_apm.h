/* Copyright (c) 2018 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef WEBRTC_APM_H_
#define WEBRTC_APM_H_

#include <stdint.h>
#include <stdio.h>

#define WEBRTC_APM_API __attribute__((visibility("default")))

/*
 * Structures exposing EchoCanceller3Config from upstream
 * echo_canceller3_config.h to webrtc-apm library callers for
 * tuning purpose. We need to update these parameter structures
 * carefully because changing them could break the caller.
 */
struct delay {
	size_t default_delay;
	size_t down_sampling_factor;
	size_t num_filters;
	size_t api_call_jitter_blocks;
	size_t min_echo_path_delay_blocks;
	size_t delay_headroom_blocks;
	size_t hysteresis_limit_1_blocks;
	size_t hysteresis_limit_2_blocks;
	size_t skew_hysteresis_blocks;
};

struct MainConfiguration {
	size_t length_blocks;
	float leakage_converged;
	float leakage_diverged;
	float error_floor;
	float noise_gate;
};

struct ShadowConfiguration {
	size_t length_blocks;
	float rate;
	float noise_gate;
};

struct filter {
	struct MainConfiguration main;
	struct ShadowConfiguration shadow;
	struct MainConfiguration main_initial;
	struct ShadowConfiguration shadow_initial;
	int config_change_duration_blocks;
};

struct erle {
	float min;
	float max_l;
	float max_h;
};

struct ep_strength {
	float lf;
	float mf;
	float hf;
	float default_len;
	int echo_can_saturate;
	int bounded_erl;
};

struct mask {
	float m1;
	float m2;
	float m3;
	float m5;
	float m6;
	float m7;
	float m8;
	float m9;

	float gain_curve_offset;
	float gain_curve_slope;
	float temporal_masking_lf;
	float temporal_masking_hf;
	size_t temporal_masking_lf_bands;
};

struct echo_audibility {
	float low_render_limit;
	float normal_render_limit;
	float floor_power;
	float audibility_threshold_lf;
	float audibility_threshold_mf;
	float audibility_threshold_hf;
	int use_stationary_properties;
};

struct render_levels {
	float active_render_limit;
	float poor_excitation_render_limit;
};

struct GainChanges {
	float max_inc;
	float max_dec;
	float rate_inc;
	float rate_dec;
	float min_inc;
	float min_dec;
};

struct gain_updates {
	struct GainChanges low_noise;
	struct GainChanges initial;
	struct GainChanges normal;
	struct GainChanges saturation;
	struct GainChanges nonlinear;
	float floor_first_increase;
};

struct GainRampup {
	float first_non_zero_gain;
	int non_zero_gain_blocks;
	int full_gain_blocks;
};

struct echo_removal_control {
	struct GainRampup gain_rampup;
	int has_clock_drift;
};

struct echo_model {
	size_t noise_floor_hold;
	float min_noise_floor_power;
	float stationary_gate_slope;
	float noise_gate_power;
	float noise_gate_slope;
	size_t render_pre_window_size;
	size_t render_post_window_size;
	float nonlinear_hold;
	float nonlinear_release;
};

struct suppressor {
	size_t bands_with_reliable_coherence;
 };

struct aec_config {
	struct delay delay;
	struct filter filter;
	struct erle erle;
	struct ep_strength ep_strength;
	struct mask gain_mask;
	struct echo_audibility echo_audibility;
	struct render_levels render_levels;
	struct gain_updates gain_updates;
	struct echo_removal_control echo_removal_control;
	struct echo_model echo_model;
	struct suppressor suppressor;
};

/* Pointer to a webrtc::AudioProcessing instance. */
typedef void* webrtc_apm;

/* Creates a webrtc_apm for forward stream properties. In CRAS use case it
 * is usually created for input stream.
 * Args:
 *    num_channels - Number of channels of the forward stream.
 *    frame_rate - Frame rate used by forward stream.
 *    aec_config - Pointer to aec config.
 */
WEBRTC_APM_API webrtc_apm webrtc_apm_create(
		unsigned int num_channels,
		unsigned int frame_rate,
		struct aec_config *aec_config);

/* Destroys a webrtc_apm instance. */
WEBRTC_APM_API void webrtc_apm_destroy(webrtc_apm apm);

/* Processes data in reverse stream. In CRAS use case this is called for
 * output stream data.
 * Args:
 *    ptr - The webrtc_apm to process reverse stream data.
 *    num_channels - Number of channels of the reverse stream.
 *    rate - Frame rate used by reverse stream.
 *    data - Pointer to the data in reverse stream to be processed.
 *    nframes - Number of frames of reverse stream's data.
 */
WEBRTC_APM_API int webrtc_apm_process_reverse_stream(
		webrtc_apm ptr,
		int num_channels, int rate,
		int16_t *data, int nframes);

/* Processes deinterleaved float data in reverse stream. Expecting data
 * size be 10 ms equivalent of frames. */
WEBRTC_APM_API int webrtc_apm_process_reverse_stream_f(
		webrtc_apm ptr,
		int num_channels, int rate,
		float *const *data);

/* Processes data in forward stream. In CRAS use case this is called for
 * input stream data.
 * Args:
 *    ptr - The webrtc_apm to process forward stream data.
 *    num_channels - Number of channels of the forward stream.
 *    rate - Frame rate used by forward stream.
 *    data - Pointer to the data in forward stream to be processed.
 *    nframes - Number of frames of forward stream's data.
 */
WEBRTC_APM_API int webrtc_apm_process_stream(
		webrtc_apm ptr, int num_channels,
		int rate, int16_t *data, int nframes);

/* Processes deinterleaved float data in forward stream. Expecting data
 * size be 10 ms equivalent of frames. */
WEBRTC_APM_API int webrtc_apm_process_stream_f(webrtc_apm ptr,
				int num_channels,
				int rate,
				float *const *data);

/* Sets the delay in ms between apm analyzes a frame in reverse stream
 * (playback) and this frame received as echo in forward stream (record)
 * This is required for echo cancellation enabled apm.
 * Args:
 *    ptr - Pointer to the webrtc_apm instance.
 *    delay_ms - The delay in ms.
 */
WEBRTC_APM_API int webrtc_apm_set_stream_delay(webrtc_apm ptr, int delay_ms);

/* Checks if apm detects echo in forward stream. */
WEBRTC_APM_API int webrtc_apm_has_echo(webrtc_apm ptr);

/* Dump aec debug info to a file.
 * Args:
 *    ptr - Pointer to the webrtc_apm instance.
 *    work_queue - Pointer holding or to hold the allocated task queue for
 *        aec dump. Will be deleted when aec dump stops.
 *    start - True to start dumping, false to stop.
 *    handle - Pointer of the file storing aec dump.
 */
WEBRTC_APM_API int webrtc_apm_aec_dump(
		webrtc_apm ptr, void** work_queue,
		int start, FILE *handle);

#endif /* WEBRTC_APM_H_ */
