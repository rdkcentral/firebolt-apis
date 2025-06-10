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

#include "FireboltSDK.h"
#include "common/types.h"
#include "error.h"
#include <any>
#include <map>
#include <mutex>
#include <optional>
#include <type_traits>

namespace Firebolt
{
class Parameters
{
public:
    Parameters() = default;
    Parameters(const std::vector<std::string>& value);
    template <typename T> Parameters(const T& param)
    {
        object_.Set(_T("value"), WPEFramework::Core::JSON::Variant{param});
    }
    ~Parameters() = default;

    Parameters& add(const char* paramName, const WPEFramework::Core::JSON::Variant& param);

    template <typename T> Parameters& add(const char* paramName, const std::optional<T>& param)
    {
        if (param.has_value())
        {
            object_.Set(paramName, WPEFramework::Core::JSON::Variant{param.value()});
        }
        return *this;
    }

    template <typename JsonType, typename ParamType> Parameters& add(const char* paramName, const ParamType& param)
    {
        object_.Set(paramName, JsonType{param}.Data());
        return *this;
    }

    template <typename JsonType, typename ParamType>
    Parameters& add(const char* paramName, const std::optional<ParamType>& param)
    {
        if (param.has_value())
        {
            object_.Set(paramName, JsonType{param.value()}.Data());
        }
        return *this;
    }
    JsonObject operator()() const;

private:
    JsonObject object_;
};

// Helper type traits for get function
template <typename T> struct IsVector
{
    static const bool value = false;
};
template <typename T> struct IsVector<std::vector<T>>
{
    static const bool value = true;
};

template <typename JsonType, typename PropertyType>
std::enable_if_t<!IsVector<PropertyType>::value, Result<PropertyType>> get(const string& methodName)
{
    JsonType jsonResult;
    Error status = FireboltSDK::Properties::Get(methodName, jsonResult);
    if (status == Error::None)
    {
        return Result<PropertyType>{jsonResult.Value()};
    }
    return Result<PropertyType>{status};
}

template <typename JsonType, typename PropertyType>
std::enable_if_t<!IsVector<PropertyType>::value, Result<PropertyType>> get(const string& methodName,
                                                                           const Parameters& parameters)
{
    JsonType jsonResult;
    Error status = FireboltSDK::Properties::Get(methodName, parameters(), jsonResult);
    if (status == Error::None)
    {
        return Result<PropertyType>{jsonResult.Value()};
    }
    return Result<PropertyType>{status};
}

// specialised version for containers
template <typename JsonType, typename PropertyType>
inline std::enable_if_t<IsVector<PropertyType>::value, Result<PropertyType>> get(const std::string& methodName)
{
    WPEFramework::Core::JSON::ArrayType<JsonType> jsonResult;
    Firebolt::Error status = FireboltSDK::Properties::Get(methodName, jsonResult);
    if (status == Firebolt::Error::None)
    {
        Result<PropertyType> result{PropertyType{}};
        auto index(jsonResult.Elements());
        while (index.Next() == true)
        {
            result->push_back(index.Current().Value());
        }
        return result;
    }
    return Result<PropertyType>{status};
}

Result<void> set(const string& methodName, const Parameters& parameters);

template <typename JsonType, typename PropertyType>
inline std::enable_if_t<!std::is_void<PropertyType>::value && !IsVector<PropertyType>::value, Result<PropertyType>>
invoke(const string& methodName, const Parameters& parameters)
{
    FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport =
        FireboltSDK::Accessor::Instance().GetTransport();
    if (!transport)
    {
        return Result<PropertyType>{Firebolt::Error::NotConnected};
    }
    JsonType jsonResult;
    auto callStatus{transport->Invoke(methodName, parameters(), jsonResult)};
    if (Error::None == callStatus)
    {
        return Result<PropertyType>{jsonResult.Value()};
    }
    return Result<PropertyType>{callStatus};
}

Result<void> invoke(const string& methodName, const Parameters& parameters);

// Specialised version for containers
template <typename JsonType, typename PropertyType>
inline std::enable_if_t<IsVector<PropertyType>::value, Result<PropertyType>> invoke(const string& methodName,
                                                                                    const Parameters& parameters)
{
    FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport =
        FireboltSDK::Accessor::Instance().GetTransport();
    if (!transport)
    {
        return Result<PropertyType>{Firebolt::Error::NotConnected};
    }
    WPEFramework::Core::JSON::ArrayType<JsonType> jsonResult;
    auto callStatus{transport->Invoke(methodName, parameters(), jsonResult)};
    if (Error::None == callStatus)
    {
        Result<PropertyType> result{PropertyType{}};
        auto index(jsonResult.Elements());
        while (index.Next() == true)
        {
            result->push_back(index.Current().Value());
        }
        return result;
    }
    return Result<PropertyType>{callStatus};
}

struct SubscriptionData
{
    string eventName;
    std::any notification;
};

template <typename JsonType, typename PropertyType>
void onPropertyChangedCallback(void* subscriptionDataPtr, const void* userData, void* jsonResponse)
{
    WPEFramework::Core::ProxyType<JsonType>& proxyResponse =
        *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonType>*>(jsonResponse));

