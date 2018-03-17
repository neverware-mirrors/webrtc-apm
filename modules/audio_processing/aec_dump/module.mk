# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

include common.mk

aec_dump_CXX_OBJECTS = \
	modules/audio_processing/aec_dump/aec_dump_impl.o \
	modules/audio_processing/aec_dump/capture_stream_info.o \
	modules/audio_processing/aec_dump/write_to_file_task.o

