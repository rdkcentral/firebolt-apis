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
#include <string>

#include "device.h"
#include "helpers.h"

namespace Firebolt::Device
{
class DeviceImpl : public IDevice, public IModule, public SubscriptionHelper
{
public:
    DeviceImpl() = default;
    DeviceImpl(const DeviceImpl&) = delete;
    DeviceImpl& operator=(const DeviceImpl&) = delete;

    ~DeviceImpl() override = default;

    // Methods
    Result<AudioProfiles> audio() const override;
    Result<std::string> distributor() const override;
    Result<HDCPVersionMap> hdcp() const override;
    Result<HDRFormatMap> hdr() const override;
    Result<std::string> id() const override;
    Result<std::string> make() const override;
    Result<std::string> model() const override;
    Result<std::string> name() const override;
    Result<NetworkInfoResult> network() const override;
    Result<std::string> platform() const override;
    Result<Resolution> screenResolution() const override;
    Result<std::string> sku() const override;
    Result<std::string> type() const override;
    Result<std::string> uid() const override;
    Result<Resolution> videoResolution() const override;

    // Events
    Result<SubscriptionId> subscribeOnAudioChanged(std::function<void(const AudioProfiles&)>&& notification) override;
    Result<SubscriptionId> subscribeOnDeviceNameChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnHdcpChanged(std::function<void(const HDCPVersionMap&)>&& notification) override;
    Result<SubscriptionId> subscribeOnHdrChanged(std::function<void(const HDRFormatMap&)>&& notification) override;
    Result<SubscriptionId> subscribeOnNameChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId> subscribeOnNetworkChanged(std::function<void(const NetworkInfoResult&)>&& notification) override;
    Result<SubscriptionId>
    subscribeOnScreenResolutionChanged(std::function<void(const std::string&)>&& notification) override;
    Result<SubscriptionId>
    subscribeOnVideoResolutionChanged(std::function<void(const std::string&)>&& notification) override;

    Result<void> unsubscribe(SubscriptionId id) override;
    void unsubscribeAll() override;

    Result<DeviceVersion> version() const override;
};
} // namespace Firebolt::Device
