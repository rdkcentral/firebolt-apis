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

#include "unit.h"

class HDMIInputTest : public ::testing::Test
{
protected:
    JsonEngine* jsonEngine;

    void SetUp() override { jsonEngine = new JsonEngine(); }

    void TearDown() override { delete jsonEngine; }
};

TEST_F(HDMIInputTest, setAutoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    bool expected_value = true;
    auto result =
        Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setAutoLowLatencyModeCapable(port, expected_value);
    EXPECT_EQ(result.error(), Firebolt::Error::None)
        << "Error on calling HDMIInputInterface.setAutoLowLatencyModeCapable() "
           "method";
}

TEST_F(HDMIInputTest, autoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    std::string expectedValues = jsonEngine->get_value("HDMIInput.autoLowLatencyModeCapable");
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().autoLowLatencyModeCapable(port);
    EXPECT_TRUE(result) << "Error on calling HDMIInputInterface.autoLowLatencyModeCapable() "
                           "method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues) == "true", *result) << "Error: wrong autoLowLatencyModeCapable returned by "
                                                                   "HDMIInputInterface.autoLowLatencyModeCapable()";
}

TEST_F(HDMIInputTest, close)
{
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().close();
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling HDMIInputInterface.close() method";
}

TEST_F(HDMIInputTest, edidVersion)
{
    std::string port = "HDMI1";
    std::string expectedValues = jsonEngine->get_value("HDMIInput.edidVersion");
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().edidVersion(port);

    std::string actual_version;
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.edidVersion() method";
    switch (*result)
    {
    case Firebolt::HDMIInput::EDIDVersion::V1_4:
        actual_version = "1.4";
        break;
    case Firebolt::HDMIInput::EDIDVersion::V2_0:
        actual_version = "2.0";
        break;
    case Firebolt::HDMIInput::EDIDVersion::UNKNOWN:
        actual_version = "unknown";
        break;
    default:
        actual_version = "invalid_version";
    }

    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_version) << "Error: wrong edidVersion returned by "
                                                                "HDMIInputInterface.edidVersion()";
}

TEST_F(HDMIInputTest, setEdidVersion)
{
    std::string port = "HDMI1";
    Firebolt::HDMIInput::EDIDVersion expected_version =
        Firebolt::HDMIInput::EDIDVersion::V1_4; // Replace with appropriate enum
                                                // value
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setEdidVersion(port, expected_version);
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling HDMIInputInterface.setEdidVersion() method";
}

TEST_F(HDMIInputTest, lowLatencyMode)
{
    std::string expectedValues = jsonEngine->get_value("HDMIInput.lowLatencyMode");
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().lowLatencyMode();
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.lowLatencyMode() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues) == "true", *result) << "Error: wrong lowLatencyMode returned by "
                                                                   "HDMIInputInterface.lowLatencyMode()";
}

TEST_F(HDMIInputTest, setLowLatencyMode)
{
    bool expected_value = true;
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setLowLatencyMode(expected_value);
    EXPECT_EQ(result.error(), Firebolt::Error::None)
        << "Error on calling HDMIInputInterface.setLowLatencyMode() method";
}

TEST_F(HDMIInputTest, open)
{
    std::string portId = "HDMI1";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().open(portId);
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error on calling HDMIInputInterface.open() method";
}

TEST_F(HDMIInputTest, port)
{
    std::string portId = "HDMI1";
    std::string expectedValues = jsonEngine->get_value("HDMIInput.port");
    auto port = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().port(portId);

    ASSERT_TRUE(port);
    std::string actual_settings;
    actual_settings += "\"arcCapable\":" + std::string(port->arcCapable ? "true" : "false") + ",";
    actual_settings += "\"arcConnected\":" + std::string(port->arcConnected ? "true" : "false") + ",";
    actual_settings +=
        "\"autoLowLatencyModeCapable\":" + std::string(port->autoLowLatencyModeCapable ? "true" : "false") + ",";
    actual_settings +=
        "\"autoLowLatencyModeSignalled\":" + std::string(port->autoLowLatencyModeSignalled ? "true" : "false") + ",";
    actual_settings += "\"connected\":" + std::string(port->connected ? "true" : "false") + ",";

    switch (port->edidVersion)
    {
    case Firebolt::HDMIInput::EDIDVersion::V1_4:
        actual_settings += "\"edidVersion\":\"1.4\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::V2_0:
        actual_settings += "\"edidVersion\":\"2.0\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::UNKNOWN:
        actual_settings += "\"edidVersion\":unknown,";
        break;
    default:
        actual_settings += "\"edidVersion\":invalid,";
    }
    actual_settings += "\"port\":\"" + std::string(port->port) + "\",";

    switch (port->signal)
    {
    case Firebolt::HDMIInput::HDMISignalStatus::NONE:
        actual_settings += "\"signal\":\"none\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::STABLE:
        actual_settings += "\"signal\":\"stable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE:
        actual_settings += "\"signal\":\"unstable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED:
        actual_settings += "\"signal\":\"unsupported\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN:
        actual_settings += "\"signal\":\"unknown\"";
        break;
    default:
        actual_settings += "\"signal\":\"invalid\"";
    }

    EXPECT_EQ(port.error(), Firebolt::Error::None) << "Error on calling HDMIInputInterface.port() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_settings)
        << "Error: wrong port returned by HDMIInputInterface.port()";
}

