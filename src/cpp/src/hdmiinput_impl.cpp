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

#include "hdmiinput_impl.h"
#include "jsondata_hdmiinput_types.h"

namespace Firebolt::HDMIInput
{
HDMIInputImpl::HDMIInputImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper), subscriptionManager_(helper, this)
{
}

Result<bool> HDMIInputImpl::autoLowLatencyModeCapable(const std::string& port) const
{
    nlohmann::json params;
    params["port"] = port;
    return helper_.get<FireboltSDK::JSON::Boolean, bool>("hdmiinput.autoLowLatencyModeCapable", params);
}

Result<EDIDVersion> HDMIInputImpl::edidVersion(const std::string& port) const
{
    nlohmann::json params;
    params["port"] = port;
    return helper_.get<JsonData::EDIDVersionJson, EDIDVersion>("HDMIInput.edidVersion", params);
}

Result<bool> HDMIInputImpl::lowLatencyMode() const
{
    return helper_.get<FireboltSDK::JSON::Boolean, bool>("hdmiinput.lowLatencyMode");
}

Result<void> HDMIInputImpl::setAutoLowLatencyModeCapable(const std::string& port, const bool value)
{
    nlohmann::json params;
    params["port"] = port;
    params["value"] = value;
    return helper_.set("hdmiinput.setAutoLowLatencyModeCapable", params);
}

Result<void> HDMIInputImpl::setEdidVersion(const std::string& port, const EDIDVersion& value)
{
    nlohmann::json params;
    params["port"] = port;
    params["value"] = FireboltSDK::JSON::ToString(JsonData::EDIDVersionEnum, value);
    return helper_.set("HDMIInput.setEdidVersion", params);
}

Result<void> HDMIInputImpl::setLowLatencyMode(const bool value)
{
    return helper_.set("hdmiinput.setLowLatencyMode", value);
}

Result<void> HDMIInputImpl::close()
{
    nlohmann::json params;
    return helper_.invoke("HDMIInput.close", params);
}

Result<void> HDMIInputImpl::open(const std::string& port)
{
    nlohmann::json params;
    params["portId"] = port;
    return helper_.invoke("HDMIInput.open", params);
}

Result<HDMIInputPort> HDMIInputImpl::port(const std::string& port)
{
    nlohmann::json params;
    params["portId"] = port;
    return helper_.get<JsonData::HDMIInputPort, HDMIInputPort>("HDMIInput.port", params);
}

Result<std::vector<HDMIInputPort>> HDMIInputImpl::ports() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<JsonData::HDMIInputPort, HDMIInputPort>, std::vector<HDMIInputPort>>(
        "HDMIInput.ports");
}

// Events
Result<SubscriptionId> HDMIInputImpl::subscribeOnAutoLowLatencyModeCapableChanged(
    std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification)
{
    return subscriptionManager_
        .subscribe<JsonData::AutoLowLatencyModeCapableChangedInfo>("hdmiinput.onAutoLowLatencyModeCapableChanged",
                                                                   std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::globalSubscribeOnAutoLowLatencyModeCapableChanged(
    std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification)
{
    return subscriptionManager_
        .subscribe<JsonData::AutoLowLatencyModeCapableChangedInfo>("HDMIInput.onAutoLowLatencyModeCapableChanged",
                                                                   std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnAutoLowLatencyModeSignalChanged(
    std::function<void(const AutoLowLatencyModeSignalChangedInfo&)>&& notification)
{
    return subscriptionManager_
        .subscribe<JsonData::AutoLowLatencyModeSignalChangedInfo>("hdmiinput.onAutoLowLatencyModeSignalChanged",
                                                                  std::move(notification));
}

Result<SubscriptionId>
HDMIInputImpl::subscribeOnConnectionChanged(std::function<void(const ConnectionChangedInfo&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::ConnectionChangedInfo>("hdmiinput.onConnectionChanged",
                                                                           std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnEdidVersionChanged(std::function<void(const EDIDVersion&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::EDIDVersionJson>("hdmiinput.onEdidVersionChanged",
                                                                     std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnLowLatencyModeChanged(std::function<void(bool)>&& notification)
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::Boolean>("hdmiinput.onLowLatencyModeChanged",
                                                                      std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnSignalChanged(std::function<void(const SignalChangedInfo&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::SignalChangedInfo>("hdmiinput.onSignalChanged",
                                                                       std::move(notification));
}

Result<void> HDMIInputImpl::unsubscribe(SubscriptionId id)
{
    return subscriptionManager_.unsubscribe(id);
}

void HDMIInputImpl::unsubscribeAll()
{
    subscriptionManager_.unsubscribeAll();
}
} // namespace Firebolt::HDMIInput
