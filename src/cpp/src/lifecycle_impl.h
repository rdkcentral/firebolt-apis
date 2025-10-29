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

#include "helpers.h"
#include "lifecycle.h"
#include <mutex>
#include <set>
#include <string>

class LifecycleTest;

namespace Firebolt::Lifecycle
{
    enum class LifecycleEventSource
{
    VOICE,
    REMOTE
};

struct LifecycleEvent
{
    LifecycleState state;
    LifecycleState previous;
    std::optional<LifecycleEventSource> source;
};

class LifecycleImpl : public ILifecycle
{
public:
    LifecycleImpl(Firebolt::Helpers::IHelper &helper);
    LifecycleImpl(const LifecycleImpl&) = delete;
    LifecycleImpl& operator=(const LifecycleImpl&) = delete;
    ~LifecycleImpl() override;

    Result<void> ready();
    virtual Result<void> close(const CloseType &type) const override;
    Result<void> finished();

    virtual Result<LifecycleState> getCurrentState() const;
    Result<SubscriptionId>
    subscribeOnStateChanged(std::function<void(const LifecycleState& oldState, const LifecycleState& newState)>&& notification) override;

    virtual Result<void> unsubscribe(SubscriptionId id) override;
    virtual void unsubscribeAll() override;

private:
    void onStateChanged(const LifecycleEvent& event);
    void subscribeToStateChangeEvents();

    Result<SubscriptionId> subscribeOnBackgroundChanged(std::function<void(const LifecycleEvent&)>&& notification);
    Result<SubscriptionId> subscribeOnForegroundChanged(std::function<void(const LifecycleEvent&)>&& notification);
    Result<SubscriptionId> subscribeOnInactiveChanged(std::function<void(const LifecycleEvent&)>&& notification);
    Result<SubscriptionId> subscribeOnSuspendedChanged(std::function<void(const LifecycleEvent&)>&& notification);
    Result<SubscriptionId> subscribeOnUnloadingChanged(std::function<void(const LifecycleEvent&)>&& notification);


private:
    Firebolt::Helpers::IHelper &helper_;
    std::mutex mutex_;
    LifecycleState currentState_{LifecycleState::INITIALIZING};
    std::set<SubscriptionId> subscriptions_;
    Firebolt::Helpers::SubscriptionManager subscriptionManager_;

    uint64_t currentId_{0};
    std::map<uint64_t, std::function<void(const LifecycleState& oldState, const LifecycleState& newState)>> onStateChangedCallbacks_;

public:
    friend class ::LifecycleTest;
};  
} // namespace Firebolt::Lifecycle
