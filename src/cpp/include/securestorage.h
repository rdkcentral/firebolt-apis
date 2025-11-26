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

namespace Firebolt::SecureStorage
{
/**
 * @brief The scope of the data
 */
enum class StorageScope
{
    DEVICE,
    ACCOUNT
};

struct StorageOptions
{
    float ttl;
};

class ISecureStorage
{
public:
    virtual ~ISecureStorage() = default;

    /**
     * @brief Clears all the secure data values
     *
     * @param[in]  scope : The scope of the key/value
     *
     * @retval The status
     */
    virtual Result<void> clear(const StorageScope& scope) = 0;

    /**
     * @brief Get stored value by key
     *
     * @param[in]  scope : The scope of the key/value
     * @param[in]  key   : Key to get
     *
     * @retval The method call result
     */
    virtual Result<std::string> get(const StorageScope& scope, const std::string& key) = 0;

    /**
     * @brief Remove a secure data value
     *
     * @param[in]  scope : The scope of the key/value
     * @param[in]  key   : Key to remove
     *
     * @retval The status
     */
    virtual Result<void> remove(const StorageScope& scope, const std::string& key) = 0;

    /**
     * @brief Set or update a secure data value
     *
     * @param[in]  scope   : The scope of the key/value
     * @param[in]  key     : Key to set
     * @param[in]  value   : Value to set
     * @param[in]  options : Optional parameters to set
     *
     * @retval The status
     */
    virtual Result<void> set(const StorageScope& scope, const std::string& key, const std::string& value,
                             const std::optional<StorageOptions>& options) = 0;

    /**
     * @brief Set or update a secure data value for a specific app.
     *
     * @param[in]  appId   : appId for which value is being set
     * @param[in]  scope   : The scope of the data key
     * @param[in]  key     : Key to set
     * @param[in]  value   : Value to set
     * @param[in]  options : Optional parameters to set
     *
     * @retval The status
     */
    virtual Result<void> setForApp(const std::string& appId, const StorageScope& scope, const std::string& key,
                                   const std::string& value, const std::optional<StorageOptions>& options) = 0;

    /**
     * @brief Removes single data value for a specific app.
     *
     * @param[in]  appId : appId for which values are removed
     * @param[in]  scope : The scope of the key/value
     * @param[in]  key   : Key to remove
     *
     * @retval The status
     */
    virtual Result<void> removeForApp(const std::string& appId, const StorageScope& scope, const std::string& key) = 0;

    /**
     * @brief Clears all the secure data values for a specific app
     *
     * @param[in]  appId : appId for which values are removed
     * @param[in]  scope : The scope of the key/value
     *
     * @retval The status
     */
    virtual Result<void> clearForApp(const std::string& appId, const StorageScope& scope) = 0;
};
} // namespace Firebolt::SecureStorage
