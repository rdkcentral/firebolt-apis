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
#include "Firebolt/json_types.h"

namespace Firebolt::SecureStorage::JsonData
{
inline Firebolt::JSON::EnumType<::Firebolt::SecureStorage::StorageScope> StorageScopeEnum({
    { "device", ::Firebolt::SecureStorage::StorageScope::DEVICE },
    { "account", ::Firebolt::SecureStorage::StorageScope::ACCOUNT },
});

class StorageOptions : public Firebolt::JSON::NL_Json_Basic<::Firebolt::SecureStorage::StorageOptions>
{
public:
    void FromJson(const nlohmann::json& json) override
    {
        ttl_ = json.at("ttl").get<float>();
    }
    ::Firebolt::SecureStorage::StorageOptions Value() const override
    {
        return ::Firebolt::SecureStorage::StorageOptions{ttl_};
    }
private:
    float ttl_;
};

} // namespace Firebolt::SecureStorage::JsonData
