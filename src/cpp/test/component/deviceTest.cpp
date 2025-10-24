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
#include "json_engine.h"
#include "firebolt.h"
#include "gtest/gtest.h"


#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class DeviceTest : public ::testing::Test
{
protected:
    void SetUp() override { eventReceived = false; }

    const std::map<std::string, ::Firebolt::Device::NetworkType> NetworkTypeMap = {
        {"wifi", ::Firebolt::Device::NetworkType::WIFI},
        {"ethernet", ::Firebolt::Device::NetworkType::ETHERNET},
        {"hybrid", ::Firebolt::Device::NetworkType::HYBRID},
    };

    const std::map<std::string, ::Firebolt::Device::NetworkState> NetworkStateMap = {
        {"connected", ::Firebolt::Device::NetworkState::CONNECTED},
        {"disconnected", ::Firebolt::Device::NetworkState::DISCONNECTED},
    };

    // Create a condition variable and mutex to wait for the events to be received
    std::condition_variable cv;
    std::mutex mtx;
    bool eventReceived;

    JsonEngine jsonEngine;
};

TEST_F(DeviceTest, name)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name();
    ASSERT_TRUE(result) << "Failed to retrieve name from Device.name() method";
    EXPECT_EQ(jsonEngine.get_value("Device.name"), result.value());
}

TEST_F(DeviceTest, Id)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id();
    ASSERT_TRUE(result) << "DeviceImpl::id() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.id");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Distributor)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().distributor();
    ASSERT_TRUE(result) << "DeviceImpl::distributor() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.distributor");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Platform)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform();
    ASSERT_TRUE(result) << "DeviceImpl::platform() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.platform");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Uid)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().uid();
    ASSERT_TRUE(result) << "DeviceImpl::uid() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.uid");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Type)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().type();
    ASSERT_TRUE(result) << "DeviceImpl::type() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.type");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Model)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model();
    ASSERT_TRUE(result) << "DeviceImpl::model() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.model");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Sku)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku();
    ASSERT_TRUE(result) << "DeviceImpl::sku() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.sku");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, TestDeviceMake)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make();
    ASSERT_TRUE(result) << "DeviceImpl::make() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.make");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Hdcp)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdcp();
    ASSERT_TRUE(result) << "Failed to retrieve hdcp from Device.hdcp() method";

    auto expectedValue = jsonEngine.get_value("Device.hdcp");
    EXPECT_EQ(result->hdcp1_4, expectedValue["hdcp1.4"]);
    EXPECT_EQ(result->hdcp2_2, expectedValue["hdcp2.2"]);
}

TEST_F(DeviceTest, Hdr)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdr();
    ASSERT_TRUE(result) << "Failed to retrieve hdr from Device.hdr() method";

    auto expectedValue = jsonEngine.get_value("Device.hdr");
    EXPECT_EQ(result->hdr10, expectedValue["hdr10"]);
    EXPECT_EQ(result->hdr10Plus, expectedValue["hdr10Plus"]);
    EXPECT_EQ(result->dolbyVision, expectedValue["dolbyVision"]);
    EXPECT_EQ(result->hlg, expectedValue["hlg"]);
}

TEST_F(DeviceTest, Audio)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio();
    ASSERT_TRUE(result) << "Failed to retrieve audio from Device.audio() method";

    auto expectedValue = jsonEngine.get_value("Device.audio");
    EXPECT_EQ(result->stereo, expectedValue["stereo"]);
    EXPECT_EQ(result->dolbyDigital5_1, expectedValue["dolbyDigital5.1"]);
    EXPECT_EQ(result->dolbyDigital5_1_plus, expectedValue["dolbyDigital5.1+"]);
    EXPECT_EQ(result->dolbyAtmos, expectedValue["dolbyAtmos"]);
}

TEST_F(DeviceTest, Network)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network();
    ASSERT_TRUE(result) << "Failed to retrieve network from Device.network() method";

    auto expectedValue = jsonEngine.get_value("Device.network");
    EXPECT_EQ(result->state, NetworkStateMap.at(expectedValue["state"]));
    EXPECT_EQ(result->type, NetworkTypeMap.at(expectedValue["type"]));
}

