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

#include "${info.title.lowercase}_impl.h"
#include "Gateway/Gateway.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {

    // Will add PROVIDER_CLASSES templates in another PR
    // Static for now

    static std::string KeyboardEmailSessionInnerCallback( void* provider, const void* userData, void* jsonResponse ) // response are params that were sent when provider was requested
    {
        WPEFramework::Core::ProxyType<JsonData_KeyboardEmailProviderRequest>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_KeyboardEmailProviderRequest>*>(jsonResponse));
          
        ASSERT(proxyResponse.IsValid() == true);

        if (!proxyResponse.IsValid()) {
          return R"({"error": "invalid data"})";
        }
        KeyboardEmailProviderRequest sessionRequest;

        unsigned id = *(unsigned *)userData;
        sessionRequest.correlationId = std::to_string(id);
        sessionRequest.parameters.type = (*proxyResponse).Parameters.Type;
        sessionRequest.parameters.message = (*proxyResponse).Parameters.Message;

        proxyResponse.Release();

        IKeyboardProvider& KeyboardProvider = *(reinterpret_cast<IKeyboardProvider*>(provider));
        return KeyboardProvider.email(sessionRequest.parameters);
    }


    static std::string KeyboardPasswordSessionInnerCallback( void* provider, const void* userData, void* jsonResponse ) // response are params that were sent when provider was requested
    {
        WPEFramework::Core::ProxyType<JsonData_KeyboardProviderRequest>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_KeyboardProviderRequest>*>(jsonResponse));
          
        ASSERT(proxyResponse.IsValid() == true);

        if (!proxyResponse.IsValid()) {
          return R"({"error": "invalid data"})";
        }
        KeyboardProviderRequest sessionRequest;

        unsigned id = *(unsigned *)userData;
        sessionRequest.correlationId = std::to_string(id);
        sessionRequest.parameters.message = (*proxyResponse).Parameters.Message;

        proxyResponse.Release();

        IKeyboardProvider& KeyboardProvider = *(reinterpret_cast<IKeyboardProvider*>(provider));
        return KeyboardProvider.password(sessionRequest.parameters);
    }


    static std::string KeyboardStandardSessionInnerCallback( void* provider, const void* userData, void* jsonResponse ) // response are params that were sent when provider was requested
    {
        WPEFramework::Core::ProxyType<JsonData_KeyboardProviderRequest>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_KeyboardProviderRequest>*>(jsonResponse));
          
        ASSERT(proxyResponse.IsValid() == true);

        if (!proxyResponse.IsValid()) {
          return R"({"error": "invalid data"})";
        }
        KeyboardProviderRequest sessionRequest;

        unsigned id = *(unsigned *)userData;
        sessionRequest.correlationId = std::to_string(id);
        sessionRequest.parameters.message = (*proxyResponse).Parameters.Message;

        proxyResponse.Release();

        IKeyboardProvider& KeyboardProvider = *(reinterpret_cast<IKeyboardProvider*>(provider));
        return KeyboardProvider.standard(sessionRequest.parameters);
    }
        
    // Custom provider method
    void KeyboardImpl::provide( IKeyboardProvider& provider )
    {
        string eventName;
        Firebolt::Error status = Firebolt::Error::None;
        JsonObject jsonParameters;

        eventName = _T("keyboard.onRequestStandard");
        status = FireboltSDK::Gateway::Instance().RegisterProviderInterface<JsonData_KeyboardProviderRequest>(eventName, jsonParameters, KeyboardStandardSessionInnerCallback, reinterpret_cast<void*>(&provider));
        if (status != Firebolt::Error::None) {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in %s subscribe = %d", eventName.c_str(), status);
        }

        eventName = _T("keyboard.onRequestPassword");
        status = FireboltSDK::Gateway::Instance().RegisterProviderInterface<JsonData_KeyboardProviderRequest>(eventName, jsonParameters, KeyboardPasswordSessionInnerCallback, reinterpret_cast<void*>(&provider));
        if (status != Firebolt::Error::None) {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in %s subscribe = %d", eventName.c_str(), status);
        }

        eventName = _T("keyboard.onRequestEmail");
        status = FireboltSDK::Gateway::Instance().RegisterProviderInterface<JsonData_KeyboardProviderRequest>(eventName, jsonParameters, KeyboardEmailSessionInnerCallback, reinterpret_cast<void*>(&provider));
        if (status != Firebolt::Error::None) {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in %s subscribe = %d", eventName.c_str(), status);
        }
    }

    // Events
    /* ${EVENTS} */

}//namespace ${info.Title}
}${end.if.implementations}
${if.enums}

namespace WPEFramework {

/* ${ENUM_IMPLEMENTATIONS} */
}${end.if.enums}

