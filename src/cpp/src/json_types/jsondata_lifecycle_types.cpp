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

#include "jsondata_lifecycle_types.h"

namespace Firebolt::Lifecycle::JsonData
{
LifecycleEvent::LifecycleEvent() : WPEFramework::Core::JSON::Container()
{
    Add(_T("state"), &state_);
    Add(_T("previous"), &previous_);
    Add(_T("source"), &source_);
}

LifecycleEvent::LifecycleEvent(const LifecycleEvent& other) : LifecycleEvent()
{
    state_ = other.state_;
    previous_ = other.previous_;
    source_ = other.source_;
}

LifecycleEvent& LifecycleEvent::operator=(const LifecycleEvent& other)
{
    state_ = other.state_;
    previous_ = other.previous_;
    source_ = other.source_;
    return *this;
}

::Firebolt::Lifecycle::LifecycleEvent LifecycleEvent::Value()
{
    ::Firebolt::Lifecycle::LifecycleEvent result{state_, previous_, std::nullopt};
    if (source_.IsSet())
    {
        result.source = source_;
    }
    return result;
}
} // namespace Firebolt::Lifecycle::JsonData

namespace WPEFramework
{
ENUM_CONVERSION_BEGIN(Firebolt::Lifecycle::CloseReason){Firebolt::Lifecycle::CloseReason::REMOTE_BUTTON,
                                                        _T("remoteButton")},
    {Firebolt::Lifecycle::CloseReason::USER_EXIT, _T("userExit")}, {Firebolt::Lifecycle::CloseReason::DONE, _T("done")},
    {Firebolt::Lifecycle::CloseReason::ERROR, _T("error")},
    ENUM_CONVERSION_END(Firebolt::Lifecycle::CloseReason)

        ENUM_CONVERSION_BEGIN(Firebolt::Lifecycle::LifecycleState){Firebolt::Lifecycle::LifecycleState::INITIALIZING,
                                                                   _T("initializing")},
    {Firebolt::Lifecycle::LifecycleState::INACTIVE, _T("inactive")},
    {Firebolt::Lifecycle::LifecycleState::FOREGROUND, _T("foreground")},
    {Firebolt::Lifecycle::LifecycleState::BACKGROUND, _T("background")},
    {Firebolt::Lifecycle::LifecycleState::UNLOADING, _T("unloading")},
    {Firebolt::Lifecycle::LifecycleState::SUSPENDED, _T("suspended")},
    ENUM_CONVERSION_END(Firebolt::Lifecycle::LifecycleState)

        ENUM_CONVERSION_BEGIN(Firebolt::Lifecycle::LifecycleEventSource){Firebolt::Lifecycle::LifecycleEventSource::VOICE,
                                                                         _T("voice")},
    {Firebolt::Lifecycle::LifecycleEventSource::REMOTE, _T("remote")},
    ENUM_CONVERSION_END(Firebolt::Lifecycle::LifecycleEventSource)
} // namespace WPEFramework