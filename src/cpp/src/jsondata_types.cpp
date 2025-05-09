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

#include "jsondata_types.h"

namespace Firebolt::Types::JsonData
{
SemanticVersion::SemanticVersion() : WPEFramework::Core::JSON::Container()
{
    Add(_T("major"), &major);
    Add(_T("minor"), &minor);
    Add(_T("patch"), &patch);
    Add(_T("readable"), &readable);
}

SemanticVersion::SemanticVersion(const SemanticVersion& other) : SemanticVersion()
{
    major = other.major;
    minor = other.minor;
    patch = other.patch;
    readable = other.readable;
}

SemanticVersion& SemanticVersion::operator=(const SemanticVersion& other)
{
    major = other.major;
    minor = other.minor;
    patch = other.patch;
    readable = other.readable;
    return *this;
}
} // namespace Firebolt::Types::JsonData
