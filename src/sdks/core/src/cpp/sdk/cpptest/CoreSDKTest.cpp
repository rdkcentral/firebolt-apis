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
#include <iomanip>
#include <stdexcept>
#include <string>
#include "CoreSDKTest.h"
#include <cassert>

using namespace std;
using Resolution = std::pair<int32_t, int32_t>;

bool CoreSDKTest::_connected;
CoreSDKTest::OnPolicyChangedNotification CoreSDKTest::_policyChangedNotification;
CoreSDKTest::OnDeviceNameChangedNotification CoreSDKTest::_deviceNameChangedNotification;
CoreSDKTest::OnAudioChangedNotification CoreSDKTest::_audioChangedNotification;
CoreSDKTest::OnScreenResolutionChangedNotification CoreSDKTest::_screenResolutionChangedNotification;
CoreSDKTest::OnClosedCaptionsSettingsChangedNotification CoreSDKTest::_closedCaptionsSettingsChangedNotification;
CoreSDKTest::OnPreferredAudioLanguagesChangedNotification CoreSDKTest::_preferredAudioLanguagesChangedNotification;
CoreSDKTest::OnBackgroundNotification CoreSDKTest::_backgroundNotification;
CoreSDKTest::OnForegroundNotification CoreSDKTest::_foregroundNotification;
CoreSDKTest::OnFriendlyNameChangedNotification CoreSDKTest::_friendlyNameChangedNotification;
CoreSDKTest::OnAvailableNotification CoreSDKTest::_availableNotification;

CoreSDKTest::OnNavigateToHomeIntentNotification CoreSDKTest::_navigateToHomeIntentNotification;
CoreSDKTest::OnNavigateToEntityIntentNotification CoreSDKTest::_navigateToEntityIntentNotification;
CoreSDKTest::OnNavigateToTuneIntentNotification CoreSDKTest::_navigateToTuneIntentNotification;

CoreSDKTest::KeyboardEmailAsyncResponse CoreSDKTest::_keyboardEmailAsyncResponse;
CoreSDKTest::KeyboardPasswordAsyncResponse CoreSDKTest::_keyboardPasswordAsyncResponse;
CoreSDKTest::KeyboardStandardAsyncResponse CoreSDKTest::_keyboardStandardAsyncResponse;


const nlohmann::json CoreSDKTest::adPolicy = {
    {"method", "advertising.onPolicyChanged"},
    {"payload", {
        {"skipRestriction", "none"},
        {"limitAdTracking", true}
    }}
};

const nlohmann::json CoreSDKTest::deviceName = {
    {"method", "device.onDeviceNameChanged"},
    {"payload", "Living Room"}
};

const nlohmann::json CoreSDKTest::audioChanged = {
    {"method", "device.onAudioChanged"},
    {"payload", {
        {"stereo", true},
        {"dolbyDigital5.1", true},
        {"dolbyDigital5.1+", true},
        {"dolbyAtmos", true}
    }}
};

const nlohmann::json CoreSDKTest::deviceScreenResolutionChanged = {
    {"method", "device.onScreenResolutionChanged"},
    {"payload", "[1920, 1080]"}
};

const nlohmann::json CoreSDKTest::preferredAudioLanguagesChanged = {
    {"method", "localization.onPreferredAudioLanguagesChanged"},
    {"payload", {"eng", "spa"}}
};

const nlohmann::json CoreSDKTest::closedCaptionsSettingsChanged = {
    {"method", "accessibility.onClosedCaptionsSettingsChanged"},
    {"payload", {
        {"enabled", true},
		{"styles", {
            {"fontFamily", "monospaced_sanserif"},
			{"fontSize", 1},
			{"fontColor", "#ffffff"},
			{"fontEdge", "none"},
			{"fontEdgeColor", "#7F7F7F"},
            {"fontOpacity", 100},
            {"backgroundColor", "#000000"},
            {"backgroundOpacity", 100},
            {"textAlign", "center"},
            {"textAlignVertical", "middle"},
            {"windowColor", "white"},
            {"windowOpacity", 50}
        }},
        {"preferredLanguages", {"eng", "spa"}}
    }}
};

const nlohmann::json CoreSDKTest::backgroundNotification = {
    {"method", "lifecycle.onBackground"},
    {"payload", {
        {"state", "background"},
		{"previous", "foreground"}
    }}
};

const nlohmann::json CoreSDKTest::foregroundNotification = {
    {"method", "lifecycle.onForeground"},
    {"payload", {
        {"state", "foreground"},
		{"previous", "inactive"},
        {"source", "remote"}
    }}
};

const nlohmann::json CoreSDKTest::friendlyNameChanged = {
    {"method", "secondscreen.onFriendlyNameChanged"},
    {"payload", {
        {"name", "friendlyName"},
		{"value", "Living Room"}
    }}
};

const nlohmann::json CoreSDKTest::navigateTo = {
    {"method", "discovery.onNavigateTo"},
    {"payload", {
        {"action", "search"},
		{"data", {
            {"query", "a cool show"}
        }},
        {"context",{
            {"campaign", "unknown"},
			{"source", "voice"}
        }}
    }}
};

const nlohmann::json CoreSDKTest::keyboardStandard = {
    {"method", "Keyboard.standard"},
    {"payload", {
        {"name", "Default Result"},
		{"value", "Living Room"}
    }}
};

const nlohmann::json CoreSDKTest::keyboardEmail = {
    {"method", "Keyboard.email"},
    {"payload", {
        {"name", "Default Result"},
		{"value", "user@domain.com"}
    }}
};

const nlohmann::json CoreSDKTest::keyboardPassword = {
    {"method", "Keyboard.password"},
    {"payload", {
        {"name", "Default Result"},
		{"value", "abc123"}
    }}
};

