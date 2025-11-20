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

#include "device_impl.h"
#include "firebolt.h"
#include "lifecycle_impl.h"
#include "localization_impl.h"
#include "metrics_impl.h"
#include "securestorage_impl.h"
#include "Firebolt/helpers.h"

namespace Firebolt
{
class FireboltAccessorImpl : public IFireboltAccessor
{
public:
    FireboltAccessorImpl()
        : device_(Firebolt::Helpers::GetHelperInstance())
        , localization_(Firebolt::Helpers::GetHelperInstance())
        , metrics_(Firebolt::Helpers::GetHelperInstance())
        , lifecycle_(Firebolt::Helpers::GetHelperInstance())
        , secureStorage_(Firebolt::Helpers::GetHelperInstance())
    {
    }

    FireboltAccessorImpl(const FireboltAccessorImpl&) = delete;
    FireboltAccessorImpl& operator=(const FireboltAccessorImpl&) = delete;

    ~FireboltAccessorImpl()
    {
        unsubscribeAll();
    }

    Firebolt::Error Connect(const Firebolt::Config &config, OnConnectionChanged listener) override
    {
        return Firebolt::Transport::GetGatewayInstance().Connect(config, listener);
    }

    Firebolt::Error Disconnect() override
    {
        unsubscribeAll();
        return Firebolt::Transport::GetGatewayInstance().Disconnect();
    }

    Device::IDevice& DeviceInterface() override { return device_; }
    Localization::ILocalization& LocalizationInterface() override { return localization_; }
    Metrics::IMetrics& MetricsInterface() override { return metrics_; }
    Lifecycle::ILifecycle& LifecycleInterface() override { return lifecycle_; }
    SecureStorage::ISecureStorage& SecureStorageInterface() override { return secureStorage_; }

private:
    void unsubscribeAll()
    {
        localization_.unsubscribeAll();
        lifecycle_.unsubscribeAll();
    }

private:
    Device::DeviceImpl device_;
    Localization::LocalizationImpl localization_;
    Metrics::MetricsImpl metrics_;
    Lifecycle::LifecycleImpl lifecycle_;
    SecureStorage::SecureStorageImpl secureStorage_;
};

/* static */ IFireboltAccessor& IFireboltAccessor::Instance()
{
    static FireboltAccessorImpl impl;
    return impl;
}
} // namespace Firebolt