TEST_F(HDMIInputTest, ports)
{
    std::string expectedValues = jsonEngine->get_value("HDMIInput.ports");
    auto ports = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().ports();

    ASSERT_TRUE(ports);
    ASSERT_NE(ports->size(), 0) << "Error: ports returned by HDMIInputInterface.ports() is empty";
    Firebolt::HDMIInput::HDMIInputPort port = ports->at(0);
    std::string actual_settings = "{";
    actual_settings += "\"arcCapable\":" + std::string(port.arcCapable ? "true" : "false") + ",";
    actual_settings += "\"arcConnected\":" + std::string(port.arcConnected ? "true" : "false") + ",";
    actual_settings +=
        "\"autoLowLatencyModeCapable\":" + std::string(port.autoLowLatencyModeCapable ? "true" : "false") + ",";
    actual_settings +=
        "\"autoLowLatencyModeSignalled\":" + std::string(port.autoLowLatencyModeSignalled ? "true" : "false") + ",";
    actual_settings += "\"connected\":" + std::string(port.connected ? "true" : "false") + ",";

    switch (port.edidVersion)
    {
    case Firebolt::HDMIInput::EDIDVersion::V1_4:
        actual_settings += "\"edidVersion\":\"1.4\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::V2_0:
        actual_settings += "\"edidVersion\":\"2.0\",";
        break;
    case Firebolt::HDMIInput::EDIDVersion::UNKNOWN:
        actual_settings += "\"edidVersion\":unknown,";
        break;
    default:
        actual_settings += "\"edidVersion\":invalid,";
    }
    actual_settings += "\"port\":\"" + std::string(port.port) + "\",";

    switch (port.signal)
    {
    case Firebolt::HDMIInput::HDMISignalStatus::NONE:
        actual_settings += "\"signal\":\"none\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::STABLE:
        actual_settings += "\"signal\":\"stable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE:
        actual_settings += "\"signal\":\"unstable\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED:
        actual_settings += "\"signal\":\"unsupported\"";
        break;
    case Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN:
        actual_settings += "\"signal\":\"unknown\"";
        break;
    default:
        actual_settings += "\"signal\":\"invalid\"";
    }
    actual_settings += "}";

    EXPECT_EQ(ports.error(), Firebolt::Error::None) << "Error on calling HDMIInputInterface.ports() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), actual_settings)
        << "Error: wrong ports returned by HDMIInputInterface.ports()";
}

// Events related tests
TEST_F(HDMIInputTest, subscribeOnAutoLowLatencyModeCapableChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnAutoLowLatencyModeCapableChanged(
        [](auto) { std::cout << "AutoLowLatencyModeCapable changed\n"; });
    EXPECT_TRUE(id.has_value()) << "Error in subscribing to AutoLowLatencyModeCapable Changed";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(id.value_or(0));
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error in unsubscribing to AutoLowLatencyModeCapable Changed";
}

TEST_F(HDMIInputTest, subscribeOnAutoLowLatencyModeSignalChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnAutoLowLatencyModeSignalChanged(
        [](auto) { std::cout << "AutoLowLatencyModeSignal changed\n"; });
    EXPECT_TRUE(id.has_value()) << "Error in subscribing to AutoLowLatencyModeSignal Changed";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(id.value_or(0));
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error in unsubscribing to AutoLowLatencyModeSignal Changed";
}

TEST_F(HDMIInputTest, subscribeOnConnectionChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnConnectionChanged(
        [](auto) { std::cout << "Connection changed\n"; });
    EXPECT_TRUE(id.has_value()) << "Error in subscribing to Connection Changed";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(id.value_or(0));
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error in unsubscribing to Connection Changed";
}

TEST_F(HDMIInputTest, subscribeOnEdidVersionChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnEdidVersionChanged(
        [](auto) { std::cout << "EdidVersion changed\n"; });
    EXPECT_TRUE(id.has_value()) << "Error in subscribing to EdidVersion Changed";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(id.value_or(0));
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error in unsubscribing to EdidVersion Changed";
}

TEST_F(HDMIInputTest, subscribeOnLowLatencyModeChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnLowLatencyModeChanged(
        [](auto) { std::cout << "LowLatencyMode changed\n"; });
    EXPECT_TRUE(id.has_value()) << "Error in subscribing to LowLatencyMode Changed";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(id.value_or(0));
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error in unsubscribing to LowLatencyMode Changed";
}

TEST_F(HDMIInputTest, subscribeOnSignalChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribeOnSignalChanged(
        [](auto) { std::cout << "Signal changed\n"; });
    EXPECT_TRUE(id.has_value()) << "Error in subscribing to Signal Changed";
    auto result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(id.value_or(0));
    EXPECT_EQ(result.error(), Firebolt::Error::None) << "Error in unsubscribing to Signal Changed";
}
