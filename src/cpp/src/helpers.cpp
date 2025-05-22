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

#include "helpers.h"

namespace Firebolt
{
Parameters::Parameters(const std::vector<std::string>& value)
{
    WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Variant> valueArray;
    for (auto& element : value)
    {
        valueArray.Add() = element;
    }
    WPEFramework::Core::JSON::Variant valueVariant;
    valueVariant.Array(valueArray);
    object_.Set(_T("value"), valueVariant);
}

Parameters& Parameters::add(const char* paramName, const WPEFramework::Core::JSON::Variant& param)
{
    object_.Set(paramName, param);
    return *this;
}

JsonObject Parameters::operator()() const
{
    return object_;
}

Result<void> set(const string& methodName, const Parameters& parameters)
{
    return Result<void>{FireboltSDK::Properties::Set(methodName, parameters())};
}

Result<void> invoke(const string& methodName, const Parameters& parameters)
{
    FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport =
        FireboltSDK::Accessor::Instance().GetTransport();
    if (!transport)
    {
        return Result<void>{Firebolt::Error::NotConnected};
    }
    WPEFramework::Core::JSON::VariantContainer result;
    return Result<void>{transport->Invoke(methodName, parameters(), result)};
}

SubscriptionHelper::~SubscriptionHelper()
{
    unsubscribeAll();
}

void SubscriptionHelper::unsubscribeAll()
{
    for (auto& subscription : subscriptions_)
    {
        FireboltSDK::Event::Instance().Unsubscribe(subscription.second.eventName, &subscription.second);
    }
    subscriptions_.clear();
}

Result<void> SubscriptionHelper::unsubscribe(uint64_t id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = subscriptions_.find(id);
    if (it == subscriptions_.end())
    {
        return Result<void>{Error::General};
    }
    auto errorStatus{FireboltSDK::Event::Instance().Unsubscribe(it->second.eventName, &it->second)};
    subscriptions_.erase(it);
    return Result<void>{errorStatus};
}
} // namespace Firebolt