#ifndef UNIT_TEST_APP
#ifdef GATEWAY_BIDIRECTIONAL
void CoreSDKTest::event_trigger(nlohmann::json event)
{
    std::cout << "Event triggered: " << event["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/bidirectionalEventPayload --header 'Content-Type: application/json' --data-raw '{ \"method\": " + event["method"].dump() + ", \"params\": " + event["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}

void CoreSDKTest::provider_trigger(nlohmann::json provider)
{
    std::cout << "Provider triggered: " << provider["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/bidirectionalPayload --header 'Content-Type: application/json' --data-raw '{ \"method\": " + provider["method"].dump() + ", \"params\": " + provider["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}

#else
void CoreSDKTest::event_trigger(nlohmann::json event)
{
    std::cout << "Event triggered: " << event["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/event --header 'Content-Type: application/json' --data-raw '{ \"method\": " + event["method"].dump() + ", \"result\": " + event["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}

void CoreSDKTest::provider_trigger(nlohmann::json provider)
{
    std::cout << "Provider triggered: " << provider["method"].dump() << std::endl;
    std::string trigger_cmd = "curl --location --request POST http://localhost:3333/api/v1/event --header 'Content-Type: application/json' --data-raw '{ \"method\": " + provider["method"].dump() + ", \"params\": " + provider["payload"].dump() + "}'";
    system(trigger_cmd.c_str());
    std::cout << std::endl;
}
#endif
#else
void CoreSDKTest::event_trigger(nlohmann::json event)
{
    std::cerr << "event_trigger not implemented when UNIT_TESTS enabled, as it requires running instance of mock-firebolt" << std::endl;
}
void CoreSDKTest::provider_trigger(nlohmann::json provider)
{
    std::cerr << "provider_trigger not implemented when UNIT_TESTS enabled, as it requires running instance of mock-firebolt" << std::endl;
}
#endif

void CoreSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
#ifndef INTERACTIVE_APP
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
#else
    if (!_connected) {
        cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
        _connected = connected;
    }
#endif
}

void CoreSDKTest::CreateFireboltInstance(const std::string& url)
{
    const std::string config = "{\
            \"waitTime\": 1000,\
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

void CoreSDKTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
    Firebolt::IFireboltAccessor::Instance().Deinitialize();
    Firebolt::IFireboltAccessor::Instance().Dispose();
}

bool CoreSDKTest::WaitOnConnectionReady()
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

void CoreSDKTest::GetAccountId()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string id = Firebolt::IFireboltAccessor::Instance().AccountInterface().id(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Account Id = " << id.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAccountId failed. " + errorMessage);
    }
}

void CoreSDKTest::GetAccountUid()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string uid = Firebolt::IFireboltAccessor::Instance().AccountInterface().uid(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Account Uid = " << uid.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAccountUid failed. " + errorMessage);
    }
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
    { Firebolt::Advertising::SkipRestriction::ALL, "all" }
};

void PrintAdvertisingPolicy(const Firebolt::Advertising::AdPolicy& policy)
{
    if (policy.skipRestriction.has_value()) {
        cout << "\tskipRestriction : " << ConvertFromEnum<Firebolt::Advertising::SkipRestriction>(skipRestrictionMap, policy.skipRestriction.value()) << endl;
    }
    if (policy.limitAdTracking.has_value()) {
        cout << "\tlimitAdTracking : " << policy.limitAdTracking.value() << endl;
    }
}

void CoreSDKTest::GetAdvertisingPolicy()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Advertising::AdPolicy policy = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().policy(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Advertising policy --> " << endl;
        PrintAdvertisingPolicy(policy);
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAdvertisingPolicy failed. " + errorMessage);
    }
}

void CoreSDKTest::OnPolicyChangedNotification::onPolicyChanged(const Firebolt::Advertising::AdPolicy& policy)
{
    cout << "New policy --> " << endl;
    PrintAdvertisingPolicy(policy);

#ifdef GATEWAY_BIDIRECTIONAL
    assert(ConvertFromEnum<Firebolt::Advertising::SkipRestriction>(skipRestrictionMap, policy.skipRestriction.value()) == adPolicy["payload"]["skipRestriction"]);
    assert(policy.limitAdTracking.value() == adPolicy["payload"]["limitAdTracking"]);
#endif
}

void CoreSDKTest::SubscribeAdvertisingPolicyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().subscribe(_policyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Advertising PolicyChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeAdvertisingPolicyChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeAdvertisingPolicyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().unsubscribe(_policyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Advertising PolicyChange is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeAdvertisingPolicyChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::BuildAdvertisingConfiguration()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Advertising::AdConfigurationOptions options;
    options.coppa = true;
    options.environment = Firebolt::Advertising::AdConfigurationOptionsEnvironment::TEST;
    options.authenticationEntity = "MVPD";

    Firebolt::Advertising::AdFrameworkConfig adFrameworkConfig = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().config(options, &error);
    if (error == Firebolt::Error::None) {
        cout << "Build AdvertisingConfiguration is success, adFrameworkConfig : " << adFrameworkConfig << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("BuildAdvertisingConfiguration failed. " + errorMessage);
    }
}

void CoreSDKTest::GetAdvertisingDeviceAttributes()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Advertising::DeviceAttributes deviceAttributes = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().deviceAttributes(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Advertising DeviceAttributes is success, deviceAttributes : " << deviceAttributes << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAdvertisingDeviceAttributes failed. " + errorMessage);
    }
}

void CoreSDKTest::GetDeviceName()
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

void CoreSDKTest::GetDeviceVersion()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string version = Firebolt::IFireboltAccessor::Instance().DeviceInterface().version(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Version = " << version.c_str() << endl;
    } else {
        cout << "Get Device Version status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::OnDeviceNameChangedNotification::onDeviceNameChanged(const std::string& name)
{
    cout << "Name changed, new name --> " << name << endl;

#ifndef INTERACTIVE_APP
#ifdef GATEWAY_BIDIRECTIONAL
    assert(name == deviceName["payload"]);
#endif
#endif
}

void CoreSDKTest::SubscribeDeviceNameChanged()
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

void CoreSDKTest::UnsubscribeDeviceNameChanged()
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

void CoreSDKTest::GetDeviceModel()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string model = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Model = " << model.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetDeviceModel failed. " + errorMessage);
    }
}

void CoreSDKTest::GetDeviceSku()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string sku = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Sku = " << sku.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetDeviceSku failed. " + errorMessage);
    }
}

void PrintDeviceAudioProfiles(const Firebolt::Device::AudioProfiles& audioProfiles)
{
   cout << "Get Device AudioProfiles :-> " << endl;
    
   cout << "Profile: Stereo, Status: " << audioProfiles.stereo << endl;
   cout << "Profile: Dolby Digital 5.1, Status: " << audioProfiles.dolbyDigital5_1 << endl;
   cout << "Profile: Dolby Digital 5.1 Plus, Status: " << audioProfiles.dolbyDigital5_1_plus << endl;
   cout << "Profile: Dolby Atmos, Status: " << audioProfiles.dolbyAtmos << endl;
}

void CoreSDKTest::GetDeviceAudio()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Device::AudioProfiles audioProfiles = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio(&error);
    if (error == Firebolt::Error::None) {
        PrintDeviceAudioProfiles(audioProfiles);
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetDeviceAudio failed. " + errorMessage);
    }
}

void CoreSDKTest::OnAudioChangedNotification::onAudioChanged(const Firebolt::Device::AudioProfiles& audioProfiles)
{
    cout << "onAudioChanged event " << endl;
    PrintDeviceAudioProfiles(audioProfiles);

#ifdef GATEWAY_BIDIRECTIONAL
    assert(audioProfiles.stereo == audioChanged["payload"]["stereo"]);
    assert(audioProfiles.dolbyDigital5_1 == audioChanged["payload"]["dolbyDigital5.1"]);
    assert(audioProfiles.dolbyDigital5_1_plus == audioChanged["payload"]["dolbyDigital5.1+"]);
    assert(audioProfiles.dolbyAtmos == audioChanged["payload"]["dolbyAtmos"]);
#endif
}

void CoreSDKTest::SubscribeDeviceAudioChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_audioChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device Audio Change is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDeviceAudioChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeDeviceAudioChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_audioChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device Audio Change is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDeviceAudioChanged failed. " + errorMessage);
    }
}

void PrintDeviceScreenResolution(const Resolution screenResolution)
{
    cout << "Get Device ScreenResolution :-> " << screenResolution.first << "x" << screenResolution.second << endl;
}

void CoreSDKTest::GetDeviceScreenResolution()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Resolution screenResolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution(&error);
    if (error == Firebolt::Error::None) {
        PrintDeviceScreenResolution(screenResolution);
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetDeviceScreenResolution failed. " + errorMessage);
    }
}

