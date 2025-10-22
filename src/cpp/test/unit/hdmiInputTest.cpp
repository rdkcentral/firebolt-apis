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

#include "hdmiinput_impl.h"
#include "json_engine.h"
#include "mock_helper.h"

const std::map<std::string, ::Firebolt::HDMIInput::EDIDVersion> EdidVersionMap = {
    { "1.4", ::Firebolt::HDMIInput::EDIDVersion::V1_4 },
    { "2.0", ::Firebolt::HDMIInput::EDIDVersion::V2_0 },
    { "unknown", ::Firebolt::HDMIInput::EDIDVersion::UNKNOWN },
};

const std::map<std::string, ::Firebolt::HDMIInput::HDMISignalStatus> SignalStatusMap = {
    { "none", ::Firebolt::HDMIInput::HDMISignalStatus::NONE },
    { "stable", ::Firebolt::HDMIInput::HDMISignalStatus::STABLE },
    { "unstable", ::Firebolt::HDMIInput::HDMISignalStatus::UNSTABLE },
    { "unsupported", ::Firebolt::HDMIInput::HDMISignalStatus::UNSUPPORTED },
    { "unknown", ::Firebolt::HDMIInput::HDMISignalStatus::UNKNOWN },
};

class HDMIInputTest : public ::testing::Test
{
protected:
    Firebolt::Result<nlohmann::json> getter(const std::string &methodName, const nlohmann::json &parameters)
    {
        nlohmann::json message;
        message["method"] = methodName;
        if (!parameters.is_null())
        {
            message["params"] = parameters;
        }

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


    void mockSubscribe(const std::string &eventName)
    {
        EXPECT_CALL(mockHelper, subscribe(_, eventName, _, _))
            .WillOnce(Invoke(
                [&](void* owner, const std::string &eventName, std::any &&notification,
                    void (*callback)(void *, const nlohmann::json &))
                {
                    return Firebolt::Result<Firebolt::SubscriptionId>{1};
                }));
        EXPECT_CALL(mockHelper, unsubscribe(1)) 
            .WillOnce(Invoke(
                [&](Firebolt::SubscriptionId id)
                {
                    return Firebolt::Result<void>{Firebolt::Error::None};
                }));
    }

protected:
    JsonEngine jsonEngine;
    nlohmann::json lastSetParams;
    ::testing::NiceMock<MockHelper> mockHelper;
    Firebolt::HDMIInput::HDMIInputImpl hdmiImpl_{mockHelper};
};

TEST_F(HDMIInputTest, autoLowLatencyModeCapable)
{
    std::string port = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["port"] = port;

    EXPECT_CALL(mockHelper, getJson("HDMIInput.autoLowLatencyModeCapable", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                return getter(methodName, parameters);
            }));

    auto result = hdmiImpl_.autoLowLatencyModeCapable(port);
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

    EXPECT_CALL(mockHelper, set("HDMIInput.setAutoLowLatencyModeCapable", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                lastSetParams = parameters;
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));

    auto result = hdmiImpl_.setAutoLowLatencyModeCapable(port, value);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.setAutoLowLatencyModeCapable() method";

    {
        nlohmann::json expectedParams;
        expectedParams["port"] = port;

        EXPECT_CALL(mockHelper, getJson("HDMIInput.autoLowLatencyModeCapable", expectedParams))
            .WillOnce(Invoke(
                [&](const std::string &methodName, const nlohmann::json &parameters)
                {
                    return Firebolt::Result<nlohmann::json>{lastSetParams["value"]};
                }));
        auto result = hdmiImpl_.autoLowLatencyModeCapable(port);
        ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.autoLowLatencyModeCapable() method";

        EXPECT_EQ(*result, value);
    }
}

TEST_F(HDMIInputTest, open)
{
    std::string port = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["portId"] = port;

    EXPECT_CALL(mockHelper, invoke("HDMIInput.open", expectedParams))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));
    hdmiImpl_.open(port);
}

TEST_F(HDMIInputTest, close)
{
    std::string port = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["portId"] = port;

    EXPECT_CALL(mockHelper, invoke("HDMIInput.close", expectedParams)).Times(0);
    hdmiImpl_.close();
}

TEST_F(HDMIInputTest, open_then_close)
{
    std::string port = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["portId"] = port;

    EXPECT_CALL(mockHelper, invoke("HDMIInput.open", expectedParams))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));
    hdmiImpl_.open(port);

    EXPECT_CALL(mockHelper, invoke("HDMIInput.close", expectedParams))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));
    hdmiImpl_.close();
}

TEST_F(HDMIInputTest, open_then_open)
{
    std::string port1 = "HDMI1";
    nlohmann::json expectedParams1;
    expectedParams1["portId"] = port1;

    EXPECT_CALL(mockHelper, invoke("HDMIInput.open", expectedParams1))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));
    hdmiImpl_.open(port1);

    std::string port2 = "HDMI2";
    nlohmann::json expectedParams2;
    expectedParams2["portId"] = port2;

    EXPECT_CALL(mockHelper, invoke("HDMIInput.close", expectedParams1))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));
    EXPECT_CALL(mockHelper, invoke("HDMIInput.open", expectedParams2))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                         { return Firebolt::Result<void>{Firebolt::Error::None}; }));
    hdmiImpl_.open(port2);
}

