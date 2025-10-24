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

#include "metrics_impl.h"
#include "json_engine.h"
#include "mock_helper.h"

class MetricsTest : public ::testing::Test, protected MockBase
{
protected:
    Firebolt::Metrics::MetricsImpl metricsImpl_{mockHelper};
};

TEST_F(MetricsTest, ready)
{
    EXPECT_CALL(mockHelper, getJson("Metrics.ready", _))
        .WillOnce(Invoke([&](const std::string &methodName, const nlohmann::json &parameters)
                        { return Firebolt::Result<nlohmann::json>{jsonEngine.get_value("Metrics.ready")}; }));

    auto result = metricsImpl_.ready();
    ASSERT_TRUE(result) << "error on get";
    auto expectedValue = jsonEngine.get_value("Metrics.ready");
    EXPECT_EQ(*result, expectedValue);
}
