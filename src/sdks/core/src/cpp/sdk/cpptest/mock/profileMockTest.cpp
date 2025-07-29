#include "profile_impl.h"
#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gateway/Gateway.h"
#include "mockGateway.h"

using namespace testing;

class ProfileMockTest : public ::testing::Test
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
TEST_F(ProfileMockTest, ApproveContentRating_Success) {
    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;
    
    EXPECT_CALL(*gm->mockGateway, Request("profile.approveContentRating", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));
    
    bool result = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approveContentRating(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(ProfileMockTest, ApproveContentRating_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("profile.approveContentRating", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));
    
    bool result = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approveContentRating(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(result);
}

TEST_F(ProfileMockTest, ApprovePurchase_Success) {
    WPEFramework::Core::JSON::Boolean mockResponse;
    mockResponse = true;
    
    EXPECT_CALL(*gm->mockGateway, Request("profile.approvePurchase", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));
    
    bool result = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approvePurchase(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_TRUE(result);
}

TEST_F(ProfileMockTest, ApprovePurchase_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("profile.approvePurchase", _, testing::Matcher<WPEFramework::Core::JSON::Boolean &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));
    
    bool result = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approvePurchase(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_FALSE(result);
}

TEST_F(ProfileMockTest, Flags_Success) {
    Firebolt::Types::JsonData_FlatMap mockResponse;
    mockResponse.Set("flag1", "value1");
    mockResponse.Set("flag2", "value2");
    
    EXPECT_CALL(*gm->mockGateway, Request("profile.flags", _, testing::Matcher<Firebolt::Types::JsonData_FlatMap &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));
    
    Firebolt::Types::FlatMap result = Firebolt::IFireboltAccessor::Instance().ProfileInterface().flags(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(result["flag1"], "value1");
    EXPECT_EQ(result["flag2"], "value2");
}

TEST_F(ProfileMockTest, Flags_Failure) {
    EXPECT_CALL(*gm->mockGateway, Request("profile.flags", _, testing::Matcher<Firebolt::Types::JsonData_FlatMap &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));
    
    Firebolt::Types::FlatMap result = Firebolt::IFireboltAccessor::Instance().ProfileInterface().flags(&gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(result.empty());
}