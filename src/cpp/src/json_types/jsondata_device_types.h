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

#include "FireboltSDK.h"
#include "device.h"

namespace Firebolt::Device::JsonData
{
using NetworkState = WPEFramework::Core::JSON::EnumType<::Firebolt::Device::NetworkState>;
using NetworkType = WPEFramework::Core::JSON::EnumType<::Firebolt::Device::NetworkType>;

class SemanticVersion : public WPEFramework::Core::JSON::Container
{
public:
    ~SemanticVersion() override = default;
    SemanticVersion();
    SemanticVersion(const SemanticVersion& other);
    SemanticVersion& operator=(const SemanticVersion& other);
    ::Firebolt::Device::SemanticVersion Value();

    WPEFramework::Core::JSON::DecSInt32 major;
    WPEFramework::Core::JSON::DecSInt32 minor;
    WPEFramework::Core::JSON::DecSInt32 patch;
    FireboltSDK::JSON::String readable;
};

class DeviceVersion : public WPEFramework::Core::JSON::Container
{
public:
    ~DeviceVersion() override = default;
    DeviceVersion();
    DeviceVersion(const DeviceVersion& other);
    DeviceVersion& operator=(const DeviceVersion& other);
    ::Firebolt::Device::DeviceVersion Value();

private:
    SemanticVersion sdk_;
    SemanticVersion api_;
    SemanticVersion firmware_;
    SemanticVersion os_;
    FireboltSDK::JSON::String debug_;
};

class AudioProfiles : public WPEFramework::Core::JSON::Container
{
public:
    ~AudioProfiles() override = default;
    AudioProfiles();
    AudioProfiles(const AudioProfiles& other);
    AudioProfiles& operator=(const AudioProfiles& other);
    ::Firebolt::Device::AudioProfiles Value() const;

private:
    WPEFramework::Core::JSON::Boolean isStereo_;
    WPEFramework::Core::JSON::Boolean isDolbyDigital5_1_;
    WPEFramework::Core::JSON::Boolean isDolbyDigital5_1_plus_;
    WPEFramework::Core::JSON::Boolean isDolbyAtmos_;
};

class HDCPVersionMap : public WPEFramework::Core::JSON::Container
{
public:
    ~HDCPVersionMap() override = default;
    HDCPVersionMap();
    HDCPVersionMap(const HDCPVersionMap& other);
    HDCPVersionMap& operator=(const HDCPVersionMap& other);
    ::Firebolt::Device::HDCPVersionMap Value();

private:
    WPEFramework::Core::JSON::Boolean isHdcp1_4_;
    WPEFramework::Core::JSON::Boolean isHdcp2_2_;
};

class HDRFormatMap : public WPEFramework::Core::JSON::Container
{
public:
    ~HDRFormatMap() override = default;
    HDRFormatMap();
    HDRFormatMap(const HDRFormatMap& other);
    HDRFormatMap& operator=(const HDRFormatMap& other);
    ::Firebolt::Device::HDRFormatMap Value();

private:
    WPEFramework::Core::JSON::Boolean isHdr10_;
    WPEFramework::Core::JSON::Boolean isHdr10Plus_;
    WPEFramework::Core::JSON::Boolean isDolbyVision_;
    WPEFramework::Core::JSON::Boolean isHlg_;
};

class NetworkInfoResult : public WPEFramework::Core::JSON::Container
{
public:
    ~NetworkInfoResult() override = default;
    NetworkInfoResult();
    NetworkInfoResult(const NetworkInfoResult& other);
    NetworkInfoResult& operator=(const NetworkInfoResult& other);
    ::Firebolt::Device::NetworkInfoResult Value();

private:
    NetworkState state_;
    NetworkType type_;
};
} // namespace Firebolt::Device::JsonData
