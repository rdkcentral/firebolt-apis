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
#include "firebolt.h"
#include "jsondata_lifecycle.h"
#include "${info.title.lowercase}.h"

/* ${IMPORTS} */

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {

#ifdef GATEWAY_BIDIRECTIONAL
#warning "to be defined when spec ready, some part could be common for UNI-DIRECTIONAL and BI-DIRECTIONAL"

${if.enums}

/* ${ENUMS:json-types} */${end.if.enums}
${if.types}
// Types
/* ${TYPES:json-types} */${end.if.types}
${if.methods}class ${info.Title}Impl : public I${info.Title}, public IModule {

public:
    ${info.Title}Impl() = default;
    ${info.Title}Impl(const ${info.Title}Impl&) = delete;
    ${info.Title}Impl& operator=(const ${info.Title}Impl&) = delete;
    ~${info.Title}Impl() override = default;

    std::string currentState = "INITIALIZING";

    // Methods & Events
    /* ${METHODS:declarations-override} */

    void finished(Firebolt::Error *err = nullptr) override ;
    void ready(Firebolt::Error *err = nullptr) override;
    std::string state(Firebolt::Error *err = nullptr) override;

};${end.if.methods}

#else

${if.enums}

/* ${ENUMS:json-types} */${end.if.enums}
${if.types}
// Types
/* ${TYPES:json-types} */${end.if.types}
${if.methods}class ${info.Title}Impl : public I${info.Title}, public IModule {

public:
    ${info.Title}Impl() = default;
    ${info.Title}Impl(const ${info.Title}Impl&) = delete;
    ${info.Title}Impl& operator=(const ${info.Title}Impl&) = delete;
    ~${info.Title}Impl() override = default;

    std::string currentState = "INITIALIZING";

    // Methods & Events
    /* ${METHODS:declarations-override} */

    void finished(Firebolt::Error *err = nullptr) override ;
    void ready(Firebolt::Error *err = nullptr) override;
    std::string state(Firebolt::Error *err = nullptr) override;
 
};${end.if.methods}

#endif

} // namespace ${info.Title}
} // namespace Firebolt
${end.if.implementations}