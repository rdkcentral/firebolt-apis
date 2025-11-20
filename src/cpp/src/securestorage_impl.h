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

#include "securestorage.h"
#include "Firebolt/helpers.h"

namespace Firebolt::SecureStorage
{
class SecureStorageImpl : public ISecureStorage
{
public:
    SecureStorageImpl(Firebolt::Helpers::IHelper &helper);
    SecureStorageImpl(const SecureStorageImpl&) = delete;
    SecureStorageImpl& operator=(const SecureStorageImpl&) = delete;
    ~SecureStorageImpl() override = default;

    Result<void> clear(const StorageScope& scope) override;
    Result<std::string> get(const StorageScope& scope, const std::string& key) override;
    Result<void> remove(const StorageScope& scope, const std::string& key) override;
    Result<void> set(const StorageScope& scope, const std::string& key, const std::string& value,
                     const std::optional<StorageOptions>& options) override;
    Result<void> setForApp(const std::string& appId, const StorageScope& scope, const std::string& key,
                           const std::string& value, const std::optional<StorageOptions>& options) override;
    Result<void> removeForApp(const std::string& appId, const StorageScope& scope, const std::string& key) override;
    Result<void> clearForApp(const std::string& appId, const StorageScope& scope) override;

private:
    Firebolt::Helpers::IHelper &helper_;
};
} // namespace Firebolt::SecureStorage
