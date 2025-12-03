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

#include "component/utils.h"
#include "firebolt/firebolt.h"
#include "json_engine.h"
#include <condition_variable>
#include <gtest/gtest.h>
#include <mutex>

class PresentationTest : public ::testing::Test
{
protected:
    void SetUp() override { eventReceived = false; }

    std::condition_variable cv;
    std::mutex mtx;
    bool eventReceived;

    JsonEngine jsonEngine;
};

TEST_F(PresentationTest, focused)
{
    auto expectedValue = jsonEngine.get_value("Presentation.focused");
    auto result = Firebolt::IFireboltAccessor::Instance().PresentationInterface().focused();

    ASSERT_TRUE(result) << "Presentation::focused() returned an error";
    EXPECT_EQ(*result, expectedValue.get<bool>());
}

TEST_F(PresentationTest, subscribeOnFocusedChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().PresentationInterface().subscribeOnFocusedChanged(
        [&](const bool& focus)
        {
            EXPECT_EQ(focus, true);
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);

    triggerEvent("Presentation.onFocusedChanged", R"({ "value": true })");

    verifyEventReceived(mtx, cv, eventReceived);
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}
