/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef AEC_CONFIG_H_
#define AEC_CONFIG_H_

#include <iniparser.h>

#include "api/audio/echo_canceller3_config.h"

#define AEC_BUFFERING_EXCESS_RENDER_DETECTION_INTERVAL_BLOCKS \
	"buffering:excess_render_detection_interval_blocks"
#define AEC_BUFFERING_EXCESS_RENDER_DETECTION_INTERVAL_BLOCKS_VALUE 250
#define AEC_BUFFERING_MAX_ALLOWED_EXCESS_RENDER_BLOCKS \
	"buffering:max_allowed_excess_render_blocks"
#define AEC_BUFFERING_MAX_ALLOWED_EXCESS_RENDER_BLOCKS_VALUE 8

#define AEC_DELAY_DEFAULT_DELAY "delay:default_delay"
#define AEC_DELAY_DEFAULT_DELAY_VALUE 5
#define AEC_DELAY_DOWN_SAMPLING_FACTOR "delay:down_sampling_factor"
#define AEC_DELAY_DOWN_SAMPLING_FACTOR_VALUE 4
#define AEC_DELAY_NUM_FILTERS "delay:num_filters"
#define AEC_DELAY_NUM_FILTERS_VALUE 5
#define AEC_DELAY_DELAY_HEADROOM_SAMPLES "delay:delay_headroom_samples"
#define AEC_DELAY_DELAY_HEADROOM_SAMPLES_VALUE 32
#define AEC_DELAY_HYSTERESIS_LIMIT_BLOCKS "delay:hysteresis_limit_blocks"
#define AEC_DELAY_HYSTERESIS_LIMIT_BLOCKS_VALUE 1
#define AEC_DELAY_FIXED_CAPTURE_DELAY_SAMPLES \
	"delay:fixed_capture_delay_samples"
#define AEC_DELAY_FIXED_CAPTURE_DELAY_SAMPLES_VALUE 0
#define AEC_DELAY_DELAY_ESTIMATE_SMOOTHING "delay:delay_estimate_smoothing"
#define AEC_DELAY_DELAY_ESTIMATE_SMOOTHING_VALUE 0.7f
#define AEC_DELAY_DELAY_CANDIDATE_DETECTION_THRESHOLD \
	"delay:delay_candidate_detection_threshold"
#define AEC_DELAY_DELAY_CANDIDATE_DETECTION_THRESHOLD_VALUE 0.2f
#define AEC_DELAY_DELAY_SELECTION_THRESHOLD_INITIAL \
	"delay:delay_selection_thresholds_initial"
#define AEC_DELAY_DELAY_SELECTION_THRESHOLD_INITIAL_VALUE 5
#define AEC_DELAY_DELAY_SELECTION_THRESHOLD_CONVERGED \
	"delay:delay_selection_thresholds_converged"
#define AEC_DELAY_DELAY_SELECTION_THRESHOLD_CONVERGED_VALUE 20

// Filter Main configuration
#define AEC_FILTER_MAIN_LENGTH_BLOCKS "filter.main:length_blocks"
#define AEC_FILTER_MAIN_LENGTH_BLOCKS_VALUE 13
#define AEC_FILTER_MAIN_LEAKAGE_CONVERGED "filter.main:leakage_converged"
#define AEC_FILTER_MAIN_LEAKAGE_CONVERGED_VALUE 0.00005f
#define AEC_FILTER_MAIN_LEAKAGE_DIVERGED "filter.main:leakage_diverged"
#define AEC_FILTER_MAIN_LEAKAGE_DIVERGED_VALUE 0.05f
#define AEC_FILTER_MAIN_ERROR_FLOOR "filter.main:error_floor"
#define AEC_FILTER_MAIN_ERROR_FLOOR_VALUE 0.001f
#define AEC_FILTER_MAIN_ERROR_CEIL "filter.main:error_ceil"
#define AEC_FILTER_MAIN_ERROR_CEIL_VALUE 2.f
#define AEC_FILTER_MAIN_NOISE_GATE "filter.main:noise_gate"
#define AEC_FILTER_MAIN_NOISE_GATE_VALUE 20075344.f

