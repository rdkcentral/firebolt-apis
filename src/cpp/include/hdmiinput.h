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

#include <functional>
#include <optional>
#include <types/fb-errors.h>
#include <types/types.h>
#include <vector>

namespace Firebolt::HDMIInput
{

// Enums
/* EDIDVersion  */
enum class EDIDVersion
{
    V1_4,
    V2_0,
    UNKNOWN
};

/* HDMISignalStatus  */
enum class HDMISignalStatus
{
    NONE,
    STABLE,
    UNSTABLE,
    UNSUPPORTED,
    UNKNOWN
};

// Types
struct SignalChangedInfo
{
    std::string port;
    HDMISignalStatus signal;
};

struct AutoLowLatencyModeSignalChangedInfo
{
    std::optional<std::string> port;
    std::optional<bool> autoLowLatencyModeSignalled;
};

struct HDMIInputPort
{
    std::string port;
    bool connected;
    HDMISignalStatus signal;
    bool arcCapable;
    bool arcConnected;
    EDIDVersion edidVersion;
    bool autoLowLatencyModeCapable;
    bool autoLowLatencyModeSignalled;
};

struct AutoLowLatencyModeCapableChangedInfo
{
    std::string port;
    bool enabled;
};

struct ConnectionChangedInfo
{
    std::optional<std::string> port;
    std::optional<bool> connected;
};

class IHDMIInput
{
public:
    virtual ~IHDMIInput() = default;

    // Methods
    /**
     * @brief Property for each port auto low latency mode setting.
     *
     * @param[in]  port : port
     *
     * @retval The autoLowLatencyModeCapable property or error
     */
    virtual Result<bool> autoLowLatencyModeCapable(const std::string& port) const = 0;

    /**
     * @brief Property for each port's active EDID version.
     *
     * @param[in]  port : port
     *
     * @retval The edidVersion property or error
     */
    virtual Result<EDIDVersion> edidVersion(const std::string& port) const = 0;

    /**
     * @brief Property for the low latency mode setting.
     *
     * @retval The lowLatencyMode property or error
     */
    virtual Result<bool> lowLatencyMode() const = 0;

    /**
     * @brief Set Property for each port auto low latency mode setting.
     *
     * @param[in] port           : port
     * @param[in] value          : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setAutoLowLatencyModeCapable(const std::string& port, const bool value) = 0;

    /**
     * @brief Set Property for each port's active EDID version.
     *
     * @param[in] port            : port
     * @param[in] value           : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setEdidVersion(const std::string& port, const EDIDVersion& value) = 0;

    /**
     * @brief Set Property for the low latency mode setting.
     *
     * @param[in] value           : The value to be set
     *
     * @retval The status
     */
    virtual Result<void> setLowLatencyMode(const bool value) = 0;

    /**
     * @brief Closes the given HDMI Port if it is the current active source for
     *        HDMI Input. If there was no active source, then there would no action taken
     *        on the device.
     *
     * @retval The status
     */
    virtual Result<void> close() = 0;

    /**
     * @brief Opens the HDMI Port allowing it to be the active source device.
     *        Incase there is a different HDMI portId already set as the active source,
     *        this call would stop the older portId before opening the given portId.
     *
     * @param[in] port            : port
     *
     * @retval The status
     */
    virtual Result<void> open(const std::string& portId) = 0;

    /**
     * @brief Retrieve a specific HDMI input port.
     *
     * @param[in]  port            : port
     *
     * @retval The method call result
     */
    virtual Result<HDMIInputPort> port(const std::string& portId) = 0;

    /**
     * @brief Retrieve a list of HDMI input ports.
     *
     * @retval The method call result
     */
    virtual Result<std::vector<HDMIInputPort>> ports() const = 0;

    // Events
    /**
     * @brief Subscribe on the change of AutoLowLatencyModeCapable property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnAutoLowLatencyModeCapableChanged(
        std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification) = 0;

    /**
     * @brief Global Subscribe on the change of AutoLowLatencyModeCapable property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> globalSubscribeOnAutoLowLatencyModeCapableChanged(
        std::function<void(const AutoLowLatencyModeCapableChangedInfo&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of AutoLowLatencyModeSignal property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnAutoLowLatencyModeSignalChanged(
        std::function<void(const AutoLowLatencyModeSignalChangedInfo&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Connection property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnConnectionChanged(std::function<void(const ConnectionChangedInfo&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of EdidVersion property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnEdidVersionChanged(std::function<void(const EDIDVersion&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of LowLatencyMode property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnLowLatencyModeChanged(std::function<void(bool)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Signal property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnSignalChanged(std::function<void(const SignalChangedInfo&)>&& notification) = 0;

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
} // namespace Firebolt::HDMIInput
