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
#include <cstring>
#include <string>
#include <cassert>
#include "ManageSDKTest.h"

using namespace std;
bool ManageSDKTest::_connected;
ManageSDKTest::OnAudioDescriptionsEnabledChangedNotification ManageSDKTest::_audioDescriptionEnabledChangedNotification;
ManageSDKTest::OnDeviceNameChangedNotification ManageSDKTest::_deviceNameChangedNotification;
ManageSDKTest::OnFontFamilyChangedNotification ManageSDKTest::_fontFamilyChangedNotification;
ManageSDKTest::OnBackgroundOpacityChangedNotification ManageSDKTest::_backgroundOpacityChangedNotification;
ManageSDKTest::OnPreferredAudioLanguagesChangedNotification ManageSDKTest::_preferredAudioLanguagesChangedNotification;
ManageSDKTest::OnAllowACRCollectionChangedNotification ManageSDKTest::_allowACRCollectionChangedNotification;
ManageSDKTest::OnSignInNotification ManageSDKTest::_signInNotification;
ManageSDKTest::OnSignOutNotification ManageSDKTest::_signOutNotification;
ManageSDKTest::OnAutoLowLatencyModeCapableChangedNotification ManageSDKTest::_autoLowLatencyModeCapableChangedNotification;
ManageSDKTest::KeyboardProvider ManageSDKTest::_keyboardProvider;
ManageSDKTest::AcknowledgeChallengeProvider ManageSDKTest::_acknowledgeChallengeProvider;
ManageSDKTest::PinChallengeProvider ManageSDKTest::_pinChallengeProvider;
Firebolt::Wifi::AccessPointList ManageSDKTest::_apList;


const nlohmann::json ManageSDKTest::audioDescriptionsEnabledChanged = {
    {"method", "audiodescriptions.onEnabledChanged"},
    {"payload", {{ "enabled", false }} }
};

const nlohmann::json ManageSDKTest::deviceNameChanged = {
    {"method", "device.onDeviceNameChanged"},
    {"payload", "Living Room" }
};

const nlohmann::json ManageSDKTest::backgroundOpacityChanged = {
    {"method", "closedcaptions.onBackgroundOpacityChanged"},
    {"payload", 99}
};

const nlohmann::json ManageSDKTest::fontFamilyChanged = {
    {"method", "closedcaptions.onFontFamilyChanged"},
    {"payload", "monospaced_sanserif"}
};

const nlohmann::json ManageSDKTest::preferredAudioLanguagesChanged = {
    {"method", "localization.onPreferredAudioLanguagesChanged"},
    {"payload", {
        {"name", "languages"},
        {"value", {"spa", "eng"}}
     }}
};

const nlohmann::json ManageSDKTest::allowACRCollectionChanged = {
    {"method", "privacy.onAllowACRCollectionChanged"},
    {"payload", true}
};

const nlohmann::json ManageSDKTest::signInEvent = {
    {"method", "discovery.onSignIn"},
    {"payload", {
        {"name", "event"},
        {"appId", "firecert"}
     }}
};

const nlohmann::json ManageSDKTest::signOutEvent = {
    {"method", "discovery.onSignOut"},
    {"payload", {
        {"name", "event"},
        {"appId", "firecert"}
     }}
};

const nlohmann::json ManageSDKTest::requestStandard = {
    {"method", "keyboard.onRequestStandard"},
    {"payload", {
          { "message", "who has a cat?" }
    }}
};

const nlohmann::json ManageSDKTest::requestEmail = {
    {"method", "keyboard.onRequestEmail"},
    {"payload", { 
          { "message", "who has a cat?" }
    }}
};

const nlohmann::json ManageSDKTest::requestPassword = {
    {"method", "keyboard.onRequestPassword"},
    {"payload", {
          { "message", "who has a cat?" }
    }}
};

const nlohmann::json ManageSDKTest::ackRequestChallenge = {
    {"method", "acknowledgeChallenge.onRequestChallenge"},
    {"payload", {
          {{"capability", "xrn:firebolt:capability:localization::postal-code"}},
          {"requestor",{
              {"id", "ReferenceApp"},
              {"name", "Firebolt Reference App"}
          }}
    }}
};

