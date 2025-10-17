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

#include "closedcaptions.h"
#include "helpers.h"
#include "jsondata_accessibility.h"

namespace Firebolt::ClosedCaptions
{
class ClosedCaptionsImpl : public IClosedCaptions, public Firebolt::Helpers::SubscriptionHelper
{
public:
    explicit ClosedCaptionsImpl(Firebolt::Helpers::IHelper &helper);
    ClosedCaptionsImpl(const ClosedCaptionsImpl&) = delete;
    ClosedCaptionsImpl& operator=(const ClosedCaptionsImpl&) = delete;

    ~ClosedCaptionsImpl() override = default;

    // Methods
    Result<std::string> backgroundColor() const override;
    Result<unsigned> backgroundOpacity() const override;
    Result<bool> enabled() const override;
    Result<std::string> fontColor() const override;
    Result<Accessibility::FontEdge> fontEdge() const override;
    Result<std::string> fontEdgeColor() const override;
    Result<Accessibility::FontFamily> fontFamily() const override;
    Result<unsigned> fontOpacity() const override;
    Result<float> fontSize() const override;
    Result<std::vector<std::string>> preferredLanguages() const override;
    Result<std::string> textAlign() const override;
    Result<std::string> textAlignVertical() const override;
    Result<std::string> windowColor() const override;
    Result<unsigned> windowOpacity() const override;

    Result<void> setBackgroundColor(const std::string& value) override;
    Result<void> setBackgroundOpacity(const unsigned value) override;
    Result<void> setEnabled(const bool value) override;
    Result<void> setFontColor(const std::string& value) override;
    Result<void> setFontEdge(const Accessibility::FontEdge& value) override;
    Result<void> setFontEdgeColor(const std::string& value) override;
    Result<void> setFontFamily(const Accessibility::FontFamily& value) override;
    Result<void> setFontOpacity(const unsigned value) override;
    Result<void> setFontSize(const float value) override;
    Result<void> setPreferredLanguages(const std::vector<std::string>& value) override;
    Result<void> setTextAlign(const std::string& value) override;
    Result<void> setTextAlignVertical(const std::string& value) override;
    Result<void> setWindowColor(const std::string& value) override;
    Result<void> setWindowOpacity(const unsigned value) override;

    // Events
    Result<SubscriptionId> subscribeOnBackgroundColorChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnBackgroundOpacityChanged(std::function<void(unsigned)>&& notification) override;
    Result<SubscriptionId> subscribeOnEnabledChanged(std::function<void(bool)>&& notification) override;
    Result<SubscriptionId> subscribeOnFontColorChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnFontEdgeChanged(std::function<void(const Accessibility::FontEdge&)>&& notification) override;
    Result<SubscriptionId> subscribeOnFontEdgeColorChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnFontFamilyChanged(std::function<void(const Accessibility::FontFamily&)>&& notification) override;
    Result<SubscriptionId> subscribeOnFontOpacityChanged(std::function<void(unsigned)>&& notification) override;
    Result<SubscriptionId> subscribeOnFontSizeChanged(std::function<void(float)>&& notification) override;
    Result<SubscriptionId> subscribeOnPreferredLanguagesChanged(std::function<void(const std::vector<std::string>&)>&& notification) override;
    Result<SubscriptionId> subscribeOnTextAlignChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnTextAlignVerticalChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnWindowColorChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnWindowOpacityChanged(std::function<void(unsigned)>&& notification) override;

    Result<void> unsubscribe(SubscriptionId id) override;
    void unsubscribeAll() override;

private:
    Firebolt::Helpers::IHelper &helper_;
};
} // namespace Firebolt::ClosedCaptions
