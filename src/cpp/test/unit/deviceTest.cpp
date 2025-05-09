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

#include "common/types.h"
#include "unit.h"

class DeviceTest : public ::testing::Test
{
protected:
    JsonEngine* jsonEngine;

    void SetUp() override { jsonEngine = new JsonEngine(); }

    void TearDown() override { delete jsonEngine; }
};

TEST_F(DeviceTest, Id)
{
    auto actual_value = jsonEngine->get_value("Device.id");
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().id();

    ASSERT_TRUE(result) << "Failed to retrieve id from Device.id() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Distributor)
{

    auto actual_value = jsonEngine->get_value("Device.distributor");
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().distributor();

    ASSERT_TRUE(result) << "Failed to retrieve distributor from Device.distributor() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Platform)
{

    auto actual_value = jsonEngine->get_value("Device.platform");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().platform();

    ASSERT_TRUE(result) << "Failed to retrieve platform from Device.platform() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Uid)
{

    auto actual_value = jsonEngine->get_value("Device.uid");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().uid();

    ASSERT_TRUE(result) << "Failed to retrieve uid from Device.uid() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Type)
{

    auto actual_value = jsonEngine->get_value("Device.type");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().type();

    ASSERT_TRUE(result) << "Failed to retrieve type from Device.type() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Model)
{

    auto actual_value = jsonEngine->get_value("Device.model");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model();

    ASSERT_TRUE(result) << "Failed to retrieve model from Device.model() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Sku)
{

    auto actual_value = jsonEngine->get_value("Device.sku");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku();

    ASSERT_TRUE(result) << "Failed to retrieve sku from Device.sku() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, TestDeviceMake)
{

    auto actual_value = jsonEngine->get_value("Device.make");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().make();

    ASSERT_TRUE(result) << "Failed to retrieve make from Device.make() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}

TEST_F(DeviceTest, Hdcp)
{
    // Parsing expected JSON values into a BooleanMap
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.hdcp"));
    Firebolt::Types::BooleanMap expectedValues;

    for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it)
    {
        expectedValues[it.key()] = it.value().get<bool>();
    }

    // Getting the actual value from the DeviceInterface
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdcp();

    ASSERT_TRUE(result) << "Failed to retrieve hdcp from Device.hdcp() method";

    // Convert HDCPVersionMap to BooleanMap for comparison
    Firebolt::Types::BooleanMap actualValues;
    actualValues["hdcp1.4"] = result->hdcp1_4;
    actualValues["hdcp2.2"] = result->hdcp2_2;

    EXPECT_EQ(actualValues, expectedValues);
}

TEST_F(DeviceTest, Hdr)
{
    // Parsing expected JSON values into a BooleanMap
    nlohmann::json expectedJson = nlohmann::json::parse(jsonEngine->get_value("Device.hdr"));
    Firebolt::Types::BooleanMap expectedValues;

    for (auto it = expectedJson.begin(); it != expectedJson.end(); ++it)
    {
        expectedValues[it.key()] = it.value().get<bool>();
    }

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().hdr();

    ASSERT_TRUE(result) << "Failed to retrieve hdr from Device.hdr() method";

    // Convert HDRFormatMap to BooleanMap for comparison
    Firebolt::Types::BooleanMap actualValues{};
    actualValues["hdr10"] = result->hdr10;
    actualValues["hdr10Plus"] = result->hdr10Plus;
    actualValues["dolbyVision"] = result->dolbyVision;
    actualValues["hlg"] = result->hlg;

    EXPECT_EQ(actualValues, expectedValues);
}

TEST_F(DeviceTest, Audio)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Device.audio"));

    // Getting the actual value from the DeviceInterface
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio();

    ASSERT_TRUE(result) << "Failed to retrieve audio from Device.audio() method";
    EXPECT_EQ(result->stereo, expectedValues["stereo"]);
    EXPECT_EQ(result->dolbyDigital5_1, expectedValues["dolbyDigital5.1"]);
    EXPECT_EQ(result->dolbyDigital5_1_plus, expectedValues["dolbyDigital5.1+"]);
    EXPECT_EQ(result->dolbyAtmos, expectedValues["dolbyAtmos"]);
}

std::string networkTypeToString(Firebolt::Device::NetworkType type)
{
    switch (type)
    {
    case Firebolt::Device::NetworkType::WIFI:
        return "wifi";
    case Firebolt::Device::NetworkType::ETHERNET:
        return "ethernet";
    case Firebolt::Device::NetworkType::HYBRID:
        return "hybrid";
    default:
        return "";
    }
}

std::string networkStateToString(Firebolt::Device::NetworkState state)
{
    switch (state)
    {
    case Firebolt::Device::NetworkState::CONNECTED:
        return "connected";
    case Firebolt::Device::NetworkState::DISCONNECTED:
        return "disconnected";
    default:
        return "";
    }
}

TEST_F(DeviceTest, Network)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Device.network"));

    // Getting the actual value from the DeviceInterface
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().network();

    // Perform the assertions
    ASSERT_TRUE(result) << "Failed to retrieve network from Device.network() method";
    EXPECT_EQ(networkStateToString(result->state), expectedValues["state"]);
    EXPECT_EQ(networkTypeToString(result->type), expectedValues["type"]);
}

TEST_F(DeviceTest, ScreenResolution)
{

    // Parse expected JSON values
    nlohmann::json expectedJson;
    std::string jsonString{};
    try
    {
        jsonString = jsonEngine->get_value("Device.screenResolution");
        expectedJson = nlohmann::json::parse(jsonString);
    }
    catch (const nlohmann::json::exception& e)
    {
        FAIL() << "Failed to parse JSON: " << e.what();
    }

    // Validate that expectedJson is an array and has the required number of
    // elements
    if (!expectedJson.is_array())
    {
        FAIL() << "Expected JSON is not an array: " << expectedJson.dump(4);
    }

    // Getting the actual value from the DeviceInterface
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution();

    // Perform the assertions
    ASSERT_TRUE(result) << "Failed to retrieve screenResolution from "
                           "Device.screenResolution() method";
    EXPECT_EQ(*result, jsonString);
}

TEST_F(DeviceTest, VideoResolution)
{

    // Parse expected JSON values
    nlohmann::json expectedJson;
    std::string jsonString{};
    try
    {
        jsonString = jsonEngine->get_value("Device.videoResolution");
        expectedJson = nlohmann::json::parse(jsonString);
    }
    catch (const nlohmann::json::exception& e)
    {
        FAIL() << "Failed to parse JSON: " << e.what();
    }

    // Validate that expectedJson is an array and has the required number of
    // elements
    if (!expectedJson.is_array())
    {
        FAIL() << "Expected JSON is not an array: " << expectedJson.dump(4);
    }

    // Getting the actual value from the DeviceInterface
    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().videoResolution();

    // Perform the assertions
    ASSERT_TRUE(result) << "Failed to retrieve videoResolution from Device.videoResolution() "
                           "method";
    EXPECT_EQ(*result, jsonString);
}

TEST_F(DeviceTest, Name)
{
    auto actual_value = jsonEngine->get_value("Device.name");

    auto result = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name();

    ASSERT_TRUE(result) << "Failed to retrieve name from Device.name() method";
    EXPECT_EQ(*result, REMOVE_QUOTES(actual_value));
}
