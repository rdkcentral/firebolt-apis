#include "../unit/unit.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include "Gateway/Gateway.h"
#include "authentication_impl.h" 
#include "mockGateway.h"

class AuthenticationMockTest : public ::testing::Test
{
protected:
    std::unique_ptr<GatewayMockTest> gm;

    void SetUp() override {
        gm = std::make_unique<GatewayMockTest>();
        gm->SetUp();
    }

    void TearDown() override {
        gm->TearDown();
        gm.reset();  // Cleanup
    }
};

TEST_F(AuthenticationMockTest, Device_Success) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "valid_device_token";

    EXPECT_CALL(*gm->mockGateway, Request("authentication.device", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&gm->error);

    EXPECT_EQ(gm->error, Firebolt::Error::None);
    EXPECT_EQ(token, "valid_device_token");
}

TEST_F(AuthenticationMockTest, Device_MultipleCalls) {
    Firebolt::Error error1 = Firebolt::Error::None;
    Firebolt::Error error2 = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse1 = "device_token_1";
    FireboltSDK::JSON::String mockResponse2 = "device_token_2";

    EXPECT_CALL(*gm->mockGateway, Request("authentication.device", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse1), Return(Firebolt::Error::None)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse2), Return(Firebolt::Error::None)));

    std::string token1 = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error1);
    std::string token2 = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error2);

    EXPECT_EQ(error1, Firebolt::Error::None);
    EXPECT_EQ(token1, "device_token_1");

    EXPECT_EQ(error2, Firebolt::Error::None);
    EXPECT_EQ(token2, "device_token_2");
}

TEST_F(AuthenticationMockTest, Device_FailsWithNotConnected) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse; // Empty response

    EXPECT_CALL(*gm->mockGateway, Request("authentication.device", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    EXPECT_EQ(error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Device_FailsWithGeneralError) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse;

    EXPECT_CALL(*gm->mockGateway, Request("authentication.device", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    EXPECT_EQ(error, Firebolt::Error::General);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Device_EmptyTokenReturned) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "";  // Empty token

    EXPECT_CALL(*gm->mockGateway, Request("authentication.device", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_TRUE(token.empty());  // Should return empty string
}

TEST_F(AuthenticationMockTest, Device_MalformedTokenReturned) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "####";  // Invalid/malformed token

    EXPECT_CALL(*gm->mockGateway, Request("authentication.device", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token, "####");  // Malformed but still returned
}

TEST_F(AuthenticationMockTest, Root_Success) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "valid_root_token";

    EXPECT_CALL(*gm->mockGateway, Request("authentication.root", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token, "valid_root_token");
}

TEST_F(AuthenticationMockTest, Root_MultipleCalls) {
    Firebolt::Error error1 = Firebolt::Error::None;
    Firebolt::Error error2 = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse1 = "root_token_1";
    FireboltSDK::JSON::String mockResponse2 = "root_token_2";

    EXPECT_CALL(*gm->mockGateway, Request("authentication.root", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse1), Return(Firebolt::Error::None)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse2), Return(Firebolt::Error::None)));

    std::string token1 = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error1);
    std::string token2 = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error2);

    EXPECT_EQ(error1, Firebolt::Error::None);
    EXPECT_EQ(token1, "root_token_1");

    EXPECT_EQ(error2, Firebolt::Error::None);
    EXPECT_EQ(token2, "root_token_2");
}

