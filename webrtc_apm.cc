/* Copyright (c) 2018 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "api/audio/echo_canceller3_factory.h"
#include "modules/audio_processing/aec_dump/aec_dump_factory.h"
#include "modules/audio_processing/include/aec_dump.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "modules/include/module_common_types.h"
#include "rtc_base/task_queue.h"

extern "C" {
#include "webrtc_apm.h"

int convert_to_aec3_config(
		const struct aec_config *config,
		webrtc::EchoCanceller3Config *aec3_config)
{
	aec3_config->delay.default_delay =
		config->delay.default_delay;
	aec3_config->delay.down_sampling_factor =
		config->delay.down_sampling_factor;
	aec3_config->delay.num_filters =
		config->delay.num_filters;
	aec3_config->delay.api_call_jitter_blocks =
		config->delay.api_call_jitter_blocks;
	aec3_config->delay.min_echo_path_delay_blocks =
		config->delay.min_echo_path_delay_blocks,
	aec3_config->delay.delay_headroom_blocks =
		config->delay.delay_headroom_blocks;
	aec3_config->delay.hysteresis_limit_1_blocks =
		config->delay.hysteresis_limit_1_blocks;
	aec3_config->delay.hysteresis_limit_2_blocks =
		config->delay.hysteresis_limit_2_blocks,
	aec3_config->delay.skew_hysteresis_blocks =
		config->delay.skew_hysteresis_blocks;
	aec3_config->delay.fixed_capture_delay_samples =
		config->delay.fixed_capture_delay_samples;

	aec3_config->filter.main = {
		config->filter.main.length_blocks,
		config->filter.main.leakage_converged,
		config->filter.main.leakage_diverged,
		config->filter.main.error_floor,
		config->filter.main.noise_gate
	};
	aec3_config->filter.shadow = {
		config->filter.shadow.length_blocks,
		config->filter.shadow.rate,
		config->filter.shadow.noise_gate
	};
	aec3_config->filter.main_initial = {
		config->filter.main_initial.length_blocks,
		config->filter.main_initial.leakage_converged,
		config->filter.main_initial.leakage_diverged,
		config->filter.main_initial.error_floor,
		config->filter.main_initial.noise_gate
	};
	aec3_config->filter.shadow_initial = {
		config->filter.shadow_initial.length_blocks,
		config->filter.shadow_initial.rate,
		config->filter.shadow_initial.noise_gate
	};
	aec3_config->filter.config_change_duration_blocks =
		config->filter.config_change_duration_blocks;
	aec3_config->filter.initial_state_seconds =
		config->filter.initial_state_seconds;
	aec3_config->filter.conservative_initial_phase =
		static_cast<bool>(config->filter.conservative_initial_phase);
	aec3_config->filter.enable_shadow_filter_output_usage =
		static_cast<bool>(
			config->filter.enable_shadow_filter_output_usage);
	aec3_config->erle = {
		config->erle.min,
		config->erle.max_l,
		config->erle.max_h,
		static_cast<bool>(config->erle.onset_detection)
	};
	aec3_config->ep_strength = {
		config->ep_strength.lf,
		config->ep_strength.mf,
		config->ep_strength.hf,
		config->ep_strength.default_len,
		static_cast<bool>(config->ep_strength.reverb_based_on_render),
		static_cast<bool>(config->ep_strength.echo_can_saturate),
		static_cast<bool>(config->ep_strength.bounded_erl)
	};

	aec3_config->gain_mask.m0 = config->gain_mask.m0;
	aec3_config->gain_mask.m1 = config->gain_mask.m1;
	aec3_config->gain_mask.m2 = config->gain_mask.m2;
	aec3_config->gain_mask.m3 = config->gain_mask.m3;
	aec3_config->gain_mask.m5 = config->gain_mask.m5;
	aec3_config->gain_mask.m6 = config->gain_mask.m6;
	aec3_config->gain_mask.m7 = config->gain_mask.m7;
	aec3_config->gain_mask.m8 = config->gain_mask.m8;
	aec3_config->gain_mask.m9 = config->gain_mask.m9;
	aec3_config->gain_mask.gain_curve_offset =
			config->gain_mask.gain_curve_offset;
	aec3_config->gain_mask.gain_curve_slope =
			config->gain_mask.gain_curve_slope;
	aec3_config->gain_mask.temporal_masking_lf =
			config->gain_mask.temporal_masking_lf;
	aec3_config->gain_mask.temporal_masking_hf =
			config->gain_mask.temporal_masking_hf;
	aec3_config->gain_mask.temporal_masking_lf_bands =
			config->gain_mask.temporal_masking_lf_bands;

	aec3_config->echo_audibility = {
		config->echo_audibility.low_render_limit,
		config->echo_audibility.normal_render_limit,
		config->echo_audibility.floor_power,
		config->echo_audibility.audibility_threshold_lf,
		config->echo_audibility.audibility_threshold_mf,
		config->echo_audibility.audibility_threshold_hf,
		static_cast<bool>(
			config->echo_audibility.use_stationary_properties)
	};
	aec3_config->render_levels = {
		config->render_levels.active_render_limit,
		config->render_levels.poor_excitation_render_limit,
		config->render_levels.poor_excitation_render_limit_ds8,
	};

	aec3_config->echo_removal_control = {
		{
		config->echo_removal_control.gain_rampup.initial_gain,
		config->echo_removal_control.gain_rampup.first_non_zero_gain,
		config->echo_removal_control.gain_rampup.non_zero_gain_blocks,
		config->echo_removal_control.gain_rampup.full_gain_blocks
		},
		static_cast<bool>(config->echo_removal_control.has_clock_drift),
		static_cast<bool>(
			config->echo_removal_control.linear_and_stable_echo_path)
	};

	webrtc::EchoCanceller3Config::EchoModel echo_model;

	echo_model.noise_floor_hold = config->echo_model.noise_floor_hold;
	echo_model.min_noise_floor_power =
			config->echo_model.min_noise_floor_power;
	echo_model.stationary_gate_slope =
			config->echo_model.stationary_gate_slope;
	echo_model.noise_gate_power = config->echo_model.noise_gate_power;
	echo_model.noise_gate_slope = config->echo_model.noise_gate_slope;
	echo_model.render_pre_window_size =
			config->echo_model.render_pre_window_size;
	echo_model.render_post_window_size =
			config->echo_model.render_post_window_size;
	echo_model.render_pre_window_size_init =
			config->echo_model.render_pre_window_size_init;
	echo_model.render_post_window_size_init =
			config->echo_model.render_post_window_size_init;
	echo_model.nonlinear_hold = config->echo_model.nonlinear_hold;
	echo_model.nonlinear_release = config->echo_model.nonlinear_release;

	aec3_config->echo_model = echo_model;

	aec3_config->suppressor.normal_tuning.mask_lf.enr_transparent =
		config->suppressor.normal_tuning.mask_lf.enr_transparent;
	aec3_config->suppressor.normal_tuning.mask_lf.enr_suppress =
		config->suppressor.normal_tuning.mask_lf.enr_suppress;
	aec3_config->suppressor.normal_tuning.mask_lf.emr_transparent =
		config->suppressor.normal_tuning.mask_lf.emr_transparent;
	aec3_config->suppressor.normal_tuning.mask_hf.enr_transparent =
		config->suppressor.normal_tuning.mask_hf.enr_transparent;
	aec3_config->suppressor.normal_tuning.mask_hf.enr_suppress =
		config->suppressor.normal_tuning.mask_hf.enr_suppress;
	aec3_config->suppressor.normal_tuning.mask_hf.emr_transparent =
		config->suppressor.normal_tuning.mask_hf.emr_transparent;
	aec3_config->suppressor.normal_tuning.max_inc_factor =
		config->suppressor.normal_tuning.max_inc_factor;
	aec3_config->suppressor.normal_tuning.max_dec_factor_lf =
		config->suppressor.normal_tuning.max_dec_factor_lf;

	aec3_config->suppressor.nearend_tuning.mask_lf.enr_transparent =
		config->suppressor.nearend_tuning.mask_lf.enr_transparent;
	aec3_config->suppressor.nearend_tuning.mask_lf.enr_suppress =
		config->suppressor.nearend_tuning.mask_lf.enr_suppress;
	aec3_config->suppressor.nearend_tuning.mask_lf.emr_transparent =
		config->suppressor.nearend_tuning.mask_lf.emr_transparent;
	aec3_config->suppressor.nearend_tuning.mask_hf.enr_transparent =
		config->suppressor.nearend_tuning.mask_hf.enr_transparent;
	aec3_config->suppressor.nearend_tuning.mask_hf.enr_suppress =
		config->suppressor.nearend_tuning.mask_hf.enr_suppress,
	aec3_config->suppressor.nearend_tuning.mask_hf.emr_transparent =
		config->suppressor.nearend_tuning.mask_hf.emr_transparent;
	aec3_config->suppressor.nearend_tuning.max_inc_factor =
		config->suppressor.nearend_tuning.max_inc_factor;
	aec3_config->suppressor.nearend_tuning.max_dec_factor_lf =
		config->suppressor.nearend_tuning.max_dec_factor_lf;

	aec3_config->suppressor.dominant_nearend_detection.enr_threshold =
		config->suppressor.dominant_nearend_detection.enr_threshold;
	aec3_config->suppressor.dominant_nearend_detection.snr_threshold =
		config->suppressor.dominant_nearend_detection.snr_threshold;
	aec3_config->suppressor.dominant_nearend_detection.hold_duration =
		config->suppressor.dominant_nearend_detection.hold_duration;
	aec3_config->suppressor.dominant_nearend_detection.trigger_threshold =
		config->suppressor.dominant_nearend_detection.trigger_threshold;

	aec3_config->suppressor.high_bands_suppression.enr_threshold =
		config->suppressor.high_bands_suppression.enr_threshold;
	aec3_config->suppressor.high_bands_suppression.max_gain_during_echo =
		config->suppressor.high_bands_suppression.max_gain_during_echo;

	aec3_config->suppressor.floor_first_increase =
		config->suppressor.floor_first_increase;
	aec3_config->suppressor.enforce_transparent =
		config->suppressor.enforce_transparent;
	aec3_config->suppressor.enforce_empty_higher_bands =
		config->suppressor.enforce_empty_higher_bands;

	return 0;
}

int convert_to_ap_config(struct apm_config *apm_config,
			 webrtc::AudioProcessing::Config *ap_config)
{
	ap_config->residual_echo_detector.enabled =
		apm_config->residual_echo_detector_enabled;
	ap_config->high_pass_filter.enabled =
		apm_config->high_pass_filter_enabled;
	ap_config->pre_amplifier.enabled =
		apm_config->pre_amplifier_enabled;
	ap_config->pre_amplifier.fixed_gain_factor =
		apm_config->pre_amplifier_fixed_gain_factor;
	ap_config->gain_controller2.enabled =
		apm_config->gain_controller2_enabled;
	ap_config->gain_controller2.fixed_gain_db =
		apm_config->gain_controller2_fixed_gain_db;
	return 0;
}

webrtc_apm webrtc_apm_create(unsigned int num_channels,
			     unsigned int frame_rate,
			     struct aec_config *aec_config,
			     struct apm_config *apm_config)
{
	int err;
	webrtc::AudioProcessing *apm;
	webrtc::AudioProcessing::ChannelLayout channel_layout;
	webrtc::AudioProcessingBuilder apm_builder;
	webrtc::EchoCanceller3Config aec3_config;
	std::unique_ptr<webrtc::EchoControlFactory> ec3_factory;
	webrtc::AudioProcessing::Config ap_config;
	webrtc::GainControl::Mode agc_mode;
	webrtc::NoiseSuppression::Level ns_level;

	if (aec_config) {
		convert_to_aec3_config(aec_config, &aec3_config);
		ec3_factory.reset(
			new webrtc::EchoCanceller3Factory(aec3_config));
	} else {
		ec3_factory.reset(new webrtc::EchoCanceller3Factory());
	}

	switch (num_channels) {
		case 1:
			channel_layout = webrtc::AudioProcessing::kMono;
			break;
		case 2:
			channel_layout = webrtc::AudioProcessing::kStereo;
			break;
		default:
			return NULL;
	}

	apm_builder.SetEchoControlFactory(std::move(ec3_factory));
	apm = apm_builder.Create();

	if (apm_config) {
		convert_to_ap_config(apm_config, &ap_config);
		apm->ApplyConfig(ap_config);

		/* Configure AGC1 */
		switch (apm_config->agc_mode) {
		case ADAPTIVE_ANALOG:
			agc_mode = webrtc::GainControl::Mode::kAdaptiveAnalog;
			break;
		case ADAPTIVE_DIGITAL:
			agc_mode = webrtc::GainControl::Mode::kAdaptiveDigital;
			break;
		case FIXED_DITIGAL:
			agc_mode = webrtc::GainControl::Mode::kFixedDigital;
			break;
		default:
			return NULL;
		}
		apm->gain_control()->set_compression_gain_db(
				apm_config->gain_control_compression_gain_db);
		apm->gain_control()->set_mode(agc_mode);
		apm->gain_control()->Enable(
				apm_config->gain_control_enabled);
		/* Configure noise suppression */
		switch (apm_config->ns_level) {
		case LOW:
			ns_level = webrtc::NoiseSuppression::Level::kLow;
			break;
		case MODERATE:
			ns_level = webrtc::NoiseSuppression::Level::kModerate;
			break;
		case HIGH:
			ns_level = webrtc::NoiseSuppression::Level::kHigh;
			break;
		case VERY_HIGH:
			ns_level = webrtc::NoiseSuppression::Level::kVeryHigh;
			break;
		default:
			return NULL;

		}
		apm->noise_suppression()->set_level(ns_level);
		apm->noise_suppression()->Enable(
				apm_config->noise_suppression_enabled);
	}

	err = apm->Initialize(frame_rate, frame_rate, frame_rate,
			      channel_layout, channel_layout, channel_layout);
	if (err) {
		delete apm;
		return NULL;
	}

	return reinterpret_cast<webrtc_apm>(apm);
}