    ASSERT(proxyResponse.IsValid() == true);

    if (proxyResponse.IsValid() == true)
    {
        auto changedProperty = proxyResponse->Value();
        proxyResponse.Release();
        SubscriptionData* subscriptionData = reinterpret_cast<SubscriptionData*>(subscriptionDataPtr);
        std::function<void(PropertyType)> notifier =
            std::any_cast<std::function<void(PropertyType)>>(subscriptionData->notification);
        notifier(changedProperty);
    }
}

// specialised callback for properties
template <typename JsonType, typename PropertyType>
inline void onContainerPropertyChangedCallback(void* subscriptionDataPtr, const void* userData, void* jsonResponse)
{
    WPEFramework::Core::ProxyType<WPEFramework::Core::JSON::ArrayType<JsonType>>& proxyResponse =
        *(reinterpret_cast<WPEFramework::Core::ProxyType<WPEFramework::Core::JSON::ArrayType<JsonType>>*>(jsonResponse));

    ASSERT(proxyResponse.IsValid() == true);

    if (proxyResponse.IsValid() == true)
    {
        std::vector<PropertyType> values;

        auto index(proxyResponse->Elements());
        while (index.Next() == true)
        {
            values.push_back(index.Current().Value());
        }
        proxyResponse.Release();

        SubscriptionData* subscriptionData = reinterpret_cast<SubscriptionData*>(subscriptionDataPtr);
        std::function<void(const std::vector<PropertyType>&)> notifier =
            std::any_cast<std::function<void(const std::vector<PropertyType>&)>>(subscriptionData->notification);
        notifier(values);
    }
}

class SubscriptionHelper
{
public:
    void unsubscribeAll();

protected:
    SubscriptionHelper() = default;
    virtual ~SubscriptionHelper();

    Result<void> unsubscribe(SubscriptionId id);
    template <typename JsonType, typename PropertyType>
    Result<SubscriptionId> subscribe(const string& eventName, std::function<void(PropertyType)>&& notification)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        subscriptions_[currentId_] = SubscriptionData{eventName, std::move(notification)};
        JsonObject jsonParameters;
        void* notificationPtr = reinterpret_cast<void*>(&subscriptions_[currentId_]);
        Error status =
            FireboltSDK::Event::Instance().Subscribe<JsonType>(eventName, jsonParameters,
                                                               onPropertyChangedCallback<JsonType, PropertyType>,
                                                               notificationPtr, nullptr);
        if (Error::None == status)
        {
            return Result<SubscriptionId>{currentId_++};
        }
        subscriptions_.erase(currentId_);
        return Result<SubscriptionId>{status};
    }

    // Specialised version for containers
    template <typename JsonType, typename PropertyType>
    Result<SubscriptionId> subscribe(const string& eventName,
                                     std::function<void(const std::vector<PropertyType>&)>&& notification)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        subscriptions_[currentId_] = SubscriptionData{eventName, std::move(notification)};
        JsonObject jsonParameters;
        void* notificationPtr = reinterpret_cast<void*>(&subscriptions_[currentId_]);
        Error status =
            FireboltSDK::Event::Instance().Subscribe<JsonType>(eventName, jsonParameters,
                                                               onContainerPropertyChangedCallback<JsonType, PropertyType>,
                                                               notificationPtr, nullptr);
        if (Error::None == status)
        {
            return Result<SubscriptionId>{currentId_++};
        }
        subscriptions_.erase(currentId_);
        return Result<SubscriptionId>{status};
    }

private:
    std::mutex mutex_;
    std::map<uint64_t, SubscriptionData> subscriptions_;
    uint64_t currentId_{0};
};
} // namespace Firebolt
