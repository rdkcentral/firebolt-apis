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

#include "Module.h"
#include "CoreSDKTests.h"

namespace FireboltSDK {
    CoreTests::CoreTests()
        : Tests()
    {
        _functionMap.emplace(std::piecewise_construct, std::forward_as_tuple("Get Discovery Policy"),
                             std::forward_as_tuple(&GetDiscoveryPolicy));
    }

    /* static */ uint32_t CoreTests::GetDiscoveryPolicy()
    {
        const string method = _T("discovery.policy");
        WPEFramework::Core::ProxyType<Policy> response;
        uint32_t status = FireboltSDK::Properties::Get(method, response);

        EXPECT_EQ(status, FireboltSDKErrorNone);
        if (status == FireboltSDKErrorNone) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::Core, Logger::Module<CoreTests>(),
            "EnableRecommendations : %d", response->EnableRecommendations.Value());
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::Core, Logger::Module<CoreTests>(),
            "ShareWatchHistory : %d", response->ShareWatchHistory.Value());
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::Core, Logger::Module<CoreTests>(),
            "RememberWatchedPrograms : %d", response->RememberWatchedPrograms.Value());
        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::Core, Logger::Module<CoreTests>(),
            "Get %s status = %d", method.c_str(), status);
        }

        return status;
    }
}

#ifdef __cplusplus
extern "C" {
#endif

uint32_t test_firebolt_core_main()
{
    return FireboltSDK::Tests::Main<FireboltSDK::CoreTests>();
}

uint32_t test_properties_get_policy()
{
    const string method = _T("discovery.policy");
    WPEFramework::Core::ProxyType<FireboltSDK::Policy> response;
    uint32_t status = FireboltSDK::Properties::Get(method, response);

    EXPECT_EQ(status, FireboltSDKErrorNone);
    if (status == FireboltSDKErrorNone) {
        FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::Core, "ctest",
        "EnableRecommendations : %d", response->EnableRecommendations.Value());
        FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::Core, "ctest",
        "ShareWatchHistory : %d", response->ShareWatchHistory.Value());
        FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::Core, "ctest",
        "RememberWatchedPrograms : %d", response->RememberWatchedPrograms.Value());
    } else {
        FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::Core, "ctest",
        "Get %s status = %d", method.c_str(), status);
    }

    return status;
}

#ifdef __cplusplus
}
#endif
