# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

rtc_base_approved_generic_CXX_OBJECTS = \
	rtc_base/third_party/base64/base64.o \
	rtc_base/bit_buffer.o \
	rtc_base/bitrate_allocation_strategy.o \
	rtc_base/buffer_queue.o \
	rtc_base/byte_buffer.o \
	rtc_base/copy_on_write_buffer.o \
	rtc_base/critical_section.o \
	rtc_base/event_tracer.o \
	rtc_base/flags.o \
	rtc_base/location.o \
	rtc_base/numerics/histogram_percentile_counter.o \
	rtc_base/platform_file.o \
	rtc_base/platform_thread.o \
	rtc_base/platform_thread_types.o \
	rtc_base/race_checker.o \
	rtc_base/random.o \
	rtc_base/rate_statistics.o \
	rtc_base/rate_tracker.o \
	rtc_base/string_to_number.o \
	rtc_base/string_encode.o \
	rtc_base/thread_checker_impl.o \
	rtc_base/timestamp_aligner.o \
	rtc_base/time_utils.o \
	rtc_base/zero_memory.o \
	rtc_base/event.o \
	rtc_base/logging.o \

# requires libevent at link
task_queue_impl_CXX_OBJECTS = \
	api/task_queue/default_task_queue_factory_libevent.o \
	api/task_queue/global_task_queue_factory.o \
	api/task_queue/task_queue_base.o \
	rtc_base/task_queue.o \
	rtc_base/task_queue_libevent.o

rtc_base_CXX_OBJECTS = \
	rtc_base/checks.o \
	rtc_base/memory/aligned_malloc.o \
	rtc_base/system/file_wrapper.o \
	$(rtc_base_approved_generic_CXX_OBJECTS) \
	$(task_queue_impl_CXX_OBJECTS)

stringutils_CXX_OBJECTS = \
	rtc_base/strings/string_builder.o \
	rtc_base/string_utils.o

CXX_STATIC_LIBRARY(rtc_base/librtc_base.pic.a): \
	CPPFLAGS+= -DWEBRTC_POSIX -DWEBRTC_LINUX
CXX_STATIC_LIBRARY(rtc_base/librtc_base.pic.a): \
	$(rtc_base_CXX_OBJECTS) \
	$(stringutils_CXX_OBJECTS)

rtc_base/librtc_base: CXX_STATIC_LIBRARY(rtc_base/librtc_base.pic.a)

clean: CLEAN(rtc_base/librtc_base.pic.a)

.PHONY: rtc_base/librtc_base
