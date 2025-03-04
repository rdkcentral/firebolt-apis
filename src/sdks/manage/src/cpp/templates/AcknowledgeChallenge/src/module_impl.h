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

class JsonData_AcknowledgeChallengeParameters: public WPEFramework::Core::JSON::Container {
public:
    ~JsonData_AcknowledgeChallengeParameters() override = default;

    JsonData_AcknowledgeChallengeParameters() {
        Add(_T("capability"), &Capability);
        Add(_T("requestor"), &Requestor);
    }

    JsonData_AcknowledgeChallengeParameters(const JsonData_AcknowledgeChallengeParameters& other) {
        Add(_T("capability"), &Capability);
        Capability = other.Capability;
        Add(_T("requestor"), &Requestor);
        Requestor = other.Requestor;
    }

    JsonData_AcknowledgeChallengeParameters& operator=(const JsonData_AcknowledgeChallengeParameters& other) {
        Add(_T("capability"), &Capability);
        Capability = other.Capability;
        Add(_T("requestor"), &Requestor);
        Requestor = other.Requestor;
        return (*this);
    }

public:
    FireboltSDK::JSON::String Capability;
    JsonData_ChallengeRequestor Requestor;
};

class JsonData_AcknowledgeChallengeProviderRequest: public WPEFramework::Core::JSON::Container {
public:
    ~JsonData_AcknowledgeChallengeProviderRequest() override = default;

    JsonData_AcknowledgeChallengeProviderRequest() {
        Add(_T("parameters"), &Parameters);
    }

    JsonData_AcknowledgeChallengeProviderRequest(const JsonData_AcknowledgeChallengeProviderRequest& other) {
        Add(_T("parameters"), &Parameters);
        Parameters = other.Parameters;
    }

    JsonData_AcknowledgeChallengeProviderRequest& operator=(const JsonData_AcknowledgeChallengeProviderRequest& other) {
        Add(_T("parameters"), &Parameters);
        Parameters = other.Parameters;
        return (*this);
    }

public:
    Firebolt::AcknowledgeChallenge::JsonData_AcknowledgeChallengeParameters Parameters;
};

class JsonData_AcknowledgeChallengeError: public WPEFramework::Core::JSON::Container {
public:
    ~JsonData_AcknowledgeChallengeError() override = default;

    JsonData_AcknowledgeChallengeError() {
        Add(_T("code"), &Code);
        Add(_T("message"), &Message);
        Add(_T("data"), &Data);
    }

    JsonData_AcknowledgeChallengeError(const JsonData_AcknowledgeChallengeError& other) {
        Add(_T("code"), &Code);
        Code = other.Code;
        Add(_T("message"), &Message);
        Message = other.Message;
        Add(_T("data"), &Data);
        Data = other.Data;
    }

    JsonData_AcknowledgeChallengeError& operator=(const JsonData_AcknowledgeChallengeError& other) {
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

class AcknowledgeChallengeImpl : public IAcknowledgeChallenge, public IModule {
public:
    AcknowledgeChallengeImpl() = default;
    AcknowledgeChallengeImpl(const AcknowledgeChallengeImpl&) = delete;
    AcknowledgeChallengeImpl& operator=(const AcknowledgeChallengeImpl&) = delete;

    ~AcknowledgeChallengeImpl() override = default;

    // Methods & Events
    void provide(IAcknowledgeChallengeProvider& provider) override;
};

} // namespace AcknowledgeChallenge
}${end.if.implementations}