const nlohmann::json ManageSDKTest::pinRequestChallenge = {
    {"method", "pinChallenge.onRequestChallenge"},
    {"payload", {
          {"requestor", {
              {"id", "ReferenceApp"},
              {"name", "Firebolt Reference App"}
          }},
          {{ "pinSpace", "purchase"}},
          {{ "capability", "xrn:firebolt:capability:commerce::purchase"}},
    }}
};

const nlohmann::json ManageSDKTest::autoLowLatencyModeCapableChanged = {
    {"method", "HDMIInput.onAutoLowLatencyModeCapableChanged"},
    {"payload", {
        {"port", "HDMI1"},
        {"enabled", true}
     }}
};

#ifndef UNIT_TEST_SUITE
#ifdef GATEWAY_BIDIRECTIONAL
void ManageSDKTest::event_trigger(nlohmann::json event)
{
    std::cout << "Event triggered: " << event["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/bidirectionalEventPayload --header 'Content-Type: application/json' --data-raw '{ \"method\": " + event["method"].dump() + ", \"params\": " + event["payload"].dump() + "}'";
    std::cout << "trigger_cmd: " << std::endl << trigger_cmd << std::endl;
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}

void ManageSDKTest::provider_trigger(nlohmann::json provider)
{
    std::cout << "Provider triggered: " << provider["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/bidirectionalPayload --header 'Content-Type: application/json' --data-raw '{ \"method\": " + provider["method"].dump() + ", \"params\": " + provider["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << "trigger_cmd: " << trigger_cmd << std::endl;
    std::cout << std::endl;
}

#else
void ManageSDKTest::event_trigger(nlohmann::json event)
{
    std::cout << "Event triggered: " << event["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/event --header 'Content-Type: application/json' --data-raw '{ \"method\": " + event["method"].dump() + ", \"result\": " + event["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}

void ManageSDKTest::provider_trigger(nlohmann::json provider)
{
    std::cout << "Provider triggered: " << provider["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/event --header 'Content-Type: application/json' --data-raw '{ \"method\": " + provider["method"].dump() + ", \"params\": " + provider["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}
#endif
#else
void ManageSDKTest::event_trigger(nlohmann::json event)
{
    std::cout << "!! Provider trigger: not implemented when UNIT_TEST enabled, because Firebolt does not connect to Mock-Firebolt in that case" << std::endl;
}

void ManageSDKTest::provider_trigger(nlohmann::json provider)
{
    std::cout << "!! Provider trigger: not implemented when UNIT_TEST enabled, because Firebolt does not connect to Mock-Firebolt in that case" << std::endl;
}
#endif

void ManageSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    if (!_connected) {
        cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
        _connected = connected;
    }
}

void ManageSDKTest::CreateFireboltInstance(const std::string& url)
{
    const std::string config = "{\
            \"waitTime\": 100000,\
            \"logLevel\": \"Info\",\
            \"workerPool\":{\
            \"queueSize\": 8,\
            \"threadCount\": 3\
            },\
            \"wsUrl\": " + url + "}";

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
    usleep(5000);
    return _connected;
}

template<typename T>
using EnumMap = std::unordered_map<T, string>;
template <typename T>
inline const string& ConvertFromEnum(EnumMap<T> enumMap, T type)
{
    return enumMap[type];
}
template <typename T>
inline const T ConvertToEnum(EnumMap<T> enumMap, const string& str)
{
     T value;
     for (auto element: enumMap) {
          if (element.second == str) {
              value = element.first;
              break;
          }
     }
     return value;
}

EnumMap<Firebolt::Advertising::SkipRestriction> skipRestrictionMap = {
    { Firebolt::Advertising::SkipRestriction::NONE, "none" },
    { Firebolt::Advertising::SkipRestriction::ADS_UNWATCHED, "adsUnwatched" },
    { Firebolt::Advertising::SkipRestriction::ADS_ALL, "adsAll" },
    { Firebolt::Advertising::SkipRestriction::ALL, "all" }};

void ManageSDKTest::GetAdvertisingSkipRestriction()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Advertising::SkipRestriction skipRestriction = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().skipRestriction(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Advertising SkipRestriction is success : " << ConvertFromEnum<Firebolt::Advertising::SkipRestriction>(skipRestrictionMap, skipRestriction) << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAdvertisingSkipRestriction failed. " + errorMessage);
    }
}

void ManageSDKTest::SetAdvertisingSkipRestriction()
{
    Firebolt::Error error = Firebolt::Error::None;
    cout << "Support SkipRestriction -> " << endl;
    for (auto skipRestriction : skipRestrictionMap) {
         cout << skipRestriction.second << endl;
    }
    
    std::string skipRestriction = "none";

    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().setSkipRestriction(ConvertToEnum<Firebolt::Advertising::SkipRestriction>(skipRestrictionMap, skipRestriction), &error);
    if (error == Firebolt::Error::None) {
        cout << "Set Advertising SkipRestriction is success " << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetAdvertisingSkipRestriction failed. " + errorMessage);
    }
}

void ManageSDKTest::ResetAdvertisingIdentifier()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().resetIdentifier(&error);
    if (error == Firebolt::Error::None) {
        cout << "Set Advertising Reset Identifier is success " << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("ResetAdvertisingIdentifier failed. " + errorMessage);
    }
}

void ManageSDKTest::SetAccountSession()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string token = "Test";
    int32_t expiresIn = 60;
    Firebolt::IFireboltAccessor::Instance().AccountInterface().session(token, expiresIn, &error);
    if (error == Firebolt::Error::None) {
        cout << "Set Account Session is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetAccountSession failed. " + errorMessage);
    }
}

void ManageSDKTest::GetAudioDescriptionsEnabled()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool enabled = Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().enabled(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get AudioDescriptions Enabled: " << (enabled ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAudioDescriptionsEnabled failed. " + errorMessage);
    }
}

void ManageSDKTest::SetAudioDescriptionsEnabled()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool enabled = true;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().setEnabled(enabled, &error);
    if (error == Firebolt::Error::None) {
        cout << "Set AudioDescriptions Enabled: " << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetAudioDescriptionsEnabled failed. " + errorMessage);
    }
}

