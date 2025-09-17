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

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

const std::map<std::string, ::Firebolt::Device::NetworkType> NetworkTypeMap = {
    { "wifi", ::Firebolt::Device::NetworkType::WIFI },
    { "ethernet", ::Firebolt::Device::NetworkType::ETHERNET },
    { "hybrid", ::Firebolt::Device::NetworkType::HYBRID },
};

const std::map<std::string, ::Firebolt::Device::NetworkState> NetworkStateMap = {
    { "connected", ::Firebolt::Device::NetworkState::CONNECTED },
    { "disconnected", ::Firebolt::Device::NetworkState::DISCONNECTED },
};

class DeviceTest : public ::testing::Test
{
protected:
    Firebolt::Result<nlohmann::json> getter(const std::string &methodName, const nlohmann::json &parameters)
    {
        nlohmann::json message;
        message["method"] = methodName;

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

protected:
    JsonEngine jsonEngine;
    ::testing::NiceMock<MockHelper> mockHelper;
    Firebolt::Device::DeviceImpl deviceImpl_{mockHelper};
};

TEST_F(DeviceTest, Id)
{
    mock("Device.id");

    auto result = deviceImpl_.id();
    ASSERT_TRUE(result) << "DeviceImpl::id() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.id");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Distributor)
{
    mock("Device.distributor");

    auto result = deviceImpl_.distributor();
    ASSERT_TRUE(result) << "DeviceImpl::distributor() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.distributor");
    EXPECT_EQ(*result, expectedValue);
}


TEST_F(DeviceTest, Platform)
{
    mock("Device.platform");

    auto result = deviceImpl_.platform();
    ASSERT_TRUE(result) << "DeviceImpl::platform() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.platform");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Uid)
{
    mock("Device.uid");

    auto result = deviceImpl_.uid();
    ASSERT_TRUE(result) << "DeviceImpl::uid() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.uid");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Type)
{
    mock("Device.type");

    auto result = deviceImpl_.type();
    ASSERT_TRUE(result) << "DeviceImpl::type() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.type");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Model)
{
    mock("Device.model");

    auto result = deviceImpl_.model();
    ASSERT_TRUE(result) << "DeviceImpl::model() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.model");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Sku)
{
    mock("Device.sku");

    auto result = deviceImpl_.sku();
    ASSERT_TRUE(result) << "DeviceImpl::sku() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.sku");
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, TestDeviceMake)
{
    mock("Device.make");

    auto result = deviceImpl_.make();
    ASSERT_TRUE(result) << "DeviceImpl::make() returned an error";

    auto expectedValue = jsonEngine.get_value("Device.make");
    EXPECT_EQ(*result, expectedValue);
}


TEST_F(DeviceTest, Hdcp)
{
    mock("Device.hdcp");

    auto result = deviceImpl_.hdcp();
    ASSERT_TRUE(result) << "Failed to retrieve hdcp from Device.hdcp() method";

    auto expectedValue = jsonEngine.get_value("Device.hdcp");
    EXPECT_EQ(result->hdcp1_4, expectedValue["hdcp1.4"]);
    EXPECT_EQ(result->hdcp2_2, expectedValue["hdcp2.2"]);
}


TEST_F(DeviceTest, Hdr)
{
    mock("Device.hdr");

    auto result = deviceImpl_.hdr();
    ASSERT_TRUE(result) << "Failed to retrieve hdr from Device.hdr() method";

    auto expectedValue = jsonEngine.get_value("Device.hdr");
    EXPECT_EQ(result->hdr10, expectedValue["hdr10"]);
    EXPECT_EQ(result->hdr10Plus, expectedValue["hdr10Plus"]);
    EXPECT_EQ(result->dolbyVision, expectedValue["dolbyVision"]);
    EXPECT_EQ(result->hlg, expectedValue["hlg"]);
}

TEST_F(DeviceTest, Audio)
{
    mock("Device.audio");

    auto result = deviceImpl_.audio();
    ASSERT_TRUE(result) << "Failed to retrieve audio from Device.audio() method";

    auto expectedValue = jsonEngine.get_value("Device.audio");
    EXPECT_EQ(result->stereo, expectedValue["stereo"]);
    EXPECT_EQ(result->dolbyDigital5_1, expectedValue["dolbyDigital5.1"]);
    EXPECT_EQ(result->dolbyDigital5_1_plus, expectedValue["dolbyDigital5.1+"]);
    EXPECT_EQ(result->dolbyAtmos, expectedValue["dolbyAtmos"]);
}

TEST_F(DeviceTest, Network)
{
    mock("Device.network");

    auto result = deviceImpl_.network();
    ASSERT_TRUE(result) << "Failed to retrieve network from Device.network() method";

    auto expectedValue = jsonEngine.get_value("Device.network");
    EXPECT_EQ(result->state, NetworkStateMap.at(expectedValue["state"]));
    EXPECT_EQ(result->type, NetworkTypeMap.at(expectedValue["type"]));
}

TEST_F(DeviceTest, ScreenResolution)
{
    mock("Device.screenResolution");

    auto result = deviceImpl_.screenResolution();
    ASSERT_TRUE(result) << "Failed to retrieve screenResolution from Device.screenResolution() method";

    auto expectedValue = jsonEngine.get_value("Device.screenResolution");
    EXPECT_EQ(result->at(0), expectedValue[0]);
    EXPECT_EQ(result->at(1), expectedValue[1]);
}

TEST_F(DeviceTest, VideoResolution)
{
    mock("Device.videoResolution");

    auto result = deviceImpl_.videoResolution();
    ASSERT_TRUE(result) << "Failed to retrieve videoResolution from Device.videoResolution() method";

    auto expectedValue = jsonEngine.get_value("Device.videoResolution");
    EXPECT_EQ(result->at(0), expectedValue[0]);
    EXPECT_EQ(result->at(1), expectedValue[1]);
}

TEST_F(DeviceTest, Name)
{
    mock("Device.name");

    auto result = deviceImpl_.name();
    ASSERT_TRUE(result) << "Failed to retrieve name from Device.name() method";

    auto expectedValue = jsonEngine.get_value("Device.name");
    EXPECT_EQ(*result, expectedValue);
}
