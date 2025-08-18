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

#include "securestorage_impl.h"
#include "jsondata_securestorage_types.h"

using namespace Firebolt::Helpers;

namespace Firebolt::SecureStorage
{
Result<void> SecureStorageImpl::clear(const StorageScope& scope)
{
    Parameters params;
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    return invoke("SecureStorage.clear", params);
}

Result<std::string> SecureStorageImpl::get(const StorageScope& scope, const std::string& key)
{
    Parameters params;
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    params.add(_T("key"), key);
    return invoke<FireboltSDK::JSON::String, std::string>("SecureStorage.get", params);
}

Result<void> SecureStorageImpl::remove(const StorageScope& scope, const std::string& key)
{
    Parameters params;
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    params.add(_T("key"), key);
    return invoke("SecureStorage.remove", params);
}

Result<void> SecureStorageImpl::set(const StorageScope& scope, const std::string& key, const std::string& value,
                                    const std::optional<StorageOptions>& options)
{
    Parameters params;
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    params.add(_T("key"), key);
    params.add(_T("value"), value);
    params.add<JsonData::StorageOptions>(_T("options"), options);
    return invoke("SecureStorage.set", params);
}

Result<void> SecureStorageImpl::setForApp(const std::string& appId, const StorageScope& scope, const std::string& key,
                                          const std::string& value, const std::optional<StorageOptions>& options)
{
    Parameters params;
    params.add(_T("appId"), appId);
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    params.add(_T("key"), key);
    params.add(_T("value"), value);
    params.add<JsonData::StorageOptions>(_T("options"), options);
    return invoke("SecureStorage.setForApp", params);
}

Result<void> SecureStorageImpl::removeForApp(const std::string& appId, const StorageScope& scope, const std::string& key)
{
    Parameters params;
    params.add(_T("appId"), appId);
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    params.add(_T("key"), key);
    return invoke("SecureStorage.removeForApp", params);
}

Result<void> SecureStorageImpl::clearForApp(const std::string& appId, const StorageScope& scope)
{
    Parameters params;
    params.add(_T("appId"), appId);
    params.add<JsonData::StorageScope>(_T("scope"), scope);
    return invoke("SecureStorage.clearForApp", params);
}
} // namespace Firebolt::SecureStorage
