#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IProperties.h"
#include "account_impl.h" 
#include "mockProperties.h"

using namespace testing;

class AccountImplMockTest : public ::testing::Test
{
protected:
    std::unique_ptr<PropertiesMockTest> pm;

    void SetUp() override
    {
        pm = std::make_unique<PropertiesMockTest>();
        pm->SetUp();
    }

    void TearDown() override
    {
        pm->TearDown();
        pm.reset(); // Cleanup
    }
};

TEST_F(AccountImplMockTest, Id_Success) {
    FireboltSDK::JSON::String mockResponse = "valid_account_id";
    EXPECT_CALL(*pm->mockProperties, Get("account.id", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().AccountInterface().id(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "valid_account_id");
}

TEST_F(AccountImplMockTest, Id_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("account.id", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().AccountInterface().id(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(AccountImplMockTest, Uid_Success) {
    FireboltSDK::JSON::String mockResponse = "valid_unique_id";
    EXPECT_CALL(*pm->mockProperties, Get("account.uid", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<1>(mockResponse), Return(Firebolt::Error::None)));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().AccountInterface().uid(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::None);
    EXPECT_EQ(result, "valid_unique_id");
}

TEST_F(AccountImplMockTest, Uid_Failure) {
    EXPECT_CALL(*pm->mockProperties, Get("account.uid", testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::Timedout));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().AccountInterface().uid(&pm->error);
    
    EXPECT_EQ(pm->error, Firebolt::Error::Timedout);
    EXPECT_EQ(result, "");
}
