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
#include "gtest/gtest.h"

class LocalizationTest : public ::testing::Test
{
protected:
    void SetUp() override { eventReceived = false; }

    // Create a condition variable and mutex to wait for the events to be received
    std::condition_variable cv;
    std::mutex mtx;
    bool eventReceived;

    JsonEngine jsonEngine;
};

TEST_F(LocalizationTest, CountryCode)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().country();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("Localization.country").get<std::string>();
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(LocalizationTest, PreferredAudioLanguages)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("Localization.preferredAudioLanguages");
    std::set<std::string> expectedSet(expectedValue.begin(), expectedValue.end());
    std::set<std::string> resultSet(result->begin(), result->end());
    EXPECT_EQ(resultSet, expectedSet);
}

TEST_F(LocalizationTest, PresentationLanguage)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().presentationLanguage();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("Localization.presentationLanguage").get<std::string>();
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(LocalizationTest, subscribeOnCountryCodeChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnCountryChanged(
        [&](const std::string& code)
        {
            EXPECT_EQ(code, "US");
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });

    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";

    // Trigger the event from the mock server
    triggerEvent("Localization.onCountryChanged", R"({"value":"US"})");
    verifyEventReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Localization.onCountryChanged", R"({"value":"eng-us"})");
    verifyEventNotReceived(mtx, cv, eventReceived);

    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(LocalizationTest, subscribeOnPreferredAudioLanguagesChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnPreferredAudioLanguagesChanged(
        [&](const std::vector<std::string>& languages)
        {
            EXPECT_EQ(languages.size(), 2);
            EXPECT_EQ(languages[0], "spa");
            EXPECT_EQ(languages[1], "eng");
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });

    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";

    // Trigger the event from the mock server
    triggerEvent("Localization.onPreferredAudioLanguagesChanged", R"({"value":["spa","eng"]})");

    verifyEventReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Localization.onPreferredAudioLanguagesChanged", R"(["es-mx","en-gb"])");
    verifyEventNotReceived(mtx, cv, eventReceived);

    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(LocalizationTest, subscribeOnPreferredPresentationLanguageChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnPresentationLanguageChanged(
        [&](const std::string& language)
        {
            EXPECT_EQ(language, "en-US");
            {
                std::lock_guard<std::mutex> lock(mtx);
                eventReceived = true;
            }
            cv.notify_one();
        });

    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";

    // Trigger the event from the mock server
    triggerEvent("Localization.onPresentationLanguageChanged", R"({"value":"en-US"})");
    verifyEventReceived(mtx, cv, eventReceived);

    SetUp();
    triggerEvent("Localization.onPresentationLanguageChanged", R"({"value":"fra"})");
    verifyEventNotReceived(mtx, cv, eventReceived);

    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}
