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

#include "./component/utils.h"
#include "firebolt.h"
#include "json_engine.h"
#include "gtest/gtest.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class LifecycleTest : public ::testing::Test
{
protected:
    void SetUp() override { eventReceived = false; }

    // Create a condition variable and mutex to wait for the events to be received
    std::condition_variable cv;
    std::mutex mtx;
    bool eventReceived;

    JsonEngine jsonEngine;
};

TEST_F(LifecycleTest, close)

{
    auto result =
        Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(Firebolt::Lifecycle::CloseType::DEACTIVATE);
    ASSERT_TRUE(result) << "Error on calling LifecycleInterface.close() method";
}

TEST_F(LifecycleTest, state)
{
    Firebolt::Result<Firebolt::Lifecycle::LifecycleState> result =
        Firebolt::IFireboltAccessor::Instance().LifecycleInterface().state();
    ASSERT_TRUE(result) << "Error on calling LifecycleInterface.state() method";

    auto expectedValue = jsonEngine.get_value("Lifecycle.state");
    EXPECT_EQ(*result, Firebolt::Lifecycle::LifecycleState::ACTIVE);
}

TEST_F(LifecycleTest, subscribeOnState)
{
    auto id = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnStateChanged(
        [&](const std::vector<Firebolt::Lifecycle::StateChange>& changes)
        {
            EXPECT_EQ(changes.size(), 1);
            std::cout << "[Subscription] Lifecycle state changed: " << static_cast<int>(changes[0].newState)
                      << ", old state: " << static_cast<int>(changes[0].oldState) << std::endl;

            EXPECT_EQ(changes[0].newState, Firebolt::Lifecycle::LifecycleState::PAUSED);
            EXPECT_EQ(changes[0].oldState, Firebolt::Lifecycle::LifecycleState::INITIALIZING);

            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);

    // Trigger the event from the mock server
    triggerEvent("Lifecycle2.onStateChanged", R"([{"newState":"paused","oldState":"initializing"}])");
    verifyEventReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Lifecycle2.onStateChanged", R"([{"newState":"paused","oldState":"badstate"}])");
    verifyEventNotReceived(mtx, cv, eventReceived);

    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}
