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

#include "CoreClientTest.h"
#include "Firebolt/config.h"
#include <iomanip>
#include <stdexcept>
#include <string>
#include <unistd.h>

using namespace std;
bool CoreClientTest::_connected;
std::map<CoreClientTest::Subscriptions, uint64_t> CoreClientTest::_subscriptionIds{};

template <typename T> inline std::string toError(const Firebolt::Result<T>& result)
{
  if (result) {
      return "";
  }
  return "Error: " + std::to_string(static_cast<int>(result.error()));
}

void CoreClientTest::ConnectionChanged(const bool connected, const Firebolt::Error error)
{
    cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << endl;
    _connected = connected;
}

void CoreClientTest::CreateFireboltInstance(const std::string& url)
{
    Firebolt::Config config;
    config.wsUrl = url;
    config.waitTime_ms = 1000;
    config.log.level = Firebolt::LogLevel::Info;

    _connected = false;
    Firebolt::IFireboltAccessor::Instance().Connect(config, ConnectionChanged);
}

void CoreClientTest::DestroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
}

bool CoreClientTest::WaitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (_connected == false))
    {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return _connected;
}

template <typename T> using EnumMap = std::unordered_map<T, string>;
template <typename T> inline const string& ConvertFromEnum(EnumMap<T> enumMap, T type)
{
    return enumMap[type];
}
template <typename T> inline const T ConvertToEnum(EnumMap<T> enumMap, const string& str)
{
    T value;
    for (auto element : enumMap)
    {
        if (element.second == str)
        {
            value = element.first;
            break;
        }
    }
    return value;
}

void CoreClientTest::GetLocalizationCountryCode()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().countryCode();

    if (result)
    {
        cout << "Get LocalizationCountryCode = " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetLocalizationCountryCode failed. " + toError(result));
    }
}

void CoreClientTest::GetLocalizationPreferredAudioLanguages()
{
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().preferredAudioLanguages();

    if (result)
    {
        cout << "Get LocalizationPregetPreferredAudioLanguages = [\n";
        for (const auto& localization : *result)
        {
            std::cout << localization << endl;
        }
        std::cout << "]\n";
    }
    else
    {
        throw std::runtime_error("GetLocalizationPregetPreferredAudioLanguages failed. " + toError(result));
    }
}

void CoreClientTest::SubscribeOnLocalizationCountryCodeChanged()
{
    auto subscriptionId = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnCountryCodeChanged(
        [](const auto&) { std::cout << "LocalizationCountryCode changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LocalizationCountryCode change is success" << endl;
        _subscriptionIds[Subscriptions::LocalizationCountryCodeChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LocalizationCountryCode failed. " + toError(subscriptionId));
    }
}

void CoreClientTest::UnsubscribeOnLocalizationCountryCodeChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LocalizationCountryCodeChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LocalizationCountryCode" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LocalizationCountryCode is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LocalizationCountryCode failed. " + toError(result));
    }
}

void CoreClientTest::SubscribeOnLocalizationPreferredAudioLanguagesChanged()
{
    auto subscriptionId =
        Firebolt::IFireboltAccessor::Instance().LocalizationInterface().subscribeOnPreferredAudioLanguagesChanged(
            [](const auto&) { std::cout << "LocalizationPreferredAudioLanguages changed\n"; });
    if (subscriptionId)
    {
        cout << "Subscribe LocalizationPreferredAudioLanguages change is success" << endl;
        _subscriptionIds[Subscriptions::LocalizationPreferredAudioLanguagesChanged] = subscriptionId.value();
    }
    else
    {
        throw std::runtime_error("Subscribe LocalizationPreferredAudioLanguages failed. " + toError(subscriptionId));
    }
}

