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

using namespace Firebolt::Helpers;

namespace Firebolt::HDMIInput
{
Result<bool> HDMIInputImpl::autoLowLatencyModeCapable(const std::string& port) const
{
    Parameters parameters;
    parameters.add(_T("port"), port);
    return get<WPEFramework::Core::JSON::Boolean, bool>(_T("hdmiinput.autoLowLatencyModeCapable"), parameters);
}

Result<EDIDVersion> HDMIInputImpl::edidVersion(const std::string& port) const
{
    Parameters parameters;
    parameters.add(_T("port"), port);
    return get<JsonData::EDIDVersionJson, EDIDVersion>(_T("HDMIInput.edidVersion"), parameters);
}

Result<bool> HDMIInputImpl::lowLatencyMode() const
{
    return get<WPEFramework::Core::JSON::Boolean, bool>(_T("hdmiinput.lowLatencyMode"));
}

Result<void> HDMIInputImpl::setAutoLowLatencyModeCapable(const std::string& port, const bool value)
{
    Parameters params;
    params.add(_T("port"), port);
    params.add(_T("value"), value);
    return set(_T("hdmiinput.setAutoLowLatencyModeCapable"), params);
}

Result<void> HDMIInputImpl::setEdidVersion(const std::string& port, const EDIDVersion& value)
{
    Parameters params;
    // params.add(_T("port"), port);
    // params.add<JsonData::EDIDVersion>(_T("value"), value);
    return set(_T("HDMIInput.setEdidVersion"), params);
}

Result<void> HDMIInputImpl::setLowLatencyMode(const bool value)
{
    return set(_T("hdmiinput.setLowLatencyMode"), value);
}

Result<void> HDMIInputImpl::close()
{
    Parameters params;
    return invoke("HDMIInput.close", params);
}

Result<void> HDMIInputImpl::open(const std::string& portId)
{
    Parameters params;
    params.add(_T("portId"), portId);
    return invoke("HDMIInput.open", params);
}

Result<HDMIInputPort> HDMIInputImpl::port(const std::string& portId)
{
    Parameters params;
    params.add(_T("portId"), portId);
    return invoke<JsonData::HDMIInputPort, HDMIInputPort>("HDMIInput.port", params);
}

Result<std::vector<HDMIInputPort>> HDMIInputImpl::ports() const
{
    Parameters params;
    return invoke<FireboltSDK::JSON::NL_Json_Array<JsonData::HDMIInputPort, HDMIInputPort>, std::vector<HDMIInputPort>>("HDMIInput.ports", params);
}

// Events
Result<SubscriptionId> HDMIInputImpl::subscribeOnAutoLowLatencyModeCapableChanged(
    std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification)
{
    return SubscriptionHelper::subscribe<
        JsonData::AutoLowLatencyModeCapableChangedInfo>(_T("hdmiinput.onAutoLowLatencyModeCapableChanged"),
                                                        std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::globalSubscribeOnAutoLowLatencyModeCapableChanged(
    std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification)
{
    return SubscriptionHelper::subscribe<
        JsonData::AutoLowLatencyModeCapableChangedInfo>(_T("HDMIInput.onAutoLowLatencyModeCapableChanged"),
                                                        std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnAutoLowLatencyModeSignalChanged(
    std::function<void(const AutoLowLatencyModeSignalChangedInfo&)>&& notification)
{
    return SubscriptionHelper::subscribe<
        JsonData::AutoLowLatencyModeSignalChangedInfo>(_T("hdmiinput.onAutoLowLatencyModeSignalChanged"),
                                                       std::move(notification));
}

Result<SubscriptionId>
HDMIInputImpl::subscribeOnConnectionChanged(std::function<void(const ConnectionChangedInfo&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::ConnectionChangedInfo>(_T("hdmiinput.onConnectionChanged"),
                                                                          std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnEdidVersionChanged(std::function<void(const EDIDVersion&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::EDIDVersionJson>(_T("hdmiinput.onEdidVersionChanged"),
                                                                std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnLowLatencyModeChanged(std::function<void(bool)>&& notification)
{
    return SubscriptionHelper::subscribe<WPEFramework::Core::JSON::Boolean>(_T("hdmiinput.onLowLatencyModeChanged"),
                                                                            std::move(notification));
}

Result<SubscriptionId> HDMIInputImpl::subscribeOnSignalChanged(std::function<void(const SignalChangedInfo&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::SignalChangedInfo>(_T("hdmiinput.onSignalChanged"),
                                                                      std::move(notification));
}

Result<void> HDMIInputImpl::unsubscribe(SubscriptionId id)
{
    return SubscriptionHelper::unsubscribe(id);
}

void HDMIInputImpl::unsubscribeAll()
{
    SubscriptionHelper::unsubscribeAll();
}
} // namespace Firebolt::HDMIInput
