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

#include "device.h"

#include <algorithm>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <types/json_types.h>

namespace Firebolt::Device::JsonData
{

inline FireboltSDK::JSON::EnumType<::Firebolt::Device::NetworkState> const NetworkStateEnum({
    { "connected",    ::Firebolt::Device::NetworkState::CONNECTED },
    { "disconnected", ::Firebolt::Device::NetworkState::DISCONNECTED },
});

inline FireboltSDK::JSON::EnumType<::Firebolt::Device::NetworkType> const NetworkTypeEnum({
    { "wifi",     ::Firebolt::Device::NetworkType::WIFI },
    { "ethernet", ::Firebolt::Device::NetworkType::ETHERNET },
    { "hybrid",   ::Firebolt::Device::NetworkType::HYBRID },
});

class SemanticVersion : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::SemanticVersion>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        major = json["major"].get<int32_t>();
        minor = json["minor"].get<int32_t>();
        patch = json["patch"].get<int32_t>();
        if (json.contains("readable"))
        {
            readable = json["readable"].get<std::string>();
        }
    }

    ::Firebolt::Device::SemanticVersion Value() const override
    {
        return ::Firebolt::Device::SemanticVersion{major, minor, patch, readable}; 
    }

private:
    int32_t major = 0;
    int32_t minor = 0;
    int32_t patch = 0;
    std::string readable = "";
};

class DeviceVersion : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::DeviceVersion>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        if (json.contains("sdk"))
        {
            sdk_.FromJson(json["sdk"]);
        }
        if (json.contains("api"))
        {
            api_.FromJson(json["api"]);
        }
        if (json.contains("firmware"))
        {
            firmware_.FromJson(json["firmware"]);
        }
        if (json.contains("os"))
        {
            os_.FromJson(json["os"]);
        }
        if (json.contains("debug"))
        {
            debug_ = to_string(json["debug"]);
        }
    }

    ::Firebolt::Device::DeviceVersion Value() const override
    {
        return ::Firebolt::Device::DeviceVersion{sdk_.Value(), api_.Value(), firmware_.Value(), os_.Value(), debug_};
    }

private:
    SemanticVersion sdk_;
    SemanticVersion api_;
    SemanticVersion firmware_;
    SemanticVersion os_;
    std::string debug_{""};
};

class AudioProfiles : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::AudioProfiles>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        isStereo_ = json["stereo"].get<bool>();
        isDolbyDigital5_1_ = json["dolbyDigital5.1"].get<bool>();
        isDolbyDigital5_1_plus_ = json["dolbyDigital5.1+"].get<bool>();
        isDolbyAtmos_ = json["dolbyAtmos"].get<bool>();
    }
    ::Firebolt::Device::AudioProfiles Value() const override
    {
        return ::Firebolt::Device::AudioProfiles{isStereo_, isDolbyDigital5_1_, isDolbyDigital5_1_plus_, isDolbyAtmos_};
    }
private:
    bool isStereo_;
    bool isDolbyDigital5_1_;
    bool isDolbyDigital5_1_plus_;
    bool isDolbyAtmos_;
};

class HDCPVersionMap : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::HDCPVersionMap>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        isHdcp1_4_ = json["hdcp1.4"].get<bool>();
        isHdcp2_2_ = json["hdcp2.2"].get<bool>();
    }
    ::Firebolt::Device::HDCPVersionMap Value() const override
    {
        return ::Firebolt::Device::HDCPVersionMap{isHdcp1_4_, isHdcp2_2_};
    }
private:
    bool isHdcp1_4_;
    bool isHdcp2_2_;
};

class HDRFormatMap : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::HDRFormatMap>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        isHdr10_ = json["hdr10"].get<bool>();
        isHdr10Plus_ = json["hdr10Plus"].get<bool>();
        isDolbyVision_ = json["dolbyVision"].get<bool>();
        isHlg_ = json["hlg"].get<bool>();
    }
    ::Firebolt::Device::HDRFormatMap Value() const override
    {
        return ::Firebolt::Device::HDRFormatMap{isHdr10_, isHdr10Plus_, isDolbyVision_, isHlg_};
    }
private:
    bool isHdr10_;
    bool isHdr10Plus_;
    bool isDolbyVision_;
    bool isHlg_;
};

class NetworkInfoResult : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Device::NetworkInfoResult>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        state_ = NetworkStateEnum.at(json["state"]);
        type_ = NetworkTypeEnum.at(json["type"]);
    }
    ::Firebolt::Device::NetworkInfoResult Value() const override
    {
        return ::Firebolt::Device::NetworkInfoResult{state_, type_};
    }
private:
    NetworkState state_;
    NetworkType type_;
};
} // namespace Firebolt::Device::JsonData
