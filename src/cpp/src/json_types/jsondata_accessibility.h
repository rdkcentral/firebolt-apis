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

#include "common/accessibility.h"
#include "Firebolt/json_types.h"

namespace Firebolt::Accessibility::JsonData
{
inline Firebolt::JSON::EnumType<::Firebolt::Accessibility::FontFamily> FontFamilyEnum({
    { "monospaced_serif", ::Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF },
    { "proportional_serif", ::Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF },
    { "monospaced_sanserif", ::Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF },
    { "proportional_sanserif", ::Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF },
    { "smallcaps", ::Firebolt::Accessibility::FontFamily::SMALLCAPS },
    { "cursive", ::Firebolt::Accessibility::FontFamily::CURSIVE },
    { "casual", ::Firebolt::Accessibility::FontFamily::CASUAL },
});

inline Firebolt::JSON::EnumType<Firebolt::Accessibility::FontEdge> FontEdgeEnum({
    { "none", ::Firebolt::Accessibility::FontEdge::NONE },
    { "raised", ::Firebolt::Accessibility::FontEdge::RAISED },
    { "depressed", ::Firebolt::Accessibility::FontEdge::DEPRESSED },
    { "uniform", ::Firebolt::Accessibility::FontEdge::UNIFORM },
    { "drop_shadow_left", ::Firebolt::Accessibility::FontEdge::DROP_SHADOW_LEFT },
    { "drop_shadow_right", ::Firebolt::Accessibility::FontEdge::DROP_SHADOW_RIGHT },
});

class FontFamily : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Accessibility::FontFamily>
{
public:
    FontFamily() = default;
    FontFamily(::Firebolt::Accessibility::FontFamily value) : value_(value) {}
    void FromJson(const nlohmann::json& json) override
    {
        value_ = FontFamilyEnum.at(json);
    }
    ::Firebolt::Accessibility::FontFamily Value() const override
    {
        return value_;
    }
private:
    ::Firebolt::Accessibility::FontFamily value_;
};

class FontEdge : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Accessibility::FontEdge>
{
public:
    FontEdge() = default;
    FontEdge(::Firebolt::Accessibility::FontEdge value) : value_(value) {}
    void FromJson(const nlohmann::json& json) override
    {
        value_ = FontEdgeEnum.at(json);
    }
    ::Firebolt::Accessibility::FontEdge Value() const override
    {
        return value_;
    }
private:
    ::Firebolt::Accessibility::FontEdge value_;
};

} // namespace Firebolt::Accessibility::JsonData
