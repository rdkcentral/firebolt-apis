/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "unit.h"

class ParametersTest : public ::testing::Test
{
protected:
	JsonEngine *jsonEngine;
	Firebolt::Error error = Firebolt::Error::None;

	void SetUp() override
	{
		jsonEngine = new JsonEngine();
	}

	void TearDown() override
	{
		delete jsonEngine;
	}
};

TEST_F(ParametersTest, Initialization)
{
    nlohmann::json expectedValues = nlohmann::json::parse(jsonEngine->get_value("Parameters.initialization"));

    Firebolt::Parameters::AppInitialization appInitialization = Firebolt::IFireboltAccessor::Instance().ParametersInterface().initialization(&error);

    EXPECT_EQ(error, Firebolt::Error::None) << "Failed to retrieve appInitialization from Parameters.initialization() method";
    EXPECT_EQ(appInitialization.us_privacy, expectedValues["us_privacy"]);
    EXPECT_EQ(appInitialization.lmt, expectedValues["lmt"]);

    ASSERT_TRUE(appInitialization.discovery.has_value());
    ASSERT_TRUE(appInitialization.discovery.value().navigateTo.has_value());

    // Deserialize the actual navigateTo value (double-deserialization to handle extra escaping)
    std::string actualNavigateToStr = appInitialization.discovery.value().navigateTo.value();
    nlohmann::json actualNavigateToJson = nlohmann::json::parse(nlohmann::json::parse(actualNavigateToStr).get<std::string>());

    // Convert expectedValues["discovery"]["navigateTo"] to a serialized JSON string
    nlohmann::json expectedNavigateTo = expectedValues["discovery"]["navigateTo"];

    EXPECT_EQ(actualNavigateToJson, expectedNavigateTo);
}
