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

#include "error.h"
/* ${IMPORTS:h} */


${if.declarations}
namespace Firebolt {
namespace ${info.Title} {

${if.enums}/* ${ENUMS} */${end.if.enums}

/* InterestType  */
enum class InterestType {
    INTEREST,
    DISINTEREST
};

/* InterestReason  */
enum class InterestReason {
    PLAYLIST,
    REACTION,
    RECORDING
};

// Types
struct Availability {
    AvailabilityType type;
    std::string id;
    std::optional<std::string> catalogId;
    std::optional<std::string> startTime;
    std::optional<std::string> endTime;
};

struct UserInterestProviderParameters {
    InterestType type;
    InterestReason reason;
};

struct ContentAccessIdentifiers {
    std::optional<std::vector<Availability>> availabilities;
    std::optional<std::vector<Entertainment::Entitlement>> entitlements;
};

/* Images */
using Images = std::string;

struct DiscoveryPolicy {
    bool enableRecommendations;
    bool shareWatchHistory;
    bool rememberWatchedPrograms;
};

struct FederatedRequest {
    std::string correlationId;
};

struct PurchasedContentParameters {
    int32_t limit;
    std::optional<Entertainment::OfferingType> offeringType;
    std::optional<Entertainment::ProgramType> programType;
};

struct EntityInfoParameters {
    std::string entityId;
    std::optional<std::string> assetId;
};

struct EntityInfoFederatedRequest {
    EntityInfoParameters parameters;
};

struct PurchasedContentFederatedRequest {
    PurchasedContentParameters parameters;
};

// Provider Interfaces
struct IProviderSession {
    virtual ~IProviderSession() = default;
};

struct IFocussableProviderSession : virtual public IProviderSession {
    virtual ~IFocussableProviderSession() override = default;

    virtual void focus( Firebolt::Error *err = nullptr ) = 0;
};
struct IDiscoveryProvider {
    virtual ~IDiscoveryProvider() = default;

    virtual void userInterest( const UserInterestProviderParameters& parameters ) = 0;
};
struct IDiscovery {

    virtual ~IDiscovery() = default;

    // Methods & Events
    /*
     clearContentAccess
     Clear both availabilities and entitlements from the subscriber. This is equivalent of calling `Discovery.contentAccess({ availabilities: [], entitlements: []})`. This is typically called when the user signs out of an account.
     
     */
    virtual void clearContentAccess( Firebolt::Error *err = nullptr ) = 0;
    /*
     contentAccess
     Inform the platform of what content the user can access either by discovering it or consuming it. Availabilities determine which content is discoverable to a user, while entitlements determine if the user can currently consume that content. Content can be available but not entitled, this means that user can see the content but when they try to open it they must gain an entitlement either through purchase or subscription upgrade. In case the access changed off-device, this API should be called any time the app comes to the foreground to refresh the access. This API should also be called any time the availabilities or entitlements change within the app for any reason. Typical reasons may include the user signing into an account or upgrading a subscription. Less common cases can cause availabilities to change, such as moving to a new service location. When availabilities or entitlements are removed from the subscriber (such as when the user signs out), then an empty array should be given. To clear both, use the Discovery.clearContentAccess convenience API.
     
     */
    virtual void contentAccess( const ContentAccessIdentifiers& ids, Firebolt::Error *err = nullptr ) = 0;
    /*
     entitlements
     Inform the platform of the users latest entitlements w/in this app.
      * @deprecated since version 0.10.0
     */
    virtual bool entitlements( const std::vector<Entertainment::Entitlement>& entitlements, Firebolt::Error *err = nullptr ) = 0;
    /*
     entityInfo
     Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow. Includes information about the program entity and its relevant associated entities, such as extras, previews, and, in the case of TV series, seasons and episodes.

See the `EntityInfo` and `WayToWatch` data structures below for more information.

The app only needs to implement Pull support for `entityInfo` at this time.
      * @deprecated 
     */
    virtual bool entityInfo( const EntityInfoResult& result, Firebolt::Error *err = nullptr ) = 0;

    /*
     launch
     Launch or foreground the specified app, and optionally instructs it to navigate to the specified user action. 
 For the Primary Experience, the appId can be any one of:  

 - xrn:firebolt:application-type:main 

 - xrn:firebolt:application-type:settings
     
     */
    virtual bool launch( const std::string& appId, const std::optional<std::string>& intent, Firebolt::Error *err = nullptr ) = 0;
    /* onNavigateTo - listen to `navigateTo` events */
    struct IOnNavigateToNotification {
        virtual void onNavigateTo( const std::string& ) = 0;
    };
    // signature callback params: 
    // method result properties : 
    virtual void subscribe( IOnNavigateToNotification& notification, Firebolt::Error *err = nullptr ) = 0;
    virtual void unsubscribe( IOnNavigateToNotification& notification, Firebolt::Error *err = nullptr ) = 0;

