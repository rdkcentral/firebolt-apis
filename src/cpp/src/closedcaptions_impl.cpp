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
ClosedCaptionsImpl::ClosedCaptionsImpl(Firebolt::Helpers::Helper &helper) : helper_(helper) {}

// Methods
Result<std::string> ClosedCaptionsImpl::backgroundColor() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("ClosedCaptions.backgroundColor");
}

Result<unsigned> ClosedCaptionsImpl::backgroundOpacity() const
{
    return helper_.get<FireboltSDK::JSON::Unsigned, unsigned>("ClosedCaptions.backgroundOpacity");
}

Result<bool> ClosedCaptionsImpl::enabled() const
{
    return helper_.get<FireboltSDK::JSON::Boolean, bool>("ClosedCaptions.enabled");
}

Result<std::string> ClosedCaptionsImpl::fontColor() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("ClosedCaptions.fontColor");
}

Result<Accessibility::FontEdge> ClosedCaptionsImpl::fontEdge() const
{
    return helper_.get<Firebolt::Accessibility::JsonData::FontEdge, Accessibility::FontEdge>("ClosedCaptions.fontEdge");
}

Result<std::string> ClosedCaptionsImpl::fontEdgeColor() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("ClosedCaptions.fontEdgeColor");
}

Result<Accessibility::FontFamily> ClosedCaptionsImpl::fontFamily() const
{
    return helper_.get<Firebolt::Accessibility::JsonData::FontFamily, Accessibility::FontFamily>(
        "ClosedCaptions.fontFamily");
}

Result<unsigned> ClosedCaptionsImpl::fontOpacity() const
{
    return helper_.get<FireboltSDK::JSON::Unsigned, unsigned>("ClosedCaptions.fontOpacity");
}

Result<float> ClosedCaptionsImpl::fontSize() const
{
    return helper_.get<FireboltSDK::JSON::Float, float>("ClosedCaptions.fontSize");
}

Result<std::vector<std::string>> ClosedCaptionsImpl::preferredLanguages() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::String, std::string>, std::vector<std::string>>(
        "ClosedCaptions.preferredLanguages");
}

Result<std::string> ClosedCaptionsImpl::textAlign() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("ClosedCaptions.textAlign");
}

Result<std::string> ClosedCaptionsImpl::textAlignVertical() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("ClosedCaptions.textAlignVertical");
}

Result<std::string> ClosedCaptionsImpl::windowColor() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("ClosedCaptions.windowColor");
}

Result<unsigned> ClosedCaptionsImpl::windowOpacity() const
{
    return helper_.get<FireboltSDK::JSON::Unsigned, unsigned>("ClosedCaptions.windowOpacity");
}

Result<void> ClosedCaptionsImpl::setBackgroundColor(const std::string& value)
{
    return helper_.set("ClosedCaptions.setBackgroundColor", value);
}

Result<void> ClosedCaptionsImpl::setBackgroundOpacity(const unsigned value)
{
    return helper_.set("ClosedCaptions.setBackgroundOpacity", value);
}

Result<void> ClosedCaptionsImpl::setEnabled(const bool value)
{
    return helper_.set("ClosedCaptions.setEnabled", value);
}

Result<void> ClosedCaptionsImpl::setFontColor(const std::string& value)
{
    return helper_.set("ClosedCaptions.setFontColor", value);
}

Result<void> ClosedCaptionsImpl::setFontEdge(const Accessibility::FontEdge& value)
{
    return helper_.set("ClosedCaptions.setFontEdge",
                       ::FireboltSDK::JSON::ToString(::Firebolt::Accessibility::JsonData::FontEdgeEnum, value));
}

Result<void> ClosedCaptionsImpl::setFontEdgeColor(const std::string& value)
{
    return helper_.set("ClosedCaptions.setFontEdgeColor", value);
}

