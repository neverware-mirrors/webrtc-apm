/* Copyright (c) 2018 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef WEBRTC_APM_H_
#define WEBRTC_APM_H_

#include <iniparser.h>
#include <stdint.h>
#include <stdio.h>

#define WEBRTC_APM_API __attribute__((visibility("default")))

/* Pointer to a webrtc::AudioProcessing instance. */
typedef void* webrtc_apm;

/* Creates a webrtc_apm for forward stream properties. In CRAS use case it
 * is usually created for input stream.
 * Args:
 *    num_channels - Number of channels of the forward stream.
 *    frame_rate - Frame rate used by forward stream.
 *    aec_config - Pointer to aec config.
 *    apm_config - Pointer to apm config.
 */
WEBRTC_APM_API webrtc_apm webrtc_apm_create(
		unsigned int num_channels,
		unsigned int frame_rate,
		dictionary *aec_ini,
		dictionary *apm_ini);

/* Dumps configs content.
 * Args:
 *    apm_ini - APM config file in ini format.
 *    aec_ini - AEC3 config file in ini format.
 */
WEBRTC_APM_API void webrtc_apm_dump_configs(
		dictionary *apm_ini,
		dictionary *aec_ini);

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
