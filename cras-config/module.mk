# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

cras-config_CC_OBJECTS = \
	cras-config/aec_config.o \
	cras-config/apm_config.o

CXX_STATIC_LIBRARY(cras-config.pic.a): \
	$(cras-config_CC_OBJECTS)

cras-config: CXX_STATIC_LIBRARY(cras-config.pic.a)

clean: CLEAN(cras-config.pic.a)

.PHONY: cras-config
