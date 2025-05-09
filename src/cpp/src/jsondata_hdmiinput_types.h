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
#include "IModule.h"
#include "hdmiinput.h"
#include "jsondata_types.h"

namespace Firebolt::HDMIInput::JsonData
{
using EDIDVersion = WPEFramework::Core::JSON::EnumType<EDIDVersion>;
using HDMISignalStatus = WPEFramework::Core::JSON::EnumType<HDMISignalStatus>;

// Types
class SignalChangedInfo : public WPEFramework::Core::JSON::Container
{
public:
    ~SignalChangedInfo() override = default;
    SignalChangedInfo();
    SignalChangedInfo(const SignalChangedInfo& other);
    SignalChangedInfo& operator=(const SignalChangedInfo& other);
    ::Firebolt::HDMIInput::SignalChangedInfo Value();

private:
    FireboltSDK::JSON::String port_;
    HDMISignalStatus signal_;
};

class AutoLowLatencyModeSignalChangedInfo : public WPEFramework::Core::JSON::Container
{
public:
    ~AutoLowLatencyModeSignalChangedInfo() override = default;
    AutoLowLatencyModeSignalChangedInfo();
    AutoLowLatencyModeSignalChangedInfo(const AutoLowLatencyModeSignalChangedInfo& other);
    AutoLowLatencyModeSignalChangedInfo& operator=(const AutoLowLatencyModeSignalChangedInfo& other);
    ::Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo Value();

private:
    FireboltSDK::JSON::String port_;
    WPEFramework::Core::JSON::Boolean isAutoLowLatencyModeSignalled_;
};

class HDMIInputPort : public WPEFramework::Core::JSON::Container
{
public:
    ~HDMIInputPort() override = default;
    HDMIInputPort();
    HDMIInputPort(const HDMIInputPort& other);
    HDMIInputPort& operator=(const HDMIInputPort& other);
    ::Firebolt::HDMIInput::HDMIInputPort Value();

private:
    FireboltSDK::JSON::String port_;
    WPEFramework::Core::JSON::Boolean isConnected_;
    HDMISignalStatus signal_;
    WPEFramework::Core::JSON::Boolean isArcCapable_;
    WPEFramework::Core::JSON::Boolean isArcConnected_;
    EDIDVersion edidVersion_;
    WPEFramework::Core::JSON::Boolean isAutoLowLatencyModeCapable_;
    WPEFramework::Core::JSON::Boolean isAutoLowLatencyModeSignalled_;
};

class AutoLowLatencyModeCapableChangedInfo : public WPEFramework::Core::JSON::Container
{
public:
    ~AutoLowLatencyModeCapableChangedInfo() override = default;
    AutoLowLatencyModeCapableChangedInfo();
    AutoLowLatencyModeCapableChangedInfo(const AutoLowLatencyModeCapableChangedInfo& other);
    AutoLowLatencyModeCapableChangedInfo& operator=(const AutoLowLatencyModeCapableChangedInfo& other);
    Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo Value();

private:
    FireboltSDK::JSON::String port_;
    WPEFramework::Core::JSON::Boolean isEnabled_;
};

class ConnectionChangedInfo : public WPEFramework::Core::JSON::Container
{
public:
    ~ConnectionChangedInfo() override = default;
    ConnectionChangedInfo();
    ConnectionChangedInfo(const ConnectionChangedInfo& other);
    ConnectionChangedInfo& operator=(const ConnectionChangedInfo& other);
    Firebolt::HDMIInput::ConnectionChangedInfo Value();

private:
    FireboltSDK::JSON::String port_;
    WPEFramework::Core::JSON::Boolean isConnected_;
};
} // namespace Firebolt::HDMIInput::JsonData
