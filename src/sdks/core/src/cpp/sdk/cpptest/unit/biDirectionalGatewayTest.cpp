#include <gtest/gtest.h>
#include "Gateway/Gateway.h"
#include "Gateway/bidi/gateway_impl.h"

class BiDirectionalGatewayTest : public ::testing::Test
{
protected:
    Firebolt::Error status = Firebolt::Error::None;
    FireboltSDK::GatewayImpl *_gatewayImpl = FireboltSDK::Gateway::Instance().get_gateway_impl();
};

TEST_F(BiDirectionalGatewayTest, Receive)
{
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = _gatewayImpl->Receive("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

TEST_F(BiDirectionalGatewayTest, Request)
{
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = _gatewayImpl->Request("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

/* Test Subscribe */
struct SkipRestrictionChanged : public Firebolt::Advertising::IAdvertising::IOnSkipRestrictionChangedNotification
{
    void onSkipRestrictionChanged(const Firebolt::Advertising::SkipRestriction &) override;
};

Firebolt::Advertising::SkipRestriction newSkipRestriction;
void SkipRestrictionChanged::onSkipRestrictionChanged(const Firebolt::Advertising::SkipRestriction &skipRestriction)
{
    std::cout << "onSkipRestrictionChanged event fired";
}

TEST_F(BiDirectionalGatewayTest, Subscribe)
{
    SkipRestrictionChanged skipRestrictionChanged;
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    JsonObject parameters;
    json response;

    status = _gatewayImpl->Subscribe(eventName, parameters, CALLBACK, reinterpret_cast<void*>(skipRestrictionChanged), nullptr);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}
/* Test Subscribe End */

TEST_F(BiDirectionalGatewayTest, UnSubscribe)
{
    std::string eventName = _T("advertising.onSkipRestrictionChanged");

    status = _gatewayImpl->Unsubscribe(eventName);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}
