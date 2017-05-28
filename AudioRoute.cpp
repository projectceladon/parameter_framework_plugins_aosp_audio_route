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

#include "AudioRoute.hpp"
#include "AudioRouteMappingKeys.hpp"
#include "AudioRouteSubsystem.hpp"
#include <AudioUtilitiesAssert.hpp>

#include <audio_route/audio_route.h>

AudioRoute::AudioRoute(const std::string &mappingValue,
                       CInstanceConfigurableElement *instanceConfigurableElement,
                       const CMappingContext &context,
                       core::log::Logger &logger)
    : CFormattedSubsystemObject(instanceConfigurableElement,
                                logger,
                                mappingValue,
                                MappingKeyAmend1,
                                (MappingKeyAmendEnd - MappingKeyAmend1 + 1),
                                context),
      mAudioRouteSubsystem(static_cast<const AudioRouteSubsystem *>(
			       instanceConfigurableElement->getBelongingSubsystem())),
      mIsDebugEnabled(context.iSet(MappingKeyDebugEnable)) /* order of initialization matters, needs to match order of appearance in .hpp, cong */
{
    mName = getFormattedMappingValue();
    int card(context.getItemAsInteger(MappingKeyCard));
    std::string xmlPath(context.getItem(MappingKeyXmlPath));

    /* delegate to subsystem class the creation of audio_route */
    mAudioRoute = const_cast<AudioRouteSubsystem *>(mAudioRouteSubsystem)->getAudioRoute(card, xmlPath);
    AUDIOUTILITIES_ASSERT(mAudioRoute != nullptr,
		      "Could not retrieve audio_route for card: "<<card<<" and path: "<<xmlPath);
}

bool AudioRoute::sendToHW(std::string & /*error*/)
{
    bool isPathActive;
    int res = 0;

    // Retrieve blackboard
    blackboardRead(&isPathActive, sizeof(isPathActive));

    logControlInfo(isPathActive);

    if (isPathActive) {
	res = audio_route_apply_and_update_path(mAudioRoute, mName.c_str());
    } else {
	res = audio_route_reset_and_update_path(mAudioRoute, mName.c_str());
    }

    return (res == 0);
}

void AudioRoute::logControlInfo(bool isPathActive) const
{
    if (mIsDebugEnabled) {

	/* the logs are controlled by the property persist.media.pfw.verbose */
	info() << "AudioRoute " << mName.c_str() <<": " << isPathActive;
    }
}
