/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <functional>
#include <optional>
#include <string>
#include "Firebolt/types.h"
#include <vector>

namespace Firebolt::Accessibility
{

struct ClosedCaptionsSettings
{
    bool enabled;
    std::vector<std::string> preferredLanguages;
};

struct VoiceGuidanceSettings
{
    bool enabled;
    float rate;
    bool navigationHints;
};

class IAccessibility
{
public:
    virtual ~IAccessibility() = default;

    /**
     * @brief Returns the audio description setting of the device
     *
     * @retval The audio description setting state or error
     */
    virtual Result<bool> audioDescription() const = 0;

    /**
     * @brief Subscribe to audio description setting changes
     *
     * @retval SubscriptionId or error
     */
    virtual Result<SubscriptionId>
        subscribeOnAudioDescriptionChanged(std::function<void(bool)> &&notification) = 0;

    /**
     * @brief Returns captions settings: enabled, and a list of zero or more languages in order of decreasing preference
     *
     * @retval ClosedCaptionsSettings or error
     */
    virtual Result<ClosedCaptionsSettings> closedCaptionsSettings() const = 0;

    virtual Result<SubscriptionId>
        subscribeOnClosedCaptionsSettingsChanged(std::function<void(const ClosedCaptionsSettings &)> &&notification) = 0;

    /**
     * @brief Returns the high contrast UI device setting
     * 
     * @retval The high contrast UI setting or error
     */ 
    virtual Result<bool> highContrastUI() const = 0;

    virtual Result<SubscriptionId>
        subscribeOnHighContrastUIChanged(std::function<void(bool)> &&notification) = 0;
      
    /**
     * @brief Returns voice guidance settings: enabled, rate, and verbosity
     * @retval VoiceGuidanceSettings or error
     */ 
    virtual Result<VoiceGuidanceSettings> voiceGuidanceSettings() const = 0;

    virtual Result<SubscriptionId>
        subscribeOnVoiceGuidanceSettingsChanged(std::function<void(const VoiceGuidanceSettings &)> &&notification) = 0;

    /**
     * @brief Remove subscriber from subscribers list. This method is generic for
     *        all subscriptions
     *
     * @param[in] id                  : The subscription id
     *
     * @retval The status
     */
    virtual Result<void> unsubscribe(SubscriptionId id) = 0;

    /**
     * @brief Remove all active subscriptions from subscribers list.
     */
    virtual void unsubscribeAll() = 0;

};

} // namespace Firebolt::Accessibility