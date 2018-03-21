# WebRTC APM

APM is the audio processing module of WebRTC project in charge of effects
like echo cancellation, noise suppression, etc.  The purpose of this
project is to build a standalone library for Chrome OS system side audio
processing.

# Files content

* scripts to copy over folders and files from upstream WebRTC project
  for APM and its dependencies.
* Copied files from upstream WebRTC project. For example: common_audio,
  modules, rtc_base and system_wrappers.
* webrtc_apm.cc/h C wrappers to access APM functions.
* common-mk based makefiles to build shared library libwebrtc_apm.so

# Update

To update this package to latest upstream WebRC:
* Run `./script/sync-apm.sh path/to/webrtc-checkout/src .`
* `emerge webrtc-apm` to see if anything breaks.
* If emerge success, then we're good.
* Otherwise look into the emerge failure, and then possibly:
  * Update sync-apm.sh to copy more files if upstream directory structure changes.
  * Update makefiles if upstream build files has changed.
  * Update webrtc-apm ebuild file if dependencies changed.
* Create a new commit