Result<void> ClosedCaptionsImpl::setFontFamily(const Accessibility::FontFamily& value)
{
    Firebolt::Accessibility::JsonData::FontFamily jsonValue{value};
    return helper_.set("ClosedCaptions.setFontFamily",
                       ::FireboltSDK::JSON::ToString(::Firebolt::Accessibility::JsonData::FontFamilyEnum, value));
}

Result<void> ClosedCaptionsImpl::setFontOpacity(const unsigned value)
{
    return helper_.set("ClosedCaptions.setFontOpacity", value);
}

Result<void> ClosedCaptionsImpl::setFontSize(const float value)
{
    return helper_.set("ClosedCaptions.setFontSize", value);
}

Result<void> ClosedCaptionsImpl::setPreferredLanguages(const std::vector<std::string>& value)
{
    return helper_.set("ClosedCaptions.setPreferredLanguages", value);
}

Result<void> ClosedCaptionsImpl::setTextAlign(const std::string& value)
{
    return helper_.set("ClosedCaptions.setTextAlign", value);
}

Result<void> ClosedCaptionsImpl::setTextAlignVertical(const std::string& value)
{
    return helper_.set("ClosedCaptions.setTextAlignVertical", value);
}

Result<void> ClosedCaptionsImpl::setWindowColor(const std::string& value)
{
    return helper_.set("ClosedCaptions.setWindowColor", value);
}

Result<void> ClosedCaptionsImpl::setWindowOpacity(const unsigned value)
{
    return helper_.set("ClosedCaptions.setWindowOpacity", value);
}

// Events
Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnBackgroundColorChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("ClosedCaptions.onBackgroundColorChanged",
                                                        std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnBackgroundOpacityChanged(std::function<void(unsigned)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::Unsigned>("ClosedCaptions.onBackgroundOpacityChanged",
                                                          std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnEnabledChanged(std::function<void(bool)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::Boolean>("ClosedCaptions.onEnabledChanged", std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontColorChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("ClosedCaptions.onFontColorChanged", std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontEdgeChanged(std::function<void(const Accessibility::FontEdge&)>&& notification)
{
    return helper_.subscribe<Firebolt::Accessibility::JsonData::FontEdge>("ClosedCaptions.onFontEdgeChanged",
                                                                          std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontEdgeColorChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("ClosedCaptions.onFontEdgeColorChanged", std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnFontFamilyChanged(std::function<void(const Accessibility::FontFamily&)>&& notification)
{
    return helper_.subscribe<Firebolt::Accessibility::JsonData::FontFamily>("ClosedCaptions.onFontFamilyChanged",
                                                                            std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnFontOpacityChanged(std::function<void(unsigned)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::Unsigned>("ClosedCaptions.onFontOpacityChanged", std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnFontSizeChanged(std::function<void(float)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::Float>("ClosedCaptions.onFontSizeChanged", std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnPreferredLanguagesChanged(
    std::function<void(const std::vector<std::string>&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::NL_Json_Array<
        FireboltSDK::JSON::String, std::string>>("ClosedCaptions.onPreferredLanguagesChanged", std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnTextAlignChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("ClosedCaptions.onTextAlignChanged", std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnTextAlignVerticalChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("ClosedCaptions.onTextAlignVerticalChanged",
                                                        std::move(notification));
}

Result<SubscriptionId>
ClosedCaptionsImpl::subscribeOnWindowColorChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("ClosedCaptions.onWindowColorChanged", std::move(notification));
}

Result<SubscriptionId> ClosedCaptionsImpl::subscribeOnWindowOpacityChanged(std::function<void(unsigned)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::Unsigned>("ClosedCaptions.onWindowOpacityChanged",
                                                          std::move(notification));
}

Result<void> ClosedCaptionsImpl::unsubscribe(SubscriptionId id)
{
    return helper_.unsubscribe(id);
}

void ClosedCaptionsImpl::unsubscribeAll()
{
    helper_.unsubscribeAll();
}
} // namespace Firebolt::ClosedCaptions
