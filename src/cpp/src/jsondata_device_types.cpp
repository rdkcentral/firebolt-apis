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

::Firebolt::Device::SemanticVersion SemanticVersion::Value()
{
    return ::Firebolt::Device::SemanticVersion{major, minor, patch, readable};
}

DeviceVersion::DeviceVersion() : WPEFramework::Core::JSON::Container()
{
    Add(_T("sdk"), &sdk_);
    Add(_T("api"), &api_);
    Add(_T("firmware"), &firmware_);
    Add(_T("os"), &os_);
    Add(_T("debug"), &debug_);
}

DeviceVersion::DeviceVersion(const DeviceVersion& other) : DeviceVersion()
{
    sdk_ = other.sdk_;
    api_ = other.api_;
    firmware_ = other.firmware_;
    os_ = other.os_;
    debug_ = other.debug_;
}

DeviceVersion& DeviceVersion::operator=(const DeviceVersion& other)
{
    sdk_ = other.sdk_;
    api_ = other.api_;
    firmware_ = other.firmware_;
    os_ = other.os_;
    debug_ = other.debug_;
    return *this;
}

::Firebolt::Device::DeviceVersion DeviceVersion::Value()
{
    std::string version{};
    if (!IsSet())
    {
        Clear();
    }
    if (!sdk_.IsSet())
    {
        sdk_.Clear();
    }
    sdk_.major = static_cast<int32_t>(1);
    sdk_.minor = static_cast<int32_t>(5);
    sdk_.patch = static_cast<int32_t>(0);
    sdk_.readable = "Firebolt Core SDK 1.5.0-next.18";
    return ::Firebolt::Device::DeviceVersion{sdk_.Value(), api_.Value(), firmware_.Value(), os_.Value(), debug_};
}

AudioProfiles::AudioProfiles() : WPEFramework::Core::JSON::Container()
{
    Add(_T("stereo"), &isStereo_);
    Add(_T("dolbyDigital5.1"), &isDolbyDigital5_1_);
    Add(_T("dolbyDigital5.1+"), &isDolbyDigital5_1_plus_);
    Add(_T("dolbyAtmos"), &isDolbyAtmos_);
}

AudioProfiles::AudioProfiles(const AudioProfiles& other) : AudioProfiles()
{
    isStereo_ = other.isStereo_;
    isDolbyDigital5_1_ = other.isDolbyDigital5_1_;
    isDolbyDigital5_1_plus_ = other.isDolbyDigital5_1_plus_;
    isDolbyAtmos_ = other.isDolbyAtmos_;
}

AudioProfiles& AudioProfiles::operator=(const AudioProfiles& other)
{
    isStereo_ = other.isStereo_;
    isDolbyDigital5_1_ = other.isDolbyDigital5_1_;
    isDolbyDigital5_1_plus_ = other.isDolbyDigital5_1_plus_;
    isDolbyAtmos_ = other.isDolbyAtmos_;
    return *this;
}

::Firebolt::Device::AudioProfiles AudioProfiles::Value() const
{
    return ::Firebolt::Device::AudioProfiles{isStereo_.Value(), isDolbyDigital5_1_.Value(),
                                             isDolbyDigital5_1_plus_.Value(), isDolbyAtmos_.Value()};
}

HDCPVersionMap::HDCPVersionMap() : WPEFramework::Core::JSON::Container()
{
    Add(_T("hdcp1.4"), &isHdcp1_4_);
    Add(_T("hdcp2.2"), &isHdcp2_2_);
}

HDCPVersionMap::HDCPVersionMap(const HDCPVersionMap& other) : HDCPVersionMap()
{
    isHdcp1_4_ = other.isHdcp1_4_;
    isHdcp2_2_ = other.isHdcp2_2_;
}

HDCPVersionMap& HDCPVersionMap::operator=(const HDCPVersionMap& other)
{
    isHdcp1_4_ = other.isHdcp1_4_;
    isHdcp2_2_ = other.isHdcp2_2_;
    return *this;
}

::Firebolt::Device::HDCPVersionMap HDCPVersionMap::Value()
{
    return ::Firebolt::Device::HDCPVersionMap{isHdcp1_4_.Value(), isHdcp2_2_.Value()};
}

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

NetworkInfoResult::NetworkInfoResult() : WPEFramework::Core::JSON::Container()
{
    Add(_T("state"), &state_);
    Add(_T("type"), &type_);
}

NetworkInfoResult::NetworkInfoResult(const NetworkInfoResult& other) : NetworkInfoResult()
{
    state_ = other.state_;
    type_ = other.type_;
}

NetworkInfoResult& NetworkInfoResult::operator=(const NetworkInfoResult& other)
{
    state_ = other.state_;
    type_ = other.type_;
    return (*this);
}

::Firebolt::Device::NetworkInfoResult NetworkInfoResult::Value()
{
    return ::Firebolt::Device::NetworkInfoResult{state_.Value(), type_.Value()};
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