void CoreSDKTest::OnScreenResolutionChangedNotification::onScreenResolutionChanged(const Resolution& screenResolution)
{
    cout << "onScreenResolutionChanged event " << endl;
    PrintDeviceScreenResolution(screenResolution);

#ifdef GATEWAY_BIDIRECTIONAL
    assert(screenResolution == deviceScreenResolutionChanged["payload"]);
#endif
}

void CoreSDKTest::SubscribeDeviceScreenResolutionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_screenResolutionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device ScreenResolution Change is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDeviceScreenResolutionChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeDeviceScreenResolutionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_screenResolutionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device ScreenResolution Change is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDeviceScreenResolutionChanged failed. " + errorMessage);
    }
}

void PrintClosedCaptionsSettings(const Firebolt::Accessibility::ClosedCaptionsSettings& closedCaptionsSettings)
{
    cout << "Get Accessibility ClosedCaptionsSettings :-> " << endl;
    cout << "ClosedCaptionsSettings::Enabled : " << closedCaptionsSettings.enabled << endl;
    
    if (closedCaptionsSettings.styles.has_value()) {
        const auto& styles = closedCaptionsSettings.styles.value();

        if (styles.fontFamily.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::FontFamily : " << static_cast<int>(styles.fontFamily.value()) << endl;
        }
    
        if (styles.fontSize.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::FontSize : " << setprecision(3) << styles.fontSize.value() << endl;
        }
        
        if (styles.fontColor.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::FontColor : " << styles.fontColor.value() << endl;
        }
        
        if (styles.fontEdge.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::FontEdge : " << static_cast<int>(styles.fontEdge.value()) << endl;
        }
        
        if (styles.fontEdgeColor.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::FontEdgeColor : " << styles.fontEdgeColor.value() << endl;
        }
        
        if (styles.fontOpacity.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::FontOpacity : " << styles.fontOpacity.value() << endl;
        }
        
        if (styles.backgroundColor.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::BackgroundColor : " << styles.backgroundColor.value() << endl;
        }
        
        if (styles.backgroundOpacity.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::BackgroundOpacity : " << styles.backgroundOpacity.value() << endl;
        }
        
        if (styles.textAlign.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::TextAlign : " << styles.textAlign.value() << endl;
        }
        
        if (styles.textAlignVertical.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::TextAlignVertical : " << styles.textAlignVertical.value() << endl;
        }
        
        if (styles.windowColor.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::WindowColor : " << styles.windowColor.value() << endl;
        }
        
        if (styles.windowOpacity.has_value()) {
            cout << "ClosedCaptionsSettings::Styles::WindowOpacity : " << styles.windowOpacity.value() << endl;
        }
    }
    
    
    if (closedCaptionsSettings.preferredLanguages.has_value()) {
        cout << "ClosedCaptionsSettings::PreferredLanguages :";
        for (auto index: closedCaptionsSettings.preferredLanguages.value()) {
            cout << " " << index;
        }
        cout << endl;
    }
}

void CoreSDKTest::GetAccessibilityClosedCaptionsSettings()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Accessibility::ClosedCaptionsSettings closedCaptionsSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings(&error);
    if (error == Firebolt::Error::None) {
        PrintClosedCaptionsSettings(closedCaptionsSettings);
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAccessibilityClosedCaptionsSettings failed. " + errorMessage);
    }
}

#ifdef GATEWAY_BIDIRECTIONAL
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

std::string fontEdgeToString(Firebolt::Accessibility::FontEdge fontEdge)
{
    std::string str = "";
    switch (fontEdge)
    {
    case Firebolt::Accessibility::FontEdge::NONE:
        str = "none";
        break;
    case Firebolt::Accessibility::FontEdge::RAISED:
        str = "raised";
        break;
    case Firebolt::Accessibility::FontEdge::DEPRESSED:
        str = "depressed";
        break;
    case Firebolt::Accessibility::FontEdge::UNIFORM:
        str = "uniform";
        break;
    case Firebolt::Accessibility::FontEdge::DROP_SHADOW_LEFT:
        str = "drop_shadow_left";
        break;
    case Firebolt::Accessibility::FontEdge::DROP_SHADOW_RIGHT:
        str = "drop_shadow_right";
        break;
    default:
        str = "unknown";
    }
    return str;
}

#endif

void CoreSDKTest::OnClosedCaptionsSettingsChangedNotification::onClosedCaptionsSettingsChanged(const Firebolt::Accessibility::ClosedCaptionsSettings& closedCaptionsSettings)
{
    cout << "ClosedCaptionsSettingsChanged event " << endl;
    PrintClosedCaptionsSettings(closedCaptionsSettings);

#ifdef GATEWAY_BIDIRECTIONAL
    assert(closedCaptionsSettings.enabled == closedCaptionsSettingsChanged["payload"]["enabled"]);
    assert(fontFamilyToString(closedCaptionsSettings.styles.value().fontFamily.value()) == closedCaptionsSettingsChanged["payload"]["styles"]["fontFamily"]);
    assert(closedCaptionsSettings.styles.value().fontSize.value() == closedCaptionsSettingsChanged["payload"]["styles"]["fontSize"]);
    assert(closedCaptionsSettings.styles.value().fontColor.value() == closedCaptionsSettingsChanged["payload"]["styles"]["fontColor"]);
    assert(fontEdgeToString(closedCaptionsSettings.styles.value().fontEdge.value()) == closedCaptionsSettingsChanged["payload"]["styles"]["fontEdge"]);
    assert(closedCaptionsSettings.styles.value().fontEdgeColor.value() == closedCaptionsSettingsChanged["payload"]["styles"]["fontEdgeColor"]);
    assert(closedCaptionsSettings.styles.value().fontOpacity.value() == closedCaptionsSettingsChanged["payload"]["styles"]["fontOpacity"]);
    assert(closedCaptionsSettings.styles.value().backgroundColor.value() == closedCaptionsSettingsChanged["payload"]["styles"]["backgroundColor"]);
    assert(closedCaptionsSettings.styles.value().backgroundOpacity.value() == closedCaptionsSettingsChanged["payload"]["styles"]["backgroundOpacity"]);
    assert(closedCaptionsSettings.styles.value().textAlign.value() == closedCaptionsSettingsChanged["payload"]["styles"]["textAlign"]);
    assert(closedCaptionsSettings.styles.value().textAlignVertical.value() == closedCaptionsSettingsChanged["payload"]["styles"]["textAlignVertical"]);
    assert(closedCaptionsSettings.styles.value().windowColor.value() == closedCaptionsSettingsChanged["payload"]["styles"]["windowColor"]);
    assert(closedCaptionsSettings.styles.value().windowOpacity.value() == closedCaptionsSettingsChanged["payload"]["styles"]["windowOpacity"]);
#endif
}

