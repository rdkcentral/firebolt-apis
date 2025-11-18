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

#include "accessibility_impl.h"
#include "jsondata_accessibility_types.h"

namespace Firebolt::Accessibility
{
AccessibilityImpl::AccessibilityImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper), 
    subscriptionManager_(helper, this) {}

Result<bool> AccessibilityImpl::audioDescription() const
{
    return helper_.get<FireboltSDK::JSON::Boolean, bool>(JsonData::Method::audioDescription);
}

Result<SubscriptionId>
        AccessibilityImpl::subscribeOnAudioDescriptionChanged(std::function<void(bool)> &&notification) 
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::Boolean, bool>(
        JsonData::OnChanged::audioDescription, std::move(notification));      
}

Result<ClosedCaptionsSettings> AccessibilityImpl::closedCaptionsSettings() const
{
    return helper_.get<JsonData::ClosedCaptionsSettings, ClosedCaptionsSettings>(
        JsonData::Method::closedCaptionsSettings);            
}

Result<SubscriptionId>
        AccessibilityImpl::subscribeOnClosedCaptionsSettingsChanged(std::function<
            void(const ClosedCaptionsSettings &)> &&notification)
{
    return subscriptionManager_.subscribe<JsonData::ClosedCaptionsSettings>(
        JsonData::OnChanged::closedCaptionsSettings, std::move(notification));      
}

Result<bool> AccessibilityImpl::highContrastUI() const
{
    return helper_.get<FireboltSDK::JSON::Boolean, bool>(JsonData::Method::highContrastUI);
}

Result<SubscriptionId>
        AccessibilityImpl::subscribeOnHighContrastUIChanged(std::function<void(bool)> &&notification)
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::Boolean, bool>(
        JsonData::OnChanged::highContrastUI, std::move(notification));      
}   

Result<VoiceGuidanceSettings> AccessibilityImpl::voiceGuidanceSettings() const
{
    return helper_.get<JsonData::VoiceGuidanceSettings, VoiceGuidanceSettings>(
        JsonData::Method::voiceGuidanceSettings);            
}

Result<SubscriptionId>
        AccessibilityImpl::subscribeOnVoiceGuidanceSettingsChanged(std::function<
            void(const VoiceGuidanceSettings &)> &&notification)
{
    return subscriptionManager_.subscribe<JsonData::VoiceGuidanceSettings>(
        JsonData::OnChanged::voiceGuidanceSettings, std::move(notification));      
}   

Result<void> AccessibilityImpl::unsubscribe(SubscriptionId id)
{
    return subscriptionManager_.unsubscribe(id);
}

void AccessibilityImpl::unsubscribeAll()
{
    subscriptionManager_.unsubscribeAll();
}
} // namespace Firebolt::Accessibility