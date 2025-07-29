/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef GATEWAY_BIDIRECTIONAL

#include "unit.h"
#include <gtest/gtest.h>
#include "Gateway/Gateway.h"

class BiDirectionalGatewayTest : public ::testing::Test
{
protected:
    Firebolt::Error status = Firebolt::Error::None;
};

static void onPolicyChangedInnerCallback( void* notification, const void* userData, void* jsonResponse )
{
    std::cout << "onPolicyChanged event fired";
}

TEST_F(BiDirectionalGatewayTest, Request)
{
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = FireboltSDK::Gateway::Instance().Request("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

TEST_F(BiDirectionalGatewayTest, Subscribe)
{
    std::string eventName = _T("advertising.onPolicyChanged");
    JsonObject parameters;
    json response;

    status = FireboltSDK::Gateway::Instance().Subscribe<WPEFramework::Core::JSON::VariantContainer>(eventName, parameters, onPolicyChangedInnerCallback, nullptr, nullptr);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}
/* Test Subscribe End */

TEST_F(BiDirectionalGatewayTest, UnSubscribe)
{
    std::string eventName = _T("advertising.onSkipRestrictionChanged");

    status = FireboltSDK::Gateway::Instance().Unsubscribe(eventName);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

#endif
