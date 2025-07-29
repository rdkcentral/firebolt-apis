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

#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "CoreSDKTest.h"

using namespace std;

const char* options = ":hu:";

void RunAllTests() {
    bool allTestsPassed = true;
    vector<string> errorMessages;

    auto runTest = [&allTestsPassed, &errorMessages](auto testFunction, const string& testName) {
        try {
            testFunction();
        } catch (const exception& e) {
            errorMessages.push_back("Test " + testName + " failed: " + e.what());
            allTestsPassed = false;
        }
    };

    // Ensure the connection is ready before running tests
    if (CoreSDKTest::WaitOnConnectionReady()) {

        // Account ID
        runTest(CoreSDKTest::GetAccountId, "GetAccountId");

        // Account UID
        runTest(CoreSDKTest::GetAccountUid, "GetAccountUid");

        // Advertising methods
        runTest(CoreSDKTest::BuildAdvertisingConfiguration, "BuildAdvertisingConfiguration");
        runTest(CoreSDKTest::GetAdvertisingDeviceAttributes, "GetAdvertisingDeviceAttributes");
        runTest(CoreSDKTest::SubscribeAdvertisingPolicyChanged, "SubscribeAdvertisingPolicyChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::adPolicy);
        runTest(CoreSDKTest::UnsubscribeAdvertisingPolicyChanged, "UnsubscribeAdvertisingPolicyChanged");

        // Device properties
        runTest(CoreSDKTest::GetDeviceModel, "GetDeviceModel");
        runTest(CoreSDKTest::GetDeviceSku, "GetDeviceSku");
        runTest(CoreSDKTest::GetDeviceName, "GetDeviceName");
        runTest(CoreSDKTest::GetDeviceName, "GetDeviceVersion");
        runTest(CoreSDKTest::SubscribeDeviceNameChanged, "SubscribeDeviceNameChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::deviceName);
        runTest(CoreSDKTest::UnsubscribeDeviceNameChanged, "UnsubscribeDeviceNameChanged");
        runTest(CoreSDKTest::GetDeviceAudio, "GetDeviceAudio");
        runTest(CoreSDKTest::SubscribeDeviceAudioChanged, "SubscribeDeviceAudioChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::audioChanged);
        runTest(CoreSDKTest::UnsubscribeDeviceAudioChanged, "UnsubscribeDeviceAudioChanged");
        runTest(CoreSDKTest::GetDeviceScreenResolution, "GetDeviceScreenResolution");
        runTest(CoreSDKTest::SubscribeDeviceScreenResolutionChanged, "SubscribeDeviceScreenResolutionChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::deviceScreenResolutionChanged);
        runTest(CoreSDKTest::UnsubscribeDeviceScreenResolutionChanged, "UnsubscribeDeviceScreenResolutionChanged");

        // Localization methods
        runTest(CoreSDKTest::GetLocalizationAdditionalInfo, "GetLocalizationAdditionalInfo");
        runTest(CoreSDKTest::GetLocalizationLatlon, "GetLocalizationLatlon");
        runTest(CoreSDKTest::GetLocalizationPreferredAudioLanguages, "GetLocalizationPreferredAudioLanguages");
        runTest(CoreSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged, "SubscribeLocalizationPreferredAudioLanguagesChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::preferredAudioLanguagesChanged);
        runTest(CoreSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged, "UnsubscribeLocalizationPreferredAudioLanguagesChanged");

        // Accessibility - Closed Captions Settings
        runTest(CoreSDKTest::GetAccessibilityClosedCaptionsSettings, "GetAccessibilityClosedCaptionsSettings");
        runTest(CoreSDKTest::SubscribeAccessibilityClosedCaptionsSettingsChanged, "SubscribeAccessibilityClosedCaptionsSettingsChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::closedCaptionsSettingsChanged);
        runTest(CoreSDKTest::UnsubscribeAccessibilityClosedCaptionsSettingsChanged, "UnsubscribeAccessibilityClosedCaptionsSettingsChanged");

#if defined(UNIT_TESTS_APP) && defined(GATEWAY_BIDIRECTIONAL)
        // Keyboard methods
        runTest(CoreSDKTest::InvokeKeyboardEmail, "InvokeKeyboardEmail");
        CoreSDKTest::provider_trigger(CoreSDKTest::keyboardEmail);
        runTest(CoreSDKTest::AbortKeyboardEmail, "AbortKeyboardEmail");

        runTest(CoreSDKTest::InvokeKeyboardPassword, "InvokeKeyboardPassword");
        CoreSDKTest::provider_trigger(CoreSDKTest::keyboardPassword);
        runTest(CoreSDKTest::AbortKeyboardPassword, "AbortKeyboardPassword");

        runTest(CoreSDKTest::InvokeKeyboardStandard, "InvokeKeyboardStandard");
        CoreSDKTest::provider_trigger(CoreSDKTest::keyboardStandard);
        runTest(CoreSDKTest::AbortKeyboardStandard, "AbortKeyboardStandard");
#endif

        // Profile methods
        runTest(CoreSDKTest::VerifyProfileApproveContentRating, "VerifyProfileApproveContentRating");
        runTest(CoreSDKTest::VerifyProfileApprovePurchase, "VerifyProfileApprovePurchase");
        runTest(CoreSDKTest::GetProfileFlags, "GetProfileFlags");

        // Authentication methods
        runTest(CoreSDKTest::GetAuthenticationDevice, "GetAuthenticationDevice");
        runTest(CoreSDKTest::GetAuthenticationSession, "GetAuthenticationSession");
        runTest(CoreSDKTest::GetAuthenticationRoot, "GetAuthenticationRoot");
        runTest(CoreSDKTest::GetAuthenticationToken, "GetAuthenticationToken");

        // Capabilities methods
        runTest(CoreSDKTest::GetCapabilitiesAvailable, "GetCapabilitiesAvailable");
        runTest(CoreSDKTest::GetCapabilitiesGranted, "GetCapabilitiesGranted");
        runTest(CoreSDKTest::GetCapabilitiesPermitted, "GetCapabilitiesPermitted");
        runTest(CoreSDKTest::GetCapabilitiesSupported, "GetCapabilitiesSupported");
        runTest(CoreSDKTest::GetCapabilitiesInfo, "GetCapabilitiesInfo");

        // Lifecycle methods
        // runTest(CoreSDKTest::LifecycleClose, "LifecycleClose");
        runTest(CoreSDKTest::LifecycleReady, "LifecycleReady");
        runTest(CoreSDKTest::LifecycleFinished, "LifecycleFinished");
        runTest(CoreSDKTest::LifecycleState, "LifecycleState");
        runTest(CoreSDKTest::SubscribeLifecycleBackgroundNotification, "SubscribeLifecycleBackgroundNotification");
        CoreSDKTest::event_trigger(CoreSDKTest::backgroundNotification);
        runTest(CoreSDKTest::UnsubscribeLifecycleBackgroundNotification, "UnsubscribeLifecycleBackgroundNotification");
        runTest(CoreSDKTest::SubscribeLifecycleForegroundNotification, "SubscribeLifecycleForegroundNotification");
        CoreSDKTest::event_trigger(CoreSDKTest::foregroundNotification);
        runTest(CoreSDKTest::UnsubscribeLifecycleForegroundNotification, "UnsubscribeLifecycleForegroundNotification");

        // Metrics methods
        runTest(CoreSDKTest::MetricsReady, "MetricsReady");
        runTest(CoreSDKTest::MetricsSignIn, "MetricsSignIn");
        runTest(CoreSDKTest::MetricsSignOut, "MetricsSignOut");
        runTest(CoreSDKTest::MetricsStartContent, "MetricsStartContent");
        runTest(CoreSDKTest::MetricsStopContent, "MetricsStopContent");
       
     

        // SecondScreen methods
        runTest(CoreSDKTest::GetSecondScreenDevice, "GetSecondScreenDevice");
        runTest(CoreSDKTest::GetSecondScreenFriendlyName, "GetSecondScreenFriendlyName");
        runTest(CoreSDKTest::SubscribeSecondScreenFriendlyNameChanged, "SubscribeSecondScreenFriendlyNameChanged");
        CoreSDKTest::event_trigger(CoreSDKTest::friendlyNameChanged);
        runTest(CoreSDKTest::UnsubscribeSecondScreenFriendlyNameChanged, "UnsubscribeSecondScreenFriendlyNameChanged");
        runTest(CoreSDKTest::GetSecondScreenProtocols, "GetSecondScreenProtocols");

        // Discovery methods
        runTest(CoreSDKTest::DiscoverySignIn, "DiscoverySignIn");
        runTest(CoreSDKTest::DiscoverySignOut, "DiscoverySignOut");
        runTest(CoreSDKTest::DiscoveryContentAccess, "DiscoveryContentAccess");
        runTest(CoreSDKTest::DiscoveryClearContentAccess, "DiscoveryClearContentAccess");
        runTest(CoreSDKTest::DiscoveryEntitlements, "DiscoveryEntitlements");
        runTest(CoreSDKTest::DiscoveryEntityInfo, "DiscoveryEntityInfo");
        runTest(CoreSDKTest::DiscoveryPolicy, "DiscoveryPolicy");
        runTest(CoreSDKTest::DiscoveryPurchasedContent, "DiscoveryPurchasedContent");
        runTest(CoreSDKTest::DiscoveryWatchNext, "DiscoveryWatchNext");
        runTest(CoreSDKTest::DiscoveryLaunch, "DiscoveryLaunch");
#ifdef POLYMORPHICS_REDUCER_METHODS
        runTest(CoreSDKTest::DiscoveryWatched, "DiscoveryWatched");
        runTest(CoreSDKTest::DiscoveryWatchedReduced, "DiscoveryWatchedReduced");
#endif
        runTest(CoreSDKTest::SubscribeDiscoveryOnNavigateToLaunchHomeIntentNotification, "SubscribeDiscoveryOnNavigateToLaunchHomeIntentNotification");
        CoreSDKTest::event_trigger(CoreSDKTest::navigateTo);
        runTest(CoreSDKTest::UnsubscribeDiscoveryOnNavigateToLaunchHomeIntentNotification, "UnsubscribeDiscoveryOnNavigateToLaunchHomeIntentNotification");

        runTest(CoreSDKTest::SubscribeDiscoveryOnNavigateToLaunchEntityIntentNotification, "SubscribeDiscoveryOnNavigateToLaunchEntityIntentNotification");
        CoreSDKTest::event_trigger(CoreSDKTest::navigateTo);
        runTest(CoreSDKTest::UnsubscribeDiscoveryOnNavigateToLaunchEntityIntentNotification, "UnsubscribeDiscoveryOnNavigateToLaunchEntityIntentNotification");

        runTest(CoreSDKTest::SubscribeDiscoveryOnNavigateToLaunchTuneIntentNotification, "SubscribeDiscoveryOnNavigateToLaunchTuneIntentNotification");
        CoreSDKTest::event_trigger(CoreSDKTest::navigateTo);
        runTest(CoreSDKTest::UnsubscribeDiscoveryOnNavigateToLaunchTuneIntentNotification, "UnsubscribeDiscoveryOnNavigateToLaunchTuneIntentNotification");

        // Parameters Initialization
        runTest(CoreSDKTest::ParametersInitialization, "ParametersInitialization");

        if (allTestsPassed) {
            cout << "============================" << endl;
            cout << "ALL CORE SDK TESTS SUCCEEDED!" << endl;
            cout << "============================" << endl;
        } else {
            cout << "============================" << endl;
            cout << "SOME TESTS FAILED:" << endl;
            for (const auto& errorMessage : errorMessages) {
                cout << errorMessage << endl;
            }
            cout << "============================" << endl;
            exit(1);
        }
   } else {
       cout << "Core Test not able to connect with server..." << endl;
       exit(1);
   }
}

int main(int argc, char* argv[]) {
    int c;
    string url = "ws://127.0.0.1:9998";
    while ((c = getopt(argc, argv, options)) != -1) {
        switch (c) {
            case 'u':
                url = optarg;
                break;
            case 'h':
                printf("./TestFireboltManage -u ws://ip:port\n");
                exit(1);
        }
    }

    printf("Firebolt Core SDK Test\n");
#ifdef GATEWAY_BIDIRECTIONAL
    printf("- Bi-Directional\n");
#else
    printf("- Uni-Directional\n");
#endif

    CoreSDKTest::CreateFireboltInstance(url);
    RunAllTests();
    CoreSDKTest::DestroyFireboltInstance();

    return 0;
}