void ManageSDKTest::OnAudioDescriptionsEnabledChangedNotification::onEnabledChanged(const bool enabled)
{
    cout << "AudioDescriptions Enabled changed, new value --> " << (enabled ? "true" : "false") << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert(enabled == audioDescriptionsEnabledChanged["payload"]["enabled"]);
#endif
}

void ManageSDKTest::SubscribeAudioDescriptionsEnabledChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().subscribe(_audioDescriptionEnabledChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe AudioDescriptions EnabledChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeAudioDescriptionsEnabledChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeAudioDescriptionsEnabledChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AudioDescriptionsInterface().unsubscribe(_audioDescriptionEnabledChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe AudioDescriptions EnabledChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeAudioDescriptionsEnabledChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::GetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Name = " << name.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetDeviceName failed. " + errorMessage);
    }
}

void ManageSDKTest::SetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string name = "Kitchen"; 
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().setName(name, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Device Name to " << name << " is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetDeviceName failed. " + errorMessage);
    }
}

void ManageSDKTest::OnDeviceNameChangedNotification::onDeviceNameChanged(const std::string& name)
{
    cout << "Name changed, new name --> " << name << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert(name == deviceNameChanged["payload"]);
#endif
}

void ManageSDKTest::SubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device NameChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDeviceNameChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device NameChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDeviceNameChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::GetClosedCaptionsBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    const float value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().backgroundOpacity(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption BackgroundOpacity = " << value << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetClosedCaptionsBackgroundOpacity failed. " + errorMessage);
    }
}

void ManageSDKTest::SetClosedCaptionsBackgroundOpacity()
{
    Firebolt::Error error = Firebolt::Error::None;
    uint32_t bgOpacity = 1;

    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setBackgroundOpacity(bgOpacity, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption BackgroundOpacity to " << bgOpacity << " is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetClosedCaptionsBackgroundOpacity failed. " + errorMessage);
    }
}

void ManageSDKTest::OnBackgroundOpacityChangedNotification::onBackgroundOpacityChanged(const float& opacity)
{
    cout << "BackgroundOpacity changed, new value --> " << opacity << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert(opacity == backgroundOpacityChanged["payload"]);
#endif
}

