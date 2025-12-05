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
#include <firebolt/json_types.h>

namespace Firebolt::Localization
{
LocalizationImpl::LocalizationImpl(Firebolt::Helpers::IHelper& helper)
    : helper_(helper),
      subscriptionManager_(helper, this)
{
}

Result<std::string> LocalizationImpl::country() const
{
    return helper_.get<Firebolt::JSON::String, std::string>("Localization.country");
}

Result<std::vector<std::string>> LocalizationImpl::preferredAudioLanguages() const
{
    return helper_.get<Firebolt::JSON::NL_Json_Array<Firebolt::JSON::String, std::string>, std::vector<std::string>>(
        "Localization.preferredAudioLanguages");
}

Result<std::string> LocalizationImpl::presentationLanguage() const
{
    return helper_.get<Firebolt::JSON::String, std::string>("Localization.presentationLanguage");
}

Result<SubscriptionId> LocalizationImpl::subscribeOnCountryChanged(std::function<void(const std::string&)>&& notification)
{
    return subscriptionManager_.subscribe<Firebolt::JSON::String>("Localization.onCountryChanged",
                                                                  std::move(notification));
}

Result<SubscriptionId> LocalizationImpl::subscribeOnPreferredAudioLanguagesChanged(
    std::function<void(const std::vector<std::string>&)>&& notification)
{
    return subscriptionManager_.subscribe<Firebolt::JSON::NL_Json_Array<
        Firebolt::JSON::String, std::string>>("Localization.onPreferredAudioLanguagesChanged", std::move(notification));
}

Result<SubscriptionId>
LocalizationImpl::subscribeOnPresentationLanguageChanged(std::function<void(const std::string&)>&& notification)
{
    return subscriptionManager_.subscribe<Firebolt::JSON::String>("Localization.onPresentationLanguageChanged",
                                                                  std::move(notification));
}

Result<void> LocalizationImpl::unsubscribe(SubscriptionId id)
{
    return subscriptionManager_.unsubscribe(id);
}

void LocalizationImpl::unsubscribeAll()
{
    subscriptionManager_.unsubscribeAll();
}
} // namespace Firebolt::Localization
