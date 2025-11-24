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

#include "lifecycle_impl.h"
#include "jsondata_lifecycle_types.h"
#include <cctype>
#include <nlohmann/json.hpp>
#include <string>

using namespace Firebolt::Helpers;

namespace Firebolt::Lifecycle
{
LifecycleImpl::LifecycleImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper), subscriptionManager_(helper, this)
{
}

LifecycleImpl::~LifecycleImpl()
{
}

Result<void> LifecycleImpl::close(const CloseType &reason) const
{
    nlohmann::json params;
    params["type"] = Firebolt::JSON::toString(JsonData::CloseReasonEnum, reason);
    return helper_.invoke("Lifecycle2.close", params);
}

Result<LifecycleState> LifecycleImpl::state() const
{
    return helper_.get<JsonData::LifecycleState, LifecycleState>("Lifecycle2.state");
}

Result<SubscriptionId>
LifecycleImpl::subscribeOnStateChanged(std::function<void(const std::vector<StateChange> &)> &&notification)
{
    return subscriptionManager_.subscribe<
        Firebolt::JSON::NL_Json_Array<JsonData::StateChange, StateChange>>("Lifecycle2.onStateChanged",
                                                                                      std::move(notification));
}

Result<void> LifecycleImpl::unsubscribe(SubscriptionId id)
{
    return subscriptionManager_.unsubscribe(id);
}

void LifecycleImpl::unsubscribeAll()
{
    subscriptionManager_.unsubscribeAll();
}
} // namespace Firebolt::Lifecycle
