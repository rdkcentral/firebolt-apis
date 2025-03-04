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
 class JsonData_KeyboardParameters: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_KeyboardParameters() override = default;

  public:
      JsonData_KeyboardParameters()
          : WPEFramework::Core::JSON::Container()
      {
          Add(_T("message"), &Message);
      }

      JsonData_KeyboardParameters(const JsonData_KeyboardParameters& other)
      {
          Add(_T("message"), &Message);
          Message = other.Message;
      }

      JsonData_KeyboardParameters& operator=(const JsonData_KeyboardParameters& other)
      {
          Add(_T("message"), &Message);
          Message = other.Message;
          return (*this);
      }

  public:
      FireboltSDK::JSON::String Message;
  };

  class JsonData_KeyboardEmailParameters: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_KeyboardEmailParameters() override = default;
    
        JsonData_KeyboardEmailParameters() {
            Add(_T("message"), &Message);
            Add(_T("type"), &Type);
        }
    
        JsonData_KeyboardEmailParameters(const JsonData_KeyboardEmailParameters& other) {
            Add(_T("message"), &Message);
            Message = other.Message;
            Add(_T("type"), &Type);
            Type = other.Type;
        }
    
        JsonData_KeyboardEmailParameters& operator=(const JsonData_KeyboardEmailParameters& other) {
            Add(_T("message"), &Message);
            Message = other.Message;
            Add(_T("type"), &Type);
            Type = other.Type;
            return (*this);
        }
    
    public:
        FireboltSDK::JSON::String Message;
        JsonData_EmailUsage Type;
    };

  class JsonData_KeyboardProviderRequest: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_KeyboardProviderRequest() override = default;

  public:
      JsonData_KeyboardProviderRequest()
          : WPEFramework::Core::JSON::Container()
      {
          Add(_T("parameters"), &Parameters);
      }

      JsonData_KeyboardProviderRequest(const JsonData_KeyboardProviderRequest& other)
      {
          Add(_T("parameters"), &Parameters);
          Parameters = other.Parameters;
      }

      JsonData_KeyboardProviderRequest& operator=(const JsonData_KeyboardProviderRequest& other)
      {
          Add(_T("parameters"), &Parameters);
          Parameters = other.Parameters;
          return (*this);
      }

  public:
      Firebolt::Keyboard::JsonData_KeyboardParameters Parameters;
  };

  class JsonData_KeyboardEmailProviderRequest: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_KeyboardEmailProviderRequest() override = default;
    
        JsonData_KeyboardEmailProviderRequest() {
            Add(_T("parameters"), &Parameters);
        }
    
        JsonData_KeyboardEmailProviderRequest(const JsonData_KeyboardEmailProviderRequest& other) {
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
        }
    
        JsonData_KeyboardEmailProviderRequest& operator=(const JsonData_KeyboardEmailProviderRequest& other) {
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
            return (*this);
        }
    
    public:
        Firebolt::Keyboard::JsonData_KeyboardEmailParameters Parameters;
    };

  class JsonData_KeyboardError: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_KeyboardError() override = default;

  public:
      JsonData_KeyboardError()
          : WPEFramework::Core::JSON::Container()
      {
          Add(_T("code"), &Code);
          Add(_T("message"), &Message);
          Add(_T("data"), &Data);
      }

      JsonData_KeyboardError(const JsonData_KeyboardError& other)
      {
          Add(_T("code"), &Code);
          Code = other.Code;
          Add(_T("message"), &Message);
          Message = other.Message;
          Add(_T("data"), &Data);
          Data = other.Data;
      }

      JsonData_KeyboardError& operator=(const JsonData_KeyboardError& other)
      {
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

  class JsonData_Error: public WPEFramework::Core::JSON::Container {
  public:
      ~JsonData_Error() override = default;

  public:
      JsonData_Error()
          : WPEFramework::Core::JSON::Container()
      {
          Add(_T("code"), &Code);
          Add(_T("message"), &Message);
          Add(_T("data"), &Data);
      }

      JsonData_Error(const JsonData_Error& other)
      {
          Add(_T("code"), &Code);
          Code = other.Code;
          Add(_T("message"), &Message);
          Message = other.Message;
          Add(_T("data"), &Data);
          Data = other.Data;
      }

      JsonData_Error& operator=(const JsonData_Error& other)
      {
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

  class KeyboardImpl : public IKeyboard, public IModule {

  public:
      KeyboardImpl() = default;
      KeyboardImpl(const KeyboardImpl&) = delete;
      KeyboardImpl& operator=(const KeyboardImpl&) = delete;

      ~KeyboardImpl() override = default;

      // Methods & Events
      void provide( IKeyboardProvider& provider ) override;

  };
     
 
 }//namespace ${info.Title}
 }${end.if.implementations}
