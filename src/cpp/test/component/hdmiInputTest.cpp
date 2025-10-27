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

#include "firebolt.h"
#include "json_engine.h"
#include "gtest/gtest.h"

class HDMIInputTest : public ::testing::Test
{
protected:
protected:
    const std::map<std::string, ::Firebolt::HDMIInput::EDIDVersion> EdidVersionMap = {
        {"1.4", ::Firebolt::HDMIInput::EDIDVersion::V1_4},
        {"2.0", ::Firebolt::HDMIInput::EDIDVersion::V2_0},
        {"unknown", ::Firebolt::HDMIInput::EDIDVersion::UNKNOWN},
    };

    const std::map<std::string, ::Firebolt::HDMIInput::HDMISignalStatus> SignalStatusMap = {
        {"none", ::Firebolt::HDMIInput::HDMISignalStatus::NONE},
        {"stable", ::Firebolt::HDMIInput::HDMISignalStatus::STABLE},
        {"unstable", ::Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE},
        {"unsupported", ::Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED},
        {"unknown", ::Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN},
    };
    JsonEngine jsonEngine;
};

TEST_F(HDMIInputTest, autoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["port"] = port;

    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().autoLowLatencyModeCapable(port);
    ASSERT_TRUE(result) << "HDMIInputImpl::autoLowLatencyModeCapable() returned an error";

    auto expectedValue = jsonEngine.get_value("HDMIInput.autoLowLatencyModeCapable").get<bool>();
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(HDMIInputTest, setAutoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    bool value = true;
    nlohmann::json expectedParams;
    expectedParams["port"] = port;
    expectedParams["value"] = value;

    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setAutoLowLatencyModeCapable(port, value);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.setAutoLowLatencyModeCapable() method";

    {
        nlohmann::json expectedParams;
        expectedParams["port"] = port;

        auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().autoLowLatencyModeCapable(port);
        ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.autoLowLatencyModeCapable() method";

        EXPECT_EQ(*result, value);
    }
}

TEST_F(HDMIInputTest, open)
{
    std::string port = "HDMI1";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().open(port);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.open() method";
}

TEST_F(HDMIInputTest, close)
{
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().close();
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.close() method";
}

TEST_F(HDMIInputTest, edidVersion)
{
    std::string port = "HDMI1";

    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().edidVersion(port);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.edidVersion() method";

    auto expectedValue = jsonEngine.get_value("HDMIInput.edidVersion");
    EXPECT_EQ(*result, EdidVersionMap.at(expectedValue));
}

TEST_F(HDMIInputTest, setEdidVersion)
{
    std::string port = "HDMI1";
    std::string valueStr = "2.0";
    Firebolt::HDMIInput::EDIDVersion value = EdidVersionMap.at(valueStr);

    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setEdidVersion(port, value);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.setEdidVersion() method";
    {
        auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().edidVersion(port);
        ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.edidVersion() method";

        EXPECT_EQ(*result, value);
    }
}

TEST_F(HDMIInputTest, lowLatencyMode)
{
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().lowLatencyMode();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("HDMIInput.lowLatencyMode").get<bool>();
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(HDMIInputTest, setLowLatencyMode)
{
    bool value = true;
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setLowLatencyMode(value);
    ASSERT_TRUE(result) << "Error on set";
}

TEST_F(HDMIInputTest, port)
{
    std::string portId = "HDMI1";

    ::Firebolt::Result<::Firebolt::HDMIInput::HDMIInputPort> result =
        Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().port(portId);
    ASSERT_TRUE(result) << "error on get";

    auto expectedValues = jsonEngine.get_value("HDMIInput.port");
    EXPECT_EQ(result->port, expectedValues["port"].get<std::string>());
    EXPECT_EQ(result->arcCapable, expectedValues["arcCapable"].get<bool>());
    EXPECT_EQ(result->arcConnected, expectedValues["arcConnected"].get<bool>());
    EXPECT_EQ(result->autoLowLatencyModeCapable, expectedValues["autoLowLatencyModeCapable"].get<bool>());
    EXPECT_EQ(result->autoLowLatencyModeSignalled, expectedValues["autoLowLatencyModeSignalled"].get<bool>());
    EXPECT_EQ(result->connected, expectedValues["connected"].get<bool>());
    EXPECT_EQ(result->edidVersion, EdidVersionMap.at(expectedValues["edidVersion"].get<std::string>()));
    EXPECT_EQ(result->signal, SignalStatusMap.at(expectedValues["signal"].get<std::string>()));
}

TEST_F(HDMIInputTest, ports)
{

    ::Firebolt::Result<std::vector<Firebolt::HDMIInput::HDMIInputPort>> result =
        Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().ports();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValues = jsonEngine.get_value("HDMIInput.ports");
    ASSERT_EQ(result->size(), expectedValues.size()) << "number of ports mismatch";

    for (size_t i = 0; i < expectedValues.size(); ++i)
    {
        auto expectedPort = expectedValues[i];
        auto actualPort = result->at(i);

        EXPECT_EQ(actualPort.port, expectedPort["port"].get<std::string>());
        EXPECT_EQ(actualPort.arcCapable, expectedPort["arcCapable"].get<bool>());
        EXPECT_EQ(actualPort.arcConnected, expectedPort["arcConnected"].get<bool>());
        EXPECT_EQ(actualPort.autoLowLatencyModeCapable, expectedPort["autoLowLatencyModeCapable"].get<bool>());
        EXPECT_EQ(actualPort.autoLowLatencyModeSignalled, expectedPort["autoLowLatencyModeSignalled"].get<bool>());
        EXPECT_EQ(actualPort.connected, expectedPort["connected"].get<bool>());
        EXPECT_EQ(actualPort.edidVersion, EdidVersionMap.at(expectedPort["edidVersion"].get<std::string>()));
        EXPECT_EQ(actualPort.signal, SignalStatusMap.at(expectedPort["signal"].get<std::string>()));
    }
}
