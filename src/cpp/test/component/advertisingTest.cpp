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

#include "./component/utils.h"
#include "firebolt.h"
#include "json_engine.h"
#include "json_types/jsondata_advertising_types.h"
#include "gtest/gtest.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class AdvertisingTest : public ::testing::Test
{

protected:
    JsonEngine jsonEngine;
};

TEST_F(AdvertisingTest, AdvertisingId)
{
    auto expectedValue = jsonEngine.get_value("Advertising.advertisingId");
    auto result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().advertisingId();

    ASSERT_TRUE(result) << "AdvertisingImpl::advertisingId() returned an error";
    EXPECT_EQ(result->ifa, expectedValue["ifa"].get<std::string>());
    EXPECT_EQ(result->ifa_type, expectedValue["ifa_type"].get<std::string>());
    EXPECT_EQ(result->lmt, expectedValue["lmt"].get<std::string>());
}

TEST_F(AdvertisingTest, Uid)
{
    auto expectedValue = jsonEngine.get_value("Advertising.uid");
    auto result = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().uid();
    ASSERT_TRUE(result) << "AdvertisingImpl::uid() returned an error";
    EXPECT_EQ(*result, expectedValue.get<std::string>());
}

