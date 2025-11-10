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

#include <algorithm>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <types/json_types.h>

namespace Firebolt::Device::JsonData
{
// Enums
inline FireboltSDK::JSON::EnumType<::Firebolt::Device::Category> const CategoryEnum({
    { "stb", ::Firebolt::Device::Category::STB },
    { "ott", ::Firebolt::Device::Category::OTT },
    { "tv",  ::Firebolt::Device::Category::TV },
});

// Types
class MemoryInfo : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::MemoryInfo>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        userMemoryUsed_ = json["userMemoryUsed"].get<uint32_t>();
        userMemoryLimit_ = json["userMemoryLimit"].get<uint32_t>();
        gpuMemoryUsed_ = json["gpuMemoryUsed"].get<uint32_t>();
        gpuMemoryLimit_ = json["gpuMemoryLimit"].get<uint32_t>();
    }
    ::Firebolt::Device::MemoryInfo Value() const override
    {
        return ::Firebolt::Device::MemoryInfo{userMemoryUsed_, userMemoryLimit_, gpuMemoryUsed_, gpuMemoryLimit_};
    }
private:
    uint32_t userMemoryUsed_;
    uint32_t userMemoryLimit_;
    uint32_t gpuMemoryUsed_;
    uint32_t gpuMemoryLimit_;
};
    
class CategoryJson : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::Category>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        category_ = CategoryEnum.at(json);
    }
    ::Firebolt::Device::Category Value() const override
    {
        return category_;
    }               
    
private:
    ::Firebolt::Device::Category category_; 
};

} // namespace Firebolt::Device::JsonData
