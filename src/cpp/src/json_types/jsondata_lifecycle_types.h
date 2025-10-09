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

#include "lifecycle.h"
#include <TypesPriv.h>

namespace Firebolt::Lifecycle::JsonData
{

inline FireboltSDK::JSON::EnumType<::Firebolt::Lifecycle::CloseReason> const CloseReasonEnum({
    { "remoteButton", ::Firebolt::Lifecycle::CloseReason::REMOTE_BUTTON },
    { "userExit", ::Firebolt::Lifecycle::CloseReason::USER_EXIT },
    { "done", ::Firebolt::Lifecycle::CloseReason::DONE },
    { "error", ::Firebolt::Lifecycle::CloseReason::ERROR },
});

inline FireboltSDK::JSON::EnumType<::Firebolt::Lifecycle::LifecycleState> const LifecycleStateEnum({
    { "initializing", ::Firebolt::Lifecycle::LifecycleState::INITIALIZING },
    { "inactive", ::Firebolt::Lifecycle::LifecycleState::INACTIVE },
    { "foreground", ::Firebolt::Lifecycle::LifecycleState::FOREGROUND },
    { "background", ::Firebolt::Lifecycle::LifecycleState::BACKGROUND },
    { "unloading", ::Firebolt::Lifecycle::LifecycleState::UNLOADING },
    { "suspended", ::Firebolt::Lifecycle::LifecycleState::SUSPENDED },
});

inline FireboltSDK::JSON::EnumType<::Firebolt::Lifecycle::LifecycleEventSource> const LifecycleEventSourceEnum({
    { "voice", ::Firebolt::Lifecycle::LifecycleEventSource::VOICE },
    { "remote", ::Firebolt::Lifecycle::LifecycleEventSource::REMOTE },
});

class LifecycleEvent : public FireboltSDK::JSON::NL_Json_Basic<::Firebolt::Lifecycle::LifecycleEvent>
{
public:
    void FromJson(const nlohmann::json& json) override {
        state_ = LifecycleStateEnum.at(json["state"]);
        previous_ = LifecycleStateEnum.at(json["previous"]);
        if (json.contains("source"))
        {
            source_ = LifecycleEventSourceEnum.at(json["source"]);
        }
    }
    ::Firebolt::Lifecycle::LifecycleEvent Value() const override
    {
        ::Firebolt::Lifecycle::LifecycleEvent result{state_, previous_, std::nullopt};
        if (source_.has_value())
        {
            result.source = source_.value();
        }
        return result;
    }
private:
    LifecycleState state_;
    LifecycleState previous_;
    std::optional<LifecycleEventSource> source_;
};
} // namespace Firebolt::Lifecycle::JsonData
