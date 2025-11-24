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
#include "localization_impl.h"
#include "mock_helper.h"

class LocalizationTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Localization::LocalizationImpl localizationImpl_{mockHelper};
};

TEST_F(LocalizationTest, CountryCode)
{
    mock("Localization.countryCode");

    auto result = localizationImpl_.countryCode();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("Localization.countryCode").get<std::string>();
    EXPECT_EQ(*result, expectedValue);
}

TEST_F(LocalizationTest, PreferredAudioLanguages)
{
    mock("Localization.preferredAudioLanguages");

    auto result = localizationImpl_.preferredAudioLanguages();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("Localization.preferredAudioLanguages");
    std::set<std::string> expectedSet(expectedValue.begin(), expectedValue.end());
    std::set<std::string> resultSet(result->begin(), result->end());
    EXPECT_EQ(resultSet, expectedSet);
}

TEST_F(LocalizationTest, subscribeOnCountryCodeChanged)
{
    mockSubscribe("Localization.onCountryCodeChanged");

    auto id = localizationImpl_.subscribeOnCountryCodeChanged([](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = localizationImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(LocalizationTest, subscribeOnPreferredAudioLanguagesChanged)
{
    mockSubscribe("Localization.onPreferredAudioLanguagesChanged");

    auto id = localizationImpl_.subscribeOnPreferredAudioLanguagesChanged([](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = localizationImpl_.unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}
