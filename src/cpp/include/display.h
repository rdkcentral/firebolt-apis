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

namespace Firebolt::Display
{
// Enums

struct DisplaySize
{
    uint32_t width;
    uint32_t height;
};
// Types

class IDisplay
{
public:
    virtual ~IDisplay   () = default;
    /**
     * @brief Returns the physical dimensions of the connected or integral display, in centimeters 

        Returns 0, 0 on a OTT/STB device when a display is not connected over HDMI

        Typical values

        43" - 97, 56
        55" - 123, 71
        65" - 145, 83
     *
     * @retval The class property or error
     */
    
    virtual Result<DisplaySize> size() const = 0;
    /**
     * @brief Returns the physical/native resolution of the connected or integral display, in pixels

        Returns 0, 0 on a OTT/STB device when a display is not connected over HDMI

        Typical values

        HD Ready - 1280, 720
        Full HD - 1920, 1080
        UHD - 3840, 2160
     *
     * @retval The uptime in seconds or error
     */
    virtual Result<DisplaySize> maxResolution() const = 0;
};

} // namespace Firebolt::Device
