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

#include <firebolt/types.h>
#include <functional>

namespace Firebolt::Presentation
{
class IPresentation
{
public:
    virtual ~IPresentation() = default;

    /**
     * @brief Returns whether the application is currently focused, i.e. receiving key presses
     *
     * @retval The focus state or error
     */
    virtual Result<bool> focused() const = 0;

    /**
     * @brief Subscribe to focus change notifications
     *
     * @param notification : The callback function, which will be called on focus change
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnFocusedChanged(std::function<void(bool)> &&notification) = 0;

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
} // namespace Firebolt::Presentation