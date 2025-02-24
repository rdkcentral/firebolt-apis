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

#include "error.h"
/* ${IMPORTS:h} */

${if.declarations}
namespace Firebolt {
namespace ${info.Title} {

${if.enums}/* ${ENUMS} */${end.if.enums}

struct ChallengeRequestor {
  std::string id;
  std::string name;
};

struct GrantResult {
  bool granted;
};

  
struct AcknowledgeChallengeParameters {
  std::string capability;
  ChallengeRequestor requestor;
};

struct AcknowledgeChallengeProviderRequest {
    std::string correlationId;
    AcknowledgeChallengeParameters parameters;
};

struct AcknowledgeChallengeError {
    int32_t code;
    std::string message;
    std::optional<std::string> data;
};

struct IAcknowledgeChallengeProvider {
    virtual ~IAcknowledgeChallengeProvider() = default;
    virtual GrantResult challenge( const AcknowledgeChallengeParameters& parameters) = 0;
};


struct IAcknowledgeChallenge {

    virtual ~IAcknowledgeChallenge() = default;

    // Methods & Events
    virtual void provide( IAcknowledgeChallengeProvider& provider ) = 0;

};
} //namespace ${info.Title}
}
${end.if.declarations}