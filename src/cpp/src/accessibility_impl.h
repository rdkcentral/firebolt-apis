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

#include "accessibility.h"
#include <firebolt/helpers.h>

namespace Firebolt::Accessibility
{

class AccessibilityImpl : public IAccessibility
{

public:
    explicit AccessibilityImpl(Firebolt::Helpers::IHelper &helper);
    AccessibilityImpl(const AccessibilityImpl &) = delete;
    AccessibilityImpl &operator=(const AccessibilityImpl &) = delete;

    ~AccessibilityImpl() override = default;

    Result<bool> audioDescription() const override;
    Result<SubscriptionId> subscribeOnAudioDescriptionChanged(std::function<void(bool)> &&notification) override;
    Result<ClosedCaptionsSettings> closedCaptionsSettings() const override;
    Result<SubscriptionId>
    subscribeOnClosedCaptionsSettingsChanged(std::function<void(const ClosedCaptionsSettings &)> &&notification) override;

    Result<bool> highContrastUI() const override;

    Result<SubscriptionId> subscribeOnHighContrastUIChanged(std::function<void(bool)> &&notification) override;

    Result<VoiceGuidanceSettings> voiceGuidanceSettings() const override;
    Result<SubscriptionId>
    subscribeOnVoiceGuidanceSettingsChanged(std::function<void(const VoiceGuidanceSettings &)> &&notification) override;

    virtual Result<void> unsubscribe(SubscriptionId id) override;
    virtual void unsubscribeAll() override;

private:
    Firebolt::Helpers::IHelper &helper_;
    Firebolt::Helpers::SubscriptionManager subscriptionManager_;
};
} // namespace Firebolt::Accessibility
