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

#include "accessibility_impl.h"
#include "json_engine.h"
#include "mock_helper.h"

class AccessibilityTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Accessibility::AccessibilityImpl accessibilityImpl_{mockHelper};
};

TEST_F(AccessibilityTest, AudioDescription)
{
    mock("Accessibility.audioDescription");
    auto expectedValue = jsonEngine.get_value("Accessibility.audioDescription");

    auto result = accessibilityImpl_.audioDescription();

    ASSERT_TRUE(result) << "AccessibilityImpl::audioDescription() returned an error";

    EXPECT_EQ(*result, expectedValue.get<bool>());
}

TEST_F(AccessibilityTest, AudioDescriptionBadResponse)
{
    mock_with_response("Accessibility.audioDescription", "invalid_response");
    ASSERT_FALSE(accessibilityImpl_.audioDescription())
        << "AccessibilityImpl::audioDescription() did not return an error";
}

TEST_F(AccessibilityTest, SubscribeOnAudioDescriptionChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onAudioDescriptionChanged");

    auto result = accessibilityImpl_.subscribeOnAudioDescriptionChanged([&](bool /*value*/) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnAudioDescriptionChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}

TEST_F(AccessibilityTest, ClosedCaptionsSettings)
{
    mock("Accessibility.closedCaptionsSettings");
    auto expectedValue = jsonEngine.get_value("Accessibility.closedCaptionsSettings");

    auto result = accessibilityImpl_.closedCaptionsSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::closedCaptionsSettings() returned an error";
    EXPECT_EQ((*result).enabled, expectedValue["enabled"].get<bool>());
    EXPECT_EQ((*result).preferredLanguages, expectedValue["preferredLanguages"].get<std::vector<std::string>>());
}

TEST_F(AccessibilityTest, ClosedCaptionsSettingsBadResponse)
{
    mock_with_response("Accessibility.closedCaptionsSettings", "invalid_response");
    ASSERT_FALSE(accessibilityImpl_.closedCaptionsSettings())
        << "AccessibilityImpl::closedCaptionsSettings() did not return an error";
}

TEST_F(AccessibilityTest, SubscribeOnClosedCaptionsSettingsChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onClosedCaptionsSettingsChanged");

    auto result = accessibilityImpl_.subscribeOnClosedCaptionsSettingsChanged(
        [&](const Firebolt::Accessibility::ClosedCaptionsSettings& /*settings*/) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnClosedCaptionsSettingsChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}

TEST_F(AccessibilityTest, HighContrastUI)
{
    mock("Accessibility.highContrastUI");
    auto expectedValue = jsonEngine.get_value("Accessibility.highContrastUI");

    auto result = accessibilityImpl_.highContrastUI();

    ASSERT_TRUE(result) << "AccessibilityImpl::highContrastUI() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(AccessibilityTest, HighContrastUIBadResponse)
{
    mock_with_response("Accessibility.highContrastUI", "invalid_response");
    ASSERT_FALSE(accessibilityImpl_.highContrastUI()) << "AccessibilityImpl::highContrastUI() did not return an error";
}

TEST_F(AccessibilityTest, SubscribeOnHighContrastUIChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onHighContrastUIChanged");

    auto result = accessibilityImpl_.subscribeOnHighContrastUIChanged([&](bool /*value*/) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnHighContrastUIChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}

TEST_F(AccessibilityTest, VoiceGuidanceSettings)
{
    mock("Accessibility.voiceGuidanceSettings");
    auto expectedValue = jsonEngine.get_value("Accessibility.voiceGuidanceSettings");

    auto result = accessibilityImpl_.voiceGuidanceSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::voiceGuidanceSettings() returned an error";
    EXPECT_EQ((*result).enabled, expectedValue["enabled"].get<bool>());
    EXPECT_EQ((*result).rate, expectedValue["rate"].get<float>());
    EXPECT_EQ((*result).navigationHints, expectedValue["navigationHints"].get<bool>());
}

TEST_F(AccessibilityTest, VoiceGuidanceSettingsBadResponse)
{
    mock_with_response("Accessibility.voiceGuidanceSettings", "invalid_response");
    ASSERT_FALSE(accessibilityImpl_.voiceGuidanceSettings())
        << "AccessibilityImpl::voiceGuidanceSettings() did not return an error";
}

TEST_F(AccessibilityTest, SubscribeOnVoiceGuidanceSettingsChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onVoiceGuidanceSettingsChanged");

    auto result = accessibilityImpl_.subscribeOnVoiceGuidanceSettingsChanged(
        [&](const Firebolt::Accessibility::VoiceGuidanceSettings& /*settings*/) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnVoiceGuidanceSettingsChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}
