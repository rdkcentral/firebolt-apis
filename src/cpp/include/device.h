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
#include <types/fb-errors.h>
#include <types/types.h>
#include <vector>

namespace Firebolt::Device
{
/**
 * @brief NetworkState The type of network that is currently active
 */
// Enums
/**
 * @brief Category The device category
 */
enum class Category
{
    STB,    //with tuner/demod, no integrated display
    OTT,    //no tuner/demod, no integrated display
    TV,     //possibly tuner/demod, with integrated display
};

// Types
/**
 * @brief MemoryInfo values in units of 1024 bytes
 */
struct MemoryInfo {
    uint32_t userMemoryUsed;   
    uint32_t userMemoryLimit;
    uint32_t gpuMemoryUsed;
    uint32_t gpuMemoryLimit;
};

class IDevice
{
public:
    virtual ~IDevice() = default;
    /**
     * @brief Get the category of the device
     *
     * @retval The category property or error
     */
    virtual Result<Category> category() const = 0;

    /**
     * @brief Returns chipset ID as a printable string, e,g. RTD1319
     *
     * @retval The chipset ID or error
     */
    virtual Result<std::string> chipsetId() = 0;

    /**
     * @brief Returns number of seconds since most recent device boot, including any time spent during deep sleep
     *
     * @retval The uptime in seconds or error
     */
    virtual Result<uint32_t> uptime() = 0;

    /**
     * @brief Returns the time in seconds since the device is active
     *
     * @retval The time in active state in seconds or error
     */
    virtual Result<uint32_t> timeInActiveState() = 0;

    /**
     * @brief Returns information about container memory usage, in units of 1024 bytes
     *
     * @retval MemoryInfo struct or error
     */
    virtual Result<MemoryInfo> memoryInfo() = 0;
};

} // namespace Firebolt::Device
