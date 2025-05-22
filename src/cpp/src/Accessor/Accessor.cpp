/*
 * Copyright 2023 Comcast Cable Communications Management, LLC
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Accessor.h"

namespace FireboltSDK
{

Accessor* Accessor::_singleton = nullptr;

Accessor::Accessor(const string& configLine) : _workerPool(), _transport(nullptr), _config()
{
    ASSERT(_singleton == nullptr);
    _singleton = this;
    _config.FromString(configLine);

    Logger::SetLogLevel(WPEFramework::Core::EnumerateType<Logger::LogLevel>(_config.LogLevel.Value().c_str()).Value());

    FIREBOLT_LOG_INFO(Logger::Category::OpenRPC, Logger::Module<Accessor>(), "Url = %s", _config.WsUrl.Value().c_str());
    _workerPool = WPEFramework::Core::ProxyType<WorkerPoolImplementation>::Create(_config.WorkerPool.ThreadCount.Value(),
                                                                                  _config.WorkerPool.StackSize.Value(),
                                                                                  _config.WorkerPool.QueueSize.Value());
    WPEFramework::Core::WorkerPool::Assign(&(*_workerPool));
    _workerPool->Run();
}

Accessor::~Accessor()
{
    WPEFramework::Core::IWorkerPool::Assign(nullptr);
    _workerPool->Stop();

    ASSERT(_singleton != nullptr);
    _singleton = nullptr;
}

Firebolt::Error Accessor::CreateEventHandler()
{
    Event::Instance().Configure(_transport);
    return Firebolt::Error::None;
}

Firebolt::Error Accessor::DestroyEventHandler()
{
    Event::Dispose();
    return Firebolt::Error::None;
}

Event& Accessor::GetEventManager()
{
    return Event::Instance();
}

Firebolt::Error Accessor::CreateTransport(const string& url,
                                          const Transport<WPEFramework::Core::JSON::IElement>::Listener& listener,
                                          const uint32_t waitTime = DefaultWaitTime)
{
    if (_transport != nullptr)
    {
        delete _transport;
    }

    _transport = new Transport<WPEFramework::Core::JSON::IElement>(static_cast<WPEFramework::Core::URL>(url), waitTime,
                                                                   listener);

    ASSERT(_transport != nullptr);
    return ((_transport != nullptr) ? Firebolt::Error::None : Firebolt::Error::Timedout);
}

Firebolt::Error Accessor::DestroyTransport()
{
    if (_transport != nullptr)
    {
        delete _transport;
        _transport = nullptr;
    }
    return Firebolt::Error::None;
}

Transport<WPEFramework::Core::JSON::IElement>* Accessor::GetTransport()
{
    ASSERT(_transport != nullptr);
    return _transport;
}

} // namespace FireboltSDK
