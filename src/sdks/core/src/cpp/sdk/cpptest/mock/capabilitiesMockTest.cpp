#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "advertising_impl.h"
#include "Gateway/Gateway.h"
#include "mockProperties.h"
#include "mockGateway.h"

class CapabilitiesMockTest : public ::testing::Test
{
protected:
    std::unique_ptr<GatewayMockTest> gm;

    void SetUp() override
    {
        gm = std::make_unique<GatewayMockTest>();
        gm->SetUp();
    }

    void TearDown() override
    {
        gm->TearDown();
        gm.reset(); // Cleanup
    }
};


TEST_F(CapabilitiesMockTest, Available_Success) {
    std::string capability = "someCapability";
    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("capabilities.available", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().available(capability, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(CapabilitiesMockTest, Available_Failure) {
    std::string capability = "someCapability";

    EXPECT_CALL(*gm->mockGateway, Request("capabilities.available", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    bool result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().available(capability, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(result);
}

TEST_F(CapabilitiesMockTest, Granted_Failure) {
    std::string capability = "someCapability";
    EXPECT_CALL(*gm->mockGateway, Request("capabilities.granted", _, Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    bool result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().granted(capability, std::nullopt, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(result);
}

// TEST_F(CapabilitiesMockTest, Info_Success) {
//     std::vector<std::string> capabilities = {"capability1", "capability2"};
//     WPEFramework::Core::JSON::ArrayType<Firebolt::Capabilities::JsonData_CapabilityInfo> mockResponse;
    
//     Firebolt::Capabilities::JsonData_CapabilityInfo info1;
//     info1.Capability = "capability1";
//     info1.Supported = true;
//     info1.Available = true;
//     mockResponse.Add(info1);

//     EXPECT_CALL(*gm->mockGateway, Request("capabilities.info", _, Matcher<WPEFramework::Core::JSON::ArrayType<Firebolt::Capabilities::JsonData_CapabilityInfo> &>(_)))
//         .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

//     auto result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().info(capabilities, &gm->error);
//     EXPECT_EQ(gm->error, Firebolt::Error::None);
//     ASSERT_FALSE(result.empty());
//     EXPECT_EQ(result[0].capability, "capability1");
//     EXPECT_TRUE(result[0].supported);
//     EXPECT_TRUE(result[0].available);
// }

// TEST_F(CapabilitiesMockTest, Info_Failure) {
//     std::vector<std::string> capabilities = {"capability1"};
//     EXPECT_CALL(*gm->mockGateway, Request("capabilities.info", _, Matcher<WPEFramework::Core::JSON::ArrayType<Firebolt::Capabilities::JsonData_CapabilityInfo> &>(_)))
//         .WillOnce(Return(Firebolt::Error::General));

//     auto result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().info(capabilities, &gm->error);
//     EXPECT_EQ(gm->error, Firebolt::Error::General);
//     EXPECT_TRUE(result.empty());
// }

TEST_F(CapabilitiesMockTest, Permitted_Success) {
    std::string capability = "someCapability";
    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;

    EXPECT_CALL(*gm->mockGateway, Request("capabilities.permitted", _, Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    bool result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().permitted(capability, std::nullopt, &gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(CapabilitiesMockTest, Permitted_Failure) {
    std::string capability = "someCapability";
    EXPECT_CALL(*gm->mockGateway, Request("capabilities.permitted", _, Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    bool result = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().permitted(capability, std::nullopt, &gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(result);
}