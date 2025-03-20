#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "secondscreen_impl.h"
#include "../unit/unit.h"
#include "Gateway/Gateway.h"
#include "mockProperties.h"
#include "mockGateway.h"

using namespace testing;

class SecondScreenMockTest : public ::testing::Test
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

TEST_F(SecondScreenMockTest, Device_Success) {
    FireboltSDK::JSON::String mockResponse = "valid_device_id";
    JsonObject jsonParameters;
    EXPECT_CALL(*gm->mockGateway, Request("secondscreen.device", _, Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().device(std::nullopt, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "valid_device_id");
}

TEST_F(SecondScreenMockTest, Device_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("secondscreen.device", _, Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    std::string result = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().device(std::nullopt, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_EQ(result, "");
}

TEST_F(SecondScreenMockTest, FriendlyName_Success) {
    FireboltSDK::JSON::String mockResponse = "Test_Device";
    EXPECT_CALL(*pm->mockProperties, Get("secondscreen.friendlyName", Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));

    std::string result = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().friendlyName(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "Test_Device");
}

TEST_F(SecondScreenMockTest, FriendlyName_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("secondscreen.friendlyName", Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string result = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().friendlyName(&pm->error);

    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(SecondScreenMockTest, Protocols_Success) {
    Firebolt::Types::JsonData_BooleanMap mockResponse;
    mockResponse.Set("AirPlay", true);
    mockResponse.Set("GoogleCast", false);
    
    EXPECT_CALL(*gm->mockGateway, Request("secondscreen.protocols", _, Matcher<Firebolt::Types::JsonData_BooleanMap &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    auto result = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().protocols(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result["AirPlay"], true);
    EXPECT_EQ(result["GoogleCast"], false);
}

TEST_F(SecondScreenMockTest, Protocols_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("secondscreen.protocols", _, Matcher<Firebolt::Types::JsonData_BooleanMap &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    auto result = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().protocols(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(result.empty());
}