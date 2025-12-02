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
#include "firebolt.h"
#include "json_engine.h"
#include "json_types/jsondata_accessibility_types.h"
#include "utils.h"

class AccessibilityTest : public ::testing::Test
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
    auto id = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribeOnAudioDescriptionChanged(

        [&](const bool& enabled)
        {
            std::cout << "[Subscription] Accessibility audio description changed" << std::endl;

            EXPECT_EQ(enabled, false);
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);

    triggerEvent("Accessibility.onAudioDescriptionChanged", R"({"value": false})");
    verifyEventReceived(mtx, cv, eventReceived);

    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}

TEST_F(AccessibilityTest, ClosedCaptionsSettings)
{
    auto expectedValue = jsonEngine.get_value("Accessibility.closedCaptionsSettings");
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings();
    ASSERT_TRUE(result) << "AccessibilityImpl::closedCaptionsSettings() returned an error";
    EXPECT_EQ((*result).enabled, expectedValue.at("enabled").get<bool>());
    EXPECT_EQ((*result).preferredLanguages, expectedValue.at("preferredLanguages").get<std::vector<std::string>>());
}

TEST_F(AccessibilityTest, SubscribeOnClosedCaptionsSettingsChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribeOnClosedCaptionsSettingsChanged(
        [&](const Firebolt::Accessibility::ClosedCaptionsSettings& settings)
        {
            std::cout << "[Subscription] Accessibility closed captions settings changed" << std::endl;

            EXPECT_EQ(settings.enabled, true);
            EXPECT_EQ(settings.preferredLanguages.size(), 2);
            EXPECT_EQ(settings.preferredLanguages[0], "eng");
            EXPECT_EQ(settings.preferredLanguages[1], "fra");

            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);

    triggerEvent("Accessibility.onClosedCaptionsSettingsChanged",
                 R"({"enabled": true, "preferredLanguages": ["eng", "fra"]})");
    verifyEventReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Accessibility.onClosedCaptionsSettingsChanged",
                 R"({"enabled": true, "preferredLanguages": ["en-gb", "fr-fr"]})");
    verifyEventNotReceived(mtx, cv, eventReceived);

    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}

TEST_F(AccessibilityTest, HighContrastUI)
{
    auto expectedValue = jsonEngine.get_value("Accessibility.highContrastUI");
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().highContrastUI();

    ASSERT_TRUE(result) << "AccessibilityImpl::highContrastUI() returned an error";
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(AccessibilityTest, SubscribeOnHighContrastUIChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribeOnHighContrastUIChanged(
        [&](const bool& enabled)
        {
            std::cout << "[Subscription] Accessibility high contrast UI changed" << std::endl;

            EXPECT_EQ(enabled, true);
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);

    triggerEvent("Accessibility.onHighContrastUIChanged", R"({"value": true})");
    verifyEventReceived(mtx, cv, eventReceived);

    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}

TEST_F(AccessibilityTest, VoiceGuidanceSettings)
{
    auto expectedValue = jsonEngine.get_value("Accessibility.voiceGuidanceSettings");
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().voiceGuidanceSettings();

    ASSERT_TRUE(result) << "AccessibilityImpl::voiceGuidanceSettings() returned an error";
    EXPECT_EQ((*result).enabled, expectedValue.at("enabled").get<bool>());
    EXPECT_EQ((*result).rate, expectedValue.at("rate").get<float>());
    EXPECT_EQ((*result).navigationHints, expectedValue.at("navigationHints").get<bool>());
}

TEST_F(AccessibilityTest, SubscribeOnVoiceGuidanceSettingsChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribeOnVoiceGuidanceSettingsChanged(
        [&](const Firebolt::Accessibility::VoiceGuidanceSettings& settings)
        {
            std::cout << "[Subscription] Accessibility voice guidance settings changed" << std::endl;

            EXPECT_EQ(settings.enabled, false);
            EXPECT_EQ(settings.rate, 1.0f);
            EXPECT_EQ(settings.navigationHints, false);

            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });
    verifyEventSubscription(id);

    triggerEvent("Accessibility.onVoiceGuidanceSettingsChanged",
                 R"({"enabled": false, "rate": 1.0, "navigationHints": false})");
    verifyEventReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Accessibility.onVoiceGuidanceSettingsChanged",
                 R"({"enabled": false, "rate": 11.0, "navigationHints": false})");
    verifyEventNotReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Accessibility.onVoiceGuidanceSettingsChanged",
                 R"({"enabled": false, "rate": 0, "navigationHints": false})");
    verifyEventNotReceived(mtx, cv, eventReceived);

    // Unsubscribe from the event
    auto result = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(id.value());
    verifyUnsubscribeResult(result);
}
