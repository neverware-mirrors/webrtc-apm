/* Copyright 2018 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <syslog.h>

#include "apm_config.h"

#define APM_CONFIG_NAME "apm.ini"

#define APM_GET_INT(ini, key)	\
	iniparser_getint(	\
		ini, key,	\
		key ## _VALUE)
#define APM_GET_FLOAT(ini, key)	\
	iniparser_getdouble(	\
		ini, key,	\
		key ## _VALUE)

void apm_config_apply(dictionary *ini, webrtc::AudioProcessing *apm)
{
	webrtc::AudioProcessing::Config config;
	webrtc::GainControl::Mode agc_mode;
	webrtc::NoiseSuppression::Level ns_level;

	if (ini == NULL)
		return;

	config.residual_echo_detector.enabled =
			APM_GET_INT(ini, APM_RESIDUAL_ECHO_DETECTOR_ENABLED);
	config.high_pass_filter.enabled =
			APM_GET_INT(ini, APM_HIGH_PASS_FILTER_ENABLED);
	config.pre_amplifier.enabled =
			APM_GET_INT(ini, APM_PRE_AMPLIFIER_ENABLED);
	config.pre_amplifier.fixed_gain_factor =
			APM_GET_FLOAT(ini, APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR);
	config.gain_controller2.enabled =
			APM_GET_INT(ini, APM_GAIN_CONTROLLER2_ENABLED);
	config.gain_controller2.adaptive_digital_mode =
		APM_GET_INT(ini, APM_GAIN_CONTROLLER2_ADAPTIVE_DIGITAL_MODE);
	config.gain_controller2.extra_saturation_margin_db =
		APM_GET_FLOAT(ini, APM_GAIN_CONTROLLER2_EXTRA_SATURATION_MARGIN_DB);
	config.gain_controller2.fixed_gain_db =
		APM_GET_FLOAT(ini, APM_GAIN_CONTROLLER2_FIXED_GAIN_DB);
	apm->ApplyConfig(config);

	apm->gain_control()->set_compression_gain_db(
			APM_GET_INT(ini, APM_GAIN_CONTROL_COMPRESSION_GAIN_DB));

	agc_mode = static_cast<webrtc::GainControl::Mode>(
			APM_GET_INT(ini, APM_GAIN_CONTROL_MODE));
	apm->gain_control()->set_mode(agc_mode);
	apm->gain_control()->Enable(APM_GET_INT(ini, APM_GAIN_CONTROL_ENABLED));

	ns_level = static_cast<webrtc::NoiseSuppression::Level>(
			APM_GET_INT(ini, APM_NOISE_SUPPRESSION_LEVEL));
	apm->noise_suppression()->set_level(ns_level);
	apm->noise_suppression()->Enable(
			APM_GET_INT(ini, APM_NOISE_SUPPRESSION_ENABLED));
}

void apm_config_dump(dictionary *ini)
{
	syslog(LOG_ERR, "---- apm config dump ----");
	syslog(LOG_ERR, "residual_echo_detector_enabled %u",
		APM_GET_INT(ini, APM_RESIDUAL_ECHO_DETECTOR_ENABLED));
	syslog(LOG_ERR, "high_pass_filter_enabled %u",
		APM_GET_INT(ini, APM_HIGH_PASS_FILTER_ENABLED));
	syslog(LOG_ERR, "pre_amplifier_enabled %u",
		APM_GET_INT(ini, APM_PRE_AMPLIFIER_ENABLED));
	syslog(LOG_ERR, "pre_amplifier_fixed_gain_factor %f",
		APM_GET_FLOAT(ini, APM_PRE_AMPLIFIER_FIXED_GAIN_FACTOR));
	syslog(LOG_ERR, "gain_controller2_enabled %u",
		APM_GET_INT(ini, APM_GAIN_CONTROLLER2_ENABLED));
	syslog(LOG_ERR, "gain_controller2_adaptive_digital_mode %d",
		APM_GET_INT(ini, APM_GAIN_CONTROLLER2_ADAPTIVE_DIGITAL_MODE));
	syslog(LOG_ERR, "gain_controller2_extra_saturation_margin_db %f",
		APM_GET_FLOAT(ini, APM_GAIN_CONTROLLER2_EXTRA_SATURATION_MARGIN_DB));
	syslog(LOG_ERR, "gain_controller2_fixed_gain_db %f",
		APM_GET_FLOAT(ini, APM_GAIN_CONTROLLER2_FIXED_GAIN_DB));
	syslog(LOG_ERR, "gain_control_compression_gain_db %u",
		APM_GET_INT(ini, APM_GAIN_CONTROL_COMPRESSION_GAIN_DB));
	syslog(LOG_ERR, "gain_control_mode %u",
		APM_GET_INT(ini, APM_GAIN_CONTROL_MODE));
	syslog(LOG_ERR, "gain_control_enabled %u",
		APM_GET_INT(ini, APM_GAIN_CONTROL_ENABLED));
	syslog(LOG_ERR, "noise_suppression_level %u",
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_LEVEL));
	syslog(LOG_ERR, "noise_suppression_enabled %u",
		APM_GET_INT(ini, APM_NOISE_SUPPRESSION_ENABLED));
}