void CoreSDKTest::SubscribeAccessibilityClosedCaptionsSettingsChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribe(_closedCaptionsSettingsChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Accessibilty ClosedCaptionSettings Change is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeAccessibilityClosedCaptionsSettingsChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeAccessibilityClosedCaptionsSettingsChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(_closedCaptionsSettingsChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Accessibilty ClosedCaptionSettings Change is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeAccessibilityClosedCaptionsSettingsChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::GetLocalizationAdditionalInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Localization::Info info = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().additionalInfo(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Localization AdditionalInfo : " << endl;
        for (auto element: info) {
            cout << "key : " << element.first << ", value : " << element.second << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetLocalizationAdditionalInfo failed. " + errorMessage);
    }
}

void CoreSDKTest::GetLocalizationLatlon()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Localization::LatLon latlon = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().latlon(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Localization LatLon pair value : " << endl;
        cout << "key : " << latlon.first << ", value : " << latlon.second << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetLocalizationLatlon failed. " + errorMessage);
    }
}

void CoreSDKTest::GetLocalizationPreferredAudioLanguages()
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

void CoreSDKTest::OnPreferredAudioLanguagesChangedNotification::onPreferredAudioLanguagesChanged(const std::vector<std::string>& languages)
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

void CoreSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged()
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

void CoreSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged()
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

void CoreSDKTest::KeyboardStandardAsyncResponse::response(const std::string& response, Firebolt::Error* error)
{
    if (error && (*error != Firebolt::Error::None)) {
        cout << "Error with keyboard standard response, error = " << static_cast<int>(*error) << endl;
    } else {
        cout << "Keyboard standard response: " << response << endl;
    }

#ifdef GATEWAY_BIDIRECTIONAL
        nlohmann::json json_response = nlohmann::json::parse(response);
        assert(json_response["name"] == keyboardStandard["payload"]["name"]);
        assert(json_response["value"] == keyboardStandard["payload"]["value"]);
#endif
}

void CoreSDKTest::InvokeKeyboardStandard()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string message = "Enter the name you'd like to associate with this device";
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().requestStandard(message, _keyboardStandardAsyncResponse, &error);
    if (error != Firebolt::Error::None) {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("InvokeKeyboardStandard failed. " + errorMessage);
    }
}

void CoreSDKTest::AbortKeyboardStandard()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().abortStandard(_keyboardStandardAsyncResponse, &error);
    if (error != Firebolt::Error::None) {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("AbortKeyboardStandard failed. " + errorMessage);
    }
}

void CoreSDKTest::KeyboardPasswordAsyncResponse::response(const std::string& response, Firebolt::Error* error)
{
    if (error && (*error != Firebolt::Error::None)) {
        cout << "Error with keyboard password response, error = " << static_cast<int>(*error) << endl;
    } else {
        cout << "Keyboard password response: " << response << endl;
    }

#ifdef GATEWAY_BIDIRECTIONAL
        nlohmann::json json_response = nlohmann::json::parse(response);
        assert(json_response["name"] == keyboardPassword["payload"]["name"]);
        assert(json_response["value"] == keyboardPassword["payload"]["value"]);
#endif
}

void CoreSDKTest::InvokeKeyboardPassword()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string message = "Enter the password to associate with this device";
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().requestPassword(message, _keyboardPasswordAsyncResponse, &error);
    if (error != Firebolt::Error::None) {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("InvokeKeyboardPassword failed. " + errorMessage);
    }
}

void CoreSDKTest::AbortKeyboardPassword()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().abortPassword(_keyboardPasswordAsyncResponse, &error);
    if (error != Firebolt::Error::None) {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("AbortKeyboardPassword failed. " + errorMessage);
    }
}

void CoreSDKTest::KeyboardEmailAsyncResponse::response(const std::string& response, Firebolt::Error* error)
{
    if (error && (*error != Firebolt::Error::None)) {
        cout << "Error with email password response, error = " << static_cast<int>(*error) << endl;
    } else {
        cout << "Keyboard email response: " << response << endl;

#ifdef GATEWAY_BIDIRECTIONAL
        nlohmann::json json_response = nlohmann::json::parse(response);
        assert(json_response["name"] == keyboardEmail["payload"]["name"]);
        assert(json_response["value"] == keyboardEmail["payload"]["value"]);
#endif
    }
}

void CoreSDKTest::InvokeKeyboardEmail()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Keyboard::EmailUsage type = Firebolt::Keyboard::EmailUsage::SIGN_IN;
    std::string message = "Enter your email to sign into this app/device";
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().requestEmail(type, message, _keyboardEmailAsyncResponse, &error);
    if (error != Firebolt::Error::None) {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("InvokeKeyboardEmail failed. " + errorMessage);
    }
}

void CoreSDKTest::AbortKeyboardEmail()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().KeyboardInterface().abortEmail(_keyboardEmailAsyncResponse, &error);
    if (error != Firebolt::Error::None) {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("AbortKeyboardEmail failed. " + errorMessage);
    }
}

void CoreSDKTest::VerifyProfileApproveContentRating()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allow = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approveContentRating(&error);
    if (error == Firebolt::Error::None) {
        cout << "Verify Profile ApproveContentRating is success value : " << allow << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("VerifyProfileApproveContentRating failed. " + errorMessage);
    }
}

void CoreSDKTest::VerifyProfileApprovePurchase()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allow = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approvePurchase(&error);
    if (error == Firebolt::Error::None) {
        cout << "Verify Profile ApprovePurchase is success value : " << allow << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("VerifyProfileApprovePurchase failed. " + errorMessage);
    }
}

void CoreSDKTest::GetProfileFlags()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Types::FlatMap flatMap = Firebolt::IFireboltAccessor::Instance().ProfileInterface().flags(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Profile flags is success value : " << endl;
        for (const auto& item : flatMap) {
            cout << "\t" << item.first << " : " << item.second << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetProfileFlags failed. " + errorMessage);
    }
}

void CoreSDKTest::LifecycleClose()
{
    Firebolt::Error error = Firebolt::Error::None;
    cout << "Enter close reason remote button(0), user exit(1), done(2) or error(3)" << endl;
    int32_t reason;
    cin >> reason;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(static_cast<Firebolt::Lifecycle::CloseReason>(reason), &error);
    if (error == Firebolt::Error::None) {
        cout << "Lifecycle close is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("LifecycleClose failed. " + errorMessage);
    }
}

EnumMap<Firebolt::Lifecycle::LifecycleState> lifecycleStateMap = {
    { Firebolt::Lifecycle::LifecycleState::INITIALIZING, "initializing" },
    { Firebolt::Lifecycle::LifecycleState::INACTIVE, "inactive" },
    { Firebolt::Lifecycle::LifecycleState::FOREGROUND, "foreground" },
    { Firebolt::Lifecycle::LifecycleState::BACKGROUND, "background" },
    { Firebolt::Lifecycle::LifecycleState::UNLOADING, "unloading" },
    { Firebolt::Lifecycle::LifecycleState::SUSPENDED, "suspended" }
};

EnumMap<Firebolt::Lifecycle::LifecycleEventSource> lifecycleEventSourceMap = {
    { Firebolt::Lifecycle::LifecycleEventSource::VOICE, "voice" },
    { Firebolt::Lifecycle::LifecycleEventSource::REMOTE, "remote" }
};

