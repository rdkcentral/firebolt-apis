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

class DeviceTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Device::DeviceImpl deviceImpl_{mockHelper};
};

TEST_F(DeviceTest, GetClass)
{
    mock("Device.deviceClass");
    auto expectedValue = jsonEngine.get_value("Device.deviceClass");

    auto result = deviceImpl_.deviceClass();

    ASSERT_TRUE(result) << "DeviceImpl::deviceClass() returned an error";

    EXPECT_EQ(static_cast<int>(*result), static_cast<int>(Firebolt::Device::JsonData::DeviceClassEnum.at(expectedValue)));
}

TEST_F(DeviceTest, TimeInActiveState)
{
    mock("Device.timeInActiveState");
    auto expectedValue = jsonEngine.get_value("Device.timeInActiveState");

    auto result = deviceImpl_.timeInActiveState();
    ASSERT_TRUE(result) << "DeviceImpl::timeInActiveState() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Uptime)
{
    mock("Device.uptime");
    auto expectedValue = jsonEngine.get_value("Device.uptime");

    auto result = deviceImpl_.uptime();
    ASSERT_TRUE(result) << "DeviceImpl::uptime() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(DeviceTest, Uid)
{
    mock("Device.uid");
    auto expectedValue = jsonEngine.get_value("Device.uid");

    auto result = deviceImpl_.uid();
    ASSERT_TRUE(result) << "DeviceImpl::uid() returned an error";

    EXPECT_EQ(*result, expectedValue);
}
