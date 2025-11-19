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

#include "CoreClientTest.h"
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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
    if (CoreClientTest::WaitOnConnectionReady())
    {

        // Device properties
        runTest(CoreClientTest::GetDeviceModel, "GetDeviceModel");
        runTest(CoreClientTest::GetDeviceSku, "GetDeviceSku");
        runTest(CoreClientTest::GetDeviceName, "GetDeviceName");
        runTest(CoreClientTest::GetDeviceVersion, "GetDeviceVersion");
        runTest(CoreClientTest::SubscribeDeviceNameChanged, "SubscribeDeviceNameChanged");
        runTest(CoreClientTest::UnsubscribeDeviceNameChanged, "UnsubscribeDeviceNameChanged");
        runTest(CoreClientTest::GetDeviceAudio, "GetDeviceAudio");
        runTest(CoreClientTest::SubscribeDeviceAudioChanged, "SubscribeDeviceAudioChanged");
        runTest(CoreClientTest::UnsubscribeDeviceAudioChanged, "UnsubscribeDeviceAudioChanged");
        runTest(CoreClientTest::GetDeviceScreenResolution, "GetDeviceScreenResolution");
        runTest(CoreClientTest::SubscribeDeviceScreenResolutionChanged, "SubscribeDeviceScreenResolutionChanged");
        runTest(CoreClientTest::UnsubscribeDeviceScreenResolutionChanged, "UnsubscribeDeviceScreenResolutionChanged");

        // Localization
        runTest(CoreClientTest::GetLocalizationCountryCode, "GetLocalizationCountryCode");
        runTest(CoreClientTest::GetLocalizationPreferredAudioLanguages, "GetLocalizationPreferredAudioLanguages");
        runTest(CoreClientTest::SubscribeOnLocalizationCountryCodeChanged, "SubscribeOnLocalizationCountryCodeChanged");
        runTest(CoreClientTest::UnsubscribeOnLocalizationCountryCodeChanged,
                "UnsubscribeOnLocalizationCountryCodeChanged");
        runTest(CoreClientTest::SubscribeOnLocalizationPreferredAudioLanguagesChanged,
                "SubscribeOnLocalizationPreferredAudioLanguagesChanged");
        runTest(CoreClientTest::UnsubscribeOnLocalizationPreferredAudioLanguagesChanged,
                "UnsubscribeOnLocalizationPreferredAudioLanguagesChanged");

        // Metrics
        runTest(CoreClientTest::MetricsReady, "MetricsReady");

        // SecureStorage
        runTest(CoreClientTest::ClearSecureStorage, "ClearSecureStorage");
        runTest(CoreClientTest::GetSecureStorage, "GetSecureStorage");
        runTest(CoreClientTest::RemoveSecureStorage, "RemoveSecureStorage");
        runTest(CoreClientTest::SetSecureStorage, "SetSecureStorage");
        runTest(CoreClientTest::SetSecureStorageForApp, "SetSecureStorageForApp");
        runTest(CoreClientTest::RemoveSecureStorageForApp, "RemoveSecureStorageForApp");
        runTest(CoreClientTest::ClearSecureStorageForApp, "ClearSecureStorageForApp");

        if (allTestsPassed)
        {
            cout << "=========================" << endl;
            cout << "ALL CORE TESTS SUCCEEDED!" << endl;
            cout << "=========================" << endl;
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
        }
    }
    else
    {
        cout << "Core Test not able to connect with server..." << endl;
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

    printf("Firebolt Core Test\n");

    CoreClientTest::CreateFireboltInstance(url);
    RunAllTests();
    CoreClientTest::DestroyFireboltInstance();

    return 0;
}