void CoreSDKTest::LifecycleReady()
{
   Firebolt::Error error = Firebolt::Error::None;
   Firebolt::IFireboltAccessor::Instance().LifecycleInterface().ready(&error);
    if (error == Firebolt::Error::None) {
        cout << "Lifecycle ready is success" << endl;
    } else {
        cout << "Lifecycle ready status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::LifecycleFinished()
{
   Firebolt::Error error = Firebolt::Error::None;
   Firebolt::IFireboltAccessor::Instance().LifecycleInterface().finished(&error);
    if (error == Firebolt::Error::None) {
        cout << "Lifecycle finished is success" << endl;
    } else {
        cout << "Lifecycle finished status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::LifecycleState()
{
   Firebolt::Error error = Firebolt::Error::None;
   const std::string state = Firebolt::IFireboltAccessor::Instance().LifecycleInterface().state(&error);

    if (error == Firebolt::Error::None) {
        cout << "State of the App = " << state.c_str() << endl;
    } else {
        cout << "State of the App throws an error = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::OnBackgroundNotification::onBackground( const Firebolt::Lifecycle::LifecycleEvent& lifecycleEvent)
{
    cout <<"onBackground event is triggered" << endl;
    cout <<"\tstate: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.state) << endl;
    cout <<"\tprevious: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.previous) << endl;
    if (lifecycleEvent.source.has_value()) {
        cout <<"\tsource: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleEventSource>(lifecycleEventSourceMap, lifecycleEvent.source.value()) << endl;
    }

#ifdef GATEWAY_BIDIRECTIONAL
    assert(ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.state) == backgroundNotification["payload"]["state"]);
    assert(ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.previous) == backgroundNotification["payload"]["previous"]);
#endif
}

void CoreSDKTest::SubscribeLifecycleBackgroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribe(_backgroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Lifecycle BackgroundNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeLifecycleBackgroundNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeLifecycleBackgroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(_backgroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Lifecycle BackgroundNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeLifecycleBackgroundNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::OnForegroundNotification::onForeground(const Firebolt::Lifecycle::LifecycleEvent& lifecycleEvent)
{
    cout <<"onForeground event is triggered" << endl;
    cout <<"\tstate: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.state) << endl;
    cout <<"\tprevious: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.previous) << endl;
    if (lifecycleEvent.source.has_value()) {
        cout <<"\tsource: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleEventSource>(lifecycleEventSourceMap, lifecycleEvent.source.value()) << endl;
    }

#ifdef GATEWAY_BIDIRECTIONAL
    assert(ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.state) == foregroundNotification["payload"]["state"]);
    assert(ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.previous) == foregroundNotification["payload"]["previous"]);
    assert(ConvertFromEnum<Firebolt::Lifecycle::LifecycleEventSource>(lifecycleEventSourceMap, lifecycleEvent.source.value()) == foregroundNotification["payload"]["source"]);
#endif
}

void CoreSDKTest::SubscribeLifecycleForegroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribe(_foregroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Lifecycle ForegroundNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeLifecycleForegroundNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeLifecycleForegroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(_foregroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Lifecycle ForegroundNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeLifecycleForegroundNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::GetAuthenticationDevice()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string device = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of Device = " << device.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAuthenticationDevice failed. " + errorMessage);
    }
}

void CoreSDKTest::GetAuthenticationSession()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string session = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of Session = " << session.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAuthenticationSession failed. " + errorMessage);
    }
}

void CoreSDKTest::GetAuthenticationRoot()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string root = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of Root = " << root.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAuthenticationRoot failed. " + errorMessage);
    }
}

void CoreSDKTest::GetAuthenticationToken()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Authentication::TokenType type = Firebolt::Authentication::TokenType::DEVICE;
    std::optional<Firebolt::Authentication::Options> options;

    const Firebolt::Authentication::Token token = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().token(type, options, &error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of token : " << endl;
        cout << "\tvalue: " << token.value.c_str() << endl;
        if (token.expires.has_value()) {
            cout << "\texpires : " << token.expires.value().c_str() << endl;
        }
        if (token.type.has_value()) {
            cout << "\ttype : " << token.type.value().c_str() << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetAuthenticationToken failed. " + errorMessage);
    }
}

EnumMap<Firebolt::Capabilities::DenyReason> denyReasonMap = {
    { Firebolt::Capabilities::DenyReason::UNPERMITTED, "unpermitted" },
    { Firebolt::Capabilities::DenyReason::UNSUPPORTED, "unsupported" },
    { Firebolt::Capabilities::DenyReason::DISABLED, "disabled" },
    { Firebolt::Capabilities::DenyReason::UNAVAILABLE, "unavailable" },
    { Firebolt::Capabilities::DenyReason::GRANT_DENIED, "grant_denied" },
    { Firebolt::Capabilities::DenyReason::UNGRANTED, "ungranted" }
};

static void PrintCapabilityInfo(const Firebolt::Capabilities::CapabilityInfo& info)
{
    if (info.capability.has_value()) {
        cout << "\tcapability : " << info.capability.value() << endl;
    }
    cout << "\tsupported : " << (info.supported ? "true" : "false") << endl;
    cout << "\tavailable : " << (info.available ? "true" : "false") << endl;
    if (info.use.permitted.has_value() || info.use.granted.has_value()) {
        if (info.use.permitted.has_value()) {
            cout << "\tuse.permitted : " << (info.use.permitted.value() ? "true" : "false") << endl;
        }
        if (info.use.granted.has_value()) {
            cout << "\tuse.granted : " << (info.use.granted.value() ? "true" : "false") << endl;
        }
    }
    if (info.manage.permitted.has_value() || info.manage.granted.has_value()) {
        if (info.manage.permitted.has_value()) {
            cout << "\tmanage.permitted : " << (info.manage.permitted.value() ? "true" : "false") << endl;
        }
        if (info.manage.granted.has_value()) {
            cout << "\tmanage.granted : " << (info.manage.granted.value() ? "true" : "false") << endl;
        }
    }
    if (info.provide.permitted.has_value() || info.provide.granted.has_value()) {
        if (info.provide.permitted.has_value()) {
            cout << "\tprovide.permitted : " << (info.provide.permitted.value() ? "true" : "false") << endl;
        }
        if (info.provide.granted.has_value()) {
            cout << "\tprovide.granted : " << (info.provide.granted.value() ? "true" : "false") << endl;
        }
    }
    if (info.details.has_value()) {
        cout << "\tdetails: " << endl;
        for (auto item : info.details.value()) {
            cout << "\t\t" << ConvertFromEnum<Firebolt::Capabilities::DenyReason>(denyReasonMap, item) << endl;
        }
    }
}

void CoreSDKTest::GetCapabilitiesAvailable()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string capability = "xrn:firebolt:capability:token:device";
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().available(capability, &error);
    if (error == Firebolt::Error::None) {
        cout << "Capabilities Available = " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetCapabilitiesAvailable failed. " + errorMessage);
    }
}

