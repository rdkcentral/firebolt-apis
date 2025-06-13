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

#include "jsondata_securestorage_types.h"

namespace Firebolt::SecureStorage::JsonData
{
StorageOptions::StorageOptions() : WPEFramework::Core::JSON::Container()
{
    Add(_T("ttl"), &ttl_);
}

StorageOptions::StorageOptions(const StorageOptions& other) : StorageOptions()
{
    ttl_ = other.ttl_;
}

StorageOptions::StorageOptions(const ::Firebolt::SecureStorage::StorageOptions& storageOptions) : StorageOptions()
{
    ttl_ = storageOptions.ttl;
}

StorageOptions& StorageOptions::operator=(const StorageOptions& other)
{
    ttl_ = other.ttl_;
    return *this;
}

::Firebolt::SecureStorage::StorageOptions StorageOptions::Value()
{
    return ::Firebolt::SecureStorage::StorageOptions{ttl_};
}

WPEFramework::Core::JSON::Variant StorageOptions::Data() const
{
    std::string storageOptionsStr{};
    ToString(storageOptionsStr);
    return WPEFramework::Core::JSON::VariantContainer{storageOptionsStr};
}
} // namespace Firebolt::SecureStorage::JsonData

namespace WPEFramework
{
ENUM_CONVERSION_BEGIN(Firebolt::SecureStorage::StorageScope){Firebolt::SecureStorage::StorageScope::DEVICE,
                                                             _T("device")},
    {Firebolt::SecureStorage::StorageScope::ACCOUNT, _T("account")},
    ENUM_CONVERSION_END(Firebolt::SecureStorage::StorageScope)
}