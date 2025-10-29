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

#include "device_impl.h"
#include "json_engine.h"
#include "mock_helper.h"
#include <firebolt.h>
#include <lifecycle_impl.h>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

#define EXPECTED_CB_ID_1 1
#define EXPECTED_CB_ID_2 2
#define BOGUS_SUBSCRIPTION_ID 999

class LifecycleTest : public ::testing::Test
{
protected:
    void mock_invoke(const std::string &methodName)
    {
        EXPECT_CALL(mockHelper, invoke(methodName, _))
            .WillOnce(Invoke([](const  std::string &methodName, const nlohmann::json &parameters)
                                { return Firebolt::Result<void>(Firebolt::Error::None); }));
    }

    void mock_subscribe(const std::string &eventName)
    {
        EXPECT_CALL(mockHelper, subscribe(_, eventName, _, _))
            .WillOnce(Invoke([](auto, const std::string &eventName, auto, auto)
                                { return Firebolt::Result<Firebolt::SubscriptionId>(Firebolt::Error::None); }));
    }

    void simulateStateChange() {
            // Simulate a state change
        Firebolt::Lifecycle::LifecycleEvent event{
            .state = Firebolt::Lifecycle::LifecycleState::ACTIVE,
            .previous = Firebolt::Lifecycle::LifecycleState::INITIALIZING,
            .source = std::nullopt
        };
        lifecycleImpl_.onStateChanged(event);
    }


protected:
    void SetUp() override {
        // This runs before EACH test
        // Initialize resources, set up mocks, etc.
    }

    void TearDown() override {
        // This runs after EACH test (optional)
        // Clean up resources
        EXPECT_CALL(mockHelper, unsubscribeAll(_))
            .WillRepeatedly(Invoke([](auto) {
                return Firebolt::Result<void>(Firebolt::Error::None);
            }));
    }

    JsonEngine jsonEngine;
    MockHelper mockHelper;
    Firebolt::Device::DeviceImpl deviceImpl_{mockHelper};
    Firebolt::Lifecycle::LifecycleImpl lifecycleImpl_{mockHelper};
    
    std::map<uint64_t, std::tuple<Firebolt::Lifecycle::LifecycleState, Firebolt::Lifecycle::LifecycleState>> cbs_called_;
    enum {OLD_STATE_INDEX, NEW_STATE_INDEX};
};

TEST_F(LifecycleTest, ready) {
    mock_invoke("lifecycle.ready");
    mock_subscribe("lifecycle.onBackground");
    mock_subscribe("lifecycle.onForeground");
    mock_subscribe("lifecycle.onInactive");
    mock_subscribe("lifecycle.onSuspended");
    mock_subscribe("lifecycle.onUnloading");

    Firebolt::Result<void> result = lifecycleImpl_.ready();
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error: wrong error code returned by Lifecycle.ready()";
}

TEST_F(LifecycleTest, close)
{
    mock_invoke("lifecycle.close");
    Firebolt::Result<void> result = lifecycleImpl_.close(Firebolt::Lifecycle::CloseType::DEACTIVATE);
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error: wrong error code returned by Lifecycle.close()";
}

TEST_F(LifecycleTest, finished)
{
    mock_invoke("lifecycle.finished");
    Firebolt::Result<void> result = lifecycleImpl_.finished();
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error: wrong error code returned by Lifecycle.close()";
}

TEST_F(LifecycleTest, getCurrentState)
{
    Firebolt::Result<Firebolt::Lifecycle::LifecycleState> result = lifecycleImpl_.getCurrentState();
    ASSERT_TRUE(result) << "Failed to retrieve current state from Lifecycle.getCurrentState() method";
    EXPECT_EQ(*result, Firebolt::Lifecycle::LifecycleState::INITIALIZING) << "Error: wrong value returned by Lifecycle.getCurrentState()";
}

TEST_F(LifecycleTest, subscribeOnStateChanged2) {

    Firebolt::Result<uint64_t> result1 = lifecycleImpl_.subscribeOnStateChanged(
        [result1, this](const Firebolt::Lifecycle::LifecycleState& oldState, 
            const Firebolt::Lifecycle::LifecycleState& newState) {
                cbs_called_[EXPECTED_CB_ID_1] = std::make_tuple(oldState, newState);
       }); 

    EXPECT_EQ(Firebolt::Error::None, result1.error()) << "Error: wrong error code returned by first subscribeOnStateChanged";
    EXPECT_EQ(*result1, EXPECTED_CB_ID_1) << "Error: wrong subscription id returned by first subscribeOnStateChanged";

    Firebolt::Result<uint64_t> result2 = lifecycleImpl_.subscribeOnStateChanged(
        [result2, this](const Firebolt::Lifecycle::LifecycleState& oldState, 
            const Firebolt::Lifecycle::LifecycleState& newState) {
                cbs_called_[EXPECTED_CB_ID_2] = std::make_tuple(oldState, newState);
       }); 

    EXPECT_EQ(Firebolt::Error::None, result2.error()) << "Error: wrong error code returned by second subscribeOnStateChanged";
    EXPECT_EQ(*result2, 2) << "Error: wrong subscription id returned by second subscribeOnStateChanged";

    simulateStateChange();

    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_1), 1) << "Error: callback 1 should be called after subscribing";
    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_2), 1) << "Error: callback 2 should be called after subscribing";

    lifecycleImpl_.unsubscribe(EXPECTED_CB_ID_1);

    cbs_called_.clear();
    simulateStateChange();

    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_1), 0) << "Error: callback should not have been called after unsubscribing";
    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_2), 1) << "Error: callback 2 should still be called after callback 1 unsubscribed";
}

TEST_F(LifecycleTest, subscribeOnStateChanged)
{
    Firebolt::Result<uint64_t> result = lifecycleImpl_.subscribeOnStateChanged([result, this](const Firebolt::Lifecycle::LifecycleState& oldState, 
       const Firebolt::Lifecycle::LifecycleState& newState) {
            cbs_called_[EXPECTED_CB_ID_1] = std::make_tuple(oldState, newState);
       }); 

    EXPECT_EQ(Firebolt::Error::None, result.error()) << "Error: wrong error code returned by subscribeOnStateChanged";

    EXPECT_EQ(*result, EXPECTED_CB_ID_1) << "Error: wrong subscription id returned by subscribeOnStateChanged";

    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_1), 0) << "Error: callback should not have been called yet";

    simulateStateChange();

    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_1), 1) << "Error: callback was not called upon state change!!!!!!";

    EXPECT_EQ(std::get<OLD_STATE_INDEX>(cbs_called_[EXPECTED_CB_ID_1]), 
        Firebolt::Lifecycle::LifecycleState::INITIALIZING) << "Error: wrong old state in subscription callback";

    EXPECT_EQ(std::get<NEW_STATE_INDEX>(cbs_called_[EXPECTED_CB_ID_1]), 
        Firebolt::Lifecycle::LifecycleState::ACTIVE) << "Error: wrong new state in subscription callback";

    EXPECT_EQ(lifecycleImpl_.unsubscribe(BOGUS_SUBSCRIPTION_ID).error(), Firebolt::Error::General) << "Error: unsubscribing with bogus subscription id should return General error";
    
    EXPECT_EQ(lifecycleImpl_.unsubscribe(EXPECTED_CB_ID_1).error(), Firebolt::Error::None) << "Error: unsubscribing with valid subscription id should return None error";

    cbs_called_.clear();
    simulateStateChange();

    EXPECT_EQ(cbs_called_.count(EXPECTED_CB_ID_1), 0) << "Error: callback should not have been called after unsubscribing";
}