TEST_F(HDMIInputTest, edidVersion)
{
    std::string port = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["port"] = port;

    EXPECT_CALL(mockHelper, getJson("HDMIInput.edidVersion", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                return getter(methodName, parameters);
            }));

    auto result = hdmiImpl_.edidVersion(port);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.edidVersion() method";

    auto expectedValue = jsonEngine.get_value("HDMIInput.edidVersion");
    EXPECT_EQ(*result, EdidVersionMap.at(expectedValue));
}

TEST_F(HDMIInputTest, setEdidVersion)
{
    std::string port = "HDMI1";
    std::string valueStr = "2.0";
    Firebolt::HDMIInput::EDIDVersion value = EdidVersionMap.at(valueStr);
    nlohmann::json expectedParams;
    expectedParams["port"] = port;
    expectedParams["value"] = valueStr;

    EXPECT_CALL(mockHelper, set("HDMIInput.setEdidVersion", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                lastSetParams = parameters;
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));
    auto result = hdmiImpl_.setEdidVersion(port, value);
    ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.setEdidVersion() method";

    {
        nlohmann::json expectedParams;
        expectedParams["port"] = port;

        EXPECT_CALL(mockHelper, getJson("HDMIInput.edidVersion", expectedParams))
            .WillOnce(Invoke(
                [&](const std::string &methodName, const nlohmann::json &parameters)
                {
                    return Firebolt::Result<nlohmann::json>{lastSetParams["value"]};
                }));
        auto result = hdmiImpl_.edidVersion(port);
        ASSERT_TRUE(result) << "Error on calling HDMIInputInterface.edidVersion() method";

        EXPECT_EQ(*result, value);
    }
}


TEST_F(HDMIInputTest, lowLatencyMode)
{
    EXPECT_CALL(mockHelper, getJson("HDMIInput.lowLatencyMode", _))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                return getter(methodName, parameters);
            }));

    auto result = hdmiImpl_.lowLatencyMode();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("HDMIInput.lowLatencyMode").get<bool>();
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(HDMIInputTest, setLowLatencyMode)
{
    bool value = true;
    nlohmann::json expectedParams = value;

    EXPECT_CALL(mockHelper, set("HDMIInput.setLowLatencyMode", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                lastSetParams = parameters;
                return Firebolt::Result<void>{Firebolt::Error::None};
            }));

    auto result = hdmiImpl_.setLowLatencyMode(value);
    ASSERT_TRUE(result) << "Error on set";

    {
        nlohmann::json expectedParams;

        EXPECT_CALL(mockHelper, getJson("HDMIInput.lowLatencyMode", _))
            .WillOnce(Invoke(
                [&](const std::string &methodName, const nlohmann::json &parameters)
                {
                    return Firebolt::Result<nlohmann::json>{lastSetParams};
                }));
        auto result = hdmiImpl_.lowLatencyMode();
        ASSERT_TRUE(result) << "Error on get";

        EXPECT_EQ(*result, value);
    }
}


TEST_F(HDMIInputTest, port)
{
    std::string portId = "HDMI1";
    nlohmann::json expectedParams;
    expectedParams["portId"] = portId;

    EXPECT_CALL(mockHelper, getJson("HDMIInput.port", expectedParams))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                return getter(methodName, parameters);
            }));

    ::Firebolt::Result<::Firebolt::HDMIInput::HDMIInputPort> result = hdmiImpl_.port(portId);
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
    EXPECT_CALL(mockHelper, getJson("HDMIInput.ports", _))
        .WillOnce(Invoke(
            [&](const std::string &methodName, const nlohmann::json &parameters)
            {
                return getter(methodName, parameters);
            }));

    ::Firebolt::Result<std::vector<Firebolt::HDMIInput::HDMIInputPort>> result = hdmiImpl_.ports();
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

// Events related tests

TEST_F(HDMIInputTest, subscribeOnAutoLowLatencyModeCapableChanged)
{
    mockSubscribe("HDMIInput.onAutoLowLatencyModeCapableChanged");

    auto id = hdmiImpl_.subscribeOnAutoLowLatencyModeCapableChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = hdmiImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(HDMIInputTest, subscribeOnAutoLowLatencyModeSignalChanged)
{
    mockSubscribe("HDMIInput.onAutoLowLatencyModeSignalChanged");

    auto id = hdmiImpl_.subscribeOnAutoLowLatencyModeSignalChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = hdmiImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}


TEST_F(HDMIInputTest, subscribeOnConnectionChanged)
{
    mockSubscribe("HDMIInput.onConnectionChanged");

    auto id = hdmiImpl_.subscribeOnConnectionChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = hdmiImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(HDMIInputTest, subscribeOnEdidVersionChanged)
{
    mockSubscribe("HDMIInput.onEdidVersionChanged");

    auto id = hdmiImpl_.subscribeOnEdidVersionChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = hdmiImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(HDMIInputTest, subscribeOnLowLatencyModeChanged)
{
    mockSubscribe("HDMIInput.onLowLatencyModeChanged");

    auto id = hdmiImpl_.subscribeOnLowLatencyModeChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = hdmiImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(HDMIInputTest, subscribeOnSignalChanged)
{
    mockSubscribe("HDMIInput.onSignalChanged");

    auto id = hdmiImpl_.subscribeOnSignalChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = hdmiImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}
