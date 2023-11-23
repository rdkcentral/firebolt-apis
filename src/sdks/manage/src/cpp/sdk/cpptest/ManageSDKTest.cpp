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

#include <unistd.h>
#include "ManageSDKTest.h"

using namespace std;
bool ManageSDKTest::_connected;
ManageSDKTest::OnDeviceNameChangedNotification ManageSDKTest::_deviceNameChangedNotification;
ManageSDKTest::OnFontFamilyChangedNotification ManageSDKTest::_fontFamilyChangedNotification;
ManageSDKTest::OnBackgroundOpacityChangedNotification ManageSDKTest::_backgroundOpacityChangedNotification;
ManageSDKTest::OnPreferredAudioLanguagesChangedNotification ManageSDKTest::_preferredAudioLanguagesChangedNotification;
#ifdef RPC_ONLY
ManageSDKTest::OnRequestChallengeNotification ManageSDKTest::_requestChallengeNotification;
#endif
ManageSDKTest::KeyboardProvider ManageSDKTest::_keyboardProvider;

void ManageSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
}

void ManageSDKTest::CreateFireboltInstance()
{
    const std::string config = "{\
            \"waitTime\": 1000,\
            \"logLevel\": \"Info\",\
            \"workerPool\":{\
            \"queueSize\": 8,\
            \"threadCount\": 3\
            },\
            \"wsUrl\": \"ws://127.0.0.1:9998\"\
            }";

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Initialize(config);
    Firebolt::IFireboltAccessor::Instance().Connect(ConnectionChanged);
}

void ManageSDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool ManageSDKTest::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false)) {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return _connected;
}

void ManageSDKTest::GetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Name = " << name.c_str() << endl;
    } else {
        cout << "Get Device Name status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().setName("Hello", &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Device Name is success" << endl;
    } else {
        cout << "Set Device Name status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::OnDeviceNameChangedNotification::onDeviceNameChanged( const std::string& name)
{
    cout << "Name changed, new name --> " << name << endl;
}

void ManageSDKTest::SubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device NameChange is success" << endl;
    } else {
        cout << "Subscribe Device NameChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::UnsubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device NameChange is success" << endl;
    } else {
        cout << "Unsubscribe Device NameChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetClosedCaptionBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    const float value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().backgroundOpacity(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption BackgroundOpacity = " << value << endl;
    } else {
        cout << "Get ClosedCaption BackgroundOpacity status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetClosedCaptionBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setBackgroundOpacity(2.0, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption BackgroundOpacity is success" << endl;
    } else {
        cout << "Set ClosedCaption BackgroundOpacity status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::OnBackgroundOpacityChangedNotification::onBackgroundOpacityChanged( const float opacity )
{
    cout << "BackgroundOpacity changed, new value --> " << opacity << endl;
}

void ManageSDKTest::SubscribeClosedCaptionsBackgroundOpacityChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(_backgroundOpacityChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
    } else {
        cout << "Subscribe ClosedCaptions BackgroundOpacityChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::UnsubscribeClosedCaptionsBackgroundOpacityChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(_backgroundOpacityChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
    } else {
        cout << "Unsubscribe ClosedCaptions BackgroundOpacityChange status = " << static_cast<int>(error) << endl;
    }
}

using FontFamilyMap = std::unordered_map<Firebolt::Accessibility::FontFamily, string>;
FontFamilyMap fontFamilyMap = {
    { Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF, "MonospacedSerif" },
    { Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF, "ProportionalSerif" },
    { Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF, "MonospacedSanserif" },
    { Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, "ProportionalSanserif" },
    { Firebolt::Accessibility::FontFamily::SMALLCAPS, "SmallCaps" },
    { Firebolt::Accessibility::FontFamily::CURSIVE, "Cursive" },
    { Firebolt::Accessibility::FontFamily::CASUAL, "Casual" }};
inline const string& ConvertToFontFamilyStr(Firebolt::Accessibility::FontFamily family)
{
    return fontFamilyMap[family];
}

