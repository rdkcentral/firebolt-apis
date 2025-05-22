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

#include "Async.h"
#include "Transport/Transport.h"

namespace FireboltSDK
{
Async* Async::_singleton = nullptr;
Async::Async() : _methodMap(), _adminLock(), _transport(nullptr)
{
    ASSERT(_singleton == nullptr);
    _singleton = this;
}

Async::~Async() /* override */
{
    Clear();
    _transport = nullptr;
    _singleton = nullptr;
}

/* static */ Async& Async::Instance()
{
    static Async* instance = new Async();
    ASSERT(instance != nullptr);
    return *instance;
}

/* static */ void Async::Dispose()
{
    ASSERT(_singleton != nullptr);

    if (_singleton != nullptr)
    {
        delete _singleton;
    }
}

void Async::Configure(Transport<WPEFramework::Core::JSON::IElement>* transport)
{
    _transport = transport;
}

void Async::Clear()
{
    _adminLock.Lock();
    MethodMap::iterator index = _methodMap.begin();
    while (index != _methodMap.end())
    {
        CallbackMap::iterator callbackIndex = index->second.begin();
        while (callbackIndex != index->second.end())
        {
            if (IsValidJob(callbackIndex->second))
            {
                WPEFramework::Core::IWorkerPool::Instance().Revoke(callbackIndex->second.job);
            }
            callbackIndex = index->second.erase(callbackIndex);
        }
        index = _methodMap.erase(index);
    }
    _adminLock.Unlock();
}
} // namespace FireboltSDK
