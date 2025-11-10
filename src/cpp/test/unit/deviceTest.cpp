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

#include "device_impl.h"
#include "json_engine.h"
#include "mock_helper.h"
#include "json_types/jsondata_device_types.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// define when json rpc schema is not available
#define USE_LOCAL_RESPONSE

class DeviceTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Device::DeviceImpl deviceImpl_{mockHelper};
};

TEST_F(DeviceTest, Category)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = "stb";
    mock_with_response("Device.category", expectedValue);
#else
    mock("Device.category");
    auto expectedValue = jsonEngine.get_value("Device.category");
#endif

    auto result = deviceImpl_.category();

    ASSERT_TRUE(result) << "DeviceImpl::category() returned an error";

    EXPECT_EQ(static_cast<int>(*result), static_cast<int>(Firebolt::Device::JsonData::CategoryEnum.at(expectedValue)));
}

TEST_F(DeviceTest, ChipsetId)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = "RTD1319";
    mock_with_response("Device.chipsetId", expectedValue);
#else
    mock("Device.chipsetId");
    auto expectedValue = jsonEngine.get_value("Device.chipsetId");
#endif

    auto result = deviceImpl_.chipsetId();
    ASSERT_TRUE(result) << "DeviceImpl::chipsetId() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Uptime)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = 3600;
    mock_with_response("Device.uptime", expectedValue);
#else
    mock("Device.uptime");
    auto expectedValue = jsonEngine.get_value("Device.uptime");
#endif

    auto result = deviceImpl_.uptime();
    ASSERT_TRUE(result) << "DeviceImpl::uptime() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, MemoryInfo)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = {{"userMemoryUsed", 204800},
                                    {"userMemoryLimit", 409600},
                                    {"gpuMemoryUsed", 102400},
                                    {"gpuMemoryLimit", 204800}};
    mock_with_response("Device.memoryInfo", expectedValue);
#else
    mock("Device.memoryInfo");
    auto expectedValue = jsonEngine.get_value("Device.memoryInfo");
#endif

    auto result = deviceImpl_.memoryInfo();

    ASSERT_TRUE(result) << "DeviceImpl::memoryInfo() returned an error";

    EXPECT_EQ(result->userMemoryUsed, expectedValue["userMemoryUsed"].get<uint32_t>());
    EXPECT_EQ(result->userMemoryLimit, expectedValue["userMemoryLimit"].get<uint32_t>());
    EXPECT_EQ(result->gpuMemoryUsed, expectedValue["gpuMemoryUsed"].get<uint32_t>());
    EXPECT_EQ(result->gpuMemoryLimit, expectedValue["gpuMemoryLimit"].get<uint32_t>());
}
