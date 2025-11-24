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

#include "json_engine.h"
#include <gmock/gmock.h>
#include <firebolt/helpers.h>

class MockHelper : public Firebolt::Helpers::IHelper
{
public:
    MOCK_METHOD(Firebolt::Result<void>, set, (const std::string &methodName, const nlohmann::json &parameters),
                (override));
    MOCK_METHOD(Firebolt::Result<void>, invoke, (const std::string &methodName, const nlohmann::json &parameters),
                (override));

    MOCK_METHOD(Firebolt::Result<Firebolt::SubscriptionId>, subscribe,
                (void *owner, const std::string &eventName, std::any &&notification,
                 void (*callback)(void *, const nlohmann::json &)),
                (override));

    MOCK_METHOD(Firebolt::Result<void>, unsubscribe, (Firebolt::SubscriptionId id), (override));

    MOCK_METHOD(void, unsubscribeAll, (void *owner), (override));

    MOCK_METHOD(Firebolt::Result<nlohmann::json>, getJson,
                (const std::string &methodName, const nlohmann::json &parameters), (override));
};

class MockBase
{
protected:
    Firebolt::Result<nlohmann::json> getter(const std::string &methodName, const nlohmann::json &parameters)
    {
        nlohmann::json message;
        message["method"] = methodName;
        if (!parameters.is_null())
        {
            message["params"] = parameters;
        }

        Firebolt::Error err = jsonEngine.MockResponse(message);
        if (err != Firebolt::Error::None)
        {
            return Firebolt::Result<nlohmann::json>{err};
        }

        return Firebolt::Result<nlohmann::json>{message["result"]};
    }

    void mock(const std::string &methodName)
    {
        EXPECT_CALL(mockHelper, getJson(methodName, _))
            .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                            { return getter(methodName, parameters); }));
    }

    void mock_with_response(const std::string &methodName, const nlohmann::json &response)
    {
        EXPECT_CALL(mockHelper, getJson(methodName, _))
            .WillOnce(Invoke([response](const std::string &/*methodName*/, const nlohmann::json &/*parameters*/)
                             { return Firebolt::Result<nlohmann::json>{response}; }));
    }

    void mockSubscribe(const std::string &eventName)
    {
        EXPECT_CALL(mockHelper, subscribe(_, eventName, _, _))
            .WillOnce(Invoke(
                [&](void* /*owner*/, const std::string &/*eventName*/, std::any &&/*notification*/,
                    void (* /*callback*/)(void *, const nlohmann::json &))
                {
                    return Firebolt::Result<Firebolt::SubscriptionId>{1};
                }));
        EXPECT_CALL(mockHelper, unsubscribe(1))
            .WillOnce(Invoke(
                [&](Firebolt::SubscriptionId /*id*/)
                {
                    return Firebolt::Result<void>{Firebolt::Error::None};
                }));
    }

protected:
    JsonEngine jsonEngine;
    nlohmann::json lastSetParams;
    ::testing::NiceMock<MockHelper> mockHelper;
};