TEST_F(DeviceTest, ScreenResolution)
{
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution();
    ASSERT_TRUE(result) << "Failed to retrieve screenResolution from Device.screenResolution() method";

    auto expectedValue = jsonEngine.get_value("Device.screenResolution");
    EXPECT_EQ(result->at(0), expectedValue[0]);
    EXPECT_EQ(result->at(1), expectedValue[1]);
}

TEST_F(DeviceTest, VideoResolution)
{

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().videoResolution();
    ASSERT_TRUE(result) << "Failed to retrieve videoResolution from Device.videoResolution() method";

    auto expectedValue = jsonEngine.get_value("Device.videoResolution");
    EXPECT_EQ(result->at(0), expectedValue[0]);
    EXPECT_EQ(result->at(1), expectedValue[1]);
}

TEST_F(DeviceTest, subscribeOnAudioChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnAudioChanged(
        [&](const auto &audio)
        {
            std::cout << "[Subscription] Audio changed: stereo: " << static_cast<int>(audio.stereo)
                      << ", dolbyDigital5.1: " << static_cast<int>(audio.dolbyDigital5_1) << std::endl;

            auto expectedValue = jsonEngine.get_value("Device.audio");
            EXPECT_EQ(audio.stereo, expectedValue["stereo"]);
            EXPECT_EQ(audio.dolbyDigital5_1, expectedValue["dolbyDigital5.1"]);
            EXPECT_EQ(audio.dolbyDigital5_1_plus, expectedValue["dolbyDigital5.1+"]);
            EXPECT_EQ(audio.dolbyAtmos, expectedValue["dolbyAtmos"]);

            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);
    // Trigger the event from the mock server
    triggerEvent("Device.onAudioChanged",
                 R"({ "stereo": true, "dolbyDigital5.1": true, "dolbyDigital5.1+": true, "dolbyAtmos": true })");

    verifyEventReceived(mtx, cv, eventReceived);
    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}
/*
TEST_F(DeviceTest, subscribeOnDeviceNameChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnDeviceNameChanged(
        [&](const auto &name)
        {
            std::cout << "[Subscription] Device name changed: " << name << std::endl;

            auto expectedValue = jsonEngine.get_value("Device.name");
            EXPECT_EQ(name, expectedValue);

            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);
    // Trigger the event from the mock server
    triggerEvent("Device.onDeviceNameChanged", R"({ "name": "Test Device Name" })");

    verifyEventReceived(mtx, cv, eventReceived);
    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}

TEST_F(DeviceTest, subscribeOnHdcpChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnHdcpChanged(
        [&](const auto &hdcp)
        {
            std::cout << "[Subscription] HDCP changed: version: " << static_cast<int>(hdcp.hdcp1_4)
                      << ", state: " << static_cast<int>(hdcp.hdcp2_2) << std::endl;

            auto expectedValue = jsonEngine.get_value("Device.hdcp");
            EXPECT_EQ(hdcp.hdcp1_4, expectedValue["hdcp1_4"]);
            EXPECT_EQ(hdcp.hdcp2_2, expectedValue["hdcp2_2"]);
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);
    // Trigger the event from the mock server
    triggerEvent("Device.onHdcpChanged", R"({ "version": 2, "state": 1 })");

    verifyEventReceived(mtx, cv, eventReceived);
    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}
*/
TEST_F(DeviceTest, subscribeOnNetworkChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribeOnNetworkChanged(
        [&](const auto &network)
        {
            std::cout << "[Subscription] Network changed: state: " << static_cast<int>(network.state)
                      << ", type: " << static_cast<int>(network.type) << std::endl;

            auto expectedValue = jsonEngine.get_value("Device.network");
            EXPECT_EQ(network.state, NetworkStateMap.at(expectedValue["state"]));
            EXPECT_EQ(network.type, NetworkTypeMap.at(expectedValue["type"]));

            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);
    // Trigger the event from the mock server
    triggerEvent("Device.onNetworkChanged", R"({ "state": "connected", "type": "wifi"})");

    verifyEventReceived(mtx, cv, eventReceived);
    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}
