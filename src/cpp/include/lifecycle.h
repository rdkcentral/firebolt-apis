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

#include <functional>
#include <string>
#include <types/fb-errors.h>
#include <types/types.h>

namespace Firebolt::Lifecycle
{
/**
 * @brief The application close reason
 */
enum class CloseReason
{
    REMOTE_BUTTON,
    USER_EXIT,
    DONE,
    ERROR
};

/**
 * @brief The application lifecycle state
 */
enum class LifecycleState
{
    INITIALIZING,
    INACTIVE,
    FOREGROUND,
    BACKGROUND,
    UNLOADING,
    SUSPENDED
};

/**
 * @brief The source of the lifecycle change.
 */
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

class ILifecycle
{
public:
    virtual ~ILifecycle() = default;

    /**
     * @brief Notify the platform that the app is ready
     *
     * @retval The status
     */
    virtual Result<void> ready() = 0;

    /**
     * @brief Request that the platform move your app out of focus
     *
     * @param[in]  reason : The reason the app is requesting to be closed
     *
     * @retval The status
     */
    virtual Result<void> close(const CloseReason& reason) = 0;

    /**
     * @brief Notify the platform that the app is done unloading
     *
     * @retval The status
     */
    virtual Result<void> finished() = 0;

    /**
     * @brief Get the current state of the app. This function is **synchronous**.
     *
     * @retval The method call result
     */
    virtual Result<std::string> state() = 0;

    /**
     * @brief Listen to the background event
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnBackgroundChanged(std::function<void(const LifecycleEvent&)>&& notification) = 0;

    /**
     * @brief Listen to the foreground event
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnForegroundChanged(std::function<void(const LifecycleEvent&)>&& notification) = 0;

    /**
     * @brief Listen to the inactive event
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnInactiveChanged(std::function<void(const LifecycleEvent&)>&& notification) = 0;

    /**
     * @brief Listen to the suspended event
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnSuspendedChanged(std::function<void(const LifecycleEvent&)>&& notification) = 0;

    /**
     * @brief Listen to the unloading event
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnUnloadingChanged(std::function<void(const LifecycleEvent&)>&& notification) = 0;

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
