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

#define MODULE_NAME LifecycleTest
#include "unit.h"
#include <thread>

class LifecycleTest : public ::testing::Test
{
protected:
    JsonEngine* jsonEngine;

    void SetUp() override { jsonEngine = new JsonEngine(); }

    void TearDown() override { delete jsonEngine; }
};

TEST_F(LifecycleTest, ready)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().ready();
    EXPECT_EQ(Firebolt::Error::None, result.error()) << "Error: wrong error code returned by "
                                                        "Lifecycle.ready()";

    // To let dispatcher execute internal job and avoid warnings
    // To be removed, when Transport Layer is refactored
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST_F(LifecycleTest, close)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(
        Firebolt::Lifecycle::CloseReason::REMOTE_BUTTON);
    EXPECT_EQ(Firebolt::Error::None, result.error()) << "Error: wrong error code returned by "
                                                        "Lifecycle.close()";
}

TEST_F(LifecycleTest, finished)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().finished();
    EXPECT_EQ(Firebolt::Error::None, result.error()) << "Error: wrong error code returned by "
                                                        "Lifecycle.finished()";
}

TEST_F(LifecycleTest, state)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().state();
    ASSERT_TRUE(result) << "Error on calling Lifecycle.state() method";

    // Value set by subscription in ready(). "INITIALIZING" is an initial value
    EXPECT_EQ("INITIALIZING", *result) << "Error: wrong value returned by "
                                          "Lifecycle.state()";
}

TEST_F(LifecycleTest, subscribeOnBackgroundChanged)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnBackgroundChanged(
        [](const auto&) { std::cout << "Background changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to Background";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to Background";
}

TEST_F(LifecycleTest, subscribeOnForegroundChanged)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnForegroundChanged(
        [](const auto&) { std::cout << "Foreground changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to Foreground";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to Foreground";
}

TEST_F(LifecycleTest, subscribeOnInactiveChanged)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnInactiveChanged(
        [](const auto&) { std::cout << "Inactive changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to Inactive";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to Inactive";
}

TEST_F(LifecycleTest, subscribeOnSuspendedChanged)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnSuspendedChanged(
        [](const auto&) { std::cout << "Suspended changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to Suspended";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to Suspended";
}

TEST_F(LifecycleTest, subscribeOnUnloadingChanged)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnUnloadingChanged(
        [](const auto&) { std::cout << "Unloading changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to Unloading";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to Unloading";
}