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

#ifndef GATEWAY_BIDIRECTIONAL

#include <gtest/gtest.h>
#include "Gateway/Gateway.h"

class UniDirectionalGatewayTest : public ::testing::Test
{
protected:
    Firebolt::Error status = Firebolt::Error::None;
};

TEST_F(UniDirectionalGatewayTest, Request)
{
    JsonObject jsonParameters;
    WPEFramework::Core::JSON::VariantContainer jsonResult;
    status = FireboltSDK::Gateway::Instance().Request("authentication.device", jsonParameters, jsonResult);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

TEST_F(UniDirectionalGatewayTest, Subscribe)
{
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    std::string jsonParameters;
    json response;

    status = FireboltSDK::Gateway::Instance().Subscribe(eventName, jsonParameters, response);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}

TEST_F(UniDirectionalGatewayTest, UnSubscribe)
{
    std::string eventName = _T("advertising.onSkipRestrictionChanged");
    std::string parameters("{\"listen\":false}");

    status = FireboltSDK::Gateway::Instance().Unsubscribe(eventName, parameters);
    EXPECT_EQ(status, Firebolt::Error::None) << "Error! status: " << static_cast<int32_t>(status);
}
#endif
