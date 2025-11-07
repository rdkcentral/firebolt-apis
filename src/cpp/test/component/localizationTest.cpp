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
#include "gtest/gtest.h"

class LocalizationTest : public ::testing::Test
{
protected:
protected:
    JsonEngine jsonEngine;
};

TEST_F(LocalizationTest, CountryCode)
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode();
    ASSERT_TRUE(result) << "error on get";

    auto expectedValue = jsonEngine.get_value("Localization.countryCode").get<std::string>();
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

TEST_F(LocalizationTest, subscribeOnCountryCodeChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnCountryCodeChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}

TEST_F(LocalizationTest, subscribeOnPreferredAudioLanguagesChanged)
{
    auto id = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnPreferredAudioLanguagesChanged(
        [](auto) { std::cout << "callback\n"; });
    ASSERT_TRUE(id) << "error on subscribe ";
    EXPECT_TRUE(id.has_value()) << "error on id";
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(id.value_or(0));
    ASSERT_TRUE(result) << "error on unsubscribe ";
}
