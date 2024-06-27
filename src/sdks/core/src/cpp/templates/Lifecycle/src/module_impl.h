/* Copyright 2023 Comcast Cable Communications Management, LLC
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

#include "FireboltSDK.h"
#include "IModule.h"
#include "metrics_impl.h"
#include <string>
#include <functional> // Needed for std::function
#include <iostream> // Needed for std::cout


/* ${IMPORTS} */
#include "${info.title.lowercase}.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.enums}

/* ${ENUMS:json-types} */${end.if.enums}
${if.types}
// Types
/* ${TYPES:json-types} */${end.if.types}
${if.methods}class ${info.Title}Impl : public I${info.Title}, public IModule {

public:
    ${info.Title}Impl() : currentState("initializing") {}
    ${info.Title}Impl(const ${info.Title}Impl&) = delete;
    ${info.Title}Impl& operator=(const ${info.Title}Impl&) = delete;

    ~${info.Title}Impl() override = default;

    void ready( Firebolt::Error *err = nullptr ) ;
    std::string state();
    void finished( Firebolt::Error *err = nullptr );
    // Methods & Events
    /* ${METHODS:declarations-override} */

private:
    std::string currentState;

    void setState(const std::string& newState) {
        currentState = newState;
    }
};${end.if.methods}

} // namespace ${info.Title}
} // namespace Firebolt
${end.if.implementations}


  
