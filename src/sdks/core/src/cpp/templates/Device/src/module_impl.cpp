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

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.providers}
/* ${PROVIDERS} */${end.if.providers}
    std::string ${info.Title}Impl::version(Firebolt::Error *err) const
    {
        JsonObject jsonParameters;
        FireboltSDK::JSON::String jsonResult;
        std::string version;

        Firebolt::Error status = Firebolt::Error::NotConnected;
        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {

            status = transport->Invoke("${info.title.lowercase}.version", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "${info.Title}.version is successfully invoked, status: %s", jsonResult.Value().c_str());
                version = jsonResult.Value().c_str();
                /* TODO: Set major, minor values here*/
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }
        return version;
    }
    // Methods
    /* ${METHODS} */

    // Events
    /* ${EVENTS} */

}//namespace ${info.Title}
}${end.if.implementations}
${if.enums}

namespace WPEFramework {

/* ${ENUMS} */
}${end.if.enums}