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
#include "hdmiinput.h"

namespace Firebolt::HDMIInput::JsonData
{
FireboltSDK::JSON::EnumType<::Firebolt::HDMIInput::EDIDVersion> const EDIDVersionEnum({
    { "1.4", ::Firebolt::HDMIInput::EDIDVersion::V1_4 },
    { "2.0", ::Firebolt::HDMIInput::EDIDVersion::V2_0 },
    { "unknown", ::Firebolt::HDMIInput::EDIDVersion::UNKNOWN },
});

FireboltSDK::JSON::EnumType<::Firebolt::HDMIInput::HDMISignalStatus> const HDMISignalStatusEnum({
    { "none", ::Firebolt::HDMIInput::HDMISignalStatus::NONE },
    { "stable", ::Firebolt::HDMIInput::HDMISignalStatus::STABLE },
    { "unstable", ::Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE },
    { "unsupported", ::Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED },
    { "unknown", ::Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN },
});

class EDIDVersionJson : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::HDMIInput::EDIDVersion>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        value_ = EDIDVersionEnum.at(json);
    }
    ::Firebolt::HDMIInput::EDIDVersion Value() const override
    {
        return value_;
    }
private:
    ::Firebolt::HDMIInput::EDIDVersion value_;
};

// Types
class SignalChangedInfo : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::HDMIInput::SignalChangedInfo>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        port = json["port"].get<std::string>();
        signal = HDMISignalStatusEnum.at(json["signal"]);
    }
    ::Firebolt::HDMIInput::SignalChangedInfo Value() const override
    {
        return ::Firebolt::HDMIInput::SignalChangedInfo{port, signal};
    }
private:
    std::string port;
    HDMISignalStatus signal;
};

class AutoLowLatencyModeSignalChangedInfo : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        port_ = json["port"].get<std::string>();
        isAutoLowLatencyModeSignalled_ = json["autoLowLatencyModeSignalled"].get<bool>();
    }
    ::Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo Value() const override
    {
        return ::Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo{port_, isAutoLowLatencyModeSignalled_};
    }
private:
    std::string port_;
    bool isAutoLowLatencyModeSignalled_;
};

class HDMIInputPort : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::HDMIInput::HDMIInputPort>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        port_ = json["port"].get<std::string>();
        isConnected_ = json["connected"].get<bool>();
        signal_ = HDMISignalStatusEnum.at(json["signal"]);
        isArcCapable_ = json["arcCapable"].get<bool>();
        isArcConnected_ = json["arcConnected"].get<bool>();
        edidVersion_ = EDIDVersionEnum.at(json["edidVersion"]);
        isAutoLowLatencyModeCapable_ = json["autoLowLatencyModeCapable"].get<bool>();
        isAutoLowLatencyModeSignalled_ = json["autoLowLatencyModeSignalled"].get<bool>();
    }
    ::Firebolt::HDMIInput::HDMIInputPort Value() const override
    {
        return ::Firebolt::HDMIInput::HDMIInputPort{port_, isConnected_, signal_, isArcCapable_, isArcConnected_, edidVersion_, isAutoLowLatencyModeCapable_, isAutoLowLatencyModeSignalled_};
    }
private:
    std::string port_;
    bool isConnected_;
    HDMISignalStatus signal_;
    bool isArcCapable_;
    bool isArcConnected_;
    EDIDVersion edidVersion_;
    bool isAutoLowLatencyModeCapable_;
    bool isAutoLowLatencyModeSignalled_;
};

class AutoLowLatencyModeCapableChangedInfo : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        port_ = json["port"].get<std::string>();
        isEnabled_ = json["enabled"].get<bool>();
    }
    ::Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo Value() const override
    {
        return ::Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo{port_, isEnabled_};
    }
private:
    std::string port_;
    bool isEnabled_;
};

class ConnectionChangedInfo : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::HDMIInput::ConnectionChangedInfo>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        port_ = json["port"].get<std::string>();
        isConnected_ = json["connected"].get<bool>();
    }
    ::Firebolt::HDMIInput::ConnectionChangedInfo Value() const override
    {
        return ::Firebolt::HDMIInput::ConnectionChangedInfo{port_, isConnected_};
    }
private:
    std::optional<std::string> port_;
    std::optional<bool> isConnected_;
};
} // namespace Firebolt::HDMIInput::JsonData
