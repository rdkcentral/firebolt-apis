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
        void onDeviceNameChanged( const std::string& ) override;
    };

    class OnFontFamilyChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnFontFamilyChangedNotification {
        void onFontFamilyChanged( const Firebolt::Accessibility::FontFamily& ) override;
    };

    class OnBackgroundOpacityChangedNotification : public Firebolt::ClosedCaptions::IClosedCaptions::IOnBackgroundOpacityChangedNotification {
        void onBackgroundOpacityChanged( const float ) override;
    };

    class OnPreferredAudioLanguagesChangedNotification : public Firebolt::Localization::ILocalization::IOnPreferredAudioLanguagesChangedNotification {
    public:
        void onPreferredAudioLanguagesChanged( const std::vector<std::string>& ) override;
    };

#ifdef RPC_ONLY
    class OnRequestChallengeNotification : public Firebolt::PinChallenge::IPinChallenge::IOnRequestChallengeNotification {
    public:
        void onRequestChallenge( const Firebolt::PinChallenge::PinChallengeProviderRequest& ) override;
    };
#endif
    class KeyboardProvider : public Firebolt::Keyboard::IKeyboardProvider {
    public:
        KeyboardProvider();
        ~KeyboardProvider() override = default;
        void standard( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session ) override;
        void password( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session ) override;
        void email( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session ) override;
        void SendMessage(bool response);

    private:
        void startKeyboardSession(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session);

    private:
        std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> _session;
        Firebolt::Keyboard::KeyboardParameters _parameters;
        bool _keyInput;
    };
    class AcknowledgeChallengeProvider : public Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeProvider {
    public:
        AcknowledgeChallengeProvider();
        ~AcknowledgeChallengeProvider() override = default;
	void challenge( const Firebolt::AcknowledgeChallenge::Challenge& parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session ) override;
        void SendMessage(bool response);

    private:
        void startAcknowledgeChallengeSession(const Firebolt::AcknowledgeChallenge::Challenge& parameters, std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> session);

    private:
        std::unique_ptr<Firebolt::AcknowledgeChallenge::IAcknowledgeChallengeSession> _session;
        Firebolt::AcknowledgeChallenge::Challenge _parameters;
        bool _challengeInput;
    };
    class PinChallengeProvider : public Firebolt::PinChallenge::IPinChallengeProvider {
    public:
        PinChallengeProvider();
        ~PinChallengeProvider() override = default;
	void challenge( const Firebolt::PinChallenge::PinChallenge& parameters, std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> session ) override;
        void SendMessage(bool response);

    private:
        void startPinChallengeSession(const Firebolt::PinChallenge::PinChallenge& parameters, std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> session);

    private:
        std::unique_ptr<Firebolt::PinChallenge::IPinChallengeSession> _session;
        Firebolt::PinChallenge::PinChallenge _parameters;
        bool _challengeInput;
    };

public:
    ManageSDKTest() = default;
    virtual ~ManageSDKTest() = default;

    static void CreateFireboltInstance(const std::string& url);
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
#ifdef RPC_ONLY
    static void SubscribePinChallengeRequestChallenge();
    static void UnsubscribePinChallengeRequestChallenge();
#endif
    static void RegisterKeyboardProvider();
    static void SendResponseMessageToKeyboardProvider();
    static void SendErrorMessageToKeyboardProvider();

    static void RegisterAcknowledgeChallengeProvider();
    static void SendResponseMessageToAcknowledgeChallengeProvider();
    static void SendErrorMessageToAcknowledgeChallengeProvider();
    static void RegisterPinChallengeProvider();
    static void SendResponseMessageToPinChallengeProvider();
    static void SendErrorMessageToPinChallengeProvider();
    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;
    static OnDeviceNameChangedNotification _deviceNameChangedNotification;
    static OnFontFamilyChangedNotification _fontFamilyChangedNotification;
    static OnBackgroundOpacityChangedNotification _backgroundOpacityChangedNotification;
    static OnPreferredAudioLanguagesChangedNotification _preferredAudioLanguagesChangedNotification;
#ifdef RPC_ONLY
    static OnRequestChallengeNotification _requestChallengeNotification;
#endif
    static KeyboardProvider _keyboardProvider;
    static AcknowledgeChallengeProvider _acknowledgeChallengeProvider;
    static PinChallengeProvider _pinChallengeProvider;
};

