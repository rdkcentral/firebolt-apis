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

#include <firebolt/types.h>
#include <functional>
#include <optional>
#include <vector>

namespace Firebolt::Localization
{

class ILocalization
{
public:
    virtual ~ILocalization() = default;

    // Methods
    /**
     * @brief Get the ISO 3166-1 alpha-2 code for the country device is located in.
     *
     * @retval The device country code or error
     */
    virtual Result<std::string> country() const = 0;

    /**
     * @brief A list of zero or more languages in order of decreasing preference.  Typically two languages are present.
     * A language may be repeated in the list
     *
     * @retval The preferred audio languages or error
     */
    virtual Result<std::vector<std::string>> preferredAudioLanguages() const = 0;

    /**
     * @brief The presentation language of the device, in BCP 47, e.g. en-US
     *
     * @retval The preferred audio languages or error
     */
    virtual Result<std::string> presentationLanguage() const = 0;

    // Events
    /**
     * @brief Subscribe on the change of countryChanged property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnCountryChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of PreferredAudioLanguagesChanged property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnPreferredAudioLanguagesChanged(std::function<void(const std::vector<std::string>&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of PresentationLanguageChanged property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnPresentationLanguageChanged(std::function<void(const std::string&)>&& notification) = 0;
    
    /**
     * @brief  Subscribe on the change of presentationLanguage property
     *
     * @param[in] id                  : The subscription id
     *
     * @retval The status
     */
    virtual Result<void> unsubscribe(SubscriptionId id) = 0;

    /**
     * @brief Remove all active subscriptions from subscribers list.
     */
    virtual void unsubscribeAll() = 0;
};
} // namespace Firebolt::Localization
