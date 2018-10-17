# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

system_wrappers_source_CXX_OBJECTS = \
	system_wrappers/source/clock.o \
	system_wrappers/source/cpu_features.o \
	system_wrappers/source/cpu_info.o \
	system_wrappers/source/event.o \
	system_wrappers/source/field_trial.o \
	system_wrappers/source/rtp_to_ntp_estimator.o \
	system_wrappers/source/sleep.o

CXX_STATIC_LIBRARY(system_wrappers/source/libsystem_wrappers.pic.a): \
	$(system_wrappers_source_CXX_OBJECTS) \
	system_wrappers/source/metrics.o

system_wrappers/source/libsystem_wrappers: \
	CXX_STATIC_LIBRARY(system_wrappers/source/libsystem_wrappers.pic.a)

clean: CLEAN(system_wrappers/source/libsystem_wrappers.pic.a)

.PHONY: system_wrappers/source/libsystem_wrappers
