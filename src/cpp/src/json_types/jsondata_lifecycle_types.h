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

#include "firebolt/lifecycle.h"
#include <firebolt/json_types.h>

namespace Firebolt::Lifecycle::JsonData
{

inline const Firebolt::JSON::EnumType<::Firebolt::Lifecycle::CloseType> CloseReasonEnum({
    {"deactivate", ::Firebolt::Lifecycle::CloseType::DEACTIVATE},
    {"unload", ::Firebolt::Lifecycle::CloseType::UNLOAD},
    {"kill_reload", ::Firebolt::Lifecycle::CloseType::KILL_RELOAD},
    {"kill_reactivate", ::Firebolt::Lifecycle::CloseType::KILL_REACTIVATE},
});

inline const Firebolt::JSON::EnumType<::Firebolt::Lifecycle::LifecycleState> LifecycleStateEnum({
    {"initializing", ::Firebolt::Lifecycle::LifecycleState::INITIALIZING},
    {"active", ::Firebolt::Lifecycle::LifecycleState::ACTIVE},
    {"paused", ::Firebolt::Lifecycle::LifecycleState::PAUSED},
    {"suspended", ::Firebolt::Lifecycle::LifecycleState::SUSPENDED},
    {"hibernated", ::Firebolt::Lifecycle::LifecycleState::HIBERNATED},
    {"terminating", ::Firebolt::Lifecycle::LifecycleState::TERMINATING},
});

class LifecycleState : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Lifecycle::LifecycleState>
{
public:
    void fromJson(const nlohmann::json& json) override { state_ = LifecycleStateEnum.at(json.get<std::string>()); }
    ::Firebolt::Lifecycle::LifecycleState value() const override { return state_; }

private:
    ::Firebolt::Lifecycle::LifecycleState state_;
};

class StateChange : public Firebolt::JSON::NL_Json_Basic<::Firebolt::Lifecycle::StateChange>
{
public:
    void fromJson(const nlohmann::json& json) override
    {
        oldState_ = LifecycleStateEnum.at(json["oldState"]);
        newState_ = LifecycleStateEnum.at(json["newState"]);
    }
    ::Firebolt::Lifecycle::StateChange value() const override
    {
        return ::Firebolt::Lifecycle::StateChange{oldState_, newState_};
    }

private:
    ::Firebolt::Lifecycle::LifecycleState oldState_;
    ::Firebolt::Lifecycle::LifecycleState newState_;
};

} // namespace Firebolt::Lifecycle::JsonData