void ManageSDKTest::GetClosedCaptionFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Accessibility::FontFamily value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontFamily(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption FontFamily value = " << ConvertToFontFamilyStr(value) << endl;
    } else {
        cout << "Get ClosedCaption FontFamily status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetClosedCaptionFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontFamily(Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption FontFamily is success" << endl;
    } else {
        cout << "Set ClosedCaption FontFamily status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::OnFontFamilyChangedNotification::onFontFamilyChanged( const Firebolt::Accessibility::FontFamily& family )
{
    cout << "FontFamily changed, new code --> " << ConvertToFontFamilyStr(family) << endl;
}

void ManageSDKTest::SubscribeClosedCaptionsFontFamilyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(_fontFamilyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe ClosedCaptions FontFamilyChange is success" << endl;
    } else {
        cout << "Subscribe ClosedCaptions FontFamilyChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::UnsubscribeClosedCaptionsFontFamilyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(_fontFamilyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe ClosedCaptions FontFamilyChange is success" << endl;
    } else {
        cout << "Unsubscribe ClosedCaptions FontFamilyChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::GetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Localization PreferredAudioLanguages : " << endl;
        for (auto language: languages) {
            cout << "----- > " <<language << endl;
        }
    } else {
        cout << "Get Localization PreferredAudioLanguages status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::SetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = { "ara", "jpn", "hin" };
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setPreferredAudioLanguages(languages, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Localization PreferredAudioLanguages is success" << endl;
    } else {
        cout << "Get Localization PreferredAudioLanguages status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::OnPreferredAudioLanguagesChangedNotification::onPreferredAudioLanguagesChanged( const std::vector<std::string>& languages)
{
    cout << "PreferredAudioLanguages Changed, new languages --> " << endl;
    for (auto language : languages) {
        cout << " -> " << language << endl;
    }
}

void ManageSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        cout << "Subscribe Localization PreferredAudioLanguagesChange status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange status = " << static_cast<int>(error) << endl;
    }
}

#ifdef RPC_ONLY
using PinSpaceMap = std::unordered_map<Firebolt::PinChallenge::PinChallengePinSpace, string>;
PinSpaceMap pinSpaceMap = {
    { Firebolt::PinChallenge::PinChallengePinSpace::PURCHASE, "Purchase" },
    { Firebolt::PinChallenge::PinChallengePinSpace::CONTENT, "Content" }};
inline const string& ConvertToPinSpaceStr(Firebolt::PinChallenge::PinChallengePinSpace pinSpace)
{
    return pinSpaceMap[pinSpace];
}

void ManageSDKTest::OnRequestChallengeNotification::onRequestChallenge( const Firebolt::PinChallenge::PinChallengeProviderRequest& pinChallenge )
{
    cout << "RequestChallenge, new challenge --> " << endl;
    cout << "CorrelationId : " << pinChallenge.correlationId << endl;
    cout << "PinChallenge.ChallengeRequestor.Id : " << pinChallenge.parameters.requestor.id << endl;
    cout << "PinChallenge.ChallengeRequestor.Name : " << pinChallenge.parameters.requestor.name << endl;
    cout << "PinChallenge.PinChallengePinSpace : " << ConvertToPinSpaceStr(pinChallenge.parameters.pinSpace) << endl;
    cout << "PinChallenge.Capability : " << *(pinChallenge.parameters.capability) << endl;
}

void ManageSDKTest::SubscribePinChallengeRequestChallenge()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().PinChallengeInterface().subscribe(_requestChallengeNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe PinChallenge RequestChallenge is success" << endl;
    } else {
        cout << "Subscribe PinChallenge RequestChallenge status = " << static_cast<int>(error) << endl;
    }
}

void ManageSDKTest::UnsubscribePinChallengeRequestChallenge()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().PinChallengeInterface().unsubscribe(_requestChallengeNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe PinChallenge RequestChallenge is success" << endl;
    } else {
        cout << "Unsubscribe PinChallenge RequestChallenge status = " << static_cast<int>(error) << endl;
    }
}
#endif

ManageSDKTest::KeyboardProvider::KeyboardProvider()
    : _session(nullptr)
    , _parameters()
    , _keyInput(false)
{
}

void ManageSDKTest::KeyboardProvider::keyboardLoop()
{
    if (_keyInput) {
        cout << " Invoking _session->focus " << endl;
        _session->focus();
        getchar();

        string key;
        cout << _parameters.message << " : ";
        getline(cin, key);
        cout<< " key --> " << key;
        Firebolt::Keyboard::KeyboardResult keyboardResult;
        keyboardResult.text = key;
        keyboardResult.canceled = false;
        cout << " Invoking _session->result " << endl;
        _session->result(keyboardResult);

        key = "";
        cout<< "\n Enter error message too for testing --> " << key;
        getline(cin, key);
        Firebolt::Keyboard::KeyboardError keyboardError;
        keyboardError.code = 123;
        keyboardError.message = key;
        cout << " Invoking _session->error " << endl;
        _session->error(keyboardError);

        _keyInput = false;
        cin.putback('\n');
    } else {
        cout << " there is no active keyboard input session " << endl;
    }
}

void ManageSDKTest::KeyboardProvider::standard(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    cout << "KeyboardProvider Standard is invoked" << endl;
    startKeyboardSession(parameters, std::move(session));
}

void ManageSDKTest::KeyboardProvider::password(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    cout << "KeyboardProvider Password is invoked" << endl;
    startKeyboardSession(parameters, std::move(session));
}

void ManageSDKTest::KeyboardProvider::email(const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session)
{
    cout << "KeyboardProvider Email is invoked" << endl;
    startKeyboardSession(parameters, std::move(session));
}

void ManageSDKTest::KeyboardProvider::startKeyboardSession( const Firebolt::Keyboard::KeyboardParameters& parameters, std::unique_ptr<Firebolt::Keyboard::IKeyboardSession> session )
{
    _session = std::move(session);
    _parameters = parameters;
    _keyInput = true;
}

void ManageSDKTest::RegisterKeyboardProvider()
{
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().provide(_keyboardProvider);
}

void ManageSDKTest::SendMessageToKeyboardProvider()
{
    _keyboardProvider.keyboardLoop();
}
