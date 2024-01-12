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

#include <ctype.h>
#include "CoreSDKCTests.h"
#include "CoreSDKTestGeneratedCode.h"

int __cnt = 0;
int __pass = 0;

int TotalTests = 0;
int TotalTestsPassed = 0;

int main()
{
    test_firebolt_create_instance();
    test_firebolt_core_main();

    // Calling C function sequences
    printf("%s:%s:%d Calling C function tests\n", __FILE__, __func__, __LINE__);
    EXECUTE("test_properties_get_device_id", test_properties_get_device_id);
    EXECUTE("test_properties_get_policy", test_properties_get_policy);
    EXECUTE("test_properties_set", test_properties_set);
    EXECUTE("test_eventregister_by_providing_callback", test_eventregister_by_providing_callback);
    EXECUTE("test_eventregister", test_eventregister);
    EXECUTE("test_string_set_get_value", test_string_set_get_value);
    EXECUTE("test_generated_properties_get_device_id", test_generated_properties_get_device_id);
    //EXECUTE("test_generated_properties_get_device_version", test_generated_properties_get_device_version);
    EXECUTE("test_generated_properties_get_accessibility_closedcaption", test_generated_properties_get_accessibility_closedcaption);
    EXECUTE("test_generated_properties_get_accessibility_voiceguidancesettings", test_generated_properties_get_accessibility_voiceguidancesettings);
    EXECUTE("test_generated_properties_get_advertising_policy", test_generated_properties_get_advertising_policy);
    EXECUTE("test_generated_event_device_name", test_generated_event_device_name);
    EXECUTE("test_generated_event_device_name_with_register_same_callback", test_generated_event_device_name_with_register_same_callback);
    EXECUTE("test_generated_event_device_screenresolution", test_generated_event_device_screenresolution);
    EXECUTE("test_generated_event_accessibility_voice_guidance_settings", test_generated_event_accessibility_voice_guidance_settings);
    //EXECUTE("test_generated_calls_metrics_lifecycle_ready", test_generated_calls_metrics_lifecycle_ready);

    test_firebolt_dispose_instance();

    printf("TOTAL: %i tests; %i PASSED, %i FAILED\n", TotalTests, TotalTestsPassed, (TotalTests - TotalTestsPassed));
}

