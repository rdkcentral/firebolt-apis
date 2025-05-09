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

#include "common/types.h"
#include "error.h"
#include <functional>
#include <optional>
#include <string>

namespace Firebolt::Device
{
/**
 * @brief NetworkState The type of network that is currently active
 */
enum class NetworkState
{
    CONNECTED,
    DISCONNECTED
};

/**
 * @brief NetworkType The type of network that is currently active
 */
enum class NetworkType
{
    WIFI,
    ETHERNET,
    HYBRID
};

struct HDRFormatMap
{
    bool hdr10;
    bool hdr10Plus;
    bool dolbyVision;
    bool hlg;
};

struct AudioProfiles
{
    bool stereo;
    bool dolbyDigital5_1;
    bool dolbyDigital5_1_plus;
    bool dolbyAtmos;
};

struct NetworkInfoResult
{
    NetworkState state;
    NetworkType type;
};

struct HDCPVersionMap
{
    bool hdcp1_4;
    bool hdcp2_2;
};

using Resolution = std::pair<int32_t, int32_t>;

class IDevice
{
public:
    virtual ~IDevice() = default;

    // Methods
    /**
     * @brief Get the supported audio profiles for the connected devices.
     *
     * @note It is not recommended to use this API for visual badging on content
     *       within your app since this does not reflect the settings of the user.
     *
     * @retval The audio property or error
     */
    virtual Result<AudioProfiles> audio() const = 0;

    /**
     * @brief Get the name of the entity which is distributing the current device.
     *        There can be multiple distributors which distribute the same device model.
     *
     * @retval The distributor property or error
     */
    virtual Result<std::string> distributor() const = 0;

    /**
     * @brief Get the negotiated HDCP profiles for a connected device.
     *
     * @note For devices that do not require additional connections (e.g. panels),
     *       `true` will be returned for all profiles.
     *
     * @retval The hdcp property or error
     */
    virtual Result<HDCPVersionMap> hdcp() const = 0;

    /**
     * @brief Get the negotiated HDR formats for the connected display and device
     *
     * @retval The hdr property or error
     */
    virtual Result<HDRFormatMap> hdr() const = 0;

    /**
     * @brief Get the platform back-office device identifier
     *
     * @retval The id property or error
     */
    virtual Result<std::string> id() const = 0;

    /**
     * @brief Get the manufacturer of the device model
     *
     * @retval The make property or error
     */
    virtual Result<std::string> make() const = 0;

    /**
     * @brief Get the manufacturer designated model of the device
     *
     * @retval The model property or error
     */
    virtual Result<std::string> model() const = 0;

    /**
     * @brief The human readable name of the device
     *
     * @retval The name property or error
     */
    virtual Result<std::string> name() const = 0;

    /**
     * @brief Get the current network status and type
     *
     * @retval The network property or error
     */
    virtual Result<NetworkInfoResult> network() const = 0;

    /**
     * @brief Get a platform identifier for the device. This API should be used to
     *        correlate metrics on the device only and cannot be guaranteed to have
     *        consistent responses across platforms.
     *
     * @retval The platform property or error
     */
    virtual Result<std::string> platform() const = 0;

    /**
     * @brief Get the resolution for the graphical surface of the app.
     *
     * @note The pairs returned will be of a [width, height] format and will
     *       correspond to the following values:
     *
     *       NTSC Standard Definition (SD): [720, 480]
     *       PAL Standard Definition (SD): [720, 576]
     *       High Definition (HD): [1280, 720]
     *       Full HD (FHD): [1920, 1080]
     *       4K Ultra High Definition (UHD): [3840, 2160]
     *
     * @deprecated Use non-Firebolt APIs specific to your platform, e.g. W3C APIs
     *
     * @retval The screenResolution property or error
     */
    virtual Result<Resolution> screenResolution() const = 0;

    /**
     * @brief Get the device sku
     *
     * @retval The sku property or error
     */
    virtual Result<std::string> sku() const = 0;

    /**
     * @brief Get the device type
     *
     * @retval The type property or error
     */
    virtual Result<std::string> type() const = 0;

    /**
     * @brief Gets a unique id for the current app & device
     *
     * @retval The uid property or error
     */
    virtual Result<std::string> uid() const = 0;

    /**
     * @brief Get the maximum supported video resolution of the currently
     *        connected device and display.
     *
     * @note The pairs returned will be of a [width, height] format and will
     *       correspond to the following values:
     *
     *       NTSC Standard Definition (SD): [720, 480]
     *       PAL Standard Definition (SD): [720, 576]
     *       High Definition (HD): [1280, 720]
     *       Full HD (FHD): [1920, 1080]
     *       4K Ultra High Definition (UHD): [3840, 2160]
     *
     * @retval The videoResolution property or error
     */
    virtual Result<Resolution> videoResolution() const = 0;

    // Events
    /**
     * @brief Subscribe on the change of Audio property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnAudioChanged(std::function<void(const AudioProfiles&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Device Name property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnDeviceNameChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Hdcp property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnHdcpChanged(std::function<void(const HDCPVersionMap&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Hdr property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnHdrChanged(std::function<void(const HDRFormatMap&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Name property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId> subscribeOnNameChanged(std::function<void(const std::string&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Network property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnNetworkChanged(std::function<void(const NetworkInfoResult&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Screen Resolution property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnScreenResolutionChanged(std::function<void(const Resolution&)>&& notification) = 0;

    /**
     * @brief Subscribe on the change of Video Resolution property
     *
     * @param[in]  notification        : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnVideoResolutionChanged(std::function<void(const Resolution&)>&& notification) = 0;

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
} // namespace Firebolt::Device
