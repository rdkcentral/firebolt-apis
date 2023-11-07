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

class CoreSDKTest {

    class OnDeviceNameChangedNotification : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification {
    public:
        void onDeviceNameChanged( const std::string& ) override;
    };
    class OnAudioChangedNotification : public Firebolt::Device::IDevice::IOnAudioChangedNotification {
    public:
        void onAudioChanged( const Firebolt::Device::AudioProfiles& ) override;
    };
    class OnScreenResolutionChangedNotification : public Firebolt::Device::IDevice::IOnScreenResolutionChangedNotification {
    public:
        void onScreenResolutionChanged( const Firebolt::Device::Resolution& ) override;
    };
    class OnPreferredAudioLanguagesChangedNotification : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    public:
        void onPreferredAudioLanguagesChanged( const std::vector<std::string>& ) override;
    };
    struct OnClosedCaptionsSettingsChangedNotification : public Firebolt::Accessibility::IAccessibility::IOnClosedCaptionsSettingsChangedNotification {
        void onClosedCaptionsSettingsChanged( const Firebolt::Accessibility::ClosedCaptionsSettings& ) override;
    };

public:
    CoreSDKTest() = default;
    virtual ~CoreSDKTest() = default;

    static void CreateFireboltInstance();
    static void DestroyFireboltInstance();
    static void TestCoreStaticSDK();
    static void GetDeviceName();
    static void SubscribeDeviceNameChanged();
    static void UnsubscribeDeviceNameChanged();
    static void GetDeviceAudio();
    static void SubscribeDeviceAudioChanged();
    static void UnsubscribeDeviceAudioChanged();
    static void GetDeviceScreenResolution();
    static void SubscribeDeviceScreenResolutionChanged();
    static void UnsubscribeDeviceScreenResolutionChanged();
    static void GetLocalizationPreferredAudioLanguages();
    static void SetLocalizationPreferredAudioLanguages();
    static void SubscribeLocalizationPreferredAudioLanguagesChanged();
    static void UnsubscribeLocalizationPreferredAudioLanguagesChanged();
    static void GetAccessibilityClosedCaptionsSettings();
    static void SubscribeAccessibilityClosedCaptionsSettingsChanged();
    static void UnsubscribeAccessibilityClosedCaptionsSettingsChanged();
    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnDeviceNameChangedNotification _deviceNameChangedNotification;
    static OnAudioChangedNotification _audioChangedNotification;
    static OnScreenResolutionChangedNotification _screenResolutionChangedNotification;
    static OnPreferredAudioLanguagesChangedNotification _preferredAudioLanguagesChangedNotification;
    static OnClosedCaptionsSettingsChangedNotification _closedCaptionsSettingsChangedNotification;
};

