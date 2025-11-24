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

#include "json_engine.h"
#include "mock_helper.h"
#include "presentation_impl.h"

class PresentationTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Presentation::PresentationImpl presentationImpl{mockHelper};
};

TEST_F(PresentationTest, Focused)
{
    mock("Presentation.focused");
    auto expectedValue = jsonEngine.get_value("Presentation.focused");

    auto result = presentationImpl.focused();

    ASSERT_TRUE(result) << "Presentation::focused() returned an error";

    EXPECT_EQ(*result, expectedValue.get<bool>());
}

TEST_F(PresentationTest, SubscribeOnFocusedChanged)
{
    mockSubscribe("Presentation.onFocusedChanged");

    auto id = presentationImpl.subscribeOnFocusedChanged([&](bool /*value*/) {});
    ASSERT_TRUE(id) << "error on subscribe";
    EXPECT_EQ(*id, 1);

    auto result = presentationImpl.unsubscribe(*id);
    ASSERT_TRUE(result) << "error on unsubscribe";
}
