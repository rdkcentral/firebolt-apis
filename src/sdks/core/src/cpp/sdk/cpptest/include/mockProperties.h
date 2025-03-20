#pragma once

#include "Properties/Properties.h"

class MockProperties : public FireboltSDK::Properties
{
public:
    MOCK_METHOD(Firebolt::Error, Get,
                (const string &propertyName,
                 FireboltSDK::JSON::String &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Advertising::JsonData_AdPolicy &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Accessibility::JsonData_AudioDescriptionSettings &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Device::JsonData_AudioProfiles &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Device::JsonData_HDCPVersionMap &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Device::JsonData_HDRFormatMap &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Device::JsonData_NetworkInfoResult &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Device::JsonData_Resolution &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Get,
                (const std::string &propertyName,
                 Firebolt::Discovery::JsonData_DiscoveryPolicy &response),
                (override));
};

class PropertiesMockTest : public ::testing::Test
{
public:
    Firebolt::Error error;
    MockProperties *mockProperties;

    void SetUp() override
    {

        std::unique_ptr<MockProperties> mock = std::make_unique<MockProperties>();
        mockProperties = mock.get();
        FireboltSDK::Properties::Instance().UpdateProperties(std::move(mock));
    }

    void TearDown() override
    {
        FireboltSDK::Properties::Instance().UpdateProperties(nullptr);
        mockProperties = nullptr;
    }

    void TestBody() override {}
};