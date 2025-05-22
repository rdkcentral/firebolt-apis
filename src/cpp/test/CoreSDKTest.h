/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
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
 */

#pragma once

#include "firebolt.h"
#include <iostream>
#include <map>

class CoreSDKTest
{
public:
    CoreSDKTest() = default;
    virtual ~CoreSDKTest() = default;

    static void CreateFireboltInstance(const std::string& url);
    static void DestroyFireboltInstance();

    // ClosedCaptions
    static void GetClosedCaptionsBackgroundOpacity();
    static void SetClosedCaptionsBackgroundOpacity();
    static void SubscribeClosedCaptionsBackgroundOpacityChanged();
    static void UnsubscribeClosedCaptionsBackgroundOpacityChanged();

    static void GetClosedCaptionsFontFamily();
    static void SetClosedCaptionsFontFamily();
    static void SubscribeClosedCaptionsFontFamilyChanged();
    static void UnsubscribeClosedCaptionsFontFamilyChanged();

    // Device
    static void GetDeviceName();
    static void GetDeviceVersion();
    static void SubscribeDeviceNameChanged();
    static void UnsubscribeDeviceNameChanged();
    static void GetDeviceModel();
    static void GetDeviceSku();
    static void GetDeviceAudio();
    static void SubscribeDeviceAudioChanged();
    static void UnsubscribeDeviceAudioChanged();
    static void GetDeviceScreenResolution();
    static void SubscribeDeviceScreenResolutionChanged();
    static void UnsubscribeDeviceScreenResolutionChanged();

    // HdmiInput
    static void SubscribeHdmiAutoLowLatencyModeCapableChanged();
    static void UnsubscribeHdmiAutoLowLatencyModeCapableChanged();
    static void GetAutoLowLatencyModeCapable();
    static void SetAutoLowLatencyModeCapable();
    static void GetEdidVersion();
    static void SetEdidVersion();
    static void GetHdmiPortInfo();

    // Lifecycle
    static void LifecycleReady();
    static void LifecycleClose();
    static void LifecycleFinished();
    static void LifecycleState();
    static void SubscribeOnLifecycleBackgroundChanged();
    static void UnsubscribeOnLifecycleBackgroundChanged();
    static void SubscribeOnLifecycleForegroundChanged();
    static void UnsubscribeOnLifecycleForegroundChanged();
    static void SubscribeOnLifecycleInactiveChanged();
    static void UnsubscribeOnLifecycleInactiveChanged();
    static void SubscribeOnLifecycleSuspendedChanged();
    static void UnsubscribeOnLifecycleSuspendedChanged();
    static void SubscribeOnLifecycleUnloadingChanged();
    static void UnsubscribeOnLifecycleUnloadingChanged();

    // Localization
    static void GetLocalizationCountryCode();
    static void GetLocalizationPreferredAudioLanguages();
    static void SubscribeOnLocalizationCountryCodeChanged();
    static void UnsubscribeOnLocalizationCountryCodeChanged();
    static void SubscribeOnLocalizationPreferredAudioLanguagesChanged();
    static void UnsubscribeOnLocalizationPreferredAudioLanguagesChanged();

    // Metrics
    static void MetricsReady();

    // SecureStorage
    static void ClearSecureStorage();
    static void GetSecureStorage();
    static void RemoveSecureStorage();
    static void SetSecureStorage();
    static void SetSecureStorageForApp();
    static void RemoveSecureStorageForApp();
    static void ClearSecureStorageForApp();

    static bool WaitOnConnectionReady();

private:
    static void ConnectionChanged(const bool, const Firebolt::Error);
    static bool _connected;

    enum class Subscriptions
    {
        ClosedCaptionsOpacity,
        ClosedCaptionsFontFamily,
        ContentDecryptionWatermarkStatus,
        DeviceName,
        DeviceAudio,
        DeviceScreenResolution,
        HdmiInputAutoLowLatencyModeCapable,
        LifecycleBackgroundChanged,
        LifecycleForegroundChanged,
        LifecycleInactiveChanged,
        LifecycleSuspendedChanged,
        LifecycleUnloadingChanged,
        LocalizationCountryCodeChanged,
        LocalizationPreferredAudioLanguagesChanged
    };

    static std::map<Subscriptions, uint64_t> _subscriptionIds;
};
