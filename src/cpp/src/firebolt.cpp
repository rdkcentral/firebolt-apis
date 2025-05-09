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

#include "FireboltSDK.h"
#include "IModule.h"
#include "closedcaptions_impl.h"
#include "device_impl.h"
#include "hdmiinput_impl.h"
#include "lifecycle_impl.h"
#include "localization_impl.h"
#include "metrics_impl.h"
#include "securestorage_impl.h"
#include <firebolt.h>

namespace Firebolt
{
class FireboltAccessorImpl : public IFireboltAccessor
{
public:
    FireboltAccessorImpl() = default;
    FireboltAccessorImpl(const FireboltAccessorImpl&) = delete;
    FireboltAccessorImpl& operator=(const FireboltAccessorImpl&) = delete;

    ~FireboltAccessorImpl()
    {
        unsubscribeAll();

        if (accessor_)
        {
            accessor_->Dispose();
            accessor_ = nullptr;
        }
    }

    Firebolt::Error Initialize(const std::string& configLine) override
    {
        accessor_ = &(FireboltSDK::Accessor::Instance(configLine));
        return Error::None;
    }

    Firebolt::Error Connect(OnConnectionChanged listener) override { return accessor_->Connect(listener); }

    Firebolt::Error Disconnect() override
    {
        unsubscribeAll();
        return accessor_->Disconnect();
    }

    ClosedCaptions::IClosedCaptions& ClosedCaptionsInterface() override { return closedCaptions_; }

    Device::IDevice& DeviceInterface() override { return device_; }

    HDMIInput::IHDMIInput& HDMIInputInterface() override { return hdmiInput_; }

    Localization::ILocalization& LocalizationInterface() override { return localization_; }

    Metrics::IMetrics& MetricsInterface() override { return metrics_; }

    Lifecycle::ILifecycle& LifecycleInterface() override { return lifecycle_; }

    SecureStorage::ISecureStorage& SecureStorageInterface() override { return secureStorage_; }

private:
    void unsubscribeAll()
    {
        closedCaptions_.unsubscribeAll();
        device_.unsubscribeAll();
        hdmiInput_.unsubscribeAll();
        localization_.unsubscribeAll();
        metrics_.unsubscribeAll();
        lifecycle_.unsubscribeAll();
        secureStorage_.unsubscribeAll();
    }

private:
    FireboltSDK::Accessor* accessor_;
    ClosedCaptions::ClosedCaptionsImpl closedCaptions_;
    Device::DeviceImpl device_;
    HDMIInput::HDMIInputImpl hdmiInput_;
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
