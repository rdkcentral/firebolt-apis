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
    static std::string PinChallengeSessionInnerCallback(void* provider, const void* userData, void* jsonResponse) {
      WPEFramework::Core::ProxyType<JsonData_PinChallengeProviderRequest>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_PinChallengeProviderRequest>*>(jsonResponse));
  
      ASSERT(proxyResponse.IsValid() == true);
  
      if (!proxyResponse.IsValid()) {
          return R"({"error": "invalid data"})";
      }
      PinChallengeProviderRequest sessionRequest;
  
      unsigned id = *(unsigned *)userData;
      sessionRequest.correlationId = std::to_string(id);
      sessionRequest.parameters.requestor.id = (*proxyResponse).Parameters.Requestor.Id;
      sessionRequest.parameters.requestor.name = (*proxyResponse).Parameters.Requestor.Name;
      sessionRequest.parameters.pinSpace = (*proxyResponse).Parameters.PinSpace;
      sessionRequest.parameters.capability = (*proxyResponse).Parameters.Capability;
  
      proxyResponse.Release();
  
      IPinChallengeProvider& pinChallengeProvider = *(reinterpret_cast<IPinChallengeProvider*>(provider));
      PinChallengeResult result = pinChallengeProvider.challenge(sessionRequest.parameters);
      return result.granted ? R"({"granted": true, "reason": ")" + std::to_string(static_cast<int>(result.reason)) + R"("})" : R"({"granted": false, "reason": ")" + std::to_string(static_cast<int>(result.reason)) + R"("})";
  }
  
  void PinChallengeImpl::provide(IPinChallengeProvider& provider) {
      string eventName;
      Firebolt::Error status = Firebolt::Error::None;
      JsonObject jsonParameters;
  
      eventName = _T("pinChallenge.onRequestChallenge");
      status = FireboltSDK::Gateway::Instance().RegisterProviderInterface<JsonData_PinChallengeProviderRequest>(eventName, jsonParameters, PinChallengeSessionInnerCallback, reinterpret_cast<void*>(&provider));
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
 
 