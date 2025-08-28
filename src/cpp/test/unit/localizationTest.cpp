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

#define MODULE_NAME LocalizationTest
#include "unit.h"

class LocalizationTest : public ::testing::Test
{
protected:
    JsonEngine* jsonEngine;

    void SetUp() override { jsonEngine = new JsonEngine(); }

    void TearDown() override { delete jsonEngine; }
};

TEST_F(LocalizationTest, CountryCode)
{
    std::string expectedValues = jsonEngine->get_value("Localization.countryCode");
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode();
    ASSERT_TRUE(result) << "Error on calling localization.countryCode() method";
    EXPECT_EQ(REMOVE_QUOTES(expectedValues), *result) << "Error: wrong countryCode returned by "
                                                         "localization.countryCode()";
}

TEST_F(LocalizationTest, PreferredAudioLanguages)
{
    std::string expectedValues = jsonEngine->get_value("Localization.preferredAudioLanguages");
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages();
    ASSERT_TRUE(result) << "Error on calling localization.PreferredAudioLanguages() method";
    std::string actualValues{"["};
    for (const auto& lang : *result)
    {
        actualValues += "\"" + lang + "\",";
    }
    actualValues.pop_back();
    actualValues += "]";

    EXPECT_EQ(expectedValues, actualValues) << "Error: wrong PreferredAudioLanguages returned by "
                                               "localization.PreferredAudioLanguages()";
}

TEST_F(LocalizationTest, subscribeOnCountryCodeChanged)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnCountryCodeChanged(
        [](const auto&) { std::cout << "CountryCode changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to CountryCode";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to CountryCode";
}

TEST_F(LocalizationTest, subscribeOnPreferredAudioLanguagesChanged)
{
    auto result =
        Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnPreferredAudioLanguagesChanged(
            [](const auto&) { std::cout << "PreferredAudioLanguages changed\n"; });
    EXPECT_TRUE(result) << "Error in subscribing to PreferredAudioLanguages";

    auto unsubResult = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(result.value_or(0));
    EXPECT_EQ(unsubResult.error(), Firebolt::Error::None) << "Error in unsubscribing to PreferredAudioLanguages";
}