void ManageSDKTest::SubscribeClosedCaptionsBackgroundOpacityChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(_backgroundOpacityChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeClosedCaptionsBackgroundOpacityChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeClosedCaptionsBackgroundOpacityChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(_backgroundOpacityChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe ClosedCaptions BackgroundOpacityChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeClosedCaptionsBackgroundOpacityChanged failed. " + errorMessage);
    }
}

EnumMap<Firebolt::Accessibility::FontFamily> fontFamilyMap = {
    { Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF, "MonospacedSerif" },
    { Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF, "ProportionalSerif" },
    { Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF, "MonospacedSanserif" },
    { Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF, "ProportionalSanserif" },
    { Firebolt::Accessibility::FontFamily::SMALLCAPS, "SmallCaps" },
    { Firebolt::Accessibility::FontFamily::CURSIVE, "Cursive" },
    { Firebolt::Accessibility::FontFamily::CASUAL, "Casual" }
};

void ManageSDKTest::GetClosedCaptionsFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Accessibility::FontFamily value = Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().fontFamily(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get ClosedCaption FontFamily value = " << ConvertFromEnum<Firebolt::Accessibility::FontFamily>(fontFamilyMap, value) << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetClosedCaptionsFontFamily failed. " + errorMessage);
    }
}

void ManageSDKTest::SetClosedCaptionsFontFamily()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Accessibility::FontFamily fontFamily = Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF;

    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().setFontFamily(fontFamily, &error);
    if (error == Firebolt::Error::None) {
        cout << "Set ClosedCaption FontFamily to MonospacedSerif is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetClosedCaptionsFontFamily failed. " + errorMessage);
    }
}

std::string fontFamilyToString(Firebolt::Accessibility::FontFamily fontFamily)
{
    std::string str = "";
    switch (fontFamily)
    {
    case Firebolt::Accessibility::FontFamily::MONOSPACED_SERIF:
        str = "monospaced_serif";
        break;
    case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SERIF:
        str = "proportional_serif";
        break;
    case Firebolt::Accessibility::FontFamily::MONOSPACED_SANSERIF:
        str = "monospaced_sanserif";
        break;
    case Firebolt::Accessibility::FontFamily::PROPORTIONAL_SANSERIF:
        str = "proportional_sanserif";
        break;
    case Firebolt::Accessibility::FontFamily::SMALLCAPS:
        str = "smallcaps";
        break;
    case Firebolt::Accessibility::FontFamily::CURSIVE:
        str = "cursive";
        break;
    case Firebolt::Accessibility::FontFamily::CASUAL:
        str = "casual";
        break;
    default:
        str = "unknown";
    }
    return str;
}

void ManageSDKTest::OnFontFamilyChangedNotification::onFontFamilyChanged(const Firebolt::Accessibility::FontFamily& family)
{
    cout << "FontFamily changed, new code --> " << fontFamilyToString(family) << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert(fontFamilyToString(family) == fontFamilyChanged["payload"]);
#endif
}

void ManageSDKTest::SubscribeClosedCaptionsFontFamilyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().subscribe(_fontFamilyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe ClosedCaptions FontFamilyChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeClosedCaptionsFontFamilyChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeClosedCaptionsFontFamilyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().ClosedCaptionsInterface().unsubscribe(_fontFamilyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe ClosedCaptions FontFamilyChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeClosedCaptionsFontFamilyChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::GetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::vector<std::string> languages = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Localization PreferredAudioLanguages : " << endl;
        for (auto language: languages) {
            cout << "----- > " << language << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetLocalizationPreferredAudioLanguages failed. " + errorMessage);
    }
}

void ManageSDKTest::SetLocalizationPreferredAudioLanguages()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::vector<std::string> newLanguages = { "eng" };

    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().setPreferredAudioLanguages(newLanguages, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Localization PreferredAudioLanguages to eng is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetLocalizationPreferredAudioLanguages failed. " + errorMessage);
    }
}

void ManageSDKTest::OnPreferredAudioLanguagesChangedNotification::onPreferredAudioLanguagesChanged(const std::vector<std::string>& languages)
{
    cout << "PreferredAudioLanguages Changed, new languages --> " << endl;
    for(size_t i = 0; i < languages.size(); i++)
    {
        cout << " -> " << languages[i] << endl;

#ifdef GATEWAY_BIDIRECTIONAL
        assert(languages[i] == preferredAudioLanguagesChanged["payload"][i]);
#endif
    }
}

void ManageSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeLocalizationPreferredAudioLanguagesChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeLocalizationPreferredAudioLanguagesChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::GetPrivacyAllowACRCollection()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allowACRCollection = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().allowACRCollection(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Privacy AllowACRCollection : " << (allowACRCollection ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetPrivacyAllowACRCollection failed. " + errorMessage);
    }
}

void ManageSDKTest::SetPrivacyAllowACRCollection()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allowACRCollection = false;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().setAllowACRCollection(allowACRCollection, &error);

    if (error == Firebolt::Error::None) {
        cout << "Set Privacy AllowACRCollection is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetPrivacyAllowACRCollection failed. " + errorMessage);
    }
}

void ManageSDKTest::OnAllowACRCollectionChangedNotification::onAllowACRCollectionChanged(const bool allowACRCollection)
{
    cout << "AllowACRCollection Changed, new value of allowACRCollection : " << (allowACRCollection ? "true" : "false") << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert(allowACRCollection == allowACRCollectionChanged["payload"]);
#endif
}

void ManageSDKTest::SubscribePrivacyAllowACRCollectionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().subscribe(_allowACRCollectionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Privacy AllowACRCollectionChanged is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribePrivacyAllowACRCollectionChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribePrivacyAllowACRCollectionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().PrivacyInterface().unsubscribe(_allowACRCollectionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Privacy AllowACRCollectionChanged is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribePrivacyAllowACRCollectionChanged failed. " + errorMessage);
    }
}

void ManageSDKTest::GetPrivacySettings()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Privacy::PrivacySettings privacySettings = Firebolt::IFireboltAccessor::Instance().PrivacyInterface().settings(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Privacy Settings -> " << endl;
        cout << "\tallowACRCollection : " << privacySettings.allowACRCollection << endl;
        cout << "\tallowResumePoints : " << privacySettings.allowResumePoints << endl;
        cout << "\tallowAppContentAdTargeting : " << privacySettings.allowAppContentAdTargeting << endl;
        cout << "\tallowCameraAnalytics : " << privacySettings.allowCameraAnalytics << endl;
        cout << "\tallowPersonalization : " << privacySettings.allowPersonalization << endl;
        cout << "\tallowPrimaryBrowseAdTargeting : " << privacySettings.allowPrimaryBrowseAdTargeting << endl;
        cout << "\tallowPrimaryContentAdTargeting : " << privacySettings.allowPrimaryContentAdTargeting << endl;
        cout << "\tallowProductAnalytics : " << privacySettings.allowProductAnalytics << endl;
        cout << "\tallowRemoteDiagnostics : " << privacySettings.allowRemoteDiagnostics << endl;
        cout << "\tallowUnentitledPersonalization : " << privacySettings.allowUnentitledPersonalization << endl;
        cout << "\tallowUnentitledResumePoints : " << privacySettings.allowUnentitledResumePoints << endl;
        cout << "\tallowWatchHistory : " << privacySettings.allowWatchHistory << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetPrivacySettings failed. " + errorMessage);
    }
}

void ManageSDKTest::OnSignInNotification::onSignIn(const Firebolt::Discovery::Event& event)
{
    cout << "Discovery SignIn Event for appId --> " << event.appId << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert( event.appId == signInEvent["payload"]["appId"]);	
#endif

}

void ManageSDKTest::SubscribeDiscoverySignInNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_signInNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery SignIn Notification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDiscoverySignInNotification failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeDiscoverySignInNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_signInNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery SignIn Notification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDiscoverySignInNotification failed. " + errorMessage);
    }
}

void ManageSDKTest::OnSignOutNotification::onSignOut(const Firebolt::Discovery::Event& event)
{
    cout << "Discovery SignOut Event for appId --> " << event.appId << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert( event.appId == signOutEvent["payload"]["appId"]);	
#endif
}

void ManageSDKTest::SubscribeDiscoverySignOutNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_signOutNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery SignOut Notification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDiscoverySignOutNotification failed. " + errorMessage);
    }
}

