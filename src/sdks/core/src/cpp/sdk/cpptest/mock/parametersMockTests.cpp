#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "parameters_impl.h"
#include "../unit/unit.h"
#include "Gateway/Gateway.h"
#include "mockGateway.h"

using namespace testing;

class ParametersMockTest : public ::testing::Test
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


TEST_F(ParametersMockTest, Initialization_Success) {
    Firebolt::Parameters::JsonData_AppInitialization mockResponse;
    mockResponse.Us_privacy = "1YYN";
    mockResponse.Lmt = true;
    mockResponse.Discovery.NavigateTo = "home";
    mockResponse.SecondScreen.LaunchRequest.Type = Firebolt::SecondScreen::SecondScreenEventType::DIAL;
    mockResponse.SecondScreen.LaunchRequest.Version = "1.0";
    mockResponse.SecondScreen.LaunchRequest.Data = "payload";
    

    EXPECT_CALL(*gm->mockGateway, Request("parameters.initialization", _, testing::Matcher<Firebolt::Parameters::JsonData_AppInitialization &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Parameters::AppInitialization result = Firebolt::IFireboltAccessor::Instance().ParametersInterface().initialization(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result.us_privacy, "1YYN");
    EXPECT_EQ(result.lmt, true);
    ASSERT_TRUE(result.discovery.has_value());
    EXPECT_EQ(result.discovery->navigateTo, "home");
    ASSERT_TRUE(result.secondScreen.has_value());
    ASSERT_TRUE(result.secondScreen->launchRequest.has_value());
    EXPECT_EQ(result.secondScreen->launchRequest->type, Firebolt::SecondScreen::SecondScreenEventType::DIAL);
    EXPECT_EQ(result.secondScreen->launchRequest->version, "1.0");
    EXPECT_EQ(result.secondScreen->launchRequest->data, "payload");
}

TEST_F(ParametersMockTest, Initialization_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("parameters.initialization", _, testing::Matcher<Firebolt::Parameters::JsonData_AppInitialization &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    Firebolt::Parameters::AppInitialization result = Firebolt::IFireboltAccessor::Instance().ParametersInterface().initialization(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
}
