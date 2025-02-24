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

 #include "FireboltSDK.h"
 #include "IModule.h"
 
 
 /* ${IMPORTS:impl} */
 #include "${info.title.lowercase}.h"
 
 ${if.implementations}
 namespace Firebolt {
 namespace ${info.Title} {
 ${if.enums}
 
 /* ${ENUMS:json-types} */${end.if.enums}

// Types
class JsonData_ChallengeRequestor: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_ChallengeRequestor() override = default;
  
      JsonData_ChallengeRequestor() {
          Add(_T("id"), &Id);
          Add(_T("name"), &Name);
      }
  
      JsonData_ChallengeRequestor(const JsonData_ChallengeRequestor& other) {
          Add(_T("id"), &Id);
          Id = other.Id;
          Add(_T("name"), &Name);
          Name = other.Name;
      }
  
      JsonData_ChallengeRequestor& operator=(const JsonData_ChallengeRequestor& other) {
          Add(_T("id"), &Id);
          Id = other.Id;
          Add(_T("name"), &Name);
          Name = other.Name;
          return (*this);
      }
  
  public:
      FireboltSDK::JSON::String Id;
      FireboltSDK::JSON::String Name;
  };
  
  class JsonData_PinChallengeParameters: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_PinChallengeParameters() override = default;
  
      JsonData_PinChallengeParameters() {
          Add(_T("requestor"), &Requestor);
          Add(_T("pinSpace"), &PinSpace);
          Add(_T("capability"), &Capability);
      }
  
      JsonData_PinChallengeParameters(const JsonData_PinChallengeParameters& other) {
          Add(_T("requestor"), &Requestor);
          Requestor = other.Requestor;
          Add(_T("pinSpace"), &PinSpace);
          PinSpace = other.PinSpace;
          Add(_T("capability"), &Capability);
          Capability = other.Capability;
      }
  
      JsonData_PinChallengeParameters& operator=(const JsonData_PinChallengeParameters& other) {
          Add(_T("requestor"), &Requestor);
          Requestor = other.Requestor;
          Add(_T("pinSpace"), &PinSpace);
          PinSpace = other.PinSpace;
          Add(_T("capability"), &Capability);
          Capability = other.Capability;
          return (*this);
      }
  
  public:
      JsonData_ChallengeRequestor Requestor;
      JsonData_PinSpace PinSpace;
      FireboltSDK::JSON::String Capability;
  };
  
  class JsonData_PinChallengeProviderRequest: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_PinChallengeProviderRequest() override = default;
  
      JsonData_PinChallengeProviderRequest() {
          Add(_T("correlationId"), &CorrelationId);
          Add(_T("parameters"), &Parameters);
      }
  
      JsonData_PinChallengeProviderRequest(const JsonData_PinChallengeProviderRequest& other) {
          Add(_T("correlationId"), &CorrelationId);
          CorrelationId = other.CorrelationId;
          Add(_T("parameters"), &Parameters);
          Parameters = other.Parameters;
      }
  
      JsonData_PinChallengeProviderRequest& operator=(const JsonData_PinChallengeProviderRequest& other) {
          Add(_T("correlationId"), &CorrelationId);
          CorrelationId = other.CorrelationId;
          Add(_T("parameters"), &Parameters);
          Parameters = other.Parameters;
          return (*this);
      }
  
  public:
      FireboltSDK::JSON::String CorrelationId;
      Firebolt::PinChallenge::JsonData_PinChallengeParameters Parameters;
  };
  
  class JsonData_PinChallengeError: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_PinChallengeError() override = default;
  
      JsonData_PinChallengeError() {
          Add(_T("code"), &Code);
          Add(_T("message"), &Message);
          Add(_T("data"), &Data);
      }
  
      JsonData_PinChallengeError(const JsonData_PinChallengeError& other) {
          Add(_T("code"), &Code);
          Code = other.Code;
          Add(_T("message"), &Message);
          Message = other.Message;
          Add(_T("data"), &Data);
          Data = other.Data;
      }
  
      JsonData_PinChallengeError& operator=(const JsonData_PinChallengeError& other) {
          Add(_T("code"), &Code);
          Code = other.Code;
          Add(_T("message"), &Message);
          Message = other.Message;
          Add(_T("data"), &Data);
          Data = other.Data;
          return (*this);
      }
  
  public:
      WPEFramework::Core::JSON::DecSInt32 Code;
      FireboltSDK::JSON::String Message;
      FireboltSDK::JSON::String Data;
  };
  
  class PinChallengeImpl : public IPinChallenge, public IModule {
  public:
      PinChallengeImpl() = default;
      PinChallengeImpl(const PinChallengeImpl&) = delete;
      PinChallengeImpl& operator=(const PinChallengeImpl&) = delete;
  
      ~PinChallengeImpl() override = default;
  
      // Methods & Events
      void provide(IPinChallengeProvider& provider) override;
  };


} // namespace PinChallenge
}${end.if.implementations}