void ManageSDKTest::UnsubscribeDiscoverySignOutNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_signOutNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery SignOut Notification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDiscoverySignOutNotification failed. " + errorMessage);
    }
}

ManageSDKTest::KeyboardProvider::KeyboardProvider()
{
}

Firebolt::Keyboard::KeyboardResult ManageSDKTest::KeyboardProvider::standard(const Firebolt::Keyboard::KeyboardParameters& parameters)
{
    cout << "KeyboardProvider Standard is invoked" << endl;
    string key;
    cout << parameters.message << " : ";
#ifdef INTERACTIVE_APP
    getline(cin, key);
#else
    key = "response-standard";
#endif
    return Firebolt::Keyboard::KeyboardResult{key};
}

Firebolt::Keyboard::KeyboardResult ManageSDKTest::KeyboardProvider::password(const Firebolt::Keyboard::KeyboardParameters& parameters)
{
    cout << "KeyboardProvider Password is invoked" << endl;
    string key;
    cout << parameters.message << " : ";
#ifdef INTERACTIVE_APP
    getline(cin, key);
#else
    key = "response-password";
#endif
    return Firebolt::Keyboard::KeyboardResult{key};
}

Firebolt::Keyboard::KeyboardResult ManageSDKTest::KeyboardProvider::email(const Firebolt::Keyboard::KeyboardEmailParameters& parameters)
{
    cout << "KeyboardProvider Email is invoked" << endl;
    string key;
    cout << parameters.message << " : ";
#ifdef INTERACTIVE_APP
    getline(cin, key);
#else
    key = "response-email";
#endif
    return Firebolt::Keyboard::KeyboardResult{key};
}

void ManageSDKTest::RegisterKeyboardProvider()
{
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().provide(_keyboardProvider);
}

ManageSDKTest::AcknowledgeChallengeProvider::AcknowledgeChallengeProvider()
{
}

Firebolt::AcknowledgeChallenge::GrantResult ManageSDKTest::AcknowledgeChallengeProvider::challenge(const Firebolt::AcknowledgeChallenge::AcknowledgeChallengeParameters& parameters)
{
    cout << "AcknowledgeChallengeProvider challenge is invoked" << endl;
    return { true };
}

void ManageSDKTest::RegisterAcknowledgeChallengeProvider()
{
    Firebolt::IFireboltAccessor::Instance().AcknowledgeChallengeInterface().provide(_acknowledgeChallengeProvider);
}

void ManageSDKTest::SendResponseMessageToAcknowledgeChallengeProvider()
{
}

void ManageSDKTest::SendErrorMessageToAcknowledgeChallengeProvider()
{
}

ManageSDKTest::PinChallengeProvider::PinChallengeProvider()
{
}

Firebolt::PinChallenge::PinChallengeResult ManageSDKTest::PinChallengeProvider::challenge(const Firebolt::PinChallenge::PinChallengeParameters& parameters)
{
    cout << "PinChallengeProvider challenge is invoked" << endl;
    Firebolt::PinChallenge::PinChallengeResult r{true, Firebolt::PinChallenge::ResultReason::NO_PIN_REQUIRED};
    return r;
}

void ManageSDKTest::RegisterPinChallengeProvider()
{
    Firebolt::IFireboltAccessor::Instance().PinChallengeInterface().provide(_pinChallengeProvider);
}

void ManageSDKTest::SendResponseMessageToPinChallengeProvider()
{
}

void ManageSDKTest::SendErrorMessageToPinChallengeProvider()
{
}

void ManageSDKTest::GetLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Localization::Info info = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&error);
    if (error == Firebolt::Error::None) {
        cout << "AdditionalInfo is success, Info : " << endl;
        for (auto element : info) {
           cout << " " << element.first << " : " <<  element.second << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetLocalizationAdditionalInfo failed. " + errorMessage);
    }
}

void ManageSDKTest::AddLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string key = "testKey";
    std::string value = std::to_string(1.0f);

    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().addAdditionalInfo(key, value, &error);
    if (error == Firebolt::Error::None) {
        cout << "Add AdditionalInfo is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("AddLocalizationAdditionalInfo failed. " + errorMessage);
    }
}

