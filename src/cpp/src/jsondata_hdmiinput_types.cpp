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

#include "jsondata_hdmiinput_types.h"

namespace Firebolt::HDMIInput::JsonData
{
SignalChangedInfo::SignalChangedInfo() : WPEFramework::Core::JSON::Container()
{
    Add(_T("port"), &port_);
    Add(_T("signal"), &signal_);
}

SignalChangedInfo::SignalChangedInfo(const SignalChangedInfo& other) : SignalChangedInfo()
{
    port_ = other.port_;
    signal_ = other.signal_;
}

SignalChangedInfo& SignalChangedInfo::operator=(const SignalChangedInfo& other)
{
    port_ = other.port_;
    signal_ = other.signal_;
    return *this;
}

::Firebolt::HDMIInput::SignalChangedInfo SignalChangedInfo::Value()
{
    return ::Firebolt::HDMIInput::SignalChangedInfo{port_, signal_};
}

AutoLowLatencyModeSignalChangedInfo::AutoLowLatencyModeSignalChangedInfo() : WPEFramework::Core::JSON::Container()
{
    Add(_T("port"), &port_);
    Add(_T("autoLowLatencyModeSignalled"), &isAutoLowLatencyModeSignalled_);
}

AutoLowLatencyModeSignalChangedInfo::AutoLowLatencyModeSignalChangedInfo(const AutoLowLatencyModeSignalChangedInfo& other)
    : AutoLowLatencyModeSignalChangedInfo()
{
    port_ = other.port_;
    isAutoLowLatencyModeSignalled_ = other.isAutoLowLatencyModeSignalled_;
}

AutoLowLatencyModeSignalChangedInfo&
AutoLowLatencyModeSignalChangedInfo::operator=(const AutoLowLatencyModeSignalChangedInfo& other)
{
    port_ = other.port_;
    isAutoLowLatencyModeSignalled_ = other.isAutoLowLatencyModeSignalled_;
    return *this;
}

::Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo AutoLowLatencyModeSignalChangedInfo::Value()
{
    ::Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo result;
    if (port_.IsSet())
    {
        result.port = port_;
    }
    if (isAutoLowLatencyModeSignalled_.IsSet())
    {
        result.autoLowLatencyModeSignalled = isAutoLowLatencyModeSignalled_;
    }
    return result;
}

HDMIInputPort::HDMIInputPort() : WPEFramework::Core::JSON::Container()
{
    Add(_T("port"), &port_);
    Add(_T("connected"), &isConnected_);
    Add(_T("signal"), &signal_);
    Add(_T("arcCapable"), &isArcCapable_);
    Add(_T("arcConnected"), &isArcConnected_);
    Add(_T("edidVersion"), &edidVersion_);
    Add(_T("autoLowLatencyModeCapable"), &isAutoLowLatencyModeCapable_);
    Add(_T("autoLowLatencyModeSignalled"), &isAutoLowLatencyModeSignalled_);
}

HDMIInputPort::HDMIInputPort(const HDMIInputPort& other) : HDMIInputPort()
{
    port_ = other.port_;
    isConnected_ = other.isConnected_;
    signal_ = other.signal_;
    isArcCapable_ = other.isArcCapable_;
    isArcConnected_ = other.isArcConnected_;
    edidVersion_ = other.edidVersion_;
    isAutoLowLatencyModeCapable_ = other.isAutoLowLatencyModeCapable_;
    isAutoLowLatencyModeSignalled_ = other.isAutoLowLatencyModeSignalled_;
}

HDMIInputPort& HDMIInputPort::operator=(const HDMIInputPort& other)
{
    port_ = other.port_;
    isConnected_ = other.isConnected_;
    signal_ = other.signal_;
    isArcCapable_ = other.isArcCapable_;
    isArcConnected_ = other.isArcConnected_;
    edidVersion_ = other.edidVersion_;
    isAutoLowLatencyModeCapable_ = other.isAutoLowLatencyModeCapable_;
    isAutoLowLatencyModeSignalled_ = other.isAutoLowLatencyModeSignalled_;
    return *this;
}

::Firebolt::HDMIInput::HDMIInputPort HDMIInputPort::Value()
{
    return ::Firebolt::HDMIInput::HDMIInputPort{port_,
                                                isConnected_,
                                                signal_,
                                                isArcCapable_,
                                                isArcConnected_,
                                                edidVersion_,
                                                isAutoLowLatencyModeCapable_,
                                                isAutoLowLatencyModeSignalled_};
}

AutoLowLatencyModeCapableChangedInfo::AutoLowLatencyModeCapableChangedInfo() : WPEFramework::Core::JSON::Container()
{
    Add(_T("port"), &port_);
    Add(_T("enabled"), &isEnabled_);
}

AutoLowLatencyModeCapableChangedInfo::AutoLowLatencyModeCapableChangedInfo(const AutoLowLatencyModeCapableChangedInfo& other)
    : AutoLowLatencyModeCapableChangedInfo()
{
    port_ = other.port_;
    isEnabled_ = other.isEnabled_;
}

AutoLowLatencyModeCapableChangedInfo&
AutoLowLatencyModeCapableChangedInfo::operator=(const AutoLowLatencyModeCapableChangedInfo& other)
{
    port_ = other.port_;
    isEnabled_ = other.isEnabled_;
    return *this;
}

Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo AutoLowLatencyModeCapableChangedInfo::Value()
{
    return Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo{port_, isEnabled_};
}

ConnectionChangedInfo::ConnectionChangedInfo() : WPEFramework::Core::JSON::Container()
{
    Add(_T("port"), &port_);
    Add(_T("connected"), &isConnected_);
}

ConnectionChangedInfo::ConnectionChangedInfo(const ConnectionChangedInfo& other) : ConnectionChangedInfo()
{
    port_ = other.port_;
    isConnected_ = other.isConnected_;
}

ConnectionChangedInfo& ConnectionChangedInfo::operator=(const ConnectionChangedInfo& other)
{
    port_ = other.port_;
    isConnected_ = other.isConnected_;
    return *this;
}

Firebolt::HDMIInput::ConnectionChangedInfo ConnectionChangedInfo::Value()
{
    Firebolt::HDMIInput::ConnectionChangedInfo result;
    if (port_.IsSet())
    {
        result.port = port_;
    }
    if (isConnected_.IsSet())
    {
        result.connected = isConnected_;
    }
    return result;
}
} // namespace Firebolt::HDMIInput::JsonData

namespace WPEFramework
{
/* EDIDVersion  */
ENUM_CONVERSION_BEGIN(Firebolt::HDMIInput::EDIDVersion){Firebolt::HDMIInput::EDIDVersion::V1_4, _T("1.4")},
    {Firebolt::HDMIInput::EDIDVersion::V2_0, _T("2.0")}, {Firebolt::HDMIInput::EDIDVersion::UNKNOWN, _T("unknown")},
    ENUM_CONVERSION_END(Firebolt::HDMIInput::EDIDVersion)

    /* HDMISignalStatus  */
    ENUM_CONVERSION_BEGIN(Firebolt::HDMIInput::HDMISignalStatus){Firebolt::HDMIInput::HDMISignalStatus::NONE,
                                                                 _T("none")},
    {Firebolt::HDMIInput::HDMISignalStatus::STABLE, _T("stable")},
    {Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE, _T("unstable")},
    {Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED, _T("unsupported")},
    {Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN, _T("unknown")},
    ENUM_CONVERSION_END(Firebolt::HDMIInput::HDMISignalStatus)

} // namespace WPEFramework
