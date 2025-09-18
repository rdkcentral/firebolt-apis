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

#include "jsondata_device_types.h"

namespace Firebolt::Device::JsonData
{

HDRFormatMap::HDRFormatMap() : WPEFramework::Core::JSON::Container()
{
    Add(_T("hdr10"), &isHdr10_);
    Add(_T("hdr10Plus"), &isHdr10Plus_);
    Add(_T("dolbyVision"), &isDolbyVision_);
    Add(_T("hlg"), &isHlg_);
}

HDRFormatMap::HDRFormatMap(const HDRFormatMap& other) : HDRFormatMap()
{
    isHdr10_ = other.isHdr10_;
    isHdr10Plus_ = other.isHdr10Plus_;
    isDolbyVision_ = other.isDolbyVision_;
    isHlg_ = other.isHlg_;
}

HDRFormatMap& HDRFormatMap::operator=(const HDRFormatMap& other)
{
    isHdr10_ = other.isHdr10_;
    isHdr10Plus_ = other.isHdr10Plus_;
    isDolbyVision_ = other.isDolbyVision_;
    isHlg_ = other.isHlg_;
    return *this;
}

::Firebolt::Device::HDRFormatMap HDRFormatMap::Value()
{
    return ::Firebolt::Device::HDRFormatMap{isHdr10_.Value(), isHdr10Plus_.Value(), isDolbyVision_.Value(),
                                            isHlg_.Value()};
}

} // namespace Firebolt::Device::JsonData

namespace WPEFramework
{

/* NetworkState The type of network that is currently active */
ENUM_CONVERSION_BEGIN(Firebolt::Device::NetworkState){Firebolt::Device::NetworkState::CONNECTED, _T("connected")},
    {Firebolt::Device::NetworkState::DISCONNECTED, _T("disconnected")},
    ENUM_CONVERSION_END(Firebolt::Device::NetworkState)

    /* NetworkType The type of network that is currently active */
    ENUM_CONVERSION_BEGIN(Firebolt::Device::NetworkType){Firebolt::Device::NetworkType::WIFI, _T("wifi")},
    {Firebolt::Device::NetworkType::ETHERNET, _T("ethernet")}, {Firebolt::Device::NetworkType::HYBRID, _T("hybrid")},
    ENUM_CONVERSION_END(Firebolt::Device::NetworkType)

} // namespace WPEFramework
