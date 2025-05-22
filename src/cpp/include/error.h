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

#include <cstdint>

namespace Firebolt
{
enum class Error : int32_t
{
    None = 0,
    General = 1,
    Timedout = 2,
    NotConnected = 3,
    AlreadyConnected = 4,
    // AuthenticationError, ?
    InvalidRequest = -32600,
    MethodNotFound = -32601,
    InvalidParams = -32602,
    CapabilityNotAvaialbale = -50300,
    CapabilityNotSupported = -50100,
    CapabilityGet = -50200,
    CapabilityNotPermitted = -40300,
};
}