// Filter Shadow configuration
#define AEC_FILTER_SHADOW_LENGTH_BLOCKS "filter.shadow:length_blocks"
#define AEC_FILTER_SHADOW_LENGTH_BLOCKS_VALUE 13
#define AEC_FILTER_SHADOW_RATE "filter.shadow:rate"
#define AEC_FILTER_SHADOW_RATE_VALUE 0.7f
#define AEC_FILTER_SHADOW_NOISE_GATE "filter.shadow:noise_gate"
#define AEC_FILTER_SHADOW_NOISE_GATE_VALUE 20075344.f

// Filter Main initial configuration
#define AEC_FILTER_MAIN_INIT_LENGTH_BLOCKS "filter.main_initial:length_blocks"
#define AEC_FILTER_MAIN_INIT_LENGTH_BLOCKS_VALUE 12
#define AEC_FILTER_MAIN_INIT_LEAKAGE_CONVERGED \
	"filter.main_initial:leakage_converged"
#define AEC_FILTER_MAIN_INIT_LEAKAGE_CONVERGED_VALUE 0.005f
#define AEC_FILTER_MAIN_INIT_LEAKAGE_DIVERGED \
	"filter.main_initial:leakage_diverged"
#define AEC_FILTER_MAIN_INIT_LEAKAGE_DIVERGED_VALUE 0.5f
#define AEC_FILTER_MAIN_INIT_ERROR_FLOOR "filter.main_initial:error_floor"
#define AEC_FILTER_MAIN_INIT_ERROR_FLOOR_VALUE 0.001f
#define AEC_FILTER_MAIN_INIT_ERROR_CEIL "filter.main_initial:error_ceil"
#define AEC_FILTER_MAIN_INIT_ERROR_CEIL_VALUE 2.f
#define AEC_FILTER_MAIN_INIT_NOISE_GATE "filter.main_initial:noise_gate"
#define AEC_FILTER_MAIN_INIT_NOISE_GATE_VALUE 20075344.f

// Filter Shadow initial configuration
#define AEC_FILTER_SHADOW_INIT_LENGTH_BLOCKS \
	"filter.shadow_initial:length_blocks"
#define AEC_FILTER_SHADOW_INIT_LENGTH_BLOCKS_VALUE 12
#define AEC_FILTER_SHADOW_INIT_RATE "filter.shadow_initial:rate"
#define AEC_FILTER_SHADOW_INIT_RATE_VALUE 0.9f
#define AEC_FILTER_SHADOW_INIT_NOISE_GATE "filter.shadow_initial:noise_gate"
#define AEC_FILTER_SHADOW_INIT_NOISE_GATE_VALUE 20075344.f

#define AEC_FILTER_CONFIG_CHANGE_DURATION_BLOCKS \
	"filter:config_change_duration_blocks"
#define AEC_FILTER_CONFIG_CHANGE_DURATION_BLOCKS_VALUE 250
#define AEC_FILTER_INITIAL_STATE_SECONDS "filter:initial_state_seconds"
#define AEC_FILTER_INITIAL_STATE_SECONDS_VALUE 2.5f
#define AEC_FILTER_CONSERVATIVE_INITIAL_PHASE \
	"filter:conservative_initial_phase"
#define AEC_FILTER_CONSERVATIVE_INITIAL_PHASE_VALUE 0
#define AEC_FILTER_ENABLE_SHADOW_FILTER_OUTPUT_USAGE \
	"filter:enable_shadow_filter_output_usage"
#define AEC_FILTER_ENABLE_SHADOW_FILTER_OUTPUT_USAGE_VALUE 1

// Erle
#define AEC_ERLE_MIN "erle:min"
#define AEC_ERLE_MIN_VALUE 1.f
#define AEC_ERLE_MAX_L "erle:max_l"
#define AEC_ERLE_MAX_L_VALUE 4.f
#define AEC_ERLE_MAX_H "erle:max_h"
#define AEC_ERLE_MAX_H_VALUE 1.5f
#define AEC_ERLE_ONSET_DETECTION "erle:onset_detection"
#define AEC_ERLE_ONSET_DETECTION_VALUE 1
#define AEC_ERLE_NUM_SECTIONS "erle:num_sections"
#define AEC_ERLE_NUM_SECTIONS_VALUE 1

// EpStrength
#define AEC_EP_STRENGTH_DEFAULT_GAIN "ep_strength:default_gain"
#define AEC_EP_STRENGTH_DEFAULT_GAIN_VALUE 1.f
#define AEC_EP_STRENGTH_DEFAULT_LEN "ep_strength:default_len"
#define AEC_EP_STRENGTH_DEFAULT_LEN_VALUE 0.83f
#define AEC_EP_STRENGTH_REVERB_BASED_ON_RENDER \
	"ep_strength:reverb_based_on_render"
