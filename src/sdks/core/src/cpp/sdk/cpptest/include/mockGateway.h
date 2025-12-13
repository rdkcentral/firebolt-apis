#pragma once
#include "Gateway/Gateway.h"

class MockGateway : public FireboltSDK::GatewayImpl
{
public:
    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 FireboltSDK::JSON::String &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 WPEFramework::Core::JSON::VariantContainer &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 WPEFramework::Core::JSON::Variant &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 WPEFramework::Core::JSON::Boolean &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Authentication::JsonData_Token &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Advertising::JsonData_AdPolicy &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Advertising::JsonData_AdvertisingId &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Advertising::JsonData_AdFrameworkConfig &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Advertising::JsonData_DeviceAttributes &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Accessibility::JsonData_AudioDescriptionSettings &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Device::JsonData_DeviceVersion &response),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Device::JsonData_AudioProfiles &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Device::JsonData_HDCPVersionMap &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Device::JsonData_HDRFormatMap &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Device::JsonData_NetworkInfoResult &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Device::JsonData_Resolution &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 WPEFramework::Core::JSON::ArrayType<Firebolt::Capabilities::JsonData_CapabilityInfo> &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Discovery::JsonData_DiscoveryPolicy &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Localization::JsonData_Info &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Localization::JsonData_LatLon &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Types::JsonData_FlatMap &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Types::JsonData_BooleanMap &result),
                (override));

    MOCK_METHOD(Firebolt::Error, Request,
                (const std::string &method,
                 const JsonObject &parameters,
                 Firebolt::Parameters::JsonData_AppInitialization &result),
                (override));
};

class GatewayMockTest : public ::testing::Test
{
public:
    Firebolt::Error error;
    MockGateway *mockGateway;

    void SetUp() override
    {
        std::unique_ptr<MockGateway> mock = std::make_unique<MockGateway>();
        mockGateway = mock.get();
        FireboltSDK::Gateway::Instance().UpdateGateway(std::move(mock));
    }

    void TearDown() override
    {
        FireboltSDK::Gateway::Instance().UpdateGateway(nullptr); // Reset the instance
        mockGateway = nullptr;
    }

    void TestBody() override {}
};