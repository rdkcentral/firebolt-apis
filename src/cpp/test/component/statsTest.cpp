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

#include "firebolt.h"
#include "json_engine.h"

class StatsTest : public ::testing::Test
{
protected:
    JsonEngine jsonEngine;
};

TEST_F(StatsTest, MemoryUsage)
{
    auto expectedValue = jsonEngine.get_value("Stats.memoryUsage");

    auto result = Firebolt::IFireboltAccessor::Instance().StatsInterface().memoryUsage();

    ASSERT_TRUE(result) << "StatsImpl::memoryUsage() returned an error";

    EXPECT_EQ(result->gpuMemoryLimit, expectedValue.at("gpuMemoryLimitKiB").get<uint32_t>());
    EXPECT_EQ(result->gpuMemoryUsed, expectedValue.at("gpuMemoryUsedKiB").get<uint32_t>());
    EXPECT_EQ(result->userMemoryLimit, expectedValue.at("userMemoryLimitKiB").get<uint32_t>());
    EXPECT_EQ(result->userMemoryUsed, expectedValue.at("userMemoryUsedKiB").get<uint32_t>());
}
