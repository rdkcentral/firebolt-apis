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
struct LifecycleEvent
{
    LifecycleState state;
    LifecycleState previous;
};

class LifecycleImpl : public ILifecycle
{
public:
    LifecycleImpl(Firebolt::Helpers::IHelper &helper);
    LifecycleImpl(const LifecycleImpl &) = delete;
    LifecycleImpl &operator=(const LifecycleImpl &) = delete;
    ~LifecycleImpl() override;

    virtual Result<void> close(const CloseType &type) const override;
    virtual Result<LifecycleState> getCurrentState() const override;

    Result<SubscriptionId>
    subscribeOnStateChanged(std::function<void(const std::vector<StateChange> &)> &&notification) override;

    virtual Result<void> unsubscribe(SubscriptionId id) override;
    virtual void unsubscribeAll() override;

private:

private:
    Firebolt::Helpers::IHelper &helper_;
    Firebolt::Helpers::SubscriptionManager subscriptionManager_;

public:
    friend class ::LifecycleTest;
};
} // namespace Firebolt::Lifecycle
