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
#include "mock_helper.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class LifecycleTest : public ::testing::Test, protected MockBase
{
protected:
    void SetUp() override {}

    void TearDown() override
    {
        EXPECT_CALL(mockHelper, unsubscribeAll(_))
            .WillRepeatedly(Invoke([](auto) { return Firebolt::Result<void>(Firebolt::Error::None); }));
    }

    Firebolt::Lifecycle::LifecycleImpl lifecycleImpl_{mockHelper};
};

TEST_F(LifecycleTest, close)
{
    nlohmann::json expectedParams;
    expectedParams["type"] = "deactivate";
    EXPECT_CALL(mockHelper, invoke("Lifecycle2.close", expectedParams))
        .WillOnce(Invoke([&](const std::string& /*methodName*/, const nlohmann::json& /*parameters*/)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));

    auto result = lifecycleImpl_.close(Firebolt::Lifecycle::CloseType::DEACTIVATE);
    ASSERT_TRUE(result) << "Error on invoke";
}

TEST_F(LifecycleTest, state)
{
    mock_with_response("Lifecycle2.state", "initializing");
    Firebolt::Result<Firebolt::Lifecycle::LifecycleState> result = lifecycleImpl_.state();
    ASSERT_TRUE(result) << "Failed to retrieve current state from Lifecycle.state() method";
    EXPECT_EQ(*result, Firebolt::Lifecycle::LifecycleState::INITIALIZING);
}

TEST_F(LifecycleTest, stateBadResponse)
{
    mock_with_response("Lifecycle2.state", "invalid_response");
    Firebolt::Result<Firebolt::Lifecycle::LifecycleState> result = lifecycleImpl_.state();
    ASSERT_FALSE(result) << "LifecycleImpl::state() did not return an error";
}

TEST_F(LifecycleTest, subscribeOnStateChanged)
{
    EXPECT_CALL(mockHelper, subscribe(_, "Lifecycle2.onStateChanged", _, _))
        .WillOnce(Invoke([&](void* /*owner*/, const std::string& /*eventName*/, std::any&& /*notification*/,
                             void (* /*callback*/)(void*, const nlohmann::json&))
                         { return Firebolt::Result<Firebolt::SubscriptionId>{1}; }));

    EXPECT_CALL(mockHelper, unsubscribe(1)).WillOnce(Return(Firebolt::Result<void>{Firebolt::Error::None}));

    auto id =
        lifecycleImpl_.subscribeOnStateChanged([](const std::vector<Firebolt::Lifecycle::StateChange>& /*changes*/) {});

    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_EQ(id.value(), 1);

    auto result = lifecycleImpl_.unsubscribe(id.value());
    ASSERT_TRUE(result) << "error on unsubscribe";
}
