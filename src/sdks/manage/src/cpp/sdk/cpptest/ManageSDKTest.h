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

#pragma once

#include <iostream>
#include "firebolt.h"

class ManageSDKTest {

    class OnDeviceNameChangedNotification : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification {
    public:
        void OnDeviceNameChanged( const std::string& ) override;
    };

    class OnFontFamilyChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontFamilyChangedNotification {
        void OnFontFamilyChanged( const Firebolt::Accessibility::FontFamily& ) override;
    };

    class OnBackgroundOpacityChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundOpacityChangedNotification {
        void OnBackgroundOpacityChanged( const float ) override;
    };

    class OnPreferredAudioLanguagesChangedNotification : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    public:
        void OnPreferredAudioLanguagesChanged( const std::vector<std::string>& ) override;
    };

    struct OnRequestChallengeNotification : public Firebolt::PinChallenge::IPinChallenge::IOnRequestChallengeNotification {
    public:
        void OnRequestChallenge( const Firebolt::PinChallenge::PinChallengeProviderRequest& ) override;
    };
public:
    ManageSDKTest() = default;
    virtual ~ManageSDKTest() = default;

    static void CreateFireboltInstance();
    static void DestroyFireboltInstance();
    static void TestManageStaticSDK();
    static void GetDeviceName();
    static void SetDeviceName();
    static void SubscribeDeviceNameChanged();
    static void UnsubscribeDeviceNameChanged();
    static void GetClosedCaptionBackgroundOpacity();
    static void SetClosedCaptionBackgroundOpacity();
    static void SubscribeClosedCaptionsBackgroundOpacityChanged();
    static void UnsubscribeClosedCaptionsBackgroundOpacityChanged();
    static void GetClosedCaptionFontFamily();
    static void SetClosedCaptionFontFamily();
    static void SubscribeClosedCaptionsFontFamilyChanged();
    static void UnsubscribeClosedCaptionsFontFamilyChanged();
    static void GetLocalizationPreferredAudioLanguages();
    static void SetLocalizationPreferredAudioLanguages();
    static void SubscribeLocalizationPreferredAudioLanguagesChanged();
    static void UnsubscribeLocalizationPreferredAudioLanguagesChanged();
    static void SubscribePinChallengeRequestChallenge();
    static void UnsubscribePinChallengeRequestChallenge();

    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnDeviceNameChangedNotification _deviceNameChangedNotification;
    static OnFontFamilyChangedNotification _fontFamilyChangedNotification;
    static OnBackgroundOpacityChangedNotification _backgroundOpacityChangedNotification;
    static OnPreferredAudioLanguagesChangedNotification _preferredAudioLanguagesChangedNotification;
    static OnRequestChallengeNotification _requestChallengeNotification;
};