int webrtc_apm_process_reverse_stream_f(
		webrtc_apm ptr,
		int num_channels, int rate,
		float *const *data)
{
	webrtc::AudioProcessing *apm;
	webrtc::StreamConfig config =
		webrtc::StreamConfig(rate, num_channels);

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);

	return apm->ProcessReverseStream(data, config, config, data);
}

int webrtc_apm_process_reverse_stream(webrtc_apm ptr,
				     int num_channels, int rate,
				     int16_t *data, int nframes)
{
	webrtc::AudioFrame af;
	webrtc::AudioProcessing *apm;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);

	af.UpdateFrame(0xFFFFFFFF, data, nframes, rate,
		       webrtc::AudioFrame::kNormalSpeech,
		       webrtc::AudioFrame::kVadUnknown,
		       num_channels);
	return apm->ProcessReverseStream(&af);
}

int webrtc_apm_process_stream_f(webrtc_apm ptr,
				int num_channels,
				int rate,
				float *const *data)
{
	webrtc::AudioProcessing *apm;

	webrtc::StreamConfig config =
		webrtc::StreamConfig(rate, num_channels);
	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	return apm->ProcessStream(data, config, config, data);
}


int webrtc_apm_process_stream(webrtc_apm ptr, int num_channels,
			     int rate, int16_t *data, int nframes)
{
	int ret;
	webrtc::AudioFrame af;
	webrtc::AudioProcessing *apm;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	//set stream delay
	af.UpdateFrame(0xFFFFFFFF, data, nframes, rate,
			webrtc::AudioFrame::kNormalSpeech,
			webrtc::AudioFrame::kVadUnknown,
			num_channels);
	ret = apm->ProcessStream(&af);
	if (ret)
		return ret;

	memcpy(data, af.data(), nframes * num_channels * 2);
	return ret;
}

