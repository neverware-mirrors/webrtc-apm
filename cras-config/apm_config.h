/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef APM_CONFIG_H_
#define APM_CONFIG_H_

#include <iniparser.h>

#include "modules/audio_processing/include/audio_processing.h"

#define APM_RESIDUAL_ECHO_DETECTOR_ENABLED "apm:residual_echo_detector_enabled"
#define APM_RESIDUAL_ECHO_DETECTOR_ENABLED_VALUE 1
#define APM_HIGH_PASS_FILTER_ENABLED "apm:high_pass_filter_enabled"
#define APM_HIGH_PASS_FILTER_ENABLED_VALUE 0
#define APM_PRE_AMPLIFIER_ENABLED "apm:pre_amplifier_enabled"
#define APM_PRE_AMPLIFIER_ENABLED_VALUE 0
#define APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR "apm:pre_amplifier_fixed_gain_factor"
#define APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR_VALUE 1.f
#define APM_GAIN_CONTROLLER2_ENABLED "apm:gain_controller2_enabled"
#define APM_GAIN_CONTROLLER2_ENABLED_VALUE 0
#define APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB \
	"apm:gain_controller2_fixed_digital_gain_db"
#define APM_GAIN_CONTROLLER2_FIXED_DIGITAL_GAIN_DB_VALUE 0.f

/* Keys for AudioProcessing::GainController2 */
#define ADAPTIVE_DIGITAL_ENABLED "apm:adaptive_digital_enabled"
#define ADAPTIVE_DIGITAL_ENABLED_VALUE 0
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR \
	"apm:adaptive_digital_level_estimator"
#define ADAPTIVE_DIGITAL_LEVEL_ESTIMATOR_VALUE 0
#define ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB \
	"apm:adaptive_digital_extra_saturation_margin_db"
#define ADAPTIVE_DIGITAL_EXTRA_SATURATION_MARGIN_DB_VALUE 2.f
#define ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR \
	"apm:adaptive_digital_use_saturation_protector"
#define ADAPTIVE_DIGITAL_USE_SATURATION_PROTECTOR_VALUE 1

#define APM_GAIN_CONTROL_COMPRESSION_GAIN_DB "apm:gain_control_compression_gain_db"
#define APM_GAIN_CONTROL_COMPRESSION_GAIN_DB_VALUE 9
/* 0: adaptive analog, 1: adaptive digital, 2: fixed digital */
#define APM_GAIN_CONTROL_MODE "apm:gain_control_mode"
#define APM_GAIN_CONTROL_MODE_VALUE 0
#define APM_GAIN_CONTROL_ENABLED "apm:gain_control_enabled"
#define APM_GAIN_CONTROL_ENABLED_VALUE 0
/* 0: low, 1: moderate, 2: high, 3: very high*/
#define APM_NOISE_SUPPRESSION_LEVEL "apm:noise_suppression_level"
#define APM_NOISE_SUPPRESSION_LEVEL_VALUE 0
#define APM_NOISE_SUPPRESSION_ENABLED "apm:noise_suppression_enabled"
#define APM_NOISE_SUPPRESSION_ENABLED_VALUE 0

/* Gets apm config from given config directory. */
void apm_config_apply(dictionary *ini, webrtc::AudioProcessing *apm);

/* Prints config content to syslog. */
void apm_config_dump(dictionary *ini);

#endif /* APM_CONFIG_H_ */
