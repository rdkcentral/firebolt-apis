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

#include <string>

namespace FireboltSDK::JSON
{
class String : public WPEFramework::Core::JSON::String
{
    using Base = WPEFramework::Core::JSON::String;

public:
    String() : Base(), value_() {}
    String(const char value[]) : Base(value), value_(value) {}
    String& operator=(const char rhs[])
    {
        Base::operator=(rhs);
        value_ = rhs;
        return (*this);
    }
    String& operator=(const string rhs)
    {
        Base::operator=(rhs);
        value_ = rhs;
        return (*this);
    }

public:
    const std::string& Value() const
    {
        value_ = Base::Value();
        return value_;
    }

private:
    mutable std::string value_;
};
} // namespace FireboltSDK::JSON
