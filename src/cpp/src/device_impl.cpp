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
#include <TypesPriv.h>

namespace Firebolt::Device
{
DeviceImpl::DeviceImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper) {}

// Methods
Result<AudioProfiles> DeviceImpl::audio() const
{
    return helper_.get<JsonData::AudioProfiles, AudioProfiles>("device.audio");
}

Result<std::string> DeviceImpl::distributor() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.distributor");
}

Result<HDCPVersionMap> DeviceImpl::hdcp() const
{
    return helper_.get<JsonData::HDCPVersionMap, HDCPVersionMap>("device.hdcp");
}

Result<HDRFormatMap> DeviceImpl::hdr() const
{
    return helper_.get<JsonData::HDRFormatMap, HDRFormatMap>("device.hdr");
}

Result<std::string> DeviceImpl::id() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.id");
}

Result<std::string> DeviceImpl::make() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.make");
}

Result<std::string> DeviceImpl::model() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.model");
}

Result<std::string> DeviceImpl::name() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.name");
}

Result<NetworkInfoResult> DeviceImpl::network() const
{
    return helper_.get<JsonData::NetworkInfoResult, NetworkInfoResult>("device.network");
}

Result<std::string> DeviceImpl::platform() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.platform");
}

Result<Resolution> DeviceImpl::screenResolution() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::Integer, int32_t>, Resolution>(
        "device.screenResolution");
}

Result<std::string> DeviceImpl::sku() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.sku");
}

Result<std::string> DeviceImpl::type() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.type");
}

Result<std::string> DeviceImpl::uid() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("device.uid");
}

Result<Resolution> DeviceImpl::videoResolution() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::Integer, int32_t>, Resolution>(
        "device.videoResolution");
}

Result<DeviceVersion> DeviceImpl::version() const
{
    return helper_.get<JsonData::DeviceVersion, DeviceVersion>("device.version");
}

// Events
Result<SubscriptionId> DeviceImpl::subscribeOnAudioChanged(std::function<void(const AudioProfiles&)>&& notification)
{
    // Call the subscribe method on the injected helper object
    return helper_.subscribe<JsonData::AudioProfiles>("device.onAudioChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnDeviceNameChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("device.onDeviceNameChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnHdcpChanged(std::function<void(const HDCPVersionMap&)>&& notification)
{
    return helper_.subscribe<JsonData::HDCPVersionMap>("device.onHdcpChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnHdrChanged(std::function<void(const HDRFormatMap&)>&& notification)
{
    return helper_.subscribe<JsonData::HDRFormatMap>("device.onHdrChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnNameChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("device.onNameChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnNetworkChanged(std::function<void(const NetworkInfoResult&)>&& notification)
{
    return helper_.subscribe<JsonData::NetworkInfoResult>("device.onNetworkChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnScreenResolutionChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("device.onScreenResolutionChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnVideoResolutionChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("device.onVideoResolutionChanged", std::move(notification));
}

Result<void> DeviceImpl::unsubscribe(SubscriptionId id)
{
    return helper_.unsubscribe(id);
}

void DeviceImpl::unsubscribeAll()
{
    helper_.unsubscribeAll();
}

} // namespace Firebolt::Device
