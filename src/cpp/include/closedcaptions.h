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

#include "common/accessibility.h"
#include <functional>
#include <optional>
#include <string>
#include <types/fb-errors.h>
#include <types/types.h>
#include <vector>

namespace Firebolt::ClosedCaptions
{

class IClosedCaptions
{
public:
    virtual ~IClosedCaptions() = default;

    // Methods
    /**
     * @brief The preferred background color for displaying closed-captions
     *
     * @retval The backgroundColor property or error
     */
    virtual Result<std::string> backgroundColor() const = 0;

    /**
     * @brief The preferred opacity for displaying closed-captions backgrounds.
     *
     * @retval The backgroundOpacity property or error
     */
    virtual Result<unsigned> backgroundOpacity() const = 0;

    /**
     * @brief Whether or not closed-captions are enabled.
     *
     * @retval The enabled property or error
     */
    virtual Result<bool> enabled() const = 0;

    /**
     * @brief The preferred font color for displaying closed-captions.
     *
     * @retval The fontColor property or error
     */
    virtual Result<std::string> fontColor() const = 0;

    /**
     * @brief The preferred font edge style for displaying closed-captions.
     *
     * @retval The fontEdge property or error
     */
    virtual Result<Accessibility::FontEdge> fontEdge() const = 0;

    /**
     * @brief The preferred font edge color for displaying closed-captions.
     *
     * @retval The fontEdgeColor property or error
     */
    virtual Result<std::string> fontEdgeColor() const = 0;

    /**
     * @brief The preferred font family for displaying closed-captions.
     *
     * @retval The fontFamily property or error
     */
    virtual Result<Accessibility::FontFamily> fontFamily() const = 0;

    /**
     * @brief The preferred opacity for displaying closed-captions characters.
     *
     * @retval The fontOpacity property or error
     */
    virtual Result<unsigned> fontOpacity() const = 0;

    /**
     * @brief The preferred font size for displaying closed-captions.
     *
     * @retval The fontSize property or error
     */
    virtual Result<float> fontSize() const = 0;

    /**
     * @brief A prioritized list of ISO 639-2/B codes for the preferred closed
     *        captions languages on this device.
     *
     * @retval The preferredLanguages property or error
     */
    virtual Result<std::vector<std::string>> preferredLanguages() const = 0;

    /**
     * @brief The preferred horizontal alignment for displaying closed-captions
     *        characters.
     *
     * @retval The textAlign property or error
     */
    virtual Result<std::string> textAlign() const = 0;

    /**
     * @brief The preferred horizontal alignment for displaying closed-captions
     *        characters.
     *
     * @retval The textAlignVertical property or error
     */
    virtual Result<std::string> textAlignVertical() const = 0;

    /**
     * @brief The preferred window color for displaying closed-captions, .
     *
     * @retval The windowColor property or error
     */
    virtual Result<std::string> windowColor() const = 0;

    /**
     * @brief The preferred window opacity for displaying closed-captions
     *        backgrounds.
     *
     * @retval The windowOpacity property or error
     */
    virtual Result<unsigned> windowOpacity() const = 0;

    /**
     * @brief Set The preferred background color for displaying
     *        closed-captions, .
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setBackgroundColor(const std::string& value) = 0;

    /**
     * @brief Set The preferred opacity for displaying closed-captions
     *        backgrounds.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setBackgroundOpacity(const unsigned value) = 0;

    /**
     * @brief Set Whether or not closed-captions are enabled.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setEnabled(const bool value) = 0;

    /**
     * @brief Set The preferred font color for displaying closed-captions.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setFontColor(const std::string& value) = 0;

    /**
     * @brief Set The preferred font edge style for displaying closed-captions.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setFontEdge(const Accessibility::FontEdge& value) = 0;

    /**
     * @brief Set The preferred font edge color for displaying closed-captions.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setFontEdgeColor(const std::string& value) = 0;

    /**
     * @brief Set The preferred font family for displaying closed-captions.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setFontFamily(const Accessibility::FontFamily& value) = 0;

    /**
     * @brief Set The preferred opacity for displaying closed-captions characters.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setFontOpacity(const unsigned value) = 0;

    /**
     * @brief Set The preferred font size for displaying closed-captions.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setFontSize(const float value) = 0;

    /**
     * @brief Set A prioritized list of ISO 639-2/B codes for the preferred closed
     *        captions languages on this device.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setPreferredLanguages(const std::vector<std::string>& value) = 0;

    /**
     * @brief Set The preferred horizontal alignment for displaying
     *        closed-captions characters.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setTextAlign(const std::string& value) = 0;

    /**
     * @brief Set The preferred horizontal alignment for displaying
     *        closed-captions characters.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setTextAlignVertical(const std::string& value) = 0;

    /**
     * @brief Set The preferred window color for displaying closed-captions, .
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setWindowColor(const std::string& value) = 0;

    /**
     * @brief Set The preferred window opacity for displaying closed-captions
     *        backgrounds.
     *
     * @param[in] value                  : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setWindowOpacity(const unsigned value) = 0;

    // Events
    /**
     * @brief Subscribe on the change of BackgroundColor property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnBackgroundColorChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of BackgroundOpacity property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnBackgroundOpacityChanged(std::function<void(unsigned)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Enabled property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnEnabledChanged(std::function<void(bool)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of FontColor property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnFontColorChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of FontEdge property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnFontEdgeChanged(std::function<void(const Accessibility::FontEdge&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of FontEdgeColor property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnFontEdgeColorChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of FontFamily property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnFontFamilyChanged(std::function<void(const Accessibility::FontFamily&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of FontOpacity property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnFontOpacityChanged(std::function<void(unsigned)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of FontSize property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnFontSizeChanged(std::function<void(float)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of PreferredLanguages property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnPreferredLanguagesChanged(std::function<void(const std::vector<std::string>&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of TextAlign property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnTextAlignChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of TextAlignVertical property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnTextAlignVerticalChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of WindowColor property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnWindowColorChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of WindowOpacity property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnWindowOpacityChanged(std::function<void(unsigned)>&& notification) = 0;

    /**
     * @brief Remove subscriber from subscribers list. This method is generic for
     *        all subscriptions
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
} // namespace Firebolt::ClosedCaptions
