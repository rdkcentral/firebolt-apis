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
#include "firebolt.h"
#include "json_types/jsondata_accessibility_types.h"
#include "mock_helper.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class AccessibilityTest : public ::testing::Test, protected MockBase
{
protected:
    void SetUp() override { eventReceived = false; }

    // Create a condition variable and mutex to wait for the events to be received
    std::condition_variable cv;
    std::mutex mtx;
    bool eventReceived;

    JsonEngine jsonEngine;
};

TEST_F(AccessibilityTest, AudioDescription)
{
    auto expectedValue = jsonEngine.get_value("Accessibility.audioDescription");
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().audioDescription();
    ASSERT_TRUE(result) << "AccessibilityImpl::audioDescription() returned an error";
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(AccessibilityTest, SubscribeOnAudioDescriptionChanged)
{
 
}

TEST_F(AccessibilityTest, ClosedCaptionsSettings)
{
    Firebolt::Accessibility::ClosedCaptionsSettings settings{true, {"en", "fr"}};
    nlohmann::json expectedValue = {{"enabled", settings.enabled},
                                    {"preferredLanguages",
                                     settings.preferredLanguages}};

    mock_with_response("Accessibility.closedCaptionsSettings", expectedValue);

    auto result = accessibilityImpl_.closedCaptionsSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::closedCaptionsSettings() returned an error";
    EXPECT_EQ((*result).enabled, settings.enabled);
    EXPECT_EQ((*result).preferredLanguages, settings.preferredLanguages);
}

TEST_F(AccessibilityTest, SubscribeOnClosedCaptionsSettingsChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onClosedCaptionsSettingsChanged");

    auto result = accessibilityImpl_.subscribeOnClosedCaptionsSettingsChanged(
        [&](const Firebolt::Accessibility::ClosedCaptionsSettings &settings) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnClosedCaptionsSettingsChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}
        
TEST_F(AccessibilityTest, HighContrastUI)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = true;
    mock_with_response("Accessibility.highContrastUI", expectedValue);
#else
    mock("Accessibility.highContrastUI");
    auto expectedValue = jsonEngine.get_value("Accessibility.highContrastUI");
#endif

    auto result = accessibilityImpl_.highContrastUI();

    ASSERT_TRUE(result) << "AccessibilityImpl::highContrastUI() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(AccessibilityTest, SubscribeOnHighContrastUIChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onHighContrastUIChanged");

    auto result = accessibilityImpl_.subscribeOnHighContrastUIChanged([&](bool value) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnHighContrastUIChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}

TEST_F(AccessibilityTest, VoiceGuidanceSettings)
{
#ifdef USE_LOCAL_RESPONSE
    Firebolt::Accessibility::VoiceGuidanceSettings settings{true, 1.5, true};
    nlohmann::json expectedValue = {{"enabled", settings.enabled},
                                    {"rate", settings.rate},
                                    {"navigationHints", settings.navigationHints}};
#else
    mock("Accessibility.voiceGuidanceSettings");
    auto expectedValue = jsonEngine.get_value("Accessibility.voiceGuidanceSettings");
#endif
    mock_with_response("Accessibility.voiceGuidanceSettings", expectedValue);

    auto result = accessibilityImpl_.voiceGuidanceSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::voiceGuidanceSettings() returned an error";
    EXPECT_EQ((*result).enabled, settings.enabled);
    EXPECT_EQ((*result).rate, settings.rate);
    EXPECT_EQ((*result).navigationHints, settings.navigationHints);
}

TEST_F(AccessibilityTest, SubscribeOnVoiceGuidanceSettingsChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe("Accessibility.onVoiceGuidanceSettingsChanged");

    auto result = accessibilityImpl_.subscribeOnVoiceGuidanceSettingsChanged(
        [&](const Firebolt::Accessibility::VoiceGuidanceSettings &settings) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnVoiceGuidanceSettingsChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}
