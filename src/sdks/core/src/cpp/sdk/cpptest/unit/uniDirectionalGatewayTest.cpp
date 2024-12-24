#include <gtest/gtest.h>
#include "Gateway/Gateway.h"
#include "Gateway/unidi/gateway_impl.h"

class UniDirectionalGatewayTest : public ::testing::Test
{
protected:
    Firebolt::Error status = Firebolt::Error::None;
    FireboltSDK::GatewayImpl *_gatewayImpl = FireboltSDK::Gateway::Instance().get_gateway_impl();
};

TEST_F(UniDirectionalGatewayTest, Request)
{
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = _gatewayImpl->Request("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

TEST_F(UniDirectionalGatewayTest, Subscribe)
{
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    std::string jsonParameters;
    json response;

    status = _gatewayImpl->Subscribe(eventName, jsonParameters, response);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

TEST_F(UniDirectionalGatewayTest, UnSubscribe)
{
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    std::string parameters("{\"listen\":false}");

    status = _gatewayImpl->Unsubscribe(eventName, parameters);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}