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
#include <firebolt/json_types.h>
#include <nlohmann/json.hpp>

namespace Firebolt::Device::JsonData
{
// Enums
inline const Firebolt::JSON::EnumType<::Firebolt::Device::DeviceClass> DeviceClassEnum({
    {"stb", ::Firebolt::Device::DeviceClass::STB},
    {"ott", ::Firebolt::Device::DeviceClass::OTT},
    {"tv", ::Firebolt::Device::DeviceClass::TV},
});

// Types
class DeviceClassJson : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Device::DeviceClass>
{
public:
    void fromJson(const nlohmann::json& json) override { deviceClass_ = DeviceClassEnum.at(json); }
    ::Firebolt::Device::DeviceClass value() const override { return deviceClass_; }

private:
    ::Firebolt::Device::DeviceClass deviceClass_;
};

} // namespace Firebolt::Device::JsonData
