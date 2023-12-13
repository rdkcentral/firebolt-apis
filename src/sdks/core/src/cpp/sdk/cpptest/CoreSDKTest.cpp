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
#include "CoreSDKTest.h"

using namespace std;
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

void CoreSDKTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
}

void CoreSDKTest::CreateFireboltInstance(const std::string& url)
{
    const std::string config = "{\
            \"waitTime\": 60000,\
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
    return _connected;
}

void CoreSDKTest::GetAccountId()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string id = Firebolt::IFireboltAccessor::Instance().AccountInterface().id(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Account Id = " << id.c_str() << endl;
    } else {
        cout << "Get Account Id status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::GetAccountUid()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string uid = Firebolt::IFireboltAccessor::Instance().AccountInterface().uid(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Account Uid = " << uid.c_str() << endl;
    } else {
        cout << "Get Account Uid status = " << static_cast<int>(error) << endl;
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
        cout << "Get Advertising policy status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::OnPolicyChangedNotification::onPolicyChanged( const Firebolt::Advertising::AdPolicy& policy )
{
    cout << "New policy --> " << endl;
    PrintAdvertisingPolicy(policy);
}
void CoreSDKTest::SubscribeAdvertisingPolicyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().subscribe(_policyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Advertising PolicyChange is success" << endl;
    } else {
        cout << "Subscribe Advertising PolicyChange status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeAdvertisingPolicyChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().unsubscribe(_policyChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Advertising PolicyChange is success" << endl;
    } else {
        cout << "Unsubscribe Advertising PolicyChange status = " << static_cast<int>(error) << endl;
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
        cout << "Build AdvertisingConfiguration status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::GetAdvertisingDeviceAttributes()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Advertising::DeviceAttributes deviceAttributes = Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().deviceAttributes(&error);
    if (error == Firebolt::Error::None) {
        cout << "Get Advertising DeviceAttributes is success, deviceAttributes : " << deviceAttributes << endl;
    } else {
        cout << "Get Advertising DeviceAttributes status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::GetDeviceName()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string name = Firebolt::IFireboltAccessor::Instance().DeviceInterface().name(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Name = " << name.c_str() << endl;
    } else {
        cout << "Get Device Name status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::OnDeviceNameChangedNotification::onDeviceNameChanged( const std::string& name)
{
    cout << "Name changed, new name --> " << name << endl;
}

void CoreSDKTest::SubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device NameChange is success" << endl;
    } else {
        cout << "Subscribe Device NameChange status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::UnsubscribeDeviceNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_deviceNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device NameChange is success" << endl;
    } else {
        cout << "Unsubscribe Device NameChange status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::GetDeviceModel()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string model = Firebolt::IFireboltAccessor::Instance().DeviceInterface().model(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Model = " << model.c_str() << endl;
    } else {
        cout << "Get Device Model status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::GetDeviceSku()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string sku = Firebolt::IFireboltAccessor::Instance().DeviceInterface().sku(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Device Sku = " << sku.c_str() << endl;
    } else {
        cout << "Get Device Sku status = " << static_cast<int>(error) << endl;
    }
}

void PrintDeviceAudioProfiles( const Firebolt::Device::AudioProfiles& audioProfiles )
{
    cout << "Get Device AudioProfiles :-> " << endl;
    for (auto& item : audioProfiles) {
        cout << "Profile: " << static_cast<int>(item.first) << " status: " << item.second << endl;
    }
}
void CoreSDKTest::GetDeviceAudio()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Device::AudioProfiles audioProfiles = Firebolt::IFireboltAccessor::Instance().DeviceInterface().audio(&error);
    if (error == Firebolt::Error::None) {
        PrintDeviceAudioProfiles(audioProfiles);
    } else {
        cout << "Get Device AudioProfiles status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::OnAudioChangedNotification::onAudioChanged( const Firebolt::Device::AudioProfiles& audioProfiles )
{
    cout << "onAudioChanged event " << endl;
    PrintDeviceAudioProfiles(audioProfiles);
}
void CoreSDKTest::SubscribeDeviceAudioChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_audioChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device Audio Change is success" << endl;
    } else {
        cout << "Subscribe Device Audio Change status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeDeviceAudioChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_audioChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device Audio Change is success" << endl;
    } else {
        cout << "Unsubscribe Device Audio Change status = " << static_cast<int>(error) << endl;
    }
}

