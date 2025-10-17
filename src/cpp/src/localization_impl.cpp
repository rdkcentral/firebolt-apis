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

#include "localization_impl.h"
#include <TypesPriv.h>

namespace Firebolt::Localization
{
LocalizationImpl::LocalizationImpl(Firebolt::Helpers::IHelper &helper) : helper_(helper) {}

Result<std::string> LocalizationImpl::countryCode() const
{
    return helper_.get<FireboltSDK::JSON::String, std::string>("localization.countryCode");
}

Result<std::vector<std::string>> LocalizationImpl::preferredAudioLanguages() const
{
    return helper_.get<FireboltSDK::JSON::NL_Json_Array<FireboltSDK::JSON::String, std::string>, std::vector<std::string>>(
        "localization.preferredAudioLanguages");
}

Result<SubscriptionId>
LocalizationImpl::subscribeOnCountryCodeChanged(std::function<void(const std::string&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::String>("localization.onCountryCodeChanged", std::move(notification));
}

Result<SubscriptionId> LocalizationImpl::subscribeOnPreferredAudioLanguagesChanged(
    std::function<void(const std::vector<std::string>&)>&& notification)
{
    return helper_.subscribe<FireboltSDK::JSON::NL_Json_Array<
        FireboltSDK::JSON::String, std::string>>("localization.onPreferredAudioLanguagesChanged",
                                                 std::move(notification));
}

Result<void> LocalizationImpl::unsubscribe(SubscriptionId id)
{
    return helper_.unsubscribe(id);
}

void LocalizationImpl::unsubscribeAll()
{
    helper_.unsubscribeAll();
}
} // namespace Firebolt::Localization
