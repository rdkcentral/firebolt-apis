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

#include "display.h"
#include <firebolt/json_types.h>
#include <nlohmann/json.hpp>

namespace Firebolt::Display::JsonData
{

// Types
class DisplaySizeJson : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Display::DisplaySize>
{
public:
    void fromJson(const nlohmann::json& json) override
    {
        width_ = json["width"].get<uint32_t>();
        height_ = json["height"].get<uint32_t>();
    }
    ::Firebolt::Display::DisplaySize value() const override { return Firebolt::Display::DisplaySize{width_, height_}; }

private:
    uint32_t width_;
    uint32_t height_;
};

} // namespace Firebolt::Display::JsonData
