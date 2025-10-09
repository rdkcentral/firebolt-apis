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

using namespace Firebolt::Helpers;

namespace Firebolt::Device
{
// Methods
Result<AudioProfiles> DeviceImpl::audio() const
{
    return get<JsonData::AudioProfiles, AudioProfiles>("device.audio");
}

Result<std::string> DeviceImpl::distributor() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.distributor");
}

Result<HDCPVersionMap> DeviceImpl::hdcp() const
{
    return get<JsonData::HDCPVersionMap, HDCPVersionMap>("device.hdcp");
}

Result<HDRFormatMap> DeviceImpl::hdr() const
{
    return get<JsonData::HDRFormatMap, HDRFormatMap>("device.hdr");
}

Result<std::string> DeviceImpl::id() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.id");
}

Result<std::string> DeviceImpl::make() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.make");
}

Result<std::string> DeviceImpl::model() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.model");
}

Result<std::string> DeviceImpl::name() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.name");
}

Result<NetworkInfoResult> DeviceImpl::network() const
{
    return get<JsonData::NetworkInfoResult, NetworkInfoResult>("device.network");
}

Result<std::string> DeviceImpl::platform() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.platform");
}

Result<Resolution> DeviceImpl::screenResolution() const
{
    return get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::Integer, int32_t>, Resolution>("device.screenResolution");
}

Result<std::string> DeviceImpl::sku() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.sku");
}

Result<std::string> DeviceImpl::type() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.type");
}

Result<std::string> DeviceImpl::uid() const
{
    return get<FireboltSDK::JSON::String, std::string>("device.uid");
}

Result<Resolution> DeviceImpl::videoResolution() const
{
    return get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::Integer, int32_t>, Resolution>("device.videoResolution");
}

// Events
Result<SubscriptionId> DeviceImpl::subscribeOnAudioChanged(std::function<void(const AudioProfiles&)>&& notification)
{
    return subscribe<JsonData::AudioProfiles>("device.onAudioChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnDeviceNameChanged(std::function<void(const std::string&)>&& notification)
{
    return subscribe<FireboltSDK::JSON::String>("device.onDeviceNameChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnHdcpChanged(std::function<void(const HDCPVersionMap&)>&& notification)
{
    return subscribe<JsonData::HDCPVersionMap>("device.onHdcpChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnHdrChanged(std::function<void(const HDRFormatMap&)>&& notification)
{
    return subscribe<JsonData::HDRFormatMap>("device.onHdrChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnNameChanged(std::function<void(const std::string&)>&& notification)
{
    return subscribe<FireboltSDK::JSON::String>("device.onNameChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnNetworkChanged(std::function<void(const NetworkInfoResult&)>&& notification)
{
    return subscribe<JsonData::NetworkInfoResult>("device.onNetworkChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnScreenResolutionChanged(std::function<void(const std::string&)>&& notification)
{
    return subscribe<FireboltSDK::JSON::String>("device.onScreenResolutionChanged", std::move(notification));
}

Result<SubscriptionId> DeviceImpl::subscribeOnVideoResolutionChanged(std::function<void(const std::string&)>&& notification)
{
    return subscribe<FireboltSDK::JSON::String>("device.onVideoResolutionChanged", std::move(notification));
}

Result<void> DeviceImpl::unsubscribe(SubscriptionId id)
{
    return SubscriptionHelper::unsubscribe(id);
}

void DeviceImpl::unsubscribeAll()
{
    SubscriptionHelper::unsubscribeAll();
}

Result<DeviceVersion> DeviceImpl::version() const
{
    return get<JsonData::DeviceVersion, DeviceVersion>("device.version");
}
} // namespace Firebolt::Device
