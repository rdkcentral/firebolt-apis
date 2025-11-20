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

class CoreClientTest
{
public:
    CoreClientTest() = default;
    virtual ~CoreClientTest() = default;

    static void CreateFireboltInstance(const std::string& url);
    static void DestroyFireboltInstance();

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
        DeviceName,
        DeviceAudio,
        DeviceScreenResolution,
        LocalizationCountryCodeChanged,
        LocalizationPreferredAudioLanguagesChanged
    };

    static std::map<Subscriptions, uint64_t> _subscriptionIds;
};
