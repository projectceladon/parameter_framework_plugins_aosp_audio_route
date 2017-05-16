#
# Copyright (c) 2017, Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libaudioroute-subsystem
LOCAL_MODULE_OWNER := intel
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
    AudioRouteSubsystemBuilder.cpp \
    AudioRouteSubsystem.cpp \
    AudioRoute.cpp

LOCAL_C_INCLUDES := \
    external/tinyalsa/include \
    $(call include-path-for, audio-route)

LOCAL_STATIC_LIBRARIES := \
    libaudio_utilities \
    libaudio_utilities_convert \
    libpfw_utility \
    liblog


LOCAL_SHARED_LIBRARIES := \
    libparameter \
    libaudioroute \
    libtinyalsa

LOCAL_CFLAGS := -Wall -Werror -Wextra

include $(BUILD_SHARED_LIBRARY)
