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
#include <nlohmann/json.hpp>
#include "firebolt.h"

class ManageSDKTest {
    class OnAudioDescriptionsEnabledChangedNotification : public Firebolt::AudioDescriptions::IAudioDescriptions::IOnEnabledChangedNotification {
    public:
        void onEnabledChanged( const bool ) override;
    };

    class OnDeviceNameChangedNotification : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification {
    public:
        void onDeviceNameChanged( const std::string& ) override;
    };

    class OnFontFamilyChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontFamilyChangedNotification {
        void onFontFamilyChanged( const Firebolt::Accessibility::FontFamily& ) override;
    };

    class OnBackgroundOpacityChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundOpacityChangedNotification {
        void onBackgroundOpacityChanged( const float& ) override;
    };

    class OnPreferredAudioLanguagesChangedNotification : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    public:
        void onPreferredAudioLanguagesChanged( const std::vector<std::string>& ) override;
    };

    class OnAllowACRCollectionChangedNotification : public Firebolt::Privacy::IPrivacy::IOnAllowACRCollectionChangedNotification {
    public:
        void onAllowACRCollectionChanged( const bool ) override;
    };

    class OnSignInNotification : public Firebolt::Discovery::IDiscovery::IOnSignInNotification {
    public:
        void onSignIn( const Firebolt::Discovery::Event& ) override;
    };

    class OnSignOutNotification : public Firebolt::Discovery::IDiscovery::IOnSignOutNotification {
    public:
        void onSignOut( const Firebolt::Discovery::Event& ) override;
    };

    class KeyboardProvider : public Firebolt::Keyboard::IKeyboardProvider {
    public:
        KeyboardProvider();
        ~KeyboardProvider() override = default;
        Firebolt::Keyboard::KeyboardResult standard( const Firebolt::Keyboard::KeyboardParameters& parameters ) override;
        Firebolt::Keyboard::KeyboardResult password( const Firebolt::Keyboard::KeyboardParameters& parameters ) override;
        Firebolt::Keyboard::KeyboardResult email( const Firebolt::Keyboard::KeyboardEmailParameters& parameters ) override;
    };
    class AcknowledgeChallengeProvider : public Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeProvider {
    public:
        AcknowledgeChallengeProvider();
        ~AcknowledgeChallengeProvider() override = default;
        Firebolt::AcknowledgeChallenge::GrantResult challenge( const Firebolt::AcknowledgeChallenge::AcknowledgeChallengeParameters& parameters ) override;
    };
    class PinChallengeProvider : public Firebolt::PinChallenge::IPinChallengeProvider {
    public:
        PinChallengeProvider();
        ~PinChallengeProvider() override = default;
        Firebolt::PinChallenge::PinChallengeResult challenge( const Firebolt::PinChallenge::PinChallengeParameters& parameters) override;
    };

    class OnAutoLowLatencyModeCapableChangedNotification : public Firebolt::HDMIInput::IHDMIInput::IOnAutoLowLatencyModeCapableChangedNotification {
    public:
        void onAutoLowLatencyModeCapableChanged( const Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo& ) override;
    };

