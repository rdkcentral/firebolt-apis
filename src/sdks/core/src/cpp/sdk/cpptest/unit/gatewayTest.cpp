#include <gtest/gtest.h>
#include "Gateway/Gateway.h"


class GatewayTest : public ::testing::Test {
protected:
	Firebolt::Error status = Firebolt::Error::None;
};

static void onPolicyChangedInnerCallback( void* notification, const void* userData, void* jsonResponse )
{
    std::cout << "onPolicyChanged event fired";
}

TEST_F(GatewayTest, Request) {
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = FireboltSDK::Gateway::Instance().Request("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status) ;
}

TEST_F(GatewayTest, Subscribe) {
    std::string eventName = _T("advertising.onPolicyChanged");
#ifdef GATEWAY_BIDIRECTIONAL
    JsonObject jsonParameters;
    status = FireboltSDK::Gateway::Instance().Subscribe<WPEFramework::Core::JSON::VariantContainer>(eventName, jsonParameters, onPolicyChangedInnerCallback, nullptr, nullptr);
#else
    WPEFramework::Core::JSON::Container response;
    std::string jsonParameters;
    status = FireboltSDK::Gateway::Instance().Subscribe(eventName, jsonParameters, response);
#endif
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status) ;
}

TEST_F(GatewayTest, UnSubscribe) {
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
#ifdef GATEWAY_BIDIRECTIONAL
    status = FireboltSDK::Gateway::Instance().Unsubscribe(eventName);
#else
    std::string params = "";
    status = FireboltSDK::Gateway::Instance().Unsubscribe(eventName, params);
#endif
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status) ;
}
