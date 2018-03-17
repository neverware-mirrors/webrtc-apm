#!/bin/bash

# Copyright 2018 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Use this script to uprev WebRTC APM code.
# Usage: ./script/sync-apm.sh  <path-to-webrtc-checkout>/src .

FROM=$1
TO=$2

OPTIONS=(-av --delete --filter="P module.mk")

rsync "${OPTIONS[@]}" ${FROM}/rtc_base ${TO}
rsync "${OPTIONS[@]}" ${FROM}/audio ${TO}
rsync "${OPTIONS[@]}" ${FROM}/common_audio ${TO}
rsync "${OPTIONS[@]}" ${FROM}/system_wrappers ${TO}
rsync "${OPTIONS[@]}" ${FROM}/common_types.h ${TO}
rsync "${OPTIONS[@]}" ${FROM}/typedefs.h ${TO}

mkdir -p ${TO}/modules
rsync "${OPTIONS[@]}" ${FROM}/modules/audio_coding ${TO}/modules
rsync "${OPTIONS[@]}" ${FROM}/modules/audio_processing ${TO}/modules
rsync "${OPTIONS[@]}" ${FROM}/modules/include ${TO}/modules

# Add video codecs headers for common includes to work.
mkdir -p ${TO}/modules/video_coding/codecs
rsync "${OPTIONS[@]}" ${FROM}/modules/video_coding/codecs/interface \
	${TO}/modules/video_coding/codecs
mkdir -p ${TO}/modules/video_coding/codecs/h264
rsync "${OPTIONS[@]}" ${FROM}/modules/video_coding/codecs/h264/include \
	${TO}/modules/video_coding/codecs/h264
mkdir -p ${TO}/modules/video_coding/codecs/vp8
rsync "${OPTIONS[@]}" ${FROM}/modules/video_coding/codecs/vp8/include \
	${TO}/modules/video_coding/codecs/vp8
mkdir -p ${TO}/modules/video_coding/codecs/vp9
rsync "${OPTIONS[@]}" ${FROM}/modules/video_coding/codecs/vp9/include \
	${TO}/modules/video_coding/codecs/vp9

rsync "${OPTIONS[@]}" --include="*.cc" --include="*.h" --include="audio" \
	--include="video" --exclude="*" ${FROM}/api/* ${TO}/api

# Adjust include path to use libevent header on chroot
sed -i 's/include "base\/third_party\/libevent\/event\.h"/include <event.h>/' \
	${TO}/rtc_base/task_queue_libevent.cc