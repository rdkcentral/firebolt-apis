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

#include "helpers.h"
#include "localization.h"

namespace Firebolt::Localization
{
class LocalizationImpl : public ILocalization
{
public:
    LocalizationImpl(Firebolt::Helpers::Helper &helper);
    LocalizationImpl(const LocalizationImpl&) = delete;
    LocalizationImpl& operator=(const LocalizationImpl&) = delete;

    ~LocalizationImpl() override = default;

    // Methods
    Result<std::string> countryCode() const override;
    Result<std::vector<std::string>> preferredAudioLanguages() const override;

    // Events
    Result<SubscriptionId> subscribeOnCountryCodeChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnPreferredAudioLanguagesChanged(
        std::function<void(const std::vector<std::string>&)>&& notification) override;

    Result<void> unsubscribe(SubscriptionId id) override;
    void unsubscribeAll() override;

private:
    Firebolt::Helpers::Helper &helper_;
};

} // namespace Firebolt::Localization
