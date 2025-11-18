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
#include "json_types/jsondata_accessibility_types.h"
#include "mock_helper.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

// define when json rpc schema is not available
#define USE_LOCAL_RESPONSE

class AccessibilityTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Accessibility::AccessibilityImpl accessibilityImpl_{mockHelper};
};

TEST_F(AccessibilityTest, AudioDescription)
{
#ifdef USE_LOCAL_RESPONSE
    nlohmann::json expectedValue = false;
    mock_with_response(Firebolt::Accessibility::JsonData::Method::audioDescription, expectedValue);
#else
    mock(Firebolt::Accessibility::JsonData::Method::audioDescription);
    auto expectedValue = jsonEngine.get_value(Firebolt::Accessibility::JsonData::Method::audioDescription);
#endif

    auto result = accessibilityImpl_.audioDescription();

    ASSERT_TRUE(result) << "AccessibilityImpl::audioDescription() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(AccessibilityTest, SubscribeOnAudioDescriptionChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe(Firebolt::Accessibility::JsonData::OnChanged::audioDescription);

    auto result = accessibilityImpl_.subscribeOnAudioDescriptionChanged([&](bool value) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnAudioDescriptionChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}

TEST_F(AccessibilityTest, ClosedCaptionsSettings)
{
    Firebolt::Accessibility::ClosedCaptionsSettings settings{true, {"en", "fr"}};
    nlohmann::json expectedValue = {{Firebolt::Accessibility::JsonData::Field::ClosedCaptionsSettings::enabled, settings.enabled},
                                    {Firebolt::Accessibility::JsonData::Field::ClosedCaptionsSettings::preferredLanguages,
                                     settings.preferredLanguages}};

    mock_with_response(Firebolt::Accessibility::JsonData::Method::closedCaptionsSettings, expectedValue);

    auto result = accessibilityImpl_.closedCaptionsSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::closedCaptionsSettings() returned an error";
    EXPECT_EQ((*result).enabled, settings.enabled);
    EXPECT_EQ((*result).preferredLanguages, settings.preferredLanguages);
}

TEST_F(AccessibilityTest, SubscribeOnClosedCaptionsSettingsChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe(Firebolt::Accessibility::JsonData::OnChanged::closedCaptionsSettings);

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
    mock_with_response(Firebolt::Accessibility::JsonData::Method::highContrastUI, expectedValue);
#else
    mock(Firebolt::Accessibility::JsonData::Method::highContrastUI);
    auto expectedValue = jsonEngine.get_value(Firebolt::Accessibility::JsonData::Method::highContrastUI );
#endif

    auto result = accessibilityImpl_.highContrastUI();

    ASSERT_TRUE(result) << "AccessibilityImpl::highContrastUI() returned an error";

    EXPECT_EQ(*result, expectedValue);
}

TEST_F(AccessibilityTest, SubscribeOnHighContrastUIChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe(Firebolt::Accessibility::JsonData::OnChanged::highContrastUI);

    auto result = accessibilityImpl_.subscribeOnHighContrastUIChanged([&](bool value) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnHighContrastUIChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}

TEST_F(AccessibilityTest, VoiceGuidanceSettings)
{
#ifdef USE_LOCAL_RESPONSE
    Firebolt::Accessibility::VoiceGuidanceSettings settings{true, 1.5, true};
    nlohmann::json expectedValue = {{Firebolt::Accessibility::JsonData::Field::VoiceGuidanceSettings::enabled, settings.enabled},
                                    {Firebolt::Accessibility::JsonData::Field::VoiceGuidanceSettings::rate, settings.rate},
                                    {Firebolt::Accessibility::JsonData::Field::VoiceGuidanceSettings::navigationHints, settings.navigationHints}};
#else
    mock(Firebolt::Accessibility::JsonData::Method::voiceGuidanceSettings);
    auto expectedValue = jsonEngine.get_value(Firebolt::Accessibility::JsonData::Method::voiceGuidanceSettings);
#endif
    mock_with_response(Firebolt::Accessibility::JsonData::Method::voiceGuidanceSettings, expectedValue);

    auto result = accessibilityImpl_.voiceGuidanceSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::voiceGuidanceSettings() returned an error";
    EXPECT_EQ((*result).enabled, settings.enabled);
    EXPECT_EQ((*result).rate, settings.rate);
    EXPECT_EQ((*result).navigationHints, settings.navigationHints);
}

TEST_F(AccessibilityTest, SubscribeOnVoiceGuidanceSettingsChanged)
{
    nlohmann::json expectedValue = 1;
    mockSubscribe(Firebolt::Accessibility::JsonData::OnChanged::voiceGuidanceSettings);

    auto result = accessibilityImpl_.subscribeOnVoiceGuidanceSettingsChanged(
        [&](const Firebolt::Accessibility::VoiceGuidanceSettings &settings) {});

    ASSERT_TRUE(result) << "AccessibilityImpl::subscribeOnVoiceGuidanceSettingsChanged() returned an error";
    EXPECT_EQ(*result, expectedValue);

    accessibilityImpl_.unsubscribe(*result);
}
