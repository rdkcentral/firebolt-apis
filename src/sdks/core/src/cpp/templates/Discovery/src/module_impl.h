/*
 * Copyright 2025 Comcast Cable Communications Management, LLC
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


/* ${IMPORTS:impl} */
#include "${info.title.lowercase}.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.enums}

/* ${ENUMS:json-types} */${end.if.enums}

    using JsonData_InterestType = WPEFramework::Core::JSON::EnumType<InterestType>;
    using JsonData_InterestReason = WPEFramework::Core::JSON::EnumType<InterestReason>;


    // Types
    class JsonData_Availability: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_Availability() override = default;
  
    public:
        JsonData_Availability()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("type"), &Type);
            Add(_T("id"), &Id);
            Add(_T("catalogId"), &CatalogId);
            Add(_T("startTime"), &StartTime);
            Add(_T("endTime"), &EndTime);
        }

        JsonData_Availability(const JsonData_Availability& other)
        {
            Add(_T("type"), &Type);
            Type = other.Type;
            Add(_T("id"), &Id);
            Id = other.Id;
            Add(_T("catalogId"), &CatalogId);
            CatalogId = other.CatalogId;
            Add(_T("startTime"), &StartTime);
            StartTime = other.StartTime;
            Add(_T("endTime"), &EndTime);
            EndTime = other.EndTime;
        }

        JsonData_Availability& operator=(const JsonData_Availability& other)
        {
            Add(_T("type"), &Type);
            Type = other.Type;
            Add(_T("id"), &Id);
            Id = other.Id;
            Add(_T("catalogId"), &CatalogId);
            CatalogId = other.CatalogId;
            Add(_T("startTime"), &StartTime);
            StartTime = other.StartTime;
            Add(_T("endTime"), &EndTime);
            EndTime = other.EndTime;
            return (*this);
        }

    public:
        Firebolt::Discovery::JsonData_AvailabilityType Type;
        FireboltSDK::JSON::String Id;
        FireboltSDK::JSON::String CatalogId;
        FireboltSDK::JSON::String StartTime;
        FireboltSDK::JSON::String EndTime;
    };

    class JsonData_UserInterestProviderParameters: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_UserInterestProviderParameters() override = default;
  
    public:
        JsonData_UserInterestProviderParameters()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("type"), &Type);
            Add(_T("reason"), &Reason);
        }

        JsonData_UserInterestProviderParameters(const JsonData_UserInterestProviderParameters& other)
        {
            Add(_T("type"), &Type);
            Type = other.Type;
            Add(_T("reason"), &Reason);
            Reason = other.Reason;
        }

        JsonData_UserInterestProviderParameters& operator=(const JsonData_UserInterestProviderParameters& other)
        {
            Add(_T("type"), &Type);
            Type = other.Type;
            Add(_T("reason"), &Reason);
            Reason = other.Reason;
            return (*this);
        }

    public:
        Firebolt::Discovery::JsonData_InterestType Type;
        Firebolt::Discovery::JsonData_InterestReason Reason;
    };

    class JsonData_ContentAccessIdentifiers: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_ContentAccessIdentifiers() override = default;
  
    public:
        JsonData_ContentAccessIdentifiers()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("availabilities"), &Availabilities);
            Add(_T("entitlements"), &Entitlements);
        }

        JsonData_ContentAccessIdentifiers(const JsonData_ContentAccessIdentifiers& other)
        {
            Add(_T("availabilities"), &Availabilities);
            Availabilities = other.Availabilities;
            Add(_T("entitlements"), &Entitlements);
            Entitlements = other.Entitlements;
        }

        JsonData_ContentAccessIdentifiers& operator=(const JsonData_ContentAccessIdentifiers& other)
        {
            Add(_T("availabilities"), &Availabilities);
            Availabilities = other.Availabilities;
            Add(_T("entitlements"), &Entitlements);
            Entitlements = other.Entitlements;
            return (*this);
        }

    public:
        WPEFramework::Core::JSON::ArrayType<Firebolt::Discovery::JsonData_Availability> Availabilities;
        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_Entitlement> Entitlements;
    };

    using JsonData_Images = WPEFramework::Core::JSON::VariantContainer;

    class JsonData_Request: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_Request() override = default;
  
    public:
        JsonData_Request()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("correlationId"), &CorrelationId);
            Add(_T("parameters"), &Parameters);
        }

        JsonData_Request(const JsonData_Request& other)
        {
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
        }

        JsonData_Request& operator=(const JsonData_Request& other)
        {
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
            return (*this);
        }

    public:
        FireboltSDK::JSON::String CorrelationId;
        Firebolt::Discovery::JsonData_UserInterestProviderParameters Parameters;
    };

    class JsonData_DiscoveryPolicy: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_DiscoveryPolicy() override = default;
  
    public:
        JsonData_DiscoveryPolicy()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("enableRecommendations"), &EnableRecommendations);
            Add(_T("shareWatchHistory"), &ShareWatchHistory);
            Add(_T("rememberWatchedPrograms"), &RememberWatchedPrograms);
        }

        JsonData_DiscoveryPolicy(const JsonData_DiscoveryPolicy& other)
        {
            Add(_T("enableRecommendations"), &EnableRecommendations);
            EnableRecommendations = other.EnableRecommendations;
            Add(_T("shareWatchHistory"), &ShareWatchHistory);
            ShareWatchHistory = other.ShareWatchHistory;
            Add(_T("rememberWatchedPrograms"), &RememberWatchedPrograms);
            RememberWatchedPrograms = other.RememberWatchedPrograms;
        }

        JsonData_DiscoveryPolicy& operator=(const JsonData_DiscoveryPolicy& other)
        {
            Add(_T("enableRecommendations"), &EnableRecommendations);
            EnableRecommendations = other.EnableRecommendations;
            Add(_T("shareWatchHistory"), &ShareWatchHistory);
            ShareWatchHistory = other.ShareWatchHistory;
            Add(_T("rememberWatchedPrograms"), &RememberWatchedPrograms);
            RememberWatchedPrograms = other.RememberWatchedPrograms;
            return (*this);
        }

    public:
        WPEFramework::Core::JSON::Boolean EnableRecommendations;
        WPEFramework::Core::JSON::Boolean ShareWatchHistory;
        WPEFramework::Core::JSON::Boolean RememberWatchedPrograms;
    };

    class JsonData_FederatedRequest: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_FederatedRequest() override = default;
  
    public:
        JsonData_FederatedRequest()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("correlationId"), &CorrelationId);
        }

        JsonData_FederatedRequest(const JsonData_FederatedRequest& other)
        {
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
        }

        JsonData_FederatedRequest& operator=(const JsonData_FederatedRequest& other)
        {
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
            return (*this);
        }

    public:
        FireboltSDK::JSON::String CorrelationId;
    };

    class JsonData_PurchasedContentParameters: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_PurchasedContentParameters() override = default;
  
    public:
        JsonData_PurchasedContentParameters()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("limit"), &Limit);
            Add(_T("offeringType"), &OfferingType);
            Add(_T("programType"), &ProgramType);
        }

        JsonData_PurchasedContentParameters(const JsonData_PurchasedContentParameters& other)
        {
            Add(_T("limit"), &Limit);
            Limit = other.Limit;
            Add(_T("offeringType"), &OfferingType);
            OfferingType = other.OfferingType;
            Add(_T("programType"), &ProgramType);
            ProgramType = other.ProgramType;
        }

        JsonData_PurchasedContentParameters& operator=(const JsonData_PurchasedContentParameters& other)
        {
            Add(_T("limit"), &Limit);
            Limit = other.Limit;
            Add(_T("offeringType"), &OfferingType);
            OfferingType = other.OfferingType;
            Add(_T("programType"), &ProgramType);
            ProgramType = other.ProgramType;
            return (*this);
        }

    public:
        WPEFramework::Core::JSON::DecSInt32 Limit;
        Firebolt::Entertainment::JsonData_OfferingType OfferingType;
        Firebolt::Entertainment::JsonData_ProgramType ProgramType;
    };

    class JsonData_EntityInfoParameters: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_EntityInfoParameters() override = default;
  
    public:
        JsonData_EntityInfoParameters()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("entityId"), &EntityId);
            Add(_T("assetId"), &AssetId);
        }

        JsonData_EntityInfoParameters(const JsonData_EntityInfoParameters& other)
        {
            Add(_T("entityId"), &EntityId);
            EntityId = other.EntityId;
            Add(_T("assetId"), &AssetId);
            AssetId = other.AssetId;
        }

        JsonData_EntityInfoParameters& operator=(const JsonData_EntityInfoParameters& other)
        {
            Add(_T("entityId"), &EntityId);
            EntityId = other.EntityId;
            Add(_T("assetId"), &AssetId);
            AssetId = other.AssetId;
            return (*this);
        }

    public:
        FireboltSDK::JSON::String EntityId;
        FireboltSDK::JSON::String AssetId;
    };

    class JsonData_EntityInfoFederatedRequest: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_EntityInfoFederatedRequest() override = default;
  
    public:
        JsonData_EntityInfoFederatedRequest()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("parameters"), &Parameters);
            Add(_T("correlationId"), &CorrelationId);
        }

        JsonData_EntityInfoFederatedRequest(const JsonData_EntityInfoFederatedRequest& other)
        {
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
        }

        JsonData_EntityInfoFederatedRequest& operator=(const JsonData_EntityInfoFederatedRequest& other)
        {
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
            return (*this);
        }

    public:
        Firebolt::Discovery::JsonData_EntityInfoParameters Parameters;
        FireboltSDK::JSON::String CorrelationId;
    };

    class JsonData_PurchasedContentFederatedRequest: public WPEFramework::Core::JSON::Container {
    public:
        ~JsonData_PurchasedContentFederatedRequest() override = default;
  
    public:
        JsonData_PurchasedContentFederatedRequest()
            : WPEFramework::Core::JSON::Container()
        {
            Add(_T("parameters"), &Parameters);
            Add(_T("correlationId"), &CorrelationId);
        }

        JsonData_PurchasedContentFederatedRequest(const JsonData_PurchasedContentFederatedRequest& other)
        {
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
        }

        JsonData_PurchasedContentFederatedRequest& operator=(const JsonData_PurchasedContentFederatedRequest& other)
        {
            Add(_T("parameters"), &Parameters);
            Parameters = other.Parameters;
            Add(_T("correlationId"), &CorrelationId);
            CorrelationId = other.CorrelationId;
            return (*this);
        }

    public:
        Firebolt::Discovery::JsonData_PurchasedContentParameters Parameters;
        FireboltSDK::JSON::String CorrelationId;
    };

    class DiscoveryImpl : public IDiscovery, public IModule {

    public:
        DiscoveryImpl() = default;
        DiscoveryImpl(const DiscoveryImpl&) = delete;
        DiscoveryImpl& operator=(const DiscoveryImpl&) = delete;

        ~DiscoveryImpl() override = default;

        // Methods & Events
        /*
         clearContentAccess
         Clear both availabilities and entitlements from the subscriber. This is equivalent of calling `Discovery.contentAccess({ availabilities: [], entitlements: []})`. This is typically called when the user signs out of an account.
         */
        void clearContentAccess( Firebolt::Error *err = nullptr ) override;

        /*
         contentAccess
         Inform the platform of what content the user can access either by discovering it or consuming it. Availabilities determine which content is discoverable to a user, while entitlements determine if the user can currently consume that content. Content can be available but not entitled, this means that user can see the content but when they try to open it they must gain an entitlement either through purchase or subscription upgrade. In case the access changed off-device, this API should be called any time the app comes to the foreground to refresh the access. This API should also be called any time the availabilities or entitlements change within the app for any reason. Typical reasons may include the user signing into an account or upgrading a subscription. Less common cases can cause availabilities to change, such as moving to a new service location. When availabilities or entitlements are removed from the subscriber (such as when the user signs out), then an empty array should be given. To clear both, use the Discovery.clearContentAccess convenience API.
         */
        void contentAccess( const ContentAccessIdentifiers& ids, Firebolt::Error *err = nullptr ) override;

        /*
         entitlements
         Inform the platform of the users latest entitlements w/in this app.
         */
        bool entitlements( const std::vector<Entertainment::Entitlement>& entitlements, Firebolt::Error *err = nullptr ) override;

        /*
         entityInfo
         Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow. Includes information about the program entity and its relevant associated entities, such as extras, previews, and, in the case of TV series, seasons and episodes.

See the `EntityInfo` and `WayToWatch` data structures below for more information.

The app only needs to implement Pull support for `entityInfo` at this time.
         */
        bool entityInfo( const EntityInfoResult& result, Firebolt::Error *err = nullptr ) override;

        /*
         launch
         Launch or foreground the specified app, and optionally instructs it to navigate to the specified user action. 
 For the Primary Experience, the appId can be any one of:  

 - xrn:firebolt:application-type:main 

 - xrn:firebolt:application-type:settings
         */
        bool launch( const std::string& appId, const std::optional<std::string>& intent, Firebolt::Error *err = nullptr ) override;

        // signature callback params: 
        // method result properties : 
        void subscribe( IDiscovery::IOnNavigateToNotification& notification, Firebolt::Error *err = nullptr ) override;
        void unsubscribe( IDiscovery::IOnNavigateToNotification& notification, Firebolt::Error *err = nullptr ) override;

        // signature callback params: 
        // method result properties : 
        void subscribe( IDiscovery::IOnPolicyChangedNotification& notification, Firebolt::Error *err = nullptr ) override;
        void unsubscribe( IDiscovery::IOnPolicyChangedNotification& notification, Firebolt::Error *err = nullptr ) override;

        void subscribe( IDiscovery::IOnPullEntityInfoNotification& notification, Firebolt::Error *err = nullptr ) override;
        void unsubscribe( IDiscovery::IOnPullEntityInfoNotification& notification, Firebolt::Error *err = nullptr ) override;

        void subscribe( IDiscovery::IOnPullPurchasedContentNotification& notification, Firebolt::Error *err = nullptr ) override;
        void unsubscribe( IDiscovery::IOnPullPurchasedContentNotification& notification, Firebolt::Error *err = nullptr ) override;

        /*
         * get the discovery policy
         * 
         */
        DiscoveryPolicy policy( Firebolt::Error *err = nullptr ) const override;
        /*
         provide
         undefined
         */
        void provide( const std::optional<bool>& enabled, Firebolt::Error *err = nullptr ) override;

        /*
         purchasedContent
         Return content purchased by the user, such as rentals and electronic sell through purchases.

The app should return the user's 100 most recent purchases in `entries`. The total count of purchases must be provided in `count`. If `count` is greater than the total number of `entries`, the UI may provide a link into the app to see the complete purchase list.

The `EntityInfo` object returned is not required to have `waysToWatch` populated, but it is recommended that it do so in case the UI wants to surface additional information on the purchases screen.

The app should implement both Push and Pull methods for `purchasedContent`.

The app should actively push `purchasedContent` when:

*  The app becomes Active.
*  When the state of the purchasedContent set has changed.
*  The app goes into Inactive or Background state, if there is a chance a change event has been missed.
         */
        bool purchasedContent( const PurchasedContentResult& result, Firebolt::Error *err = nullptr ) override;

        /*
         signIn
         Inform the platform that your user is signed in, for increased visibility in search & discovery. Sign-in state is used separately from what content can be access through entitlements and availabilities. Sign-in state may be used when deciding whether to choose this app to handle a user intent. For instance, if the user tries to launch something generic like playing music from an artist, only a signed-in app will be chosen. If the user wants to tune to a channel, only a signed-in app will be chosen to handle that intent. While signIn can optionally include entitlements as those typically change at signIn time, it is recommended to make a separate call to Discovery.contentAccess for entitlements. signIn is not only for when a user explicitly enters login credentials. If an app does not require any credentials from the user to consume content, such as in a free app, then the app should call signIn immediately on launch.
         */
        bool signIn( const std::optional<std::vector<Entertainment::Entitlement>>& entitlements, Firebolt::Error *err = nullptr ) override;

        /*
         signOut
         Inform the platform that your user has signed out. See `Discovery.signIn` for more details on how the sign-in state is used.signOut will NOT clear entitlements, the app should make a separate call to Discovery.clearContentAccess. Apps should also call signOut when a login token has expired and the user is now in a signed-out state.
         */
        bool signOut( Firebolt::Error *err = nullptr ) const override;

        /*
         watchNext
         Suggest a call-to-action for this app on the platform home screen
         */
        bool watchNext( const std::string& title, const Entertainment::ContentIdentifiers& identifiers, const std::optional<std::string>& expires, const std::optional<Images>& images, Firebolt::Error *err = nullptr ) override;

    };

} //namespace ${info.Title}
}${end.if.implementations}
