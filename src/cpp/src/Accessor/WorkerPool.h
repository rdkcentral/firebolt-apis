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

#pragma once

#include "Module.h"

namespace FireboltSDK
{

class WorkerPoolImplementation : public WPEFramework::Core::WorkerPool
{
public:
    WorkerPoolImplementation() = delete;
    WorkerPoolImplementation(const WorkerPoolImplementation&) = delete;
    WorkerPoolImplementation& operator=(const WorkerPoolImplementation&) = delete;

    WorkerPoolImplementation(const uint8_t threads, const uint32_t stackSize, const uint32_t queueSize)
        : WorkerPool(threads, stackSize, queueSize, &_dispatcher)
    {
    }

    ~WorkerPoolImplementation()
    {
        // Diable the queue so the minions can stop, even if they are processing and waiting for work..
        Stop();
    }

public:
    void Stop() { WPEFramework::Core::WorkerPool::Stop(); }

    void Run() { WPEFramework::Core::WorkerPool::Run(); }

private:
    class Dispatcher : public WPEFramework::Core::ThreadPool::IDispatcher
    {
    public:
        Dispatcher(const Dispatcher&) = delete;
        Dispatcher& operator=(const Dispatcher&) = delete;

        Dispatcher() = default;
        ~Dispatcher() override = default;

    private:
        void Initialize() override {}
        void Deinitialize() override {}
        void Dispatch(WPEFramework::Core::IDispatch* job) override { job->Dispatch(); }
    };

    Dispatcher _dispatcher;
};

class Worker : public WPEFramework::Core::IDispatch
{
public:
    typedef std::function<void(const void*)> Dispatcher;

protected:
    Worker(const Dispatcher& dispatcher, const void* userData) : _dispatcher(dispatcher), _userData(userData) {}

public:
    Worker() = delete;
    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

    ~Worker() = default;

public:
    static WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> Create(const Dispatcher& dispatcher,
                                                                               const void* userData);

    void Dispatch() override { _dispatcher(_userData); }

private:
    Dispatcher _dispatcher;
    const void* _userData;
};
} // namespace FireboltSDK
