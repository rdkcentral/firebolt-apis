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

#include "display_impl.h"
#include "json_engine.h"
#include "mock_helper.h"

class DisplayTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Display::DisplayImpl displayImpl_{mockHelper};
};

TEST_F(DisplayTest, Size)
{
    mock("Display.size");
    auto expectedValue = jsonEngine.get_value("Display.size");
    std::cout << "Expected Value: " << expectedValue.dump() << std::endl;
    auto result = displayImpl_.size();
    ASSERT_TRUE(result) << "DisplayImpl::size() returned an error";

    EXPECT_EQ(result->height, expectedValue.at("height").get<uint32_t>());
    EXPECT_EQ(result->width, expectedValue.at("width").get<uint32_t>());
}

TEST_F(DisplayTest, MaxResolution)
{
    mock("Display.maxResolution");
    auto expectedValue = jsonEngine.get_value("Display.maxResolution");

    auto result = displayImpl_.maxResolution();
    ASSERT_TRUE(result) << "DisplayImpl::maxResolution() returned an error";

    EXPECT_EQ(result->height, expectedValue.at("height").get<uint32_t>());
    EXPECT_EQ(result->width, expectedValue.at("width").get<uint32_t>());
}
