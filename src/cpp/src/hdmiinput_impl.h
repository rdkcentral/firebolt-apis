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
#include "IModule.h"
#include "hdmiinput.h"
#include "helpers.h"
#include "jsondata_types.h"

namespace Firebolt::HDMIInput
{
class HDMIInputImpl : public IHDMIInput, public IModule, public SubscriptionHelper
{

public:
    HDMIInputImpl() = default;
    HDMIInputImpl(const HDMIInputImpl&) = delete;
    HDMIInputImpl& operator=(const HDMIInputImpl&) = delete;

    ~HDMIInputImpl() override = default;

    // Methods
    Result<bool> autoLowLatencyModeCapable(const std::string& port) const override;
    Result<EDIDVersion> edidVersion(const std::string& port) const override;
    Result<bool> lowLatencyMode() const override;
    Result<void> setAutoLowLatencyModeCapable(const std::string& port, const bool value) override;
    Result<void> setEdidVersion(const std::string& port, const EDIDVersion& value) override;
    Result<void> setLowLatencyMode(const bool value) override;
    Result<void> close() override;
    Result<void> open(const std::string& portId) override;
    Result<HDMIInputPort> port(const std::string& portId) override;
    Result<std::vector<HDMIInputPort>> ports() const override;

    // Events
    Result<SubscriptionId> subscribeOnAutoLowLatencyModeCapableChanged(
        std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification) override;
    Result<SubscriptionId> globalSubscribeOnAutoLowLatencyModeCapableChanged(
        std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification) override;
    Result<SubscriptionId> subscribeOnAutoLowLatencyModeSignalChanged(
        std::function<void(const AutoLowLatencyModeSignalChangedInfo&)>&& notification) override;
    Result<SubscriptionId>
    subscribeOnConnectionChanged(std::function<void(const ConnectionChangedInfo&)>&& notification) override;
    Result<SubscriptionId> subscribeOnEdidVersionChanged(std::function<void(const EDIDVersion&)>&& notification) override;
    Result<SubscriptionId> subscribeOnLowLatencyModeChanged(std::function<void(bool)>&& notification) override;
    Result<SubscriptionId> subscribeOnSignalChanged(std::function<void(const SignalChangedInfo&)>&& notification) override;
    Result<void> unsubscribe(SubscriptionId id) override;
    void unsubscribeAll() override;
};
} // namespace Firebolt::HDMIInput