#define AEC_EP_STRENGTH_REVERB_BASED_ON_RENDER_VALUE 1
#define AEC_EP_STRENGTH_ECHO_CAN_SATURATE "ep_strength:echo_can_saturate"
#define AEC_EP_STRENGTH_ECHO_CAN_SATURATE_VALUE 1
#define AEC_EP_STRENGTH_BOUNDED_ERL "ep_strength:bounded_erl"
#define AEC_EP_STRENGTH_BOUNDED_ERL_VALUE 0

#define AEC_ECHO_AUDIBILITY_LOW_RENDER_LIMIT "echo_audibility:low_render_limit"
#define AEC_ECHO_AUDIBILITY_LOW_RENDER_LIMIT_VALUE 4 * 64.f
#define AEC_ECHO_AUDIBILITY_NORMAL_RENDER_LIMIT \
	"echo_audibility:normal_render_limit"
#define AEC_ECHO_AUDIBILITY_NORMAL_RENDER_LIMIT_VALUE 64.f
#define AEC_ECHO_AUDIBILITY_FLOOR_POWER "echo_audibility:floor_power"
#define AEC_ECHO_AUDIBILITY_FLOOR_POWER_VALUE 2 * 64.f
#define AEC_ECHO_AUDIBILITY_AUDIBILITY_THRESHOLD_LF \
	"echo_audibility:audibility_threshold_lf"
#define AEC_ECHO_AUDIBILITY_AUDIBILITY_THRESHOLD_LF_VALUE 10
#define AEC_ECHO_AUDIBILITY_AUDIBILITY_THRESHOLD_MF \
	"echo_audibility:audibility_threshold_mf"
#define AEC_ECHO_AUDIBILITY_AUDIBILITY_THRESHOLD_MF_VALUE 10
#define AEC_ECHO_AUDIBILITY_AUDIBILITY_THRESHOLD_HF \
	"echo_audibility:audibility_threshold_hf"
#define AEC_ECHO_AUDIBILITY_AUDIBILITY_THRESHOLD_HF_VALUE 10
#define AEC_ECHO_AUDIBILITY_USE_STATIONARY_PROPERTIES \
	"echo_audibility:use_stationary_properties"
#define AEC_ECHO_AUDIBILITY_USE_STATIONARY_PROPERTIES_VALUE 0
#define AEC_ECHO_AUDIBILITY_USE_STATIONARITY_PROPERTIES_AT_INIT \
	 "echo_audibility:use_stationarity_properties_at_init"
#define AEC_ECHO_AUDIBILITY_USE_STATIONARITY_PROPERTIES_AT_INIT_VALUE 0

// Rendering levels
#define AEC_RENDER_LEVELS_ACTIVE_RENDER_LIMIT \
	"render_levels:active_render_limit"
#define AEC_RENDER_LEVELS_ACTIVE_RENDER_LIMIT_VALUE 100.f
#define AEC_RENDER_LEVELS_POOR_EXCITATION_RENDER_LIMIT \
	"render_levels:poor_excitation_render_limit"
#define AEC_RENDER_LEVELS_POOR_EXCITATION_RENDER_LIMIT_VALUE 150.f
#define AEC_RENDER_LEVELS_POOR_EXCITATION_RENDER_LIMIT_DS8 \
	"render_levels:poor_excitation_render_limit_ds8"
#define AEC_RENDER_LEVELS_POOR_EXCITATION_RENDER_LIMIT_DS8_VALUE 20.f

// Echo removal controls
#define AEC_ECHO_REMOVAL_CTL_HAS_CLOCK_DRIFT \
	"echo_removal_control:has_clock_drift"
#define AEC_ECHO_REMOVAL_CTL_HAS_CLOCK_DRIFT_VALUE 0
#define AEC_ECHO_REMOVAL_CTL_LINEAR_AND_STABLE_ECHO_PATH \
	"echo_removal_control:linear_and_stable_echo_path"
#define AEC_ECHO_REMOVAL_CTL_LINEAR_AND_STABLE_ECHO_PATH_VALUE 0

