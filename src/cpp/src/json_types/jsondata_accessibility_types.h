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
#include <types/json_types.h>

namespace Firebolt::Accessibility::JsonData
{
namespace Method
{
static const std::string audioDescription = "Accessibility.audioDescription";
static const std::string closedCaptionsSettings = "Accessibility.closedCaptionsSettings";
static const std::string highContrastUI = "Accessibility.highContrastUI";
static const std::string voiceGuidanceSettings = "Accessibility.voiceGuidanceSettings";
} // namespace Method

namespace OnChanged
{
static const std::string audioDescription = "Accessibility.onAudioDescriptionChanged";
static const std::string closedCaptionsSettings = "Accessibility.onClosedCaptionsSettingsChanged";
static const std::string highContrastUI = "Accessibility.onHighContrastUIChanged";
static const std::string voiceGuidanceSettings = "Accessibility.onVoiceGuidanceSettingsChanged";
} // namespace OnChanged

namespace Field
{
namespace ClosedCaptionsSettings
{
static const std::string enabled = "enabled";
static const std::string preferredLanguages = "preferredLanguages";
} // namespace ClosedCaptionsSettings

namespace VoiceGuidanceSettings
{
static const std::string enabled = "enabled";
static const std::string rate = "rate";
static const std::string navigationHints = "navigationHints";
} // namespace VoiceGuidanceSettings
} // namespace Field

class ClosedCaptionsSettings : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Accessibility::ClosedCaptionsSettings>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        enabled_ = json[Field::ClosedCaptionsSettings::enabled].get<bool>();
        preferredLanguages_ = json[Field::ClosedCaptionsSettings::preferredLanguages].get<std::vector<std::string>>();
    }
    ::Firebolt::Accessibility::ClosedCaptionsSettings Value() const override
    {
        return ::Firebolt::Accessibility::ClosedCaptionsSettings{enabled_, preferredLanguages_};
    }
private:
    bool enabled_;
    std::vector<std::string> preferredLanguages_;
};

class VoiceGuidanceSettings : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Accessibility::VoiceGuidanceSettings>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        enabled_ = json[Field::VoiceGuidanceSettings::enabled].get<bool>();
        rate_ = json[Field::VoiceGuidanceSettings::rate].get<float>();
        navigationHints_ = json[Field::VoiceGuidanceSettings::navigationHints].get<bool>();
    }
    ::Firebolt::Accessibility::VoiceGuidanceSettings Value() const override
    {
        return ::Firebolt::Accessibility::VoiceGuidanceSettings{enabled_, rate_, navigationHints_};
    }
private:
    bool enabled_;
    float rate_;
    bool navigationHints_;
};

} // namespace Firebolt::Accessibility::JsonData