    /* onPolicyChanged - get the discovery policy */
    struct IOnPolicyChangedNotification {
        virtual void onPolicyChanged( const DiscoveryPolicy& ) = 0;
    };
    // signature callback params: 
    // method result properties : 
    virtual void subscribe( IOnPolicyChangedNotification& notification, Firebolt::Error *err = nullptr ) = 0;
    virtual void unsubscribe( IOnPolicyChangedNotification& notification, Firebolt::Error *err = nullptr ) = 0;

    /* onPullEntityInfo - Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow. Includes information about the program entity and its relevant associated entities, such as extras, previews, and, in the case of TV series, seasons and episodes.

See the `EntityInfo` and `WayToWatch` data structures below for more information.

The app only needs to implement Pull support for `entityInfo` at this time. */
    struct IOnPullEntityInfoNotification {
        virtual EntityInfoResult onPullEntityInfo( EntityInfoParameters ) = 0;
    };
    virtual void subscribe( IOnPullEntityInfoNotification& notification, Firebolt::Error *err = nullptr ) = 0;
    virtual void unsubscribe( IOnPullEntityInfoNotification& notification, Firebolt::Error *err = nullptr ) = 0;

    /* onPullPurchasedContent - Return content purchased by the user, such as rentals and electronic sell through purchases.

The app should return the user's 100 most recent purchases in `entries`. The total count of purchases must be provided in `count`. If `count` is greater than the total number of `entries`, the UI may provide a link into the app to see the complete purchase list.

The `EntityInfo` object returned is not required to have `waysToWatch` populated, but it is recommended that it do so in case the UI wants to surface additional information on the purchases screen.

The app should implement both Push and Pull methods for `purchasedContent`.

The app should actively push `purchasedContent` when:

*  The app becomes Active.
*  When the state of the purchasedContent set has changed.
*  The app goes into Inactive or Background state, if there is a chance a change event has been missed. */
    struct IOnPullPurchasedContentNotification {
        virtual PurchasedContentResult onPullPurchasedContent( PurchasedContentParameters ) = 0;
    };
    virtual void subscribe( IOnPullPurchasedContentNotification& notification, Firebolt::Error *err = nullptr ) = 0;
    virtual void unsubscribe( IOnPullPurchasedContentNotification& notification, Firebolt::Error *err = nullptr ) = 0;

    /*
     * get the discovery policy
     * 
     */
    virtual DiscoveryPolicy policy( Firebolt::Error *err = nullptr ) const = 0;

    /*
     provide
     undefined
     
     */
    virtual void provide( const std::optional<bool>& enabled, Firebolt::Error *err = nullptr ) = 0;
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
      * @deprecated 
     */
    virtual bool purchasedContent( const PurchasedContentResult& result, Firebolt::Error *err = nullptr ) = 0;

    /*
     signIn
     Inform the platform that your user is signed in, for increased visibility in search & discovery. Sign-in state is used separately from what content can be access through entitlements and availabilities. Sign-in state may be used when deciding whether to choose this app to handle a user intent. For instance, if the user tries to launch something generic like playing music from an artist, only a signed-in app will be chosen. If the user wants to tune to a channel, only a signed-in app will be chosen to handle that intent. While signIn can optionally include entitlements as those typically change at signIn time, it is recommended to make a separate call to Discovery.contentAccess for entitlements. signIn is not only for when a user explicitly enters login credentials. If an app does not require any credentials from the user to consume content, such as in a free app, then the app should call signIn immediately on launch.
     
     */
    virtual bool signIn( const std::optional<std::vector<Entertainment::Entitlement>>& entitlements, Firebolt::Error *err = nullptr ) = 0;

    /*
     signOut
     Inform the platform that your user has signed out. See `Discovery.signIn` for more details on how the sign-in state is used.signOut will NOT clear entitlements, the app should make a separate call to Discovery.clearContentAccess. Apps should also call signOut when a login token has expired and the user is now in a signed-out state.
     
     */
    virtual bool signOut( Firebolt::Error *err = nullptr ) const = 0;

    /*
     watchNext
     Suggest a call-to-action for this app on the platform home screen
     
     */
    virtual bool watchNext( const std::string& title, const Entertainment::ContentIdentifiers& identifiers, const std::optional<std::string>& expires, const std::optional<Images>& images, Firebolt::Error *err = nullptr ) = 0;
};

} //namespace ${info.Title}
}
${end.if.declarations}

