# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

rtc_base_approved_generic_CXX_OBJECTS = \
	rtc_base/base64.o \
	rtc_base/bitbuffer.o \
	rtc_base/bitrateallocationstrategy.o \
	rtc_base/bufferqueue.o \
	rtc_base/bytebuffer.o \
	rtc_base/copyonwritebuffer.o \
	rtc_base/criticalsection.o \
	rtc_base/event_tracer.o \
	rtc_base/file.o \
	rtc_base/flags.o \
	rtc_base/location.o \
	rtc_base/numerics/histogram_percentile_counter.o \
	rtc_base/pathutils.o \
	rtc_base/platform_file.o \
	rtc_base/platform_thread.o \
	rtc_base/platform_thread_types.o \
	rtc_base/race_checker.o \
	rtc_base/random.o \
	rtc_base/rate_statistics.o \
	rtc_base/ratetracker.o \
	rtc_base/string_to_number.o \
	rtc_base/stringencode.o \
	rtc_base/thread_checker_impl.o \
	rtc_base/timestampaligner.o \
	rtc_base/timeutils.o \
	rtc_base/zero_memory.o \
	rtc_base/file_posix.o \
	rtc_base/event.o \
	rtc_base/logging.o \

# requires libevent at link
task_queue_impl_CXX_OBJECTS = \
	rtc_base/task_queue_libevent.o \
	rtc_base/task_queue_posix.o

rtc_base_CXX_OBJECTS = \
	rtc_base/checks.o \
	rtc_base/memory/aligned_malloc.o \
	rtc_base/system/file_wrapper.o \
	$(rtc_base_approved_generic_CXX_OBJECTS) \
	$(task_queue_impl_CXX_OBJECTS)

stringutils_CXX_OBJECTS = \
	rtc_base/strings/string_builder.o \
	rtc_base/stringutils.o

CXX_STATIC_LIBRARY(rtc_base/librtc_base.pic.a): \
	CPPFLAGS+= -DWEBRTC_POSIX -DWEBRTC_LINUX
CXX_STATIC_LIBRARY(rtc_base/librtc_base.pic.a): \
	$(rtc_base_CXX_OBJECTS) \
	$(stringutils_CXX_OBJECTS)

rtc_base/librtc_base: CXX_STATIC_LIBRARY(rtc_base/librtc_base.pic.a)

clean: CLEAN(rtc_base/librtc_base.pic.a)

.PHONY: rtc_base/librtc_base
