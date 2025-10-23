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

#include "device_impl.h"
#include "jsondata_device_types.h"

namespace Firebolt::Device
{
DeviceImpl::DeviceImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper), subscriptionManager_(helper, this) {}

// Methods
Result<AudioProfiles> DeviceImpl::audio() const
{
    return helper_.get<JsonData::AudioProfiles, AudioProfiles>("Device.audio");
}

Result<std::string> DeviceImpl::distributor() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.distributor");
}

Result<HDCPVersionMap> DeviceImpl::hdcp() const
{
    return helper_.get<JsonData::HDCPVersionMap, HDCPVersionMap>("Device.hdcp");
}

Result<HDRFormatMap> DeviceImpl::hdr() const
{
    return helper_.get<JsonData::HDRFormatMap, HDRFormatMap>("Device.hdr");
}

Result<std::string> DeviceImpl::id() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.id");
}

Result<std::string> DeviceImpl::make() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.make");
}

Result<std::string> DeviceImpl::model() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.model");
}

Result<std::string> DeviceImpl::name() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.name");
}

Result<NetworkInfoResult> DeviceImpl::network() const
{
    return helper_.get<JsonData::NetworkInfoResult, NetworkInfoResult>("Device.network");
}

Result<std::string> DeviceImpl::platform() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.platform");
}

Result<Resolution> DeviceImpl::screenResolution() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::Integer, int32_t>, Resolution>(
        "Device.screenResolution");
}

Result<std::string> DeviceImpl::sku() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.sku");
}

Result<std::string> DeviceImpl::type() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.type");
}

Result<std::string> DeviceImpl::uid() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.uid");
}

Result<Resolution> DeviceImpl::videoResolution() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::Integer, int32_t>, Resolution>(
        "Device.videoResolution");
}

Result<DeviceVersion> DeviceImpl::version() const
{
    return helper_.get<JsonData::DeviceVersion, DeviceVersion>("Device.version");
}

// Events
Result<SubscriptionId> DeviceImpl::subscribeOnAudioChanged(std::function<void(const AudioProfiles&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::AudioProfiles>("Device.onAudioChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnDeviceNameChanged(std::function<void(const std::string&)>&& notification)
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::String>("Device.onDeviceNameChanged",
                                                                     std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnHdcpChanged(std::function<void(const HDCPVersionMap&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::HDCPVersionMap>("Device.onHdcpChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnHdrChanged(std::function<void(const HDRFormatMap&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::HDRFormatMap>("Device.onHdrChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnNameChanged(std::function<void(const std::string&)>&& notification)
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::String>("Device.onNameChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnNetworkChanged(std::function<void(const NetworkInfoResult&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::NetworkInfoResult>("Device.onNetworkChanged",
                                                                       std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnScreenResolutionChanged(std::function<void(const std::string&)>&& notification)
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::String>("Device.onScreenResolutionChanged",
                                                                     std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnVideoResolutionChanged(std::function<void(const std::string&)>&& notification)
{
    return subscriptionManager_.subscribe<FireboltSDK::JSON::String>("Device.onVideoResolutionChanged",
                                                                     std::move(notification));
}

Result<void> DeviceImpl::unsubscribe(SubscriptionId id)
{
    return subscriptionManager_.unsubscribe(id);
}

void DeviceImpl::unsubscribeAll()
{
    subscriptionManager_.unsubscribeAll();
}

} // namespace Firebolt::Device