void CoreSDKTest::SubscribeCapabilitiesAvailableChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string capability = "xrn:firebolt:capability:usergrant:pinchallenge";
    Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().subscribe(capability, _availableNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Capabilities AvailableNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeCapabilitiesAvailableChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeCapabilitiesAvailableChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().unsubscribe(_availableNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Capabilities AvailableNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeCapabilitiesAvailableChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::OnAvailableNotification::onAvailable(const Firebolt::Capabilities::CapabilityInfo& info)
{
    cout << "OnAvailableNotification is invoked " << endl;
    cout << "capabilityInfo: " << endl;
    PrintCapabilityInfo(info);
}

void CoreSDKTest::GetCapabilitiesGranted()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string capability = "xrn:firebolt:capability:localization:postal-code";
    std::optional<Firebolt::Capabilities::CapabilityOption> options;
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().granted(capability, options, &error);
    if (error == Firebolt::Error::None) {
        cout << "Capabilities Granted = " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetCapabilitiesGranted failed. " + errorMessage);
    }
}

void CoreSDKTest::GetCapabilitiesPermitted()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string capability = "xrn:firebolt:capability:input:keyboard";
    std::optional<Firebolt::Capabilities::CapabilityOption> options = std::make_optional<Firebolt::Capabilities::CapabilityOption>();
    options.value().role = std::make_optional<Firebolt::Capabilities::Role>();
    options.value().role.value() = Firebolt::Capabilities::Role::MANAGE;
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().permitted(capability, options, &error);
    if (error == Firebolt::Error::None) {
        cout << "Capabilities Permitted = " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetCapabilitiesPermitted failed. " + errorMessage);
    }
}

void CoreSDKTest::GetCapabilitiesSupported()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string capability = "xrn:firebolt:capability:wifi:scan";
    bool status = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().supported(capability, &error);
    if (error == Firebolt::Error::None) {
        cout << "Capabilities Supported = " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetCapabilitiesSupported failed. " + errorMessage);
    }
}

void CoreSDKTest::GetCapabilitiesInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::vector<std::string> capabilities = { "xrn:firebolt:capability:device:model", "xrn:firebolt:capability:input:keyboard", "xrn:firebolt:capability:protocol:bluetoothle", "xrn:firebolt:capability:token:device", "xrn:firebolt:capability:token:platform", "xrn:firebolt:capability:protocol:moca", "xrn:firebolt:capability:wifi:scan", "xrn:firebolt:capability:localization:postal-code", "xrn:firebolt:capability:localization:locality"};
    std::vector<Firebolt::Capabilities::CapabilityInfo> info = Firebolt::IFireboltAccessor::Instance().CapabilitiesInterface().info(capabilities, &error);
    if (error == Firebolt::Error::None) {
        cout << "Capabilities Info : " << endl;
        for (auto element : info) {
            PrintCapabilityInfo(element);
            cout << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetCapabilitiesInfo failed. " + errorMessage);
    }
}

void CoreSDKTest::MetricsStartContent()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().startContent(entityId, &error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics Start Content = " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("MetricsStartContent failed. " + errorMessage);
    }
}

void CoreSDKTest::MetricsStopContent()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().stopContent(entityId, &error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics Stop Content = " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("MetricsStopContent failed. " + errorMessage);
    }
}

void CoreSDKTest::MetricsReady()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready(&error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics Ready status = " << (status ? "true" : "false") << endl;
    } else {
        cout << "Metrics Ready status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::MetricsSignIn()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signIn(&error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics signIn status = " << (status ? "true" : "false") << endl;
    } else {
        cout << "Metrics signIn status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::MetricsSignOut()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().signOut(&error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics signOut status = " << (status ? "true" : "false") << endl;
    } else {
        cout << "Metrics signOut status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::GetSecondScreenDevice()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> type;
    std::string deviceId = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().device(type, &error);

    if (error == Firebolt::Error::None) {
        cout << "Get SecondScreen Device : " << deviceId.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetSecondScreenDevice failed. " + errorMessage);
    }
}

void CoreSDKTest::GetSecondScreenProtocols()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Types::BooleanMap map = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().protocols(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get SecondScreen Protocols : " << endl;
        for (auto element : map) {
            cout << element.first << " : " << (element.second ? "true" : "false") << endl;
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetSecondScreenProtocols failed. " + errorMessage);
    }
}

void CoreSDKTest::GetSecondScreenFriendlyName()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string friendlyName = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().friendlyName(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get SecondScreen FriendlyName : " << friendlyName.c_str() << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("GetSecondScreenFriendlyName failed. " + errorMessage);
    }
}

void CoreSDKTest::OnFriendlyNameChangedNotification::onFriendlyNameChanged(const std::string& friendlyName)
{
    cout << "OnFriendlyNameChangedNotification friendlyName : " << friendlyName.c_str() << endl;

#ifdef GATEWAY_BIDIRECTIONAL
    nlohmann::json friendlyNameJson = nlohmann::json::parse(friendlyName);
    assert(friendlyNameJson["name"] == friendlyNameChanged["payload"]["name"]);
    assert(friendlyNameJson["value"] == friendlyNameChanged["payload"]["value"]);
#endif
}

void CoreSDKTest::SubscribeSecondScreenFriendlyNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().subscribe(_friendlyNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe SecondScreen FriendlyNameChangedNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeSecondScreenFriendlyNameChanged failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeSecondScreenFriendlyNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().unsubscribe(_friendlyNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe SecondScreen FriendlyNameChangedNotification is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeSecondScreenFriendlyNameChanged failed. " + errorMessage);
    }
}

EnumMap<Firebolt::SecondScreen::SecondScreenEventType> secondScreenEventTypeMap = {
    { Firebolt::SecondScreen::SecondScreenEventType::DIAL, "dial" }
};

