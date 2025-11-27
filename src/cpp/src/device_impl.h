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

#include "device.h"
#include <firebolt/helpers.h>

namespace Firebolt::Device
{
class DeviceImpl : public IDevice
{
public:
    explicit DeviceImpl(Firebolt::Helpers::IHelper& helper);
    DeviceImpl(const DeviceImpl&) = delete;
    DeviceImpl& operator=(const DeviceImpl&) = delete;

    ~DeviceImpl() override = default;

    Result<DeviceClass> deviceClass() const override;
    Result<uint32_t> uptime() const override;
    Result<u_int32_t> timeInActiveState() const override;
    Result<std::string> chipsetId() const override;
    Result<std::string> uid() const override;

private:
    Firebolt::Helpers::IHelper& helper_;
    // Methods
};
} // namespace Firebolt::Device
