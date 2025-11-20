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

#include <functional>
#include <optional>
#include <string>
#include "Firebolt/types.h"
#include <vector>

namespace Firebolt::Stats
{
struct MemoryInfo
{
    uint32_t userMemoryUsed;
    uint32_t userMemoryLimit;
    uint32_t gpuMemoryUsed;
    uint32_t gpuMemoryLimit;
};

class IStats
{
public:
    virtual ~IStats() = default;

    /**
     @brief Returns information about container memory usage, in units of 1024 bytes
    *
    * @retval The platform property or error
    * @retval MemoryInfo struct or error
    */
    virtual Result<MemoryInfo> memoryUsage() const = 0;
};

} // namespace Firebolt::Stats