void CoreClientTest::UnsubscribeOnLocalizationPreferredAudioLanguagesChanged()
{
    const auto subscriptionIter = _subscriptionIds.find(Subscriptions::LocalizationPreferredAudioLanguagesChanged);
    if (subscriptionIter == _subscriptionIds.end())
    {
        cout << "Not subscribed for LocalizationPreferredAudioLanguages" << endl;
        return;
    }
    auto result = Firebolt::IFireboltAccessor::Instance().LocalizationInterface().unsubscribe(subscriptionIter->second);
    if (result.error() == Firebolt::Error::None)
    {
        cout << "Unsubscribe LocalizationPreferredAudioLanguages is success" << endl;
        _subscriptionIds.erase(subscriptionIter);
    }
    else
    {
        throw std::runtime_error("Unsubscribe LocalizationPreferredAudioLanguages failed. " + toError(result));
    }
}

void CoreClientTest::MetricsReady()
{
    auto result = Firebolt::IFireboltAccessor::Instance().MetricsInterface().ready();
    if (result)
    {
        cout << "MetricsReady is a success: " << *result << endl;
    }
    else
    {
        throw std::runtime_error("MetricsReady failed. " + toError(result));
    }
}

void CoreClientTest::ClearSecureStorage()
{
    auto result = Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().clear(
        Firebolt::SecureStorage::StorageScope::ACCOUNT);

    if (Firebolt::Error::None == result.error())
    {
        cout << "ClearSecureStorage is a success" << endl;
    }
    else
    {
        throw std::runtime_error("ClearSecureStorage failed. " + toError(result));
    }
}

void CoreClientTest::GetSecureStorage()
{
    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().get(Firebolt::SecureStorage::StorageScope::DEVICE,
                                                                             "authRefreshToken");

    if (result)
    {
        cout << "GetSecureStorage is a success: " << *result << endl;
    }
    else
    {
        throw std::runtime_error("GetSecureStorage failed. " + toError(result));
    }
}

void CoreClientTest::RemoveSecureStorage()
{
    auto result =
        Firebolt::IFireboltAccessor::Instance().SecureStorageInterface().remove(Firebolt::SecureStorage::StorageScope::DEVICE,
                                                                                "authRefreshToken");

    if (Firebolt::Error::None == result.error())
    {
        cout << "RemoveSecureStorage is a success" << endl;
    }
    else
    {
        throw std::runtime_error("RemoveSecureStorage failed. " + toError(result));
    }
}

void CoreClientTest::SetSecureStorage()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .set(Firebolt::SecureStorage::StorageScope::DEVICE, "authRefreshToken",
                           "VGhpcyBub3QgYSByZWFsIHRva2VuLgo", Firebolt::SecureStorage::StorageOptions{600});

    if (Firebolt::Error::None == result.error())
    {
        cout << "SetSecureStorage is a success" << endl;
    }
    else
    {
        throw std::runtime_error("SetSecureStorage failed. " + toError(result));
    }
}

void CoreClientTest::SetSecureStorageForApp()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .setForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT, "authRefreshToken",
                                 "VGhpcyBub3QgYSByZWFsIHRva2VuLgo", Firebolt::SecureStorage::StorageOptions{600});

    if (Firebolt::Error::None == result.error())
    {
        cout << "SetSecureStorageForApp is a success" << endl;
    }
    else
    {
        throw std::runtime_error("SetSecureStorageForApp failed. " + toError(result));
    }
}

void CoreClientTest::RemoveSecureStorageForApp()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .removeForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT, "authRefreshToken");

    if (Firebolt::Error::None == result.error())
    {
        cout << "RemoveSecureStorageForApp is a success" << endl;
    }
    else
    {
        throw std::runtime_error("RemoveSecureStorageForApp failed. " + toError(result));
    }
}

void CoreClientTest::ClearSecureStorageForApp()
{
    auto result = Firebolt::IFireboltAccessor::Instance()
                      .SecureStorageInterface()
                      .clearForApp("foo", Firebolt::SecureStorage::StorageScope::ACCOUNT);

    if (Firebolt::Error::None == result.error())
    {
        cout << "ClearSecureStorageForApp is a success" << endl;
    }
    else
    {
        throw std::runtime_error("ClearSecureStorageForApp failed. " + toError(result));
    }
}