// EchoModel
#define AEC_ECHO_MODEL_NOISE_FLOOR_HOLD "echo_model:noise_floor_hold"
#define AEC_ECHO_MODEL_NOISE_FLOOR_HOLD_VALUE 50
#define AEC_ECHO_MODEL_MIN_NOISE_FLOOR_POWER "echo_model:min_noise_floor_power"
#define AEC_ECHO_MODEL_MIN_NOISE_FLOOR_POWER_VALUE 1638400.f
#define AEC_ECHO_MODEL_STATIONARY_GATE_SLOPE "echo_model:stationary_gate_slope"
#define AEC_ECHO_MODEL_STATIONARY_GATE_SLOPE_VALUE 10.f
#define AEC_ECHO_MODEL_NOISE_GATE_POWER "echo_model:noise_gate_power"
#define AEC_ECHO_MODEL_NOISE_GATE_POWER_VALUE 27509.42f
#define AEC_ECHO_MODEL_NOISE_GATE_SLOPE "echo_model:noise_gate_slope"
#define AEC_ECHO_MODEL_NOISE_GATE_SLOPE_VALUE 0.3f
#define AEC_ECHO_MODEL_RENDER_PRE_WINDOW_SIZE \
	"echo_model:render_pre_window_size"
#define AEC_ECHO_MODEL_RENDER_PRE_WINDOW_SIZE_VALUE 1
#define AEC_ECHO_MODEL_RENDER_POST_WINDOW_SIZE \
	"echo_model:render_post_window_size"
#define AEC_ECHO_MODEL_RENDER_POST_WINDOW_SIZE_VALUE 1
#define AEC_ECHO_MODEL_RENDER_PRE_WINDOW_SIZE_INIT \
	"echo_model:render_pre_window_size_init"
#define AEC_ECHO_MODEL_RENDER_PRE_WINDOW_SIZE_INIT_VALUE 10
#define AEC_ECHO_MODEL_RENDER_POST_WINDOW_SIZE_INIT \
	"echo_model:render_post_window_size_init"
#define AEC_ECHO_MODEL_RENDER_POST_WINDOW_SIZE_INIT_VALUE 10
#define AEC_ECHO_MODEL_NONLINEAR_HOLD "echo_model:nonlinear_hold"
#define AEC_ECHO_MODEL_NONLINEAR_HOLD_VALUE 1
#define AEC_ECHO_MODEL_NONLINEAR_RELEASE "echo_model:nonlinear_release"
#define AEC_ECHO_MODEL_NONLINEAR_RELEASE_VALUE 0.001f

#define AEC_SUPPRESSOR_NEAREND_AVERAGE_BLOCKS \
	"suppressor:nearend_average_blocks"
#define AEC_SUPPRESSOR_NEAREND_AVERAGE_BLOCKS_VALUE 4

#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_LF_ENR_TRANSPARENT \
	"suppressor.normal_tuning:mask_lf_enr_transparent"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_LF_ENR_TRANSPARENT_VALUE .3f
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_LF_ENR_SUPPRESS \
	"suppressor.normal_tuning:mask_lf_enr_suppress"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_LF_ENR_SUPPRESS_VALUE .4f
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_LF_EMR_TRANSPARENT \
	"suppressor.normal_tuning:mask_lf_emr_transparent"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_LF_EMR_TRANSPARENT_VALUE .3f

#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_HF_ENR_TRANSPARENT \
	"suppressor.normal_tuning:mask_hf_enr_transparent"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_HF_ENR_TRANSPARENT_VALUE .07f
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_HF_ENR_SUPPRESS \
	"suppressor.normal_tuning:mask_hf_enr_suppress"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_HF_ENR_SUPPRESS_VALUE .1f
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_HF_EMR_TRANSPARENT \
	"suppressor.normal_tuning:mask_hf_emr_transparent"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MASK_HF_EMR_TRANSPARENT_VALUE .3f

#define AEC_SUPPRESSOR_NORMAL_TUNING_MAX_INC_FACTOR \
	"suppressor.normal_tuning:max_inc_factor"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MAX_INC_FACTOR_VALUE 2.0f
#define AEC_SUPPRESSOR_NORMAL_TUNING_MAX_DEC_FACTOR_LF \
	"suppressor.normal_tuning:max_dec_factor_lf"
#define AEC_SUPPRESSOR_NORMAL_TUNING_MAX_DEC_FACTOR_LF_VALUE 0.25f

