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

#include "CoreSDKTest.h"
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <thread>

using namespace std;

const char* options = ":hu:";

void RunAllTests()
{
    bool allTestsPassed = true;
    vector<string> errorMessages;

    auto runTest = [&allTestsPassed, &errorMessages](auto testFunction, const string& testName)
    {
        try
        {
            testFunction();
        }
        catch (const exception& e)
        {
            errorMessages.push_back("Test " + testName + " failed: " + e.what());
            allTestsPassed = false;
        }
    };

    // Ensure the connection is ready before running tests
    if (CoreSDKTest::WaitOnConnectionReady())
    {

        // ClosedCaptions methods
        runTest(CoreSDKTest::GetClosedCaptionsBackgroundOpacity, "GetClosedCaptionsBackgroundOpacity");
        runTest(CoreSDKTest::SetClosedCaptionsBackgroundOpacity, "SetClosedCaptionsBackgroundOpacity");
        runTest(CoreSDKTest::SubscribeClosedCaptionsBackgroundOpacityChanged,
                "SubscribeClosedCaptionsBackgroundOpacityChanged");
        runTest(CoreSDKTest::UnsubscribeClosedCaptionsBackgroundOpacityChanged,
                "UnsubscribeClosedCaptionsBackgroundOpacityChanged");

        runTest(CoreSDKTest::GetClosedCaptionsFontFamily, "GetClosedCaptionsFontFamily");
        runTest(CoreSDKTest::SetClosedCaptionsFontFamily, "SetClosedCaptionsFontFamily");
        runTest(CoreSDKTest::SubscribeClosedCaptionsFontFamilyChanged, "SubscribeClosedCaptionsFontFamilyChanged");
        runTest(CoreSDKTest::UnsubscribeClosedCaptionsFontFamilyChanged, "UnsubscribeClosedCaptionsFontFamilyChanged");

        // Device properties
        runTest(CoreSDKTest::GetDeviceModel, "GetDeviceModel");
        runTest(CoreSDKTest::GetDeviceSku, "GetDeviceSku");
        runTest(CoreSDKTest::GetDeviceName, "GetDeviceName");
        runTest(CoreSDKTest::GetDeviceVersion, "GetDeviceVersion");
        runTest(CoreSDKTest::SubscribeDeviceNameChanged, "SubscribeDeviceNameChanged");
        runTest(CoreSDKTest::UnsubscribeDeviceNameChanged, "UnsubscribeDeviceNameChanged");
        runTest(CoreSDKTest::GetDeviceAudio, "GetDeviceAudio");
        runTest(CoreSDKTest::SubscribeDeviceAudioChanged, "SubscribeDeviceAudioChanged");
        runTest(CoreSDKTest::UnsubscribeDeviceAudioChanged, "UnsubscribeDeviceAudioChanged");
        runTest(CoreSDKTest::GetDeviceScreenResolution, "GetDeviceScreenResolution");
        runTest(CoreSDKTest::SubscribeDeviceScreenResolutionChanged, "SubscribeDeviceScreenResolutionChanged");
        runTest(CoreSDKTest::UnsubscribeDeviceScreenResolutionChanged, "UnsubscribeDeviceScreenResolutionChanged");

        // HdmiInput
        runTest(CoreSDKTest::SubscribeHdmiAutoLowLatencyModeCapableChanged,
                "SubscribeHdmiAutoLowLatencyModeCapableChanged");
        runTest(CoreSDKTest::UnsubscribeHdmiAutoLowLatencyModeCapableChanged,
                "UnsubscribeHdmiAutoLowLatencyModeCapableChanged");
        runTest(CoreSDKTest::GetAutoLowLatencyModeCapable, "GetAutoLowLatencyModeCapable");
        runTest(CoreSDKTest::SetAutoLowLatencyModeCapable, "SetAutoLowLatencyModeCapable");
        runTest(CoreSDKTest::GetEdidVersion, "GetEdidVersion");
        runTest(CoreSDKTest::SetEdidVersion, "SetEdidVersion");
        runTest(CoreSDKTest::GetHdmiPortInfo, "GetHdmiPortInfo");

        // Lifecycle
        runTest(CoreSDKTest::LifecycleReady, "LifecycleReady");
        runTest(CoreSDKTest::LifecycleClose, "LifecycleClose");
        runTest(CoreSDKTest::LifecycleFinished, "LifecycleFinished");
        runTest(CoreSDKTest::LifecycleState, "LifecycleState");
        runTest(CoreSDKTest::SubscribeOnLifecycleBackgroundChanged, "SubscribeOnLifecycleBackgroundChanged");
        runTest(CoreSDKTest::UnsubscribeOnLifecycleBackgroundChanged, "UnsubscribeOnLifecycleBackgroundChanged");
        runTest(CoreSDKTest::SubscribeOnLifecycleForegroundChanged, "SubscribeOnLifecycleForegroundChanged");
        runTest(CoreSDKTest::UnsubscribeOnLifecycleForegroundChanged, "UnsubscribeOnLifecycleForegroundChanged");
        runTest(CoreSDKTest::SubscribeOnLifecycleInactiveChanged, "SubscribeOnLifecycleInactiveChanged");
        runTest(CoreSDKTest::UnsubscribeOnLifecycleInactiveChanged, "UnsubscribeOnLifecycleInactiveChanged");
        runTest(CoreSDKTest::SubscribeOnLifecycleSuspendedChanged, "SubscribeOnLifecycleSuspendedChanged");
        runTest(CoreSDKTest::UnsubscribeOnLifecycleSuspendedChanged, "UnsubscribeOnLifecycleSuspendedChanged");
        runTest(CoreSDKTest::SubscribeOnLifecycleUnloadingChanged, "SubscribeOnLifecycleUnloadingChanged");
        runTest(CoreSDKTest::UnsubscribeOnLifecycleUnloadingChanged, "UnsubscribeOnLifecycleUnloadingChanged");

        // Localization
        runTest(CoreSDKTest::GetLocalizationCountryCode, "GetLocalizationCountryCode");
        runTest(CoreSDKTest::GetLocalizationPreferredAudioLanguages, "GetLocalizationPreferredAudioLanguages");
        runTest(CoreSDKTest::SubscribeOnLocalizationCountryCodeChanged, "SubscribeOnLocalizationCountryCodeChanged");
        runTest(CoreSDKTest::UnsubscribeOnLocalizationCountryCodeChanged,
                "UnsubscribeOnLocalizationCountryCodeChanged");
        runTest(CoreSDKTest::SubscribeOnLocalizationPreferredAudioLanguagesChanged,
                "SubscribeOnLocalizationPreferredAudioLanguagesChanged");
        runTest(CoreSDKTest::UnsubscribeOnLocalizationPreferredAudioLanguagesChanged,
                "UnsubscribeOnLocalizationPreferredAudioLanguagesChanged");

        // Metrics
        runTest(CoreSDKTest::MetricsReady, "MetricsReady");

        // SecureStorage
        runTest(CoreSDKTest::ClearSecureStorage, "ClearSecureStorage");
        runTest(CoreSDKTest::GetSecureStorage, "GetSecureStorage");
        runTest(CoreSDKTest::RemoveSecureStorage, "RemoveSecureStorage");
        runTest(CoreSDKTest::SetSecureStorage, "SetSecureStorage");
        runTest(CoreSDKTest::SetSecureStorageForApp, "SetSecureStorageForApp");
        runTest(CoreSDKTest::RemoveSecureStorageForApp, "RemoveSecureStorageForApp");
        runTest(CoreSDKTest::ClearSecureStorageForApp, "ClearSecureStorageForApp");

        if (allTestsPassed)
        {
            cout << "============================" << endl;
            cout << "ALL CORE SDK TESTS SUCCEEDED!" << endl;
            cout << "============================" << endl;
        }
        else
        {
            cout << "============================" << endl;
            cout << "SOME TESTS FAILED:" << endl;
            for (const auto& errorMessage : errorMessages)
            {
                cout << errorMessage << endl;
            }
            cout << "============================" << endl;
            exit(1);
        }
    }
    else
    {
        cout << "Core Test not able to connect with server..." << endl;
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    int c;
    string url = "ws://127.0.0.1:9998";
    while ((c = getopt(argc, argv, options)) != -1)
    {
        switch (c)
        {
        case 'u':
            url = optarg;
            break;
        case 'h':
            printf("./TestFireboltManage -u ws://ip:port\n");
            exit(1);
        }
    }

    printf("Firebolt Core SDK Test\n");

    CoreSDKTest::CreateFireboltInstance(url);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    RunAllTests();
    CoreSDKTest::DestroyFireboltInstance();

    return 0;
}