void ManageSDKTest::RemoveLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string key = "testKey";

    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().removeAdditionalInfo(key, &error);
    if (error == Firebolt::Error::None) {
        cout << "Remove AdditionalInfo is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("RemoveLocalizationAdditionalInfo failed. " + errorMessage);
    }
}

void ManageSDKTest::GetUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string appId = "certApp";

    std::vector<Firebolt::UserGrants::GrantInfo> grantInfo = Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().app(appId, &error);
    if (error == Firebolt::Error::None) {
        cout << "Get UserGrants Permission is success" << endl;
        if (grantInfo.size() > 0) {
            cout << "Grant Permission list : " << endl;
            for (auto info : grantInfo) {
                cout << "GrantState : " << static_cast<int>(info.state) << endl;
                cout << "Capability : " << info.capability << endl;
                cout << "Role : " << static_cast<int>(info.role) << endl;
                cout << "Lifespan : " << static_cast<int>(info.lifespan) << endl;
            }
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetUserGrantsPermission failed. " + errorMessage);
    }
}

void ManageSDKTest::GrantUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::UserGrants::GrantModificationOptions grantModificationOptions;
    std::string appId = "certApp";
    grantModificationOptions.appId = std::make_optional<std::string>(appId);

    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().grant(Firebolt::Capabilities::Role::USE, "xrn:firebolt:capability:device:model", grantModificationOptions, &error);
    if (error == Firebolt::Error::None) {
        cout << "Grant UserGrants Permission is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GrantUserGrantsPermission failed. " + errorMessage);
    }
}

void ManageSDKTest::DenyUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::UserGrants::GrantModificationOptions grantModificationOptions;
    std::string appId = "certApp";
    grantModificationOptions.appId = std::make_optional<std::string>(appId);

    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().deny(Firebolt::Capabilities::Role::USE, "xrn:firebolt:capability:device:model", grantModificationOptions, &error);
    if (error == Firebolt::Error::None) {
        cout << "Deny UserGrants Permission is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DenyUserGrantsPermission failed. " + errorMessage);
    }
}

void ManageSDKTest::ClearUserGrantsPermission()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::UserGrants::GrantModificationOptions grantModificationOptions;
    std::string appId = "certApp";
    grantModificationOptions.appId = std::make_optional<std::string>(appId);

    Firebolt::IFireboltAccessor::Instance().UserGrantsInterface().clear(Firebolt::Capabilities::Role::USE, "xrn:firebolt:capability:device:model", grantModificationOptions, &error);
    if (error == Firebolt::Error::None) {
        cout << "Clear UserGrants Permission is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("ClearUserGrantsPermission failed. " + errorMessage);
    }
}

void PrintAP(const Firebolt::Wifi::AccessPoint ap)
{
    if (ap.ssid.has_value()) {
        cout << " SSID : " << ap.ssid.value() << endl;
    }
    if (ap.securityMode.has_value()) {
        cout << " SecurityMode : " << static_cast<int>(ap.securityMode.value()) << endl;
    }
    if (ap.signalStrength.has_value()) {
        cout << " SignalStrength : " << ap.signalStrength.value() << endl;
    }
    if (ap.frequency.has_value()) {
        cout << " Frequency : " << ap.frequency.value() << endl;
    }
}

void PrintAPList(const Firebolt::Wifi::AccessPointList& apList)
{
    if (apList.list.has_value()) {
        cout<< "list ---->" << endl;
        uint32_t index = 0;
        for (const auto ap : apList.list.value()) {
            cout << index << ". " << endl;
            PrintAP(ap);
            cout << endl;
            index++;
        }
    } else {
        cout << "empty list " << endl;
    }
}

void ManageSDKTest::WifiScan()
{
    Firebolt::Error error = Firebolt::Error::None;
    int32_t timeout = 1;
    _apList = Firebolt::IFireboltAccessor::Instance().WifiInterface().scan(timeout, &error);
    if (error == Firebolt::Error::None) {
        cout << "Wifi Scan is success, ";
	PrintAPList(_apList);
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("WifiScan failed. " + errorMessage);
    }
}

