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

#include "AudioRouteSubsystem.hpp"
#include "SubsystemObjectFactory.h"
#include "AudioRouteMappingKeys.hpp"
#include "AudioRoute.hpp"
#include <AudioUtilitiesAssert.hpp>

#include <audio_route/audio_route.h>

const char *const AudioRouteSubsystem::mKeyName = "Name";
const char *const AudioRouteSubsystem::mKeyCard = "Card";
const char *const AudioRouteSubsystem::mKeyXmlPath = "Path";
const char *const AudioRouteSubsystem::mKeyDebugEnable = "Debug";
const char *const AudioRouteSubsystem::mKeyAmend1 = "Amend1";
const char *const AudioRouteSubsystem::mKeyAmend2 = "Amend2";
const char *const AudioRouteSubsystem::mKeyAmend3 = "Amend3";

const char *const AudioRouteSubsystem::mAudioRoutePathComponentName = "AR";

AudioRouteSubsystem::AudioRouteSubsystem(const std::string &name, core::log::Logger &logger)
    : CSubsystem(name, logger), mAudioRoute(nullptr)
{

    // Provide mapping keys to upper layer (the order needs to be the same as in the .hpp file)
    addContextMappingKey(mKeyName);
    addContextMappingKey(mKeyCard);
    addContextMappingKey(mKeyXmlPath);
    addContextMappingKey(mKeyDebugEnable);
    addContextMappingKey(mKeyAmend1);
    addContextMappingKey(mKeyAmend2);
    addContextMappingKey(mKeyAmend3);

    // Provide creators to upper layer
    addSubsystemObjectFactory(
        new TSubsystemObjectFactory<AudioRoute>(
            mAudioRoutePathComponentName,
	    /* bail if the following Mapping keys are not provided in the Structure file */
            (1 << MappingKeyAmend1) | (1 << MappingKeyCard) | (1 << MappingKeyXmlPath))
        );
}

struct audio_route *AudioRouteSubsystem::getAudioRoute(int card, const std::string &xmlPath)
{
    if (mAudioRoute == nullptr) {
	mAudioRoute = audio_route_init(card, xmlPath.c_str());

	AUDIOUTILITIES_ASSERT(mAudioRoute != nullptr,
		      "Could not instantiate audio_route for card: "<<card<<" and path: "<<xmlPath);
    }

    return mAudioRoute;
}