void PrintDeviceScreenResolution( const Firebolt::Device::Resolution& resolution )
{
    cout << "Get Device ScreenResolution :-> " << endl;
    cout << resolution.first << " X " << resolution.second << endl;
}
void CoreSDKTest::GetDeviceScreenResolution()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Device::Resolution resolution = Firebolt::IFireboltAccessor::Instance().DeviceInterface().screenResolution(&error);
    if (error == Firebolt::Error::None) {
        PrintDeviceScreenResolution(resolution);
    } else {
        cout << "Get Device ScreenResolution status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::OnScreenResolutionChangedNotification::onScreenResolutionChanged( const Firebolt::Device::Resolution& resolution )
{
    cout << "onScreenResolutionChanged event " << endl;
    PrintDeviceScreenResolution(resolution);
}
void CoreSDKTest::SubscribeDeviceScreenResolutionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(_screenResolutionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Device ScreenResolution Change is success" << endl;
    } else {
        cout << "Subscribe Device ScreenResolution Change status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeDeviceScreenResolutionChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(_screenResolutionChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Device ScreenResolution Change is success" << endl;
    } else {
        cout << "Unsubscribe Device ScreenResolution Change status = " << static_cast<int>(error) << endl;
    }
}

void PrintClosedCaptionsSettings( const Firebolt::Accessibility::ClosedCaptionsSettings& closedCaptionsSettings)
{
    cout << "Get Accessibility ClosedCaptionsSettings :-> " << endl;
    cout << "ClosedCaptionsSettings::Enabled : " << closedCaptionsSettings.enabled << endl;
    if (closedCaptionsSettings.styles.fontFamily.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::FontFamily : " << static_cast<int>(closedCaptionsSettings.styles.fontFamily.value()) << endl;
    }
    if (closedCaptionsSettings.styles.fontSize.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::FontSize : " << setprecision(3) << closedCaptionsSettings.styles.fontSize.value() << endl;
    }
    if (closedCaptionsSettings.styles.fontColor.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::FontColor : " << closedCaptionsSettings.styles.fontColor.value() << endl;
    }
    if (closedCaptionsSettings.styles.fontEdge.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::FontEdge : " << static_cast<int>(closedCaptionsSettings.styles.fontEdge.value()) << endl;
    }
    if (closedCaptionsSettings.styles.fontEdgeColor.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::FontEdgeColor : " << closedCaptionsSettings.styles.fontEdgeColor.value() << endl;
    }
    if (closedCaptionsSettings.styles.fontOpacity.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::FontOpacity : " << closedCaptionsSettings.styles.fontOpacity.value() << endl;
    }
    if (closedCaptionsSettings.styles.backgroundColor.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::BackgroundColor : " << closedCaptionsSettings.styles.backgroundColor.value() << endl;
    }
    if (closedCaptionsSettings.styles.backgroundOpacity.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::BackgroundOpacity : " << closedCaptionsSettings.styles.backgroundOpacity.value() << endl;
    }
    if (closedCaptionsSettings.styles.textAlign.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::TextAlign : " << closedCaptionsSettings.styles.textAlign.value() << endl;
    }
    if (closedCaptionsSettings.styles.textAlignVertical.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::TextAlignVertical : " << closedCaptionsSettings.styles.textAlignVertical.value() << endl;
    }
    if (closedCaptionsSettings.styles.windowColor.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::WindowColor : " << closedCaptionsSettings.styles.windowColor.value() << endl;
    }
    if (closedCaptionsSettings.styles.windowOpacity.has_value()) {
        cout << "ClosedCaptionsSettings::Styles::WindowOpacity : " << closedCaptionsSettings.styles.windowOpacity.value() << endl;
    }
    cout << "ClosedCaptionsSettings::PreferredLanguages :";

    for (auto index: closedCaptionsSettings.preferredLanguages.value()) {
        cout << " " << index;
    }
    cout << endl;
}
void CoreSDKTest::GetAccessibilityClosedCaptionsSettings()
{
    Firebolt::Error error = Firebolt::Error::None;
    const Firebolt::Accessibility::ClosedCaptionsSettings closedCaptionsSettings = Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().closedCaptionsSettings(&error);
    if (error == Firebolt::Error::None) {
        PrintClosedCaptionsSettings(closedCaptionsSettings);
    } else {
        cout << "Get Accessibility ClosedCaptionsSettings status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::OnClosedCaptionsSettingsChangedNotification::onClosedCaptionsSettingsChanged( const Firebolt::Accessibility::ClosedCaptionsSettings& closedCaptionsSettings )
{
    cout << "ClosedCaptionsSettingsChanged event " << endl;
    PrintClosedCaptionsSettings(closedCaptionsSettings);
}
void CoreSDKTest::SubscribeAccessibilityClosedCaptionsSettingsChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().subscribe(_closedCaptionsSettingsChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Accessibilty ClosedCaptionSettings Change is success" << endl;
    } else {
        cout << "Subscribe Accessibilty ClosedCaptionSettings Change status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeAccessibilityClosedCaptionsSettingsChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().AccessibilityInterface().unsubscribe(_closedCaptionsSettingsChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Accessibilty ClosedCaptionSettings Change is success" << endl;
    } else {
        cout << "Unsubscribe Accessibilty ClosedCaptionSettings Change status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::GetLocalizationPreferredAudioLanguages()
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
void CoreSDKTest::OnPreferredAudioLanguagesChangedNotification::onPreferredAudioLanguagesChanged( const std::vector<std::string>& languages)
{
    cout << "PreferredAudioLanguages Changed, new languages --> " << endl;
    for (auto language : languages) {
        cout << " -> " << language << endl;
    }
}
void CoreSDKTest::SubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        cout << "Subscribe Localization PreferredAudioLanguagesChange status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeLocalizationPreferredAudioLanguagesChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(_preferredAudioLanguagesChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange is success" << endl;
    } else {
        cout << "Unsubscribe Localization PreferredAudioLanguagesChange status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::InvokeKeyboardStandard()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string message = "Enter the name you'd like to associate with this device";
    string response = Firebolt::IFireboltAccessor::Instance().KeyboardInterface().standard(message, &error);
    if (error == Firebolt::Error::None) {
        cout << "Keyboard standard response: " << response << endl;
    } else {
        cout << "Error while invoking keyboard.standard method, error = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::InvokeKeyboardPassword()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string message = "Enter the password to associate with this device";
    string response = Firebolt::IFireboltAccessor::Instance().KeyboardInterface().password(message, &error);
    if (error == Firebolt::Error::None) {
        cout << "Keyboard password response: " << response << endl;
    } else {
        cout << "Error while invoking keyboard.password method, error = " << static_cast<int>(error) << endl;
    }

}
void CoreSDKTest::InvokeKeyboardEmail()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Keyboard::EmailUsage type = Firebolt::Keyboard::EmailUsage::SIGN_IN;
    std::string message = "Enter your email to sign into this app/device";
    string response = Firebolt::IFireboltAccessor::Instance().KeyboardInterface().email(type, message, &error);
    if (error == Firebolt::Error::None) {
        cout << "Keyboard email response: " << response << endl;
    } else {
        cout << "Error while invoking keyboard.email method, error = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::VerifyProfileApproveContentRating()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allow = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approveContentRating(&error);
    if (error == Firebolt::Error::None) {
        cout << "Verify Profile ApproveContentRating is success value : " << allow << endl;
    } else {
        cout << "Verify Profile ApproveContentRating status : " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::VerifyProfileApprovePurchase()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool allow = Firebolt::IFireboltAccessor::Instance().ProfileInterface().approvePurchase(&error);
    if (error == Firebolt::Error::None) {
        cout << "Verify Profile ApprovePurchase is success value : " << allow << endl;
    } else {
        cout << "Verify Profile ApprovePurchase status : " << static_cast<int>(error) << endl;
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
        cout << "Get Profile flags status : " << static_cast<int>(error) << endl;
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
        cout << "Lifecycle close status = " << static_cast<int>(error) << endl;
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
void CoreSDKTest::OnBackgroundNotification::onBackground( const Firebolt::Lifecycle::LifecycleEvent& lifecycleEvent)
{
    cout <<"onBackground event is triggered" << endl;
    cout <<"\tstate: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.state) << endl;
    cout <<"\tprevious: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.previous) << endl;
    if (lifecycleEvent.source.has_value()) {
    cout <<"\tsource: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleEventSource>(lifecycleEventSourceMap, lifecycleEvent.source.value()) << endl;
    }
}
void CoreSDKTest::SubscribeLifecycleBackgroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribe(_backgroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Lifecycle BackgroundNotification is success" << endl;
    } else {
        cout << "Subscribe Lifecycle BackgroundNotification status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeLifecycleBackgroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(_backgroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Lifecycle BackgroundNotification is success" << endl;
    } else {
        cout << "Unsubscribe Lifecycle BackgroundNotification status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::OnForegroundNotification::onForeground( const Firebolt::Lifecycle::LifecycleEvent& lifecycleEvent)
{
    cout <<"onForeground event is triggered" << endl;
    cout <<"\tstate: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.state) << endl;
    cout <<"\tprevious: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleState>(lifecycleStateMap, lifecycleEvent.previous) << endl;
    if (lifecycleEvent.source.has_value()) {
    cout <<"\tsource: " << ConvertFromEnum<Firebolt::Lifecycle::LifecycleEventSource>(lifecycleEventSourceMap, lifecycleEvent.source.value()) << endl;
    }
}
void CoreSDKTest::SubscribeLifecycleForegroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribe(_foregroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe Lifecycle ForegroundNotification is success" << endl;
    } else {
        cout << "Subscribe Lifecycle ForegroundNotification status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeLifecycleForegroundNotification()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(_foregroundNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe Lifecycle ForegroundNotification is success" << endl;
    } else {
        cout << "Unsubscribe Lifecycle ForegroundNotification status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::GetAuthenticationDevice()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string device = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of Device = " << device.c_str() << endl;
    } else {
        cout << "Get Authentication of Device status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::GetAuthenticationSession()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string session = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of Session = " << session.c_str() << endl;
    } else {
        cout << "Get Authentication of Session status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::GetAuthenticationRoot()
{
    Firebolt::Error error = Firebolt::Error::None;
    const std::string root = Firebolt::IFireboltAccessor::Instance().AuthenticationInterface().device(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get Authentication of Root = " << root.c_str() << endl;
    } else {
        cout << "Get Authentication of Root status = " << static_cast<int>(error) << endl;
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
        cout << "Get Authentication of Device status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::MetricsStartContent()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    const bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().startContent(entityId, &error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics Start Content = " << status << endl;
    } else {
        cout << "Metrics Start Content status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::MetricsStopContent()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::optional<std::string> entityId;
    const bool status = Firebolt::IFireboltAccessor::Instance().MetricsInterface().stopContent(entityId, &error);

    if (error == Firebolt::Error::None) {
        cout << "Metrics Stop Content = " << status << endl;
    } else {
        cout << "Metrics Stop Content status = " << static_cast<int>(error) << endl;
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
        cout << "Get SecondScreen Device status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::GetSecondScreenFriendlyName()
{
    Firebolt::Error error = Firebolt::Error::None;
    std::string friendlyName = Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().friendlyName(&error);

    if (error == Firebolt::Error::None) {
        cout << "Get SecondScreen FriendlyName : " << friendlyName.c_str() << endl;
    } else {
        cout << "Get SecondScreen FriendlyName status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::OnFriendlyNameChangedNotification::onFriendlyNameChanged( const std::string& friendlyName)
{
    cout << "OnFriendlyNameChangedNotification friendlyName : " << friendlyName.c_str() << endl;
}
void CoreSDKTest::SubscribeSecondScreenFriendlyNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().subscribe(_friendlyNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Subscribe SecondScreen FriendlyNameChangedNotification is success" << endl;
    } else {
        cout << "Subscribe SecondScreen FriendlyNameChangedNotification status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::UnsubscribeSecondScreenFriendlyNameChanged()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().SecondScreenInterface().unsubscribe(_friendlyNameChangedNotification, &error);
    if (error == Firebolt::Error::None) {
        cout << "Unsubscribe SecondScreen FriendlyNameChangedNotification is success" << endl;
    } else {
        cout << "Unsubscribe SecondScreen FriendlyNameChangedNotification status = " << static_cast<int>(error) << endl;
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
                cout <<"\tsecondScreen:launchRequest:type : " << ConvertFromEnum<Firebolt::SecondScreen::SecondScreenEventType>(secondScreenEventTypeMap, event.type) << endl;
                if (event.version.has_value()) {
                    cout <<"\tsecondScreen:launchRequest:version : " << event.version.value().c_str() << endl;
                }
                if (event.data.has_value()) {
                    cout <<"\tsecondScreen:launchRequest:data : " << event.data.value().c_str() << endl;
                }
            }
        }
    } else {
        cout << "Parameters Initialization status = " << static_cast<int>(error) << endl;
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
        cout << "Discovery SignIn status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::DiscoverySignOut()
{
    Firebolt::Error error = Firebolt::Error::None;
    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().signOut(&error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery SignOut is " << (status ? "true" : "false") << endl;
    } else {
        cout << "Discovery SignOut status = " << static_cast<int>(error) << endl;
    }
}

void CoreSDKTest::DiscoveryContentAccess()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::ContentAccessIdentifiers contentAccessIdentifiers;
    contentAccessIdentifiers.availabilities =  std::make_optional<std::vector<Firebolt::Discovery::Availability>>();
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
        cout << "Discovery ContentAccess status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::DiscoveryClearContentAccess()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().clearContentAccess(&error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery ClearContentAccess is success" << endl;
    } else {
        cout << "Discovery ClearContentAccess status = " << static_cast<int>(error) << endl;
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
        cout << "Discovery Entitlements status = " << static_cast<int>(error) << endl;
    }
}
void CoreSDKTest::DiscoveryEntityInfo()
{
    Firebolt::Error error = Firebolt::Error::None;
    Firebolt::Discovery::EntityInfoResult result;
    result.expires = "2025-01-01T00:00:00.000Z";
    {
        result.entity.identifiers.entityId = "98765";
        result.entity.title = "Perfect Strangers";
        result.entity.entityType = "program";
        result.entity.programType = Firebolt::Entertainment::ProgramType::SERIES;
        result.entity.synopsis = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.";
        result.entity.releaseDate = "1986-01-01T00:00:00.000Z";
        result.entity.contentRatings = std::make_optional<std::vector<Firebolt::Entertainment::ContentRating>>();
        {
            Firebolt::Entertainment::ContentRating contentRating;
            contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::US_TV;
            contentRating.rating = "TV-PG";
            result.entity.contentRatings.value().push_back(contentRating);
        }
        {
            Firebolt::Entertainment::ContentRating contentRating;
            contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::CA_TV;
            contentRating.rating = "TV-PG";
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
        entityInfo.identifiers.entityId = "112";
        entityInfo.identifiers.seriesId = "98765";
        entityInfo.title = "Picture This";
        entityInfo.entityType = "program";
        entityInfo.programType = Firebolt::Entertainment::ProgramType::EPISODE;
        entityInfo.synopsis = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.";
        entityInfo.releaseDate = "1993-01-01T00:00:00.000Z";
        entityInfo.contentRatings = std::make_optional<std::vector<Firebolt::Entertainment::ContentRating>>();
        {
            Firebolt::Entertainment::ContentRating contentRating;
            contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::CA_TV_FR;
            contentRating.rating = "TV_PG";
            entityInfo.contentRatings.value().push_back(contentRating);
        }
        {
            Firebolt::Entertainment::ContentRating contentRating;
            contentRating.scheme = Firebolt::Entertainment::ContentRatingScheme::CA_MOVIE_FR;
            contentRating.rating = "TV_PG";
            entityInfo.contentRatings.value().push_back(contentRating);
        }

        entityInfo.waysToWatch = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatch>>();
        Firebolt::Entertainment::WayToWatch wayToWatch;
        wayToWatch.identifiers.assetId = "234";
        wayToWatch.expires = "2026-01-01T00:00:00.000Z";
        wayToWatch.entitled = true;
        wayToWatch.entitledExpires = "2026-01-01T00:00:00.000Z";
        wayToWatch.offeringType = Firebolt::Entertainment::OfferingType::BUY;
        wayToWatch.price = 3.99;
        wayToWatch.videoQuality = std::make_optional<std::vector<Firebolt::Entertainment::WayToWatchVideoQuality>>();
        wayToWatch.videoQuality.value().push_back(Firebolt::Entertainment::WayToWatchVideoQuality::HD);
        wayToWatch.audioProfile.push_back(Firebolt::Types::AudioProfile::DOLBY_DIGITAL_7_1_PLUS);
        wayToWatch.audioLanguages = std::make_optional<std::vector<std::string>>();
        wayToWatch.audioLanguages.value().push_back("de");
        wayToWatch.closedCaptions = std::make_optional<std::vector<std::string>>();
        wayToWatch.closedCaptions.value().push_back("de");
        wayToWatch.subtitles = std::make_optional<std::vector<std::string>>();
        wayToWatch.subtitles.value().push_back("de");
        wayToWatch.audioDescriptions = std::make_optional<std::vector<std::string>>();
        wayToWatch.audioDescriptions.value().push_back("de");
        entityInfo.waysToWatch.value().push_back(wayToWatch);
        result.related.value().push_back(entityInfo);
    }

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().entityInfo(result, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery EntityInfo is " << (status ? "true" : "false") << endl;
    } else {
        cout << "Discovery EntityInfo status = " << static_cast<int>(error) << endl;
    }
}
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
        cout << "Discovery Watched status = " << static_cast<int>(error) << endl;
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
        cout << "Discovery Watched Reduced status = " << static_cast<int>(error) << endl;
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
    images = "\"3x4\": {\"en-US\": \"https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg\", \"es\": \"https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg\"}, \"16x9\": {\"en\": \"https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg\"}";

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().watchNext(title, identifiers, expires, images, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery Watched Next is " << (status ? "true" : "false") << endl;
    } else {
        cout << "Discovery Watched Next status = " << static_cast<int>(error) << endl;
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
        cout << "Discovery Policy status = " << static_cast<int>(error) << endl;
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
    entityInfo.entityType = "program";
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
    //result.entries.push_back(entityInfo);

    bool status = Firebolt::IFireboltAccessor::Instance().DiscoveryInterface().purchasedContent(result, &error);
    if (error == Firebolt::Error::None) {
        cout << "Discovery PurchasedContent is " << (status ? "true" : "false") << endl;
    } else {
        cout << "Discovery PurchasedContent status = " << static_cast<int>(error) << endl;
    }
}
