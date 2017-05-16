/*
**
** Copyright (c) 2017, Intel Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#pragma once

#include "Subsystem.h"
#include <AudioNonCopyable.hpp>

struct audio_route;

class AudioRouteSubsystem : public CSubsystem, private audio_utilities::utilities::NonCopyable
{
public:
    AudioRouteSubsystem(const std::string &strName, core::log::Logger &logger);
    struct audio_route *getAudioRoute(int card, const std::string &xmlPath);
private:
    static const char *const mKeyName; /**< name key mapping string. */
    static const char *const mKeyCard; /**< card key mapping string. */
    static const char *const mKeyXmlPath; /**< XML path mapping string. */
    static const char *const mKeyDebugEnable; /**< Debug enable mapping string. */
    static const char *const mKeyAmend1; /**< amend1 key mapping string. */
    static const char *const mKeyAmend2; /**< amend2 key mapping string. */
    static const char *const mKeyAmend3; /**< amend3 key mapping string. */

    static const char *const mAudioRoutePathComponentName; /**< name of audio_route path component. */

    struct audio_route *mAudioRoute;
};
