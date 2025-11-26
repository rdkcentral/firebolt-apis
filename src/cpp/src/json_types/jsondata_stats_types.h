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

#include "stats.h"
#include <firebolt/json_types.h>
#include <nlohmann/json.hpp>

namespace Firebolt::Stats::JsonData
{
class MemoryInfo : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Stats::MemoryInfo>
{
public:
    void fromJson(const nlohmann::json& json) override
    {
        userMemoryUsed = json["userMemoryUsedKiB"].get<uint32_t>();
        userMemoryLimit = json["userMemoryLimitKiB"].get<uint32_t>();
        gpuMemoryUsed = json["gpuMemoryUsedKiB"].get<uint32_t>();
        gpuMemoryLimit = json["gpuMemoryLimitKiB"].get<uint32_t>();
    }
    ::Firebolt::Stats::MemoryInfo value() const override
    {
        return ::Firebolt::Stats::MemoryInfo{userMemoryUsed, userMemoryLimit, gpuMemoryUsed, gpuMemoryLimit};
    }

private:
    uint32_t userMemoryUsed;
    uint32_t userMemoryLimit;
    uint32_t gpuMemoryUsed;
    uint32_t gpuMemoryLimit;
};
} // namespace Firebolt::Stats::JsonData
