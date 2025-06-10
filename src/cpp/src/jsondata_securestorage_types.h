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
#include "securestorage.h"

namespace Firebolt::SecureStorage::JsonData
{
using StorageScope = WPEFramework::Core::JSON::EnumType<::Firebolt::SecureStorage::StorageScope>;

class StorageOptions : public WPEFramework::Core::JSON::Container
{
public:
    ~StorageOptions() override = default;
    StorageOptions();
    StorageOptions(const StorageOptions& other);
    explicit StorageOptions(const ::Firebolt::SecureStorage::StorageOptions& storageOptions);
    StorageOptions& operator=(const StorageOptions& other);
    ::Firebolt::SecureStorage::StorageOptions Value();
    WPEFramework::Core::JSON::Variant Data() const;

private:
    WPEFramework::Core::JSON::Float ttl_;
};
} // namespace Firebolt::SecureStorage::JsonData
