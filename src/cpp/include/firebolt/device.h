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

#include <firebolt/types.h>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace Firebolt::Device
{
// Enums
/**
 * @brief DeviceClass The device class
 */
enum class DeviceClass
{
    STB, // with tuner/demod, no integrated display
    OTT, // no tuner/demod, no integrated display
    TV,  // possibly tuner/demod, with integrated display
};

// Types

class IDevice
{
public:
    virtual ~IDevice() = default;
    /**
     * @brief Get the class of the device
     *
     * @retval The class property or error
     */
    virtual Result<DeviceClass> deviceClass() const = 0;

    /**
     * @brief Returns number of seconds since most recent device boot, including any time spent during deep sleep
     *
     * @retval The uptime in seconds or error
     */
    virtual Result<uint32_t> uptime() const = 0;

    /**
     * @brief Returns number of seconds since most recent device boot, including any time spent during deep sleep
     *
     * @retval The uptime in seconds or error
     */
    virtual Result<u_int32_t> timeInActiveState() const = 0;

    /**
     * @brief Returns chipset ID as a printable string, e.g. "BCM72180"
     *
     * @retval The uid string or error
     */
    virtual Result<std::string> chipsetId() const = 0;

    /**
     * @brief Returns a persistent unique UUID for the current app and device.  The UUID is reset when the app or device is reset
     *
     * @retval The uid string or error
     */
    virtual Result<std::string> uid() const = 0;
};

} // namespace Firebolt::Device