#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_LF_ENR_TRANSPARENT \
	"suppressor.nearend_tuning:mask_lf_enr_transparent"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_LF_ENR_TRANSPARENT_VALUE 1.09f
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_LF_ENR_SUPPRESS \
	"suppressor.nearend_tuning:mask_lf_enr_suppress"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_LF_ENR_SUPPRESS_VALUE 1.1f
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_LF_EMR_TRANSPARENT \
	"suppressor.nearend_tuning:mask_lf_emr_transparent"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_LF_EMR_TRANSPARENT_VALUE .3f

#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_HF_ENR_TRANSPARENT \
	"suppressor.nearend_tuning:mask_hf_enr_transparent"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_HF_ENR_TRANSPARENT_VALUE .1f
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_HF_ENR_SUPPRESS \
	"suppressor.nearend_tuning:mask_hf_enr_suppress"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_HF_ENR_SUPPRESS_VALUE .3f
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_HF_EMR_TRANSPARENT \
	"suppressor.nearend_tuning:mask_hf_emr_transparent"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MASK_HF_EMR_TRANSPARENT_VALUE .3f

#define AEC_SUPPRESSOR_NEAREND_TUNING_MAX_INC_FACTOR \
	"suppressor.nearend_tuning:max_inc_factor"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MAX_INC_FACTOR_VALUE 2.0f
#define AEC_SUPPRESSOR_NEAREND_TUNING_MAX_DEC_FACTOR_LF \
	"suppressor.nearend_tuning:max_dec_factor_lf"
#define AEC_SUPPRESSOR_NEAREND_TUNING_MAX_DEC_FACTOR_LF_VALUE 0.25f

#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_ENR_THRESHOLD \
	"suppressor.dominant_nearend_detection:enr_threshold"
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_ENR_THRESHOLD_VALUE .25f
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_ENR_EXIT_THRESHOLD \
	"suppressor.dominant_nearend_detection:enr_exit_threshold"
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_ENR_EXIT_THRESHOLD_VALUE 10.f
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_SNR_THRESHOLD \
	"suppressor.dominant_nearend_detection:snr_threshold"
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_SNR_THRESHOLD_VALUE 30.f
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_HOLD_DURATION \
	"suppressor.dominant_nearend_detection:hold_duration"
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_HOLD_DURATION_VALUE 50
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_TRIGGER_THRESHOLD \
	"suppressor.dominant_nearend_detection:trigger_threshold"
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_TRIGGER_THRESHOLD_VALUE 12
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_USE_DURING_INITIAL_PHASE \
	"suppressor.dominant_nearend_detection:use_during_initial_phase"
#define AEC_SUPPRESSOR_DOMINANT_NEAREND_DETECTION_USE_DURING_INITIAL_PHASE_VALUE 1

#define AEC_SUPPRESSOR_HIGH_BANDS_SUPPRESSION_ENR_THRESHOLD \
	"suppressor.high_bands_suppression:enr_threshold"
#define AEC_SUPPRESSOR_HIGH_BANDS_SUPPRESSION_ENR_THRESHOLD_VALUE 1.f
#define AEC_SUPPRESSOR_HIGH_BANDS_SUPPRESSION_MAX_GAIN_DURING_ECHO \
	"suppressor.high_bands_suppression:max_gain_during_echo"
#define AEC_SUPPRESSOR_HIGH_BANDS_SUPPRESSION_MAX_GAIN_DURING_ECHO_VALUE 1.f

#define AEC_SUPPRESSOR_FLOOR_FIRST_INCREASE "suppressor:floor_first_increase"
#define AEC_SUPPRESSOR_FLOOR_FIRST_INCREASE_VALUE 0.00001f
#define AEC_SUPPRESSOR_ENFORCE_TRANSPARENT "suppressor:enforce_transparent"
#define AEC_SUPPRESSOR_ENFORCE_TRANSPARENT_VALUE 0
#define AEC_SUPPRESSOR_ENFORCE_EMPTY_HIGHER_BANDS \
	"suppressor:enforce_empty_higher_bands"
#define AEC_SUPPRESSOR_ENFORCE_EMPTY_HIGHER_BANDS_VALUE 0

/* Gets the aec config from given config directory. */
void aec_config_get(dictionary *ini, webrtc::EchoCanceller3Config *config);

/* Prints the config content to syslog. */
void aec_config_dump(dictionary *config);

#endif /* AEC_CONFIG_H_ */
