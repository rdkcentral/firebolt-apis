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
#include <string>
#include <vector>

namespace Firebolt::Advertising
{
// Types
struct Ifa
{
    /* UUID*/
    std::string ifa;

    /* Advertising ID type
        One of
        "dpid" - device provided ID
        "sspid" - SSP provided ID
        "sessionid" - session/synthetic ID
    */
    std::string ifa_type;

    /* Limit Ad Tracking
        One of
        "0" - LMT disabled
        "1" - LMT enabled
    */
    std::string lmt;
};

class IAdvertising
{
public:
    virtual ~IAdvertising() = default;

    /**
     * @brief Request that the platform move your app out of focus
     *
     * @return Ifa struct or error
     *
     */
    virtual Result<Ifa> advertisingId() const = 0;

    /**
     * @brief  Return a persistent unique UUID for
     * the current app and device.  The UUID is reset
     * when the app or device is reset
     *
     *
     * @return Uid or error
     */
    virtual Result<std::string> uid() const = 0;
};
} // namespace Firebolt::Advertising
