#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gateway/Gateway.h"
#include "mockGateway.h"
#include "securestorage_impl.h"

using namespace testing;

class SecureStorageMockTest : public ::testing::Test
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

TEST_F(SecureStorageMockTest, Clear_Success) {
    Firebolt::SecureStorage::StorageScope scope;
    EXPECT_CALL(*gm->mockGateway, Request("securestorage.clear", _, testing::Matcher<WPEFramework::Core::JSON::VariantContainer &>(_)))
        .WillOnce(Return(Firebolt::Error::None));
    
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(scope, &gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
}

TEST_F(SecureStorageMockTest, Clear_Failure) {
    Firebolt::SecureStorage::StorageScope scope;
    EXPECT_CALL(*gm->mockGateway, Request("securestorage.clear", _, testing::Matcher<WPEFramework::Core::JSON::VariantContainer &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));
    
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(scope, &gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::NotConnected);
}

TEST_F(SecureStorageMockTest, Get_Failure) {
    Firebolt::SecureStorage::StorageScope scope;
    std::string key = "testKey";
    
    EXPECT_CALL(*gm->mockGateway, Request("securestorage.get", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    
    std::string result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(scope, key, &gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::General);
    EXPECT_EQ(result, "");
}

TEST_F(SecureStorageMockTest, Set_Success) {
    Firebolt::SecureStorage::StorageScope scope;
    std::string key = "testKey";
    std::string value = "testValue";
    std::optional<Firebolt::SecureStorage::StorageOptions> options;
    
    EXPECT_CALL(*gm->mockGateway, Request("securestorage.set", _, testing::Matcher<WPEFramework::Core::JSON::VariantContainer &>(_)))
        .WillOnce(Return(Firebolt::Error::None));
    
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().set(scope, key, value, options, &gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::None);
}

TEST_F(SecureStorageMockTest, Set_Failure) {
    Firebolt::SecureStorage::StorageScope scope;
    std::string key = "testKey";
    std::string value = "testValue";
    std::optional<Firebolt::SecureStorage::StorageOptions> options;
    
    EXPECT_CALL(*gm->mockGateway, Request("securestorage.set", _, testing::Matcher<WPEFramework::Core::JSON::VariantContainer &>(_)))
        .WillOnce(Return(Firebolt::Error::General));
    
    Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().set(scope, key, value, options, &gm->error);
    
    EXPECT_EQ(gm->error, Firebolt::Error::General);
}
