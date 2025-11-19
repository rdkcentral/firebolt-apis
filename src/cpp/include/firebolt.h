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

#include "fireboltclient_export.h"
#include "device.h"
#include "lifecycle.h"
#include "localization.h"
#include "metrics.h"
#include "securestorage.h"
#include <config.h>
#include <types/types.h>
#include <functional>

namespace Firebolt
{
class FIREBOLTCLIENT_EXPORT IFireboltAccessor
{
public:
    virtual ~IFireboltAccessor() = default;

    /**
     * @brief Connection status listener callback
     *
     * @param connected : Connection status: true - Connected, false - Disconnected
     * @param error     : Reason, if any.
     *
     * @return None
     */
    using OnConnectionChanged = std::function<void(const bool connected, const Firebolt::Error error)>;

    /**
     * @brief Get the FireboltAccessor singleton instance
     *
     * @return FireboltAccessor Instance
     */
    static IFireboltAccessor& Instance();

    /**
     * @brief Attempt a initialize Firebolt Client and connection to the endpoint using given config.
     *        This method is asynchronous and the user is expected to wait for the OnConnectionChanged callback
     *        to report successful connection before calling APIs methods
     *
     * @param config: Configuration parameters
     *
     * @param listener : Connection status listener
     *
     * @return Firebolt::Error
     */
    virtual Firebolt::Error Connect(const Firebolt::Config &config, OnConnectionChanged listener) = 0;

    /**
     * @brief Disconnects from the Websocket endpoint.
     *
     * @return Firebolt::Error
     */
    virtual Firebolt::Error Disconnect() = 0;

    /**
     * @brief Returns instance of Device interface
     *
     * @return Reference to Device interface
     */
    virtual Device::IDevice& DeviceInterface() = 0;

    /**
     * @brief Returns instance of Localization interface
     *
     * @return Reference to Localization interface
     */
    virtual Localization::ILocalization& LocalizationInterface() = 0;

    /**
     * @brief Returns instance of Metrics interface
     *
     * @return Reference to Metrics interface
     */
    virtual Metrics::IMetrics& MetricsInterface() = 0;

    /**
     * @brief Returns instance of Lifecycle interface
     *
     * @return Reference to Lifecycle interface
     */
    virtual Lifecycle::ILifecycle& LifecycleInterface() = 0;

    /**
     * @brief Returns instance of SecureStorage interface
     *
     * @return Reference to SecureStorage interface
     */
    virtual SecureStorage::ISecureStorage& SecureStorageInterface() = 0;
};
} // namespace Firebolt
