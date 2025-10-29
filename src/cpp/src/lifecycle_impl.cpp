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
#include <cctype>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

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
LifecycleImpl::LifecycleImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper), subscriptionManager_(helper, this) {}

LifecycleImpl::~LifecycleImpl()
{
    //subscriptionManager_.unsubscribeAll() is called from the subscriptionManager destructor
}

Result<void> LifecycleImpl::ready()
{
    nlohmann::json params;
    subscribeToStateChangeEvents();

    const auto status = helper_.invoke("lifecycle.ready", params);
    if (status) {
        readyDispatcher();
    }
    return status;
}

Result<void> LifecycleImpl::close(const CloseType &reason) const 
{
    nlohmann::json params;
    params["reason"] = FireboltSDK::JSON::ToString(JsonData::CloseReasonEnum, reason);
    return helper_.invoke("lifecycle.close", params);
}

Result<void> LifecycleImpl::finished()
{
    nlohmann::json params;
    return helper_.invoke("lifecycle.finished", params);
}

Result<LifecycleState> LifecycleImpl::getCurrentState() const 
{
    return Result<LifecycleState>(currentState_); 
}

void LifecycleImpl::subscribeToStateChangeEvents() {
    auto callback = [this](const LifecycleEvent& event) { this->onStateChanged(event); };
    subscribeOnBackgroundChanged(callback);
    subscribeOnForegroundChanged(callback);
    subscribeOnInactiveChanged(callback);
    subscribeOnSuspendedChanged(callback);
    subscribeOnUnloadingChanged(callback); 
}

void LifecycleImpl::onStateChanged(const LifecycleEvent& event)
{
    std::unique_lock lock{mutex_};
    LifecycleState oldState = currentState_;
    currentState_ = event.state;

    for (const auto& [id, func] : onStateChangedCallbacks_) {
        func(oldState, currentState_);
    }
}

Result<SubscriptionId>
    LifecycleImpl::subscribeOnStateChanged(std::function<void(const LifecycleState& oldState, const LifecycleState& newState)>&& notification) 
{
    std::lock_guard<std::mutex> lock(mutex_);

    uint64_t newId = ++currentId_;
    onStateChangedCallbacks_[newId] = std::move(notification);

    return Result<SubscriptionId>(newId);
}

Result<void> LifecycleImpl::unsubscribe(SubscriptionId id) 
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = onStateChangedCallbacks_.find(id);
    if (it == onStateChangedCallbacks_.end()) {
        return Result<void>{Error::General};
    }
    onStateChangedCallbacks_.erase(it);
    return Result<void>(Firebolt::Error::None);
}

void LifecycleImpl::unsubscribeAll()
{
    std::lock_guard<std::mutex> lock(mutex_);
    onStateChangedCallbacks_.clear();
}

Result<SubscriptionId> LifecycleImpl::subscribeOnBackgroundChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::LifecycleEvent>("lifecycle.onBackground", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnForegroundChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::LifecycleEvent>("lifecycle.onForeground", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnInactiveChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::LifecycleEvent>("lifecycle.onInactive", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnSuspendedChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::LifecycleEvent>("lifecycle.onSuspended", std::move(notification));
}

Result<SubscriptionId> LifecycleImpl::subscribeOnUnloadingChanged(std::function<void(const LifecycleEvent&)>&& notification)
{
    return subscriptionManager_.subscribe<JsonData::LifecycleEvent>("lifecycle.onUnloading", std::move(notification));
}

} // namespace Firebolt::Lifecycle

