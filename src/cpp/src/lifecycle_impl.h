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
#include "helpers.h"
#include "lifecycle.h"
#include <mutex>
#include <set>
#include <string>

namespace Firebolt::Lifecycle
{
class LifecycleImpl : public ILifecycle, public SubscriptionHelper
{
public:
    LifecycleImpl() = default;
    LifecycleImpl(const LifecycleImpl&) = delete;
    LifecycleImpl& operator=(const LifecycleImpl&) = delete;
    ~LifecycleImpl() override;

    Result<void> ready() override;
    Result<void> close(const CloseReason& reason) override;
    Result<void> finished() override;
    Result<std::string> state() override;
    Result<SubscriptionId> subscribeOnBackgroundChanged(std::function<void(const LifecycleEvent&)>&& notification) override;
    Result<SubscriptionId> subscribeOnForegroundChanged(std::function<void(const LifecycleEvent&)>&& notification) override;
    Result<SubscriptionId> subscribeOnInactiveChanged(std::function<void(const LifecycleEvent&)>&& notification) override;
    Result<SubscriptionId> subscribeOnSuspendedChanged(std::function<void(const LifecycleEvent&)>&& notification) override;
    Result<SubscriptionId> subscribeOnUnloadingChanged(std::function<void(const LifecycleEvent&)>&& notification) override;
    Result<void> unsubscribe(SubscriptionId id) override;
    void unsubscribeAll() override;

private:
    void onStateChanged(const LifecycleEvent& event);
    void subscribeOnStateChange();

private:
    std::mutex mutex_;
    std::string currentState_{"INITIALIZING"};
    std::set<SubscriptionId> subscriptions_;
};
} // namespace Firebolt::Lifecycle
