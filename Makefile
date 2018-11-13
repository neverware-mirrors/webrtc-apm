# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk
include pc_utils.mk

LDFLAGS += -Wl,-z,defs
CPPFLAGS += -DWEBRTC_POSIX

ifeq (${USE_NEON},1)
CPPFLAGS += -DWEBRTC_HAS_NEON
endif

libaudio_processing: module/libaudio_processing

webrtc_apm_PC_DEPS = libevent protobuf

webrtc_apm_CXX_OBJECTS = \
	webrtc_apm.o

CXX_LIBRARY(libwebrtc_apm.so): \
	CPPFLAGS += -I.

CXX_LIBRARY(libwebrtc_apm.so): \
	$(webrtc_apm_CXX_OBJECTS) \
	libaudio_processing \
	rtc_base/librtc_base \
	common_audio/libcommon_audio \
	system_wrappers/source/libsystem_wrappers \
	modules/audio_coding/libaudio_coding \
	modules/audio_processing/libaudioproc_debug_proto \
	absl \
	cras-config

CXX_LIBRARY(libwebrtc_apm.so): CPPFLAGS += \
	$(call get_pc_cflags,$(webrtc_apm_PC_DEPS))

CXX_LIBRARY(libwebrtc_apm.so): LDLIBS += \
	libaudio_processing.pic.a \
	common_audio/libcommon_audio.pic.a \
	system_wrappers/source/libsystem_wrappers.pic.a \
	modules/audio_coding/libaudio_coding.pic.a \
	rtc_base/librtc_base.pic.a \
	libaudioproc_debug_proto.pic.a \
	absl.pic.a \
	cras-config.pic.a \
	$(call get_pc_libs,$(webrtc_apm_PC_DEPS)) \
	-liniparser

all: CXX_LIBRARY(libwebrtc_apm.so)
