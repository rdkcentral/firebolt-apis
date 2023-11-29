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
CoreSDKTest::OnDeviceNameChangedNotification CoreSDKTest::_deviceNameChangedNotification;
CoreSDKTest::OnAudioChangedNotification CoreSDKTest::_audioChangedNotification;
CoreSDKTest::OnScreenResolutionChangedNotification CoreSDKTest::_screenResolutionChangedNotification;
CoreSDKTest::OnClosedCaptionsSettingsChangedNotification CoreSDKTest::_closedCaptionsSettingsChangedNotification;
CoreSDKTest::OnPreferredAudioLanguagesChangedNotification CoreSDKTest::_preferredAudioLanguagesChangedNotification;
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

void CoreSDKTest::GetDeviceSKU()
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

