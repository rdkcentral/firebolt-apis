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
#include "firebolt.h"
#include "jsondata_lifecycle_types.h"
#include <algorithm>
#include <nlohmann/json.hpp>
#include <string>
#include <cctype>
#include <TypesPriv.h>

using namespace Firebolt::Helpers;

namespace
{
void readyDispatcher()
{
    Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready();
}
} // namespace

namespace Firebolt::Lifecycle
{
LifecycleImpl::~LifecycleImpl()
{
    for (const SubscriptionId& id : subscriptions_)
    {
        SubscriptionHelper::unsubscribe(id);
    }
}

Result<void> LifecycleImpl::ready()
{
    nlohmann::json params;
    subscribeOnStateChange();
    const auto status = invoke("lifecycle.ready", params);
    if (status) {
        readyDispatcher();
    }
    return status;
}

Result<void> LifecycleImpl::close(const CloseReason& reason)
{
    nlohmann::json params;
    params["reason"] = FireboltSDK::JSON::ToString(JsonData::CloseReasonEnum, reason);
    return invoke("lifecycle.close", params);
}

Result<void> LifecycleImpl::finished()
{
    nlohmann::json params;
    return invoke("lifecycle.finished", params);
}

Result<std::string> LifecycleImpl::state()
{
    std::unique_lock lock{mutex_};
    std::string state = FireboltSDK::JSON::ToString(JsonData::LifecycleStateEnum, currentState_);
    std::transform(state.begin(), state.end(), state.begin(), ::toupper);
    return Result<std::string>{state};
}

Result<SubscriptionId> LifecycleImpl::subscribeOnBackgroundChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::LifecycleEvent>("lifecycle.onBackground", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnForegroundChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::LifecycleEvent>("lifecycle.onForeground", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnInactiveChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::LifecycleEvent>("lifecycle.onInactive", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnSuspendedChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::LifecycleEvent>("lifecycle.onSuspended", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnUnloadingChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return SubscriptionHelper::subscribe<JsonData::LifecycleEvent>("lifecycle.onUnloading", std::move(notification));
}

Result<void> LifecycleImpl::unsubscribe(SubscriptionId id)
{
    return SubscriptionHelper::unsubscribe(id);
}

void LifecycleImpl::unsubscribeAll()
{
    SubscriptionHelper::unsubscribeAll();
}

void LifecycleImpl::onStateChanged(const LifecycleEvent& event)
{
    std::unique_lock lock{mutex_};
    currentState_ = event.state;
}

void LifecycleImpl::subscribeOnStateChange()
{
    auto callback = [this](const LifecycleEvent& event) { this->onStateChanged(event); };
    auto result = subscribeOnBackgroundChanged(callback);
    if (result)
    {
        subscriptions_.insert(*result);
    }
    result = subscribeOnForegroundChanged(callback);
    if (result)
    {
        subscriptions_.insert(*result);
    }
    result = subscribeOnInactiveChanged(callback);
    if (result)
    {
        subscriptions_.insert(*result);
    }
    result = subscribeOnSuspendedChanged(callback);
    if (result)
    {
        subscriptions_.insert(*result);
    }
    result = subscribeOnUnloadingChanged(callback);
    if (result)
    {
        subscriptions_.insert(*result);
    }
}
} // namespace Firebolt::Lifecycle
