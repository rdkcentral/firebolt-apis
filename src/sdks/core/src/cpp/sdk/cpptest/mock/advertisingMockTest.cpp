#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "advertising_impl.h"
#include "Gateway/Gateway.h"
#include "mockProperties.h"
#include "mockGateway.h"

using namespace testing;

class AdvertisingMockTest : public ::testing::Test
{
protected:
    std::unique_ptr<GatewayMockTest> gm;
    std::unique_ptr<PropertiesMockTest> pm;

    void SetUp() override
    {
        gm = std::make_unique<GatewayMockTest>();
        gm->SetUp();

        pm = std::make_unique<PropertiesMockTest>();
        pm->SetUp();
    }

    void TearDown() override
    {
        gm->TearDown();
        gm.reset(); // Cleanup

        pm->TearDown();
        pm.reset(); // Cleanup
    }
};

TEST_F(AdvertisingMockTest, AdvertisingId_Success)
{
    Firebolt::Advertising::JsonData_AdvertisingId mockResponse;
    mockResponse.Ifa = "valid_ad_id";
    mockResponse.Ifa_type = "randomized";
    mockResponse.Lmt = "true";

    EXPECT_CALL(*gm->mockGateway, Request("advertising.advertisingId", _, testing::Matcher<Firebolt::Advertising::JsonData_AdvertisingId &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Advertising::AdvertisingId result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().advertisingId(std::nullopt, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result.ifa, "valid_ad_id");
    EXPECT_EQ(result.ifa_type.value(), "randomized");
    EXPECT_EQ(result.lmt.value(), "true");
}

TEST_F(AdvertisingMockTest, AdvertisingId_Failure)
{
    EXPECT_CALL(*gm->mockGateway, Request("advertising.advertisingId", _, testing::Matcher<Firebolt::Advertising::JsonData_AdvertisingId &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Advertising::AdvertisingId result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().advertisingId(std::nullopt, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_EQ(result.ifa, "");
    EXPECT_FALSE(result.ifa_type.has_value());
    EXPECT_FALSE(result.lmt.has_value());
}

TEST_F(AdvertisingMockTest, AppBundleId_Success)
{
    FireboltSDK::JSON::String mockResponse = "com.example.app";
    EXPECT_CALL(*gm->mockGateway, Request("advertising.appBundleId", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().appBundleId(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "com.example.app");
}

TEST_F(AdvertisingMockTest, AppBundleId_Failure)
{
    EXPECT_CALL(*gm->mockGateway, Request("advertising.appBundleId", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().appBundleId(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(AdvertisingMockTest, Config_Success)
{
    Firebolt::Advertising::JsonData_AdFrameworkConfig mockResponse;
    mockResponse.FromString("{\"configKey\": \"configValue\"}");
    EXPECT_CALL(*gm->mockGateway, Request("advertising.config", _, testing::Matcher<Firebolt::Advertising::JsonData_AdFrameworkConfig &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Advertising::AdConfigurationOptions options;
    options.coppa = true;
    options.environment = Firebolt::Advertising::AdConfigurationOptionsEnvironment::TEST;
    options.authenticationEntity = "test_auth";

    Firebolt::Advertising::AdvertisingImpl advertisingImpl;
    Firebolt::Advertising::AdFrameworkConfig result = advertisingImpl.config(options, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "{\"configKey\":\"configValue\"}");
}

TEST_F(AdvertisingMockTest, Config_Failure)
{
    EXPECT_CALL(*gm->mockGateway, Request("advertising.config", _, testing::Matcher<Firebolt::Advertising::JsonData_AdFrameworkConfig &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Advertising::AdConfigurationOptions options;
    options.coppa = false;
    options.environment = Firebolt::Advertising::AdConfigurationOptionsEnvironment::PROD;
    options.authenticationEntity = "auth";

    Firebolt::Advertising::AdvertisingImpl advertisingImpl;
    Firebolt::Advertising::AdFrameworkConfig result = advertisingImpl.config(options, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(AdvertisingMockTest, Config_InvalidJsonResponse)
{
    Firebolt::Advertising::AdConfigurationOptions options;

    // Mocking an invalid JSON response
    Firebolt::Advertising::JsonData_AdFrameworkConfig mockResponse;
    mockResponse.FromString("{invalid_json_response}"); // Simulating a malformed JSON

    EXPECT_CALL(*gm->mockGateway, Request("advertising.config", _, testing::Matcher<Firebolt::Advertising::JsonData_AdFrameworkConfig &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Advertising::AdFrameworkConfig result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().config(options, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "{}"); // Expect an empty/default AdFrameworkConfig due to parsing failure.
}

TEST_F(AdvertisingMockTest, DeviceAttributes_Success)
{
    Firebolt::Advertising::JsonData_DeviceAttributes mockResponse;
    mockResponse.Set("deviceKey", WPEFramework::Core::JSON::Variant("deviceValue"));
    EXPECT_CALL(*gm->mockGateway, Request("advertising.deviceAttributes", _, testing::Matcher<Firebolt::Advertising::JsonData_DeviceAttributes &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Advertising::DeviceAttributes result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().deviceAttributes(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "{\"deviceKey\":\"deviceValue\"}");
}

TEST_F(AdvertisingMockTest, DeviceAttributes_Failure)
{
    EXPECT_CALL(*gm->mockGateway, Request("advertising.deviceAttributes", _, testing::Matcher<Firebolt::Advertising::JsonData_DeviceAttributes &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Advertising::DeviceAttributes result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().deviceAttributes(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(AdvertisingMockTest, DeviceAttributes_InvalidJson)
{
    Firebolt::Advertising::JsonData_DeviceAttributes mockResponse;
    mockResponse.Set("error", WPEFramework::Core::JSON::Variant("invalid_json_response"));
    EXPECT_CALL(*gm->mockGateway, Request("advertising.deviceAttributes", _, testing::Matcher<Firebolt::Advertising::JsonData_DeviceAttributes &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Advertising::DeviceAttributes result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().deviceAttributes(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "{\"error\":\"invalid_json_response\"}");
}

TEST_F(AdvertisingMockTest, Policy_PartialSuccess_SkipRestrictionOnly)
{
    Firebolt::Advertising::JsonData_AdPolicy mockResponse;
    mockResponse.SkipRestriction = Firebolt::Advertising::SkipRestriction::NONE;

    EXPECT_CALL(*pm->mockProperties, Get("advertising.policy", testing::Matcher<Firebolt::Advertising::JsonData_AdPolicy &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Advertising::AdPolicy result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().policy(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result.skipRestriction, Firebolt::Advertising::SkipRestriction::NONE);
    EXPECT_FALSE(result.limitAdTracking);
}

TEST_F(AdvertisingMockTest, Policy_Failure)
{
    EXPECT_CALL(*pm->mockProperties, Get("advertising.policy", testing::Matcher<Firebolt::Advertising::JsonData_AdPolicy &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Advertising::AdPolicy result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().policy(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_FALSE(result.skipRestriction);
    EXPECT_FALSE(result.limitAdTracking);
}
