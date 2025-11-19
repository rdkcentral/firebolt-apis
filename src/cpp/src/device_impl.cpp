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
DeviceImpl::DeviceImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper) {}

Result<DeviceClass> DeviceImpl::deviceClass() const
{
    return Result(helper_.get<JsonData::DeviceClassJson, DeviceClass>("Device.deviceClass"));
}

Result<u_int32_t> DeviceImpl::timeInActiveState() const
{
    return helper_.get<FireboltSDK::JSON::Integer, u_int32_t>("Device.timeInActiveState");
}

Result<uint32_t> DeviceImpl::uptime() const
{
    return helper_.get<FireboltSDK::JSON::Integer, uint32_t>("Device.uptime");
}

Result<std::string> DeviceImpl::uid() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("Device.uid");
}
} // namespace Firebolt::Device
