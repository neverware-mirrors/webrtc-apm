# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

absl_CXX_OBJECTS = \
	absl/base/internal/raw_logging.o \
	absl/types/bad_optional_access.o

# CXX_STATIC_LIBRARY(absl.pic.a): \
# 	CPPFLAGS+= -DWEBRTC_POSIX -DWEBRTC_LINUX

CXX_STATIC_LIBRARY(absl.pic.a): \
	$(absl_CXX_OBJECTS)

absl: CXX_STATIC_LIBRARY(absl.pic.a)

clean: CLEAN(absl.pic.a)

.PHONY: absl
