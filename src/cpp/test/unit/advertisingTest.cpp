/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
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
 */

#include "advertising_impl.h"
#include "json_engine.h"
#include "mock_helper.h"
#include "json_types/jsondata_advertising_types.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// define when json rpc schema is not available
#define USE_LOCAL_RESPONSE

class AdvertisingTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Advertising::AdvertisingImpl advertisingImpl_{mockHelper};
};

TEST_F(AdvertisingTest, advertisingId)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue;
    expectedValue["ifa"] = "unique-device-uid-67890";
    expectedValue["ifa_type"] = "dpid";
    expectedValue["lmt"] = "1";
    mock_with_response("Advertising.advertisingId", expectedValue);
#else
    mock("Advertising.advertisingId");
    auto expectedValue = jsonEngine.get_value("Advertising.advertisingId");
    std::cout << "***Expected Value from JSON Engine: " << expectedValue.dump() << std::endl;
#endif

    auto result = advertisingImpl_.advertisingId();
    ASSERT_TRUE(result) << "AdvertisingImpl::advertisingId() returned an error";

    EXPECT_EQ(result->ifa, expectedValue["ifa"].get<std::string>());
    EXPECT_EQ(result->ifa_type, expectedValue["ifa_type"].get<std::string>());
    EXPECT_EQ(result->lmt, expectedValue["lmt"].get<std::string>());
}

TEST_F(AdvertisingTest, uid)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = "unique-device-uid-67890";
    mock_with_response("Advertising.uid", expectedValue);
#else
    mock("Advertising.uid");
    auto expectedValue = jsonEngine.get_value("Advertising.uid");
#endif 

    auto result = advertisingImpl_.uid();
    ASSERT_TRUE(result) << "AdvertisingImpl::uid() returned an error";

    EXPECT_EQ(*result, expectedValue.get<std::string>());
}

