#include <gtest/gtest.h>
#include "Gateway/Gateway.h"


class GatewayTest : public ::testing::Test {
protected:
	Firebolt::Error status = Firebolt::Error::None;
};


TEST_F(GatewayTest, Request) {
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = FireboltSDK::Gateway::Instance().Request("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status) ;
}

TEST_F(GatewayTest, Subscribe) {
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    std::string jsonParameters;
    json response;
    status = FireboltSDK::Gateway::Instance().Subscribe<json>(eventName, jsonParameters, response);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status) ;
}

TEST_F(GatewayTest, UnSubscribe) {
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    std::string parameters("{\"listen\":false}");
    status = FireboltSDK::Gateway::Instance().Unsubscribe(eventName, parameters);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status) ;
}