void webrtc_apm_destroy(webrtc_apm ptr)
{
	webrtc::AudioProcessing *apm;
	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	delete apm;
}

int webrtc_apm_set_stream_delay(webrtc_apm ptr, int delay_ms)
{
	webrtc::AudioProcessing *apm;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	return apm->set_stream_delay_ms(delay_ms);
}

int webrtc_apm_aec_dump(webrtc_apm ptr, void** wq_ptr, int start, FILE *handle)
{
	webrtc::AudioProcessing *apm;
	rtc::TaskQueue *work_queue;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);

	if (start) {
		work_queue = new rtc::TaskQueue("aecdump-worker-queue",
						rtc::TaskQueue::Priority::LOW);
		auto aec_dump = webrtc::AecDumpFactory::Create(handle, -1, work_queue);
		if (!aec_dump)
			return -ENOMEM;
		apm->AttachAecDump(std::move(aec_dump));
		*wq_ptr = reinterpret_cast<void *>(work_queue);
	} else {
		apm->DetachAecDump();
		work_queue = reinterpret_cast<rtc::TaskQueue *>(*wq_ptr);
		if (work_queue) {
			delete work_queue;
			work_queue = NULL;
		}
	}
	return 0;
}

int webrtc_apm_has_echo(webrtc_apm ptr)
{
	webrtc::AudioProcessing *apm;

	apm = reinterpret_cast<webrtc::AudioProcessing *>(ptr);
	return apm->echo_cancellation()->stream_has_echo();
}

} // extern "C"
