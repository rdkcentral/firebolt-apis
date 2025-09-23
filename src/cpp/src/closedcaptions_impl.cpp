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

#include "closedcaptions_impl.h"

using namespace Firebolt::Helpers;

namespace Firebolt::ClosedCaptions
{
// Methods
Result<std::string> ClosedCaptionsImpl::backgroundColor() const
{
    return get<FireboltSDK::JSON::String, std::string>(_T("ClosedCaptions.backgroundColor"));
}

Result<float> ClosedCaptionsImpl::backgroundOpacity() const
{
    return get<WPEFramework::Core::JSON::Float, float>(_T("ClosedCaptions.backgroundOpacity"));
}

Result<bool> ClosedCaptionsImpl::enabled() const
{
    return get<WPEFramework::Core::JSON::Boolean, bool>(_T("ClosedCaptions.enabled"));
}

Result<std::string> ClosedCaptionsImpl::fontColor() const
{
    return get<FireboltSDK::JSON::String, std::string>(_T("ClosedCaptions.fontColor"));
}

Result<Accessibility::FontEdge> ClosedCaptionsImpl::fontEdge() const
{
    return get<Firebolt::Accessibility::JsonData::FontEdge, Accessibility::FontEdge>(_T("ClosedCaptions.fontEdge"));
}

Result<std::string> ClosedCaptionsImpl::fontEdgeColor() const
{
    return get<FireboltSDK::JSON::String, std::string>(_T("ClosedCaptions.fontEdgeColor"));
}

Result<Accessibility::FontFamily> ClosedCaptionsImpl::fontFamily() const
{
    return get<Firebolt::Accessibility::JsonData::FontFamily, Accessibility::FontFamily>(
        _T("ClosedCaptions.fontFamily"));
}

Result<float> ClosedCaptionsImpl::fontOpacity() const
{
    return get<WPEFramework::Core::JSON::Float, float>(_T("ClosedCaptions.fontOpacity"));
}

Result<float> ClosedCaptionsImpl::fontSize() const
{
    return get<WPEFramework::Core::JSON::Float, float>(_T("ClosedCaptions.fontSize"));
}

Result<std::vector<std::string>> ClosedCaptionsImpl::preferredLanguages() const
{
    return get<FireboltSDK::JSON::WPE_String, std::vector<std::string>>(_T("ClosedCaptions.preferredLanguages"));
}

Result<std::string> ClosedCaptionsImpl::textAlign() const
{
    return get<FireboltSDK::JSON::String, std::string>(_T("ClosedCaptions.textAlign"));
}

Result<std::string> ClosedCaptionsImpl::textAlignVertical() const
{
    return get<FireboltSDK::JSON::String, std::string>(_T("ClosedCaptions.textAlignVertical"));
}

Result<std::string> ClosedCaptionsImpl::windowColor() const
{
    return get<FireboltSDK::JSON::String, std::string>(_T("ClosedCaptions.windowColor"));
}

Result<float> ClosedCaptionsImpl::windowOpacity() const
{
    return get<WPEFramework::Core::JSON::Float, float>(_T("ClosedCaptions.windowOpacity"));
}

Result<void> ClosedCaptionsImpl::setBackgroundColor(const std::string& value)
{
    return setNL(_T("ClosedCaptions.setBackgroundColor"), value);
}

Result<void> ClosedCaptionsImpl::setBackgroundOpacity(const float value)
{
    return setNL(_T("ClosedCaptions.setBackgroundOpacity"), value);
}

Result<void> ClosedCaptionsImpl::setEnabled(const bool value)
{
    return setNL(_T("ClosedCaptions.setEnabled"), value);
}

Result<void> ClosedCaptionsImpl::setFontColor(const std::string& value)
{
    return setNL(_T("ClosedCaptions.setFontColor"), value);
}

Result<void> ClosedCaptionsImpl::setFontEdge(const Accessibility::FontEdge& value)
{
    return setNL(_T("ClosedCaptions.setFontEdge"), ::FireboltSDK::JSON::ToString(::Firebolt::Accessibility::JsonData::FontEdgeEnum, value));
}

Result<void> ClosedCaptionsImpl::setFontEdgeColor(const std::string& value)
{
    return setNL(_T("ClosedCaptions.setFontEdgeColor"), value);
}

Result<void> ClosedCaptionsImpl::setFontFamily(const Accessibility::FontFamily& value)
{
    Firebolt::Accessibility::JsonData::FontFamily jsonValue{value};
    return setNL(_T("ClosedCaptions.setFontFamily"), ::FireboltSDK::JSON::ToString(::Firebolt::Accessibility::JsonData::FontFamilyEnum, value));
}

Result<void> ClosedCaptionsImpl::setFontOpacity(const float value)
{
    return setNL(_T("ClosedCaptions.setFontOpacity"), value);
}

Result<void> ClosedCaptionsImpl::setFontSize(const float value)
{
    return setNL(_T("ClosedCaptions.setFontSize"), value);
}

Result<void> ClosedCaptionsImpl::setPreferredLanguages(const std::vector<std::string>& value)
{
    return setNL(_T("ClosedCaptions.setPreferredLanguages"), value);
}

Result<void> ClosedCaptionsImpl::setTextAlign(const std::string& value)
{
    return setNL(_T("ClosedCaptions.setTextAlign"), value);
}

Result<void> ClosedCaptionsImpl::setTextAlignVertical(const std::string& value)
{
    return setNL(_T("ClosedCaptions.setTextAlignVertical"), value);
}

Result<void> ClosedCaptionsImpl::setWindowColor(const std::string& value)
{
    return setNL(_T("ClosedCaptions.setWindowColor"), value);
}

Result<void> ClosedCaptionsImpl::setWindowOpacity(const float value)
{
    return setNL(_T("ClosedCaptions.setWindowOpacity"), value);
}

// Events
Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnBackgroundColorChanged(std::function<void(const std::string&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::String>(_T("ClosedCaptions.onBackgroundColorChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnBackgroundOpacityChanged(std::function<void(float)>&& notification)
{
    return SubscriptionHelper::subscribe<
        WPEFramework::Core::JSON::Float>(_T("ClosedCaptions.onBackgroundOpacityChanged"), std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnEnabledChanged(std::function<void(bool)>&& notification)
{
    return SubscriptionHelper::subscribe<WPEFramework::Core::JSON::Boolean>(_T("ClosedCaptions.onEnabledChanged"),
                                                                            std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontColorChanged(std::function<void(const std::string&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::String>(_T("ClosedCaptions.onFontColorChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontEdgeChanged(std::function<void(const Accessibility::FontEdge&)>&& notification)
{
    return SubscriptionHelper::subscribe<
        Firebolt::Accessibility::JsonData::FontEdge>(_T("ClosedCaptions.onFontEdgeChanged"), std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontEdgeColorChanged(std::function<void(const std::string&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::String>(_T("ClosedCaptions.onFontEdgeColorChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontFamilyChanged(std::function<void(const Accessibility::FontFamily&)>&& notification)
{
    return SubscriptionHelper::subscribe<
        Firebolt::Accessibility::JsonData::FontFamily>(_T("ClosedCaptions.onFontFamilyChanged"), std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnFontOpacityChanged(std::function<void(float)>&& notification)
{
    return SubscriptionHelper::subscribe<WPEFramework::Core::JSON::Float>(_T("ClosedCaptions.onFontOpacityChanged"),
                                                                          std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnFontSizeChanged(std::function<void(float)>&& notification)
{
    return SubscriptionHelper::subscribe<WPEFramework::Core::JSON::Float>(_T("ClosedCaptions.onFontSizeChanged"),
                                                                          std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnPreferredLanguagesChanged(
    std::function<void(const std::vector<std::string>&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::WPE_String>(_T("ClosedCaptions.onPreferredLanguagesChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnTextAlignChanged(std::function<void(const std::string&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::String>(_T("ClosedCaptions.onTextAlignChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnTextAlignVerticalChanged(std::function<void(const std::string&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::String>(_T("ClosedCaptions.onTextAlignVerticalChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnWindowColorChanged(std::function<void(const std::string&)>&& notification)
{
    return SubscriptionHelper::subscribe<FireboltSDK::JSON::String>(_T("ClosedCaptions.onWindowColorChanged"),
                                                                    std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnWindowOpacityChanged(std::function<void(float)>&& notification)
{
    return SubscriptionHelper::subscribe<WPEFramework::Core::JSON::Float>(_T("ClosedCaptions.onWindowOpacityChanged"),
                                                                          std::move(notification));
}

Result<void> ClosedCaptionsImpl::unsubscribe(SubscriptionId id)
{
    return SubscriptionHelper::unsubscribe(id);
}

void ClosedCaptionsImpl::unsubscribeAll()
{
    SubscriptionHelper::unsubscribeAll();
}
} // namespace Firebolt::ClosedCaptions
