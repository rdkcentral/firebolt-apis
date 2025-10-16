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

#include <gmock/gmock.h>
#include <helpers.h>

class MockHelper : public Firebolt::Helpers::Helper
{
public:
    MOCK_METHOD(Firebolt::Result<nlohmann::json>, getJson,
                (const std::string &methodName, const nlohmann::json &parameters), (override));
    MOCK_METHOD(Firebolt::Result<void>, set, (const std::string &methodName, const nlohmann::json &parameters),
                (override));
    MOCK_METHOD(Firebolt::Result<void>, invoke, (const std::string &methodName, const nlohmann::json &parameters),
                (override));
    MOCK_METHOD(Firebolt::Result<void>, unsubscribe, (::Firebolt::SubscriptionId id), (override));
    MOCK_METHOD(void, unsubscribeAll, (), (override));

private:
    MOCK_METHOD(Firebolt::Result<Firebolt::SubscriptionId>, subscribeImpl,
                (const std::string &eventName, std::any &&notification, void (*callback)(void *, const nlohmann::json &)),
                (override));
};