void CoreSDKTest::ParametersInitialization()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Parameters::AppInitialization appInitialization = Firebolt::IFireboltAccessor::Instance().ParametersInterface().initialization(&error);
    if (error == Firebolt::Error::None) {
        cout << "Parameters Initialization is success" << endl;
        if (appInitialization.us_privacy.has_value()) {
            cout << "\tus_privacy : " << appInitialization.us_privacy.value().c_str() << endl;
        }
        if (appInitialization.lmt.has_value()) {
            cout << "\tlmt : " << appInitialization.lmt.value() << endl;
        }
        if (appInitialization.discovery.has_value()) {
            if (appInitialization.discovery.value().navigateTo.has_value()) {
                cout << "\tdiscovery:navigateTo : " << appInitialization.discovery.value().navigateTo.value().c_str() << endl;
            }
        }
        if (appInitialization.secondScreen.has_value()) {
            if (appInitialization.secondScreen.value().launchRequest.has_value()) {
                Firebolt::SecondScreen::SecondScreenEvent event = appInitialization.secondScreen.value().launchRequest.value();
                cout << "\tsecondScreen:launchRequest:type : " << ConvertFromEnum<Firebolt::SecondScreen::SecondScreenEventType>(secondScreenEventTypeMap, event.type) << endl;
                if (event.version.has_value()) {
                    cout << "\tsecondScreen:launchRequest:version : " << event.version.value().c_str() << endl;
                }
                if (event.data.has_value()) {
                    cout << "\tsecondScreen:launchRequest:data : " << event.data.value().c_str() << endl;
                }
            }
        }
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("ParametersInitialization failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoverySignIn()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::vector<Firebolt::Entertainment::Entitlement>> entitlements = std::make_optional<std::vector<Firebolt::Entertainment::Entitlement>>();
    Firebolt::Entertainment::Entitlement entitlement;
    entitlement.startTime = "2025-01-01T00:00:00.000Z";
    entitlement.endTime = "2025-01-01T00:00:00.000Z";
    entitlements.value().push_back(entitlement);

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().signIn(entitlements, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery SignIn is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoverySignIn failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoverySignOut()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().signOut(&error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery SignOut is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoverySignOut failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryContentAccess()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::ContentAccessIdentifiers contentAccessIdentifiers;
    contentAccessIdentifiers.availabilities = std::make_optional<std::vector<Firebolt::Discovery::Availability>>();
    Firebolt::Discovery::Availability availability;
    availability.type = Firebolt::Discovery::AvailabilityType::CHANNEL_LINEUP;
    availability.id = "partner.com/availability/123";
    availability.startTime = "2021-04-23T18:25:43.511Z";
    availability.endTime = "2021-04-23T18:25:43.511Z";
    contentAccessIdentifiers.availabilities.value().push_back(availability);

    contentAccessIdentifiers.entitlements = std::make_optional<std::vector<Firebolt::Entertainment::Entitlement>>();
    Firebolt::Entertainment::Entitlement entitlement;
    entitlement.startTime = "2025-01-01T00:00:00.000Z";
    entitlement.endTime = "2025-01-01T00:00:00.000Z";
    contentAccessIdentifiers.entitlements.value().push_back(entitlement);

    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().contentAccess(contentAccessIdentifiers, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery ContentAccess is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryContentAccess failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryClearContentAccess()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().clearContentAccess(&error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery ClearContentAccess is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryClearContentAccess failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryEntitlements()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::vector<Firebolt::Entertainment::Entitlement> entitlements;
    Firebolt::Entertainment::Entitlement entitlement;
    entitlement.startTime = "2025-01-01T00:00:00.000Z";
    entitlement.endTime = "2025-01-01T00:00:00.000Z";
    entitlements.push_back(entitlement);

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().entitlements(entitlements, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery Entitlements is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryEntitlements failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryWatchNext()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string title = "A Cool Show";
    Firebolt::Entertainment::ContentIdentifiers identifiers;
    identifiers.entityId = "partner.com/entity/123";
    std::optional<std::string> expires = "2021-04-23T18:25:43.511Z";
    std::optional<Firebolt::Discovery::Images> images = std::make_optional<Firebolt::Discovery::Images>();
    images = "{\"3x4\": {\"en-US\": \"https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg\", \"es\": \"https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg\"}, \"16x9\": {\"en\": \"https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg\"}}";

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().watchNext(title, identifiers, expires, images, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery Watched Next is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryWatchNext failed. " + errorMessage);
    }
}


void CoreSDKTest::DiscoveryPolicy()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::DiscoveryPolicy policy = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().policy(&error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery Policy is " << endl;
        cout << "\tenableRecommendations: " << policy.enableRecommendations << endl;
        cout << "\tshareWatchHistory: " << policy.shareWatchHistory << endl;
        cout << "\trememberWatchedPrograms: " << policy.rememberWatchedPrograms << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryPolicy failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryEntityInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::EntityInfoResult result;
    result.expires = "2025-01-01T00:00:00.000Z";
    {
        result.entity.identifiers.entityId = "345";
        result.entity.title = "Cool Running";
        result.entity.entityType = Firebolt::Entertainment::EntityInfoEntityType::PROGRAM;
        result.entity.programType = Firebolt::Entertainment::ProgramType::MOVIE;
        result.entity.synopsis = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.";
        result.entity.releaseDate = "1993-01-01T00:00:00.000Z";
        result.entity.contentRatings = std::make_optional<std::vector<Firebolt::Entertainment::ContentRating>>();
        {
            Firebolt::Entertainment::ContentRating contentRating;
            contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::US_MOVIE;
            contentRating.rating = "PG";
            result.entity.contentRatings.value().push_back(contentRating);
        }
        {
            Firebolt::Entertainment::ContentRating contentRating;
            contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::CA_MOVIE;
            contentRating.rating = "G";
            result.entity.contentRatings.value().push_back(contentRating);
        }

        Firebolt::Entertainment::WayToWatch wayToWatch;
        result.entity.waysToWatch = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatch>>();
        wayToWatch.identifiers.assetId = "123";
        wayToWatch.expires = "2025-01-01T00:00:00.000Z";
        wayToWatch.entitled = true;
        wayToWatch.entitledExpires = "2025-01-01T00:00:00.000Z";
        wayToWatch.offeringType = Firebolt::Entertainment::OfferingType::BUY;
        wayToWatch.price = 2.99;
        wayToWatch.videoQuality = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatchVideoQuality>>();
        wayToWatch.videoQuality.value().push_back(Firebolt::Entertainment::WayToWatchVideoQuality::UHD);
        wayToWatch.audioProfile.push_back(Firebolt::Types::AudioProfile::DOLBY_ATMOS);
        wayToWatch.audioLanguages = std::make_optional<std::vector<std::string>>();
        wayToWatch.audioLanguages.value().push_back("en");
        wayToWatch.closedCaptions = std::make_optional<std::vector<std::string>>();
        wayToWatch.closedCaptions.value().push_back("en");
        wayToWatch.subtitles = std::make_optional<std::vector<std::string>>();
        wayToWatch.subtitles.value().push_back("es");
        wayToWatch.audioDescriptions = std::make_optional<std::vector<std::string>>();
        wayToWatch.audioDescriptions.value().push_back("en");
        result.entity.waysToWatch.value().push_back(wayToWatch);
    }
    {
        result.related = std::make_optional<std::vector<Firebolt::Entertainment::EntityInfo>>();
        Firebolt::Entertainment::EntityInfo entityInfo;
        entityInfo.identifiers.entityId = "345";
        entityInfo.title = "Cool Runnings Trailer";
        entityInfo.entityType = Firebolt::Entertainment::EntityInfoEntityType::PROGRAM;
        entityInfo.programType = Firebolt::Entertainment::ProgramType::PREVIEW;
        entityInfo.releaseDate = "1993-01-01T00:00:00.000Z";
        entityInfo.waysToWatch = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatch>>();
        Firebolt::Entertainment::WayToWatch wayToWatch;
        wayToWatch.identifiers.assetId = "123111";
        wayToWatch.identifiers.entityId = "345";
        wayToWatch.expires = "2026-01-01T00:00:00.000Z";
        wayToWatch.entitled = true;
        wayToWatch.videoQuality = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatchVideoQuality>>();
        wayToWatch.videoQuality.value().push_back(Firebolt::Entertainment::WayToWatchVideoQuality::HD);
        wayToWatch.audioProfile.push_back(Firebolt::Types::AudioProfile::DOLBY_ATMOS);
        wayToWatch.audioLanguages = std::make_optional<std::vector<std::string>>();
        wayToWatch.audioLanguages.value().push_back("en");
        wayToWatch.closedCaptions = std::make_optional<std::vector<std::string>>();
        wayToWatch.closedCaptions.value().push_back("en");
        entityInfo.waysToWatch.value().push_back(wayToWatch);
        result.related.value().push_back(entityInfo);
    }

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().entityInfo(result, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery EntityInfo is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryEntityInfo failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryPurchasedContent()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::PurchasedContentResult result;
    result.expires = "2025-01-01T00:00:00.000Z";
    result.totalCount = 10;
    Firebolt::Entertainment::EntityInfo entityInfo;
    entityInfo.identifiers.entityId = "345";
    entityInfo.title = "Cool Runnings";
    entityInfo.entityType = Firebolt::Entertainment::EntityInfoEntityType::PROGRAM;
    entityInfo.programType = Firebolt::Entertainment::ProgramType::MOVIE;
    entityInfo.synopsis = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.";
    entityInfo.releaseDate = "1993-01-01T00:00:00.000Z";
    entityInfo.contentRatings = std::make_optional<std::vector<Firebolt::Entertainment::ContentRating>>();
    {
        Firebolt::Entertainment::ContentRating contentRating;
        contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::US_MOVIE;
        contentRating.rating = "PG";
        entityInfo.contentRatings.value().push_back(contentRating);
    }
    {
        Firebolt::Entertainment::ContentRating contentRating;
        contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::CA_TV;
        contentRating.rating = "TV-PG";
        entityInfo.contentRatings.value().push_back(contentRating);
    }

    Firebolt::Entertainment::WayToWatch wayToWatch;
    entityInfo.waysToWatch = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatch>>();
    wayToWatch.identifiers.assetId = "123";
    wayToWatch.expires = "2025-01-01T00:00:00.000Z";
    wayToWatch.entitled = true;
    wayToWatch.entitledExpires = "2025-01-01T00:00:00.000Z";
    wayToWatch.offeringType = Firebolt::Entertainment::OfferingType::BUY;
    wayToWatch.price = 2.99;
    wayToWatch.videoQuality = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatchVideoQuality>>();
    wayToWatch.videoQuality.value().push_back(Firebolt::Entertainment::WayToWatchVideoQuality::UHD);
    wayToWatch.audioProfile.push_back(Firebolt::Types::AudioProfile::DOLBY_ATMOS);
    wayToWatch.audioLanguages = std::make_optional<std::vector<std::string>>();
    wayToWatch.audioLanguages.value().push_back("en");
    wayToWatch.closedCaptions = std::make_optional<std::vector<std::string>>();
    wayToWatch.closedCaptions.value().push_back("en");
    wayToWatch.subtitles = std::make_optional<std::vector<std::string>>();
    wayToWatch.subtitles.value().push_back("es");
    wayToWatch.audioDescriptions = std::make_optional<std::vector<std::string>>();
    wayToWatch.audioDescriptions.value().push_back("en");
    entityInfo.waysToWatch.value().push_back(wayToWatch);
    result.entries.push_back(entityInfo);

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().purchasedContent(result, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery PurchasedContent is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryPurchasedContent failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryLaunch()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string appId = "123";
    {
        std::optional<std::string> intent = std::make_optional<std::string>();
        cout << "Calling Discovery Launch TuneIntent method " << endl;
        bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().launch(appId, intent, &error);
        
        if (error == Firebolt::Error::None) {
            cout << "Discovery Launch TuneIntent is " << (status ? "true" : "false") << endl;
        } else {
            std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
            throw std::runtime_error("DiscoveryLaunch failed. " + errorMessage);
        }
    }

    {
        std::optional<std::string> intent = std::make_optional<std::string>();
        cout << "Calling Discovery Launch SearchIntent method " << endl;
        bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().launch(appId, intent, &error);
        if (error == Firebolt::Error::None) {
            cout << "Discovery Launch HomeIntent is " << (status ? "true" : "false") << endl;
        } else {
            std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
            throw std::runtime_error("DiscoveryLaunch failed. " + errorMessage);
        }
    }

    {
        std::optional<std::string> intent = std::make_optional<std::string>();
        cout << "Calling Discovery Launch HomeIntent method " << endl;
        bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().launch(appId, intent, &error);
        if (error == Firebolt::Error::None) {
            cout << "Discovery Launch HomeIntent is " << (status ? "true" : "false") << endl;
        } else {
            std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
            throw std::runtime_error("DiscoveryLaunch failed. " + errorMessage);
        }
    }
}
#ifdef POLYMORPHICS_REDUCER_METHODS
void CoreSDKTest::DiscoveryWatched()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string entityId = "partner.com/entity/123";
    std::optional<float> progress = 0.95;
    std::optional<bool> completed = true;
    std::optional<std::string> watchedOn = "2021-04-23T18:25:43.511Z";

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().watched(entityId, progress, completed, watchedOn, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery Watched is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryWatched failed. " + errorMessage);
    }
}

void CoreSDKTest::DiscoveryWatchedReduced()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::WatchedInfo watchedInfo;
    watchedInfo.entityId = "partner.com/entity/123";
    watchedInfo.progress = 0.95;
    watchedInfo.completed = true;
    watchedInfo.watchedOn = "2021-04-23T18:25:43.511Z";
    std::vector<Firebolt::Discovery::WatchedInfo> watchedInfoList;
    watchedInfoList.push_back(watchedInfo);

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().watched(watchedInfoList, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery Watched Reduced is " << (status ? "true" : "false") << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("DiscoveryWatchedReduced failed. " + errorMessage);
    }
}
#endif

void CoreSDKTest::SubscribeDiscoveryOnNavigateToLaunchHomeIntentNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_navigateToHomeIntentNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery OnNavigateToLaunch HomeIntent is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDiscoveryOnNavigateToLaunchNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::SubscribeDiscoveryOnNavigateToLaunchEntityIntentNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_navigateToEntityIntentNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery OnNavigateToLaunch EntityIntent is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDiscoveryOnNavigateToLaunchNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::SubscribeDiscoveryOnNavigateToLaunchTuneIntentNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().subscribe(_navigateToTuneIntentNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Discovery OnNavigateToLaunch TuneIntent is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("SubscribeDiscoveryOnNavigateToLaunchNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeDiscoveryOnNavigateToLaunchHomeIntentNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_navigateToHomeIntentNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery OnNavigateToLaunch HomeIntent is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDiscoveryOnNavigateToLaunchNotification failed. " + errorMessage);
    }
}


void CoreSDKTest::UnsubscribeDiscoveryOnNavigateToLaunchEntityIntentNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_navigateToEntityIntentNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery OnNavigateToLaunch EntityIntent is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDiscoveryOnNavigateToLaunchNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::UnsubscribeDiscoveryOnNavigateToLaunchTuneIntentNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().unsubscribe(_navigateToTuneIntentNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Discovery OnNavigateToLaunch TuneIntent is success" << endl;
    } else {
        std::string errorMessage = "Error: " + std::to_string(static_cast<int>(error));
        throw std::runtime_error("UnsubscribeDiscoveryOnNavigateToLaunchNotification failed. " + errorMessage);
    }
}

void CoreSDKTest::OnNavigateToHomeIntentNotification::onNavigateTo(const std::string& intent)
{
    cout << "OnNavigateToHomeIntentNotification::onNavigateTo for action : " << intent << endl; 
}

void CoreSDKTest::OnNavigateToEntityIntentNotification::onNavigateTo(const std::string& intent)
{
    cout << "OnNavigateToEntityIntentNotification::onNavigateTo for action : " << intent << endl;
}

void CoreSDKTest::OnNavigateToTuneIntentNotification::onNavigateTo(const std::string& intent)
{
    cout << "OnNavigateToTuneIntentNotification::onNavigateTo for action : " << intent << endl;
}
