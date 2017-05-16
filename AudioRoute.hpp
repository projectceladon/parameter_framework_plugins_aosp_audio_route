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


#include "FormattedSubsystemObject.h"
#include "InstanceConfigurableElement.h"
#include "MappingContext.h"

struct audio_route;
class AudioRouteSubsystem;

class AudioRoute : public CFormattedSubsystemObject
{
private:
    /* since we have just a Boolean we don't use a private structure. when a structure is
       used it needs to be packed */

public:
    AudioRoute(const std::string &mappingValue,
               CInstanceConfigurableElement *instanceConfigurableElement,
               const CMappingContext &context,
               core::log::Logger &logger);

protected:
    /**
     * Sync to HW.
     * From CSubsystemObject
     *
     * @param[out] error: if return code is false, it contains it contains the description
     *                     of the error, empty std::string otherwise.
     *
     * @return true if success, false otherwise.
     */
    virtual bool sendToHW(std::string &error);
    void logControlInfo(bool isPathActive) const;

private:
    const AudioRouteSubsystem *mAudioRouteSubsystem; /**< Route subsytem plugin. */
    std::string mName;
    struct audio_route *mAudioRoute;
    /** Debug on */
    bool mIsDebugEnabled;
};
