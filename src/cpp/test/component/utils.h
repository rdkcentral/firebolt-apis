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

#include <firebolt.h>

#include <string>
#include <condition_variable>
#include <mutex>
#include <nlohmann/json.hpp>

std::string httpGet(const std::string &url);
std::string httpPost(const std::string &url, const std::string &postData);

void triggerEvent(const std::string &method, const std::string &params);
void triggerRaw(const nlohmann::json &payload);

void verifyEventSubscription(const Firebolt::Result<Firebolt::SubscriptionId> &id);
void verifyUnsubscribeResult(const Firebolt::Result<void> &result);
void verifyEventReceived(std::mutex &mtx, std::condition_variable &cv, bool &eventReceived);

template <typename T> inline std::string toError(const Firebolt::Result<T> &result)
{
    if (result)
    {
        return "";
    }
    return "Error: " + std::to_string(static_cast<int>(result.error()));
}