public:
    ManageSDKTest() = default;
    virtual ~ManageSDKTest() = default;

    static void CreateFireboltInstance(const std::string& url);
    static void DestroyFireboltInstance();
    static void TestManageStaticSDK();

    static void GetAdvertisingSkipRestriction();
    static void SetAdvertisingSkipRestriction();
    static void ResetAdvertisingIdentifier();

    static void SetAccountSession();

    static void GetAudioDescriptionsEnabled();
    static void SetAudioDescriptionsEnabled();
    static void SubscribeAudioDescriptionsEnabledChanged();
    static void UnsubscribeAudioDescriptionsEnabledChanged();

    static void GetDeviceName();
    static void SetDeviceName();
    static void SubscribeDeviceNameChanged();
    static void UnsubscribeDeviceNameChanged();

    static void GetClosedCaptionsBackgroundOpacity();
    static void SetClosedCaptionsBackgroundOpacity();
    static void SubscribeClosedCaptionsBackgroundOpacityChanged();
    static void UnsubscribeClosedCaptionsBackgroundOpacityChanged();

    static void GetClosedCaptionsFontFamily();
    static void SetClosedCaptionsFontFamily();
    static void SubscribeClosedCaptionsFontFamilyChanged();
    static void UnsubscribeClosedCaptionsFontFamilyChanged();

    static void GetLocalizationPreferredAudioLanguages();
    static void SetLocalizationPreferredAudioLanguages();
    static void SubscribeLocalizationPreferredAudioLanguagesChanged();
    static void UnsubscribeLocalizationPreferredAudioLanguagesChanged();

    static void GetPrivacyAllowACRCollection();
    static void SetPrivacyAllowACRCollection();
    static void SubscribePrivacyAllowACRCollectionChanged();
    static void UnsubscribePrivacyAllowACRCollectionChanged();
    static void GetPrivacySettings();

    static void SubscribeDiscoverySignInNotification();
    static void UnsubscribeDiscoverySignInNotification();
    static void SubscribeDiscoverySignOutNotification();
    static void UnsubscribeDiscoverySignOutNotification();

    static void RegisterKeyboardProvider();
    static void SendResponseMessageToKeyboardProvider();
    static void SendErrorMessageToKeyboardProvider();

    static void RegisterAcknowledgeChallengeProvider();
    static void SendResponseMessageToAcknowledgeChallengeProvider();
    static void SendErrorMessageToAcknowledgeChallengeProvider();

    static void RegisterPinChallengeProvider();
    static void SendResponseMessageToPinChallengeProvider();
    static void SendErrorMessageToPinChallengeProvider();

    static void GetLocalizationAdditionalInfo();
    static void AddLocalizationAdditionalInfo();
    static void RemoveLocalizationAdditionalInfo();

    static void GetUserGrantsPermission();
    static void GrantUserGrantsPermission();
    static void DenyUserGrantsPermission();
    static void ClearUserGrantsPermission();

    static void WifiScan();
    static void WifiConnect();
    static void WifiDisconnect();

    static void GlobalSubscribeHdmiAutoLowLatencyModeCapableChanged();
    static void GlobalUnsubscribeHdmiAutoLowLatencyModeCapableChanged();

    static void GetAutoLowLatencyModeCapable();
    static void SetAutoLowLatencyModeCapable();
    static void GetEdidVersion();
    static void SetEdidVersion();
    static void GetHdmiPortInfo();

    static bool WaitOnConnectionReady();

    static void event_trigger(nlohmann::json event);
    static void provider_trigger(nlohmann::json provider);

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnAudioDescriptionsEnabledChangedNotification _audioDescriptionEnabledChangedNotification;
    static OnDeviceNameChangedNotification _deviceNameChangedNotification;
    static OnFontFamilyChangedNotification _fontFamilyChangedNotification;
    static OnBackgroundOpacityChangedNotification _backgroundOpacityChangedNotification;
    static OnPreferredAudioLanguagesChangedNotification _preferredAudioLanguagesChangedNotification;
    static OnAllowACRCollectionChangedNotification _allowACRCollectionChangedNotification;
    static KeyboardProvider _keyboardProvider;
    static AcknowledgeChallengeProvider _acknowledgeChallengeProvider;
    static PinChallengeProvider _pinChallengeProvider;
    static OnSignInNotification _signInNotification;
    static OnSignOutNotification _signOutNotification;
    static OnAutoLowLatencyModeCapableChangedNotification _autoLowLatencyModeCapableChangedNotification;

    static Firebolt::Wifi::AccessPointList _apList;

public:
    static const nlohmann::json audioDescriptionsEnabledChanged;
    static const nlohmann::json deviceNameChanged;
    static const nlohmann::json backgroundOpacityChanged;
    static const nlohmann::json fontFamilyChanged;
    static const nlohmann::json preferredAudioLanguagesChanged;
    static const nlohmann::json allowACRCollectionChanged;
    static const nlohmann::json signInEvent;
    static const nlohmann::json signOutEvent;
    static const nlohmann::json autoLowLatencyModeCapableChanged;
    static const nlohmann::json requestStandard;
    static const nlohmann::json requestEmail;
    static const nlohmann::json requestPassword;
    static const nlohmann::json ackRequestChallenge;
    static const nlohmann::json pinRequestChallenge;
};