TEST_F(AuthenticationMockTest, Root_FailsWithNotConnected) {
    Firebolt::Error error = Firebolt::Error::None;

    EXPECT_CALL(*gm->mockGateway, Request("authentication.root", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error);

    EXPECT_EQ(error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Root_EmptyTokenReturned) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "";  // Empty response

    EXPECT_CALL(*gm->mockGateway, Request("authentication.root", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Root_FailsWithGeneralError) {
    Firebolt::Error error = Firebolt::Error::None;

    EXPECT_CALL(*gm->mockGateway, Request("authentication.root", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().root(&error);

    EXPECT_EQ(error, Firebolt::Error::General);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Session_Success) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "valid_session_token";

    EXPECT_CALL(*gm->mockGateway, Request("authentication.session", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token, "valid_session_token");
}

TEST_F(AuthenticationMockTest, Session_MultipleCalls) {
    Firebolt::Error error1 = Firebolt::Error::None;
    Firebolt::Error error2 = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse1 = "session_token_1";
    FireboltSDK::JSON::String mockResponse2 = "session_token_2";

    EXPECT_CALL(*gm->mockGateway, Request("authentication.session", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse1), Return(Firebolt::Error::None)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse2), Return(Firebolt::Error::None)));

    std::string token1 = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error1);
    std::string token2 = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error2);

    EXPECT_EQ(error1, Firebolt::Error::None);
    EXPECT_EQ(token1, "session_token_1");

    EXPECT_EQ(error2, Firebolt::Error::None);
    EXPECT_EQ(token2, "session_token_2");
}

TEST_F(AuthenticationMockTest, Session_FailsWithNotConnected) {
    Firebolt::Error error = Firebolt::Error::None;

    EXPECT_CALL(*gm->mockGateway, Request("authentication.session", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error);

    EXPECT_EQ(error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Session_EmptyTokenReturned) {
    Firebolt::Error error = Firebolt::Error::None;
    FireboltSDK::JSON::String mockResponse = "";  // Empty response

    EXPECT_CALL(*gm->mockGateway, Request("authentication.session", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Session_FailsWithGeneralError) {
    Firebolt::Error error = Firebolt::Error::None;

    EXPECT_CALL(*gm->mockGateway, Request("authentication.session", _, testing::Matcher<FireboltSDK::JSON::String &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    std::string token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().session(&error);

    EXPECT_EQ(error, Firebolt::Error::General);
    EXPECT_TRUE(token.empty());
}

TEST_F(AuthenticationMockTest, Token_Success) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::DEVICE;
    Firebolt::Authentication::JsonData_Token mockResponse;
    mockResponse.Value = "valid_auth_token";

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, std::nullopt, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token.value, "valid_auth_token");
}

TEST_F(AuthenticationMockTest, Token_WithOptions) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::PLATFORM;
    Firebolt::Authentication::Options options = "{\"scope\", \"test_scope\"}";
    Firebolt::Authentication::JsonData_Token mockResponse;
    mockResponse.Value = "valid_platform_token";

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, options, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token.value, "valid_platform_token");
}

TEST_F(AuthenticationMockTest, Token_WithExpirationAndType) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::DISTRIBUTOR;
    Firebolt::Authentication::JsonData_Token mockResponse;
    mockResponse.Value = "valid_distributor_token";
    mockResponse.Expires = "1680998400";  // Unix timestamp for expiration
    mockResponse.Type = "distributor";

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, std::nullopt, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token.value, "valid_distributor_token");
    EXPECT_EQ(token.expires, "1680998400");
    EXPECT_EQ(token.type, "distributor");
}

TEST_F(AuthenticationMockTest, Token_FailsWithNotConnected) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::DEVICE;

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(Return(Firebolt::Error::NotConnected));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, std::nullopt, &error);

    EXPECT_EQ(error, Firebolt::Error::NotConnected);
    EXPECT_TRUE(token.value.empty());
}

TEST_F(AuthenticationMockTest, Token_EmptyTokenReturned) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::PLATFORM;
    Firebolt::Authentication::JsonData_Token mockResponse;
    mockResponse.Value = "";  // Empty token

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, std::nullopt, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_TRUE(token.value.empty());
}

TEST_F(AuthenticationMockTest, Token_FailsWithGeneralError) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::DISTRIBUTOR;

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(Return(Firebolt::Error::General));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, std::nullopt, &error);

    EXPECT_EQ(error, Firebolt::Error::General);
    EXPECT_TRUE(token.value.empty());
}

TEST_F(AuthenticationMockTest, Token_MalformedTokenReturned) {
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType tokenType = Firebolt::Authentication::TokenType::PLATFORM;
    Firebolt::Authentication::JsonData_Token mockResponse;
    mockResponse.Value = "####";  // Malformed token

    EXPECT_CALL(*gm->mockGateway,
                Request("authentication.token", _,
                        testing::Matcher<Firebolt::Authentication::JsonData_Token &>(_)))
        .WillOnce(DoAll(SetArgReferee<2>(mockResponse), Return(Firebolt::Error::None)));

    Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(tokenType, std::nullopt, &error);

    EXPECT_EQ(error, Firebolt::Error::None);
    EXPECT_EQ(token.value, "####");  // Malformed but still returned
}