void ManageSDKTest::WifiConnect()
{
    Firebolt::Error error = Firebolt::Error::None;
    if (_apList.list.has_value()) {
        cout << "Scanned access pointlist : " << endl;
        PrintAPList(_apList);
        cout << "Select access point from the list: enter index : ";
        int32_t index;
        cin >> index;
        Firebolt::Wifi::AccessPoint ap = _apList.list.value()[index];
        std::string passphrase;
        cout << "Enter passphrase to connect ";
        cin >> passphrase;

        string ssid = ap.ssid.has_value() ? ap.ssid.value() : "";
        printf("%s:%s:%d _apList.list.value()[index] = %s\n", __FILE__, __func__, __LINE__, ssid.c_str());
        Firebolt::Wifi::WifiSecurityMode securityMode = ap.securityMode.has_value() ? ap.securityMode.value() : Firebolt::Wifi::WifiSecurityMode::NONE;
        Firebolt::Wifi::AccessPoint connectedAP = Firebolt::IFireboltAccessor::Instance().WifiInterface().connect(ssid, passphrase, securityMode , &error);
        if (error == Firebolt::Error::None) {
            cout << "Wifi Connect is success, ";
            PrintAP(connectedAP);
        } else {
            std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
            throw std::runtime_error("WifiConnect failed. " + errorMessage);
        }
    } else {
        cout << "Empty AP list, please initiate scan before trying connect " << endl;
    }
}

void ManageSDKTest::WifiDisconnect()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().WifiInterface().disconnect(&error);
    if (error == Firebolt::Error::None) {
        cout << "Wifi Disconnect is success, ";
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("WifiDisconnect failed. " + errorMessage);
    }
}

void ManageSDKTest::OnAutoLowLatencyModeCapableChangedNotification::onAutoLowLatencyModeCapableChanged( const Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo& info)
{
    cout << "Low latency capable changed: " << info.port << ", " << info.enabled << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    assert( info.port == autoLowLatencyModeCapableChanged["payload"]["port"]);
    assert( info.enabled == autoLowLatencyModeCapableChanged["payload"]["enabled"]);
#endif

}

void ManageSDKTest::GlobalSubscribeHdmiAutoLowLatencyModeCapableChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().globalSubscribe(_autoLowLatencyModeCapableChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Global Subscribe for HDMIInput AutoLowLatencyModeCapable is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeHDMIInputAutoLowLatencyModeCapable failed." + errorMessage);
    }
}

void ManageSDKTest::GlobalUnsubscribeHdmiAutoLowLatencyModeCapableChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().globalUnsubscribe(_autoLowLatencyModeCapableChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Global Unsubscribe for HDMIInput AutoLowLatencyModeCapable is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeHDMIInputAutoLowLatencyModeCapable failed." + errorMessage);
    }
}

void ManageSDKTest::GetAutoLowLatencyModeCapable()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string port = "HDMI1";
    bool result = Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().autoLowLatencyModeCapable(port, &error);

    if (error == Firebolt::Error::None) {
        cout << "GetAutoLowLatencyModeCapable is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAutoLowLatencyModeCapable failed. " + errorMessage);
    }
}

void ManageSDKTest::SetAutoLowLatencyModeCapable()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string port = "HDMI1";
    bool value = false;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setAutoLowLatencyModeCapable(port, value, &error);

    if (error == Firebolt::Error::None) {
        cout << "SetAutoLowLatencyModeCapable is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetAutoLowLatencyModeCapable failed. " + errorMessage);
    }
}

void ManageSDKTest::GetEdidVersion()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string port = "HDMI1";
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().edidVersion(port, &error);

    if (error == Firebolt::Error::None) {
        cout << "GetEdidVersion is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetEdidVersion failed. " + errorMessage);
    }
}

void ManageSDKTest::SetEdidVersion()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string port = "HDMI1";
    Firebolt::HDMIInput::EDIDVersion value = Firebolt::HDMIInput::EDIDVersion::V1_4;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().setEdidVersion(port, value, &error);

    if (error == Firebolt::Error::None) {
        cout << "SetEdidVersion is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SetEdidVersionfailed. " + errorMessage);
    }
}

void ManageSDKTest::GetHdmiPortInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string portId = "HDMI1";
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().port(portId, &error);

    if (error == Firebolt::Error::None) {
        cout << "GetHdmiPortInfo is a success." << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetHdmiPortInfo failed. " + errorMessage);
    }
}
