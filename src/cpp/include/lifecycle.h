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

#include "Firebolt/types.h"
#include <functional>
#include <string>
#include <vector>

namespace Firebolt::Lifecycle
{

/**
 * @brief The app lifecycle state
 */
enum class LifecycleState
{
    INITIALIZING,
    ACTIVE,
    PAUSED,
    SUSPENDED,
    HIBERNATED,
    TERMINATING,
};

/**
 * @brief The app close type
 */
enum class CloseType
{
    DEACTIVATE,
    UNLOAD,
    KILL_RELOAD,
    KILL_REACTIVATE,
};

/**
 * @brief Represents a transition between two lifecycle states, including whether the app is focused after the transition
 */
struct StateChange
{
    LifecycleState oldState;
    LifecycleState newState;
    bool focused;
};

class ILifecycle
{
public:
    virtual ~ILifecycle() = default;

    /**
     * @brief Request that the platform move your app out of focus
     *
     * @param[in] type The type of the close app is requesting
     */
    virtual Result<void> close(const CloseType &type) const = 0;

    /**
     * @brief Get the current lifecycle state of the app
     *
     * @retval The current lifecycle state or error
     */
    virtual Result<LifecycleState> state() const = 0;

    /**
     * @brief Subscribe to lifecycle state changes
     *
     * @param notification : The callback function, which receives a vector of state changes performed by the platform
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnStateChanged(std::function<void(const std::vector<StateChange>&)> &&notification) = 0;

    /**
     * @brief Remove subscriber from subscribers list. This method is generic for
     *        all subscriptions
     *
     * @param[in] id                  : The subscription id
     *
     * @retval The status
     */
    virtual Result<void> unsubscribe(SubscriptionId id) = 0;

    /**
     * @brief Remove all active subscriptions from subscribers list.
     */
    virtual void unsubscribeAll() = 0;
};
} // namespace Firebolt::Lifecycle
