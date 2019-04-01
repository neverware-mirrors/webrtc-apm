/* Copyright (c) 2018 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "api/audio/echo_canceller3_factory.h"
#include "api/task_queue/default_task_queue_factory.h"
#include "cras-config/aec_config.h"
#include "cras-config/apm_config.h"
#include "modules/audio_processing/aec_dump/aec_dump_factory.h"
#include "modules/audio_processing/include/aec_dump.h"
#include "modules/audio_processing/include/audio_processing.h"
#include "modules/include/module_common_types.h"
#include "rtc_base/task_queue.h"

extern "C" {
#include <errno.h>

#include "webrtc_apm.h"

webrtc_apm webrtc_apm_create(unsigned int num_channels,
			     unsigned int frame_rate,
			     dictionary *aec_ini,
			     dictionary *apm_ini)
{
	int err;
	webrtc::AudioProcessing *apm;
	webrtc::AudioProcessing::ChannelLayout channel_layout;
	webrtc::AudioProcessingBuilder apm_builder;
	webrtc::EchoCanceller3Config aec3_config;
	std::unique_ptr<webrtc::EchoControlFactory> ec3_factory;

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

	if (aec_ini) {
		aec_config_get(aec_ini, &aec3_config);
		ec3_factory.reset(
			new webrtc::EchoCanceller3Factory(aec3_config));
	} else {
		ec3_factory.reset(new webrtc::EchoCanceller3Factory());
	}

	apm_builder.SetEchoControlFactory(std::move(ec3_factory));
	apm = apm_builder.Create();

	if (apm_ini)
		apm_config_apply(apm_ini, apm);

	err = apm->Initialize(frame_rate, frame_rate, frame_rate,
			      channel_layout, channel_layout, channel_layout);
	if (err) {
		delete apm;
		return NULL;
	}

	return reinterpret_cast<webrtc_apm>(apm);
}

void webrtc_apm_dump_configs(dictionary *apm_ini,
			     dictionary *aec_ini)
{
	if (apm_ini)
		apm_config_dump(apm_ini);
	if (aec_ini)
		aec_config_dump(aec_ini);
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

} // extern "C"
