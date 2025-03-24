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

#include "${info.title.lowercase}_impl.h"
#include "Gateway/Gateway.h"

${if.implementations}
namespace Firebolt {
namespace ${info.Title} {

    static void DiscoveryUserInterestSessionInnerCallback( void* provider, const void* userData, void* jsonRequest )
    {
        WPEFramework::Core::ProxyType<JsonData_Request>& proxyRequest = *(reinterpret_cast<WPEFramework::Core::ProxyType<JsonData_Request>*>(jsonRequest));

        ASSERT(proxyRequest.IsValid() == true);

        if (!proxyRequest.IsValid()) {
            return;
        }

        UserInterestProviderParameters parameters;

        parameters.type = (*proxyRequest).Parameters.Type;
        parameters.reason = (*proxyRequest).Parameters.Reason;

        proxyRequest.Release();

        IDiscoveryProvider& discoveryProvider = *(reinterpret_cast<IDiscoveryProvider*>(provider));
        discoveryProvider.userInterest(parameters);
    }

    // Methods
    /* clearContentAccess - Clear both availabilities and entitlements from the subscriber. This is equivalent of calling `Discovery.contentAccess({ availabilities: [], entitlements: []})`. This is typically called when the user signs out of an account. */
    void DiscoveryImpl::clearContentAccess( Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;


        JsonObject jsonParameters;

        WPEFramework::Core::JSON::VariantContainer jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.clearContentAccess", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.clearContentAccess is successfully invoked");

        }

        if (err != nullptr) {
            *err = status;
        }

        return;
    }

    /* contentAccess - Inform the platform of what content the user can access either by discovering it or consuming it. Availabilities determine which content is discoverable to a user, while entitlements determine if the user can currently consume that content. Content can be available but not entitled, this means that user can see the content but when they try to open it they must gain an entitlement either through purchase or subscription upgrade. In case the access changed off-device, this API should be called any time the app comes to the foreground to refresh the access. This API should also be called any time the availabilities or entitlements change within the app for any reason. Typical reasons may include the user signing into an account or upgrading a subscription. Less common cases can cause availabilities to change, such as moving to a new service location. When availabilities or entitlements are removed from the subscriber (such as when the user signs out), then an empty array should be given. To clear both, use the Discovery.clearContentAccess convenience API. */
    void DiscoveryImpl::contentAccess( const ContentAccessIdentifiers& ids, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;


        JsonObject jsonParameters;
        auto element = ids;
            JsonData_ContentAccessIdentifiers idsContainer;
            {
                if (element.availabilities.has_value()) {
                    WPEFramework::Core::JSON::ArrayType<Firebolt::Discovery::JsonData_Availability> availabilitiesArray;
                    std::vector<Availability> availabilities = element.availabilities.value();
                    for (auto& element : availabilities) {
                        Firebolt::Discovery::JsonData_Availability availabilitiesContainer;
                        {
                            availabilitiesContainer.Type = element.type;
                            availabilitiesContainer.Id = element.id;
                            if (element.catalogId.has_value()) {
                                availabilitiesContainer.CatalogId = element.catalogId.value();
                            }
                            if (element.startTime.has_value()) {
                                availabilitiesContainer.StartTime = element.startTime.value();
                            }
                            if (element.endTime.has_value()) {
                                availabilitiesContainer.EndTime = element.endTime.value();
                            }
                        }
                        availabilitiesArray.Add() = availabilitiesContainer;
                    }
                    idsContainer.Availabilities = availabilitiesArray;
                }
                if (element.entitlements.has_value()) {
                    WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_Entitlement> entitlementsArray;
                    std::vector<Entertainment::Entitlement> entitlements = element.entitlements.value();
                    for (auto& element : entitlements) {
                        Firebolt::Entertainment::JsonData_Entitlement entitlementsContainer;
                        {
                            entitlementsContainer.EntitlementId = element.entitlementId;
                            if (element.startTime.has_value()) {
                                entitlementsContainer.StartTime = element.startTime.value();
                            }
                            if (element.endTime.has_value()) {
                                entitlementsContainer.EndTime = element.endTime.value();
                            }
                        }
                        entitlementsArray.Add() = entitlementsContainer;
                    }
                    idsContainer.Entitlements = entitlementsArray;
                }
            }
            string idsStr;
            idsContainer.ToString(idsStr);
            WPEFramework::Core::JSON::VariantContainer idsVariantContainer(idsStr);
            WPEFramework::Core::JSON::Variant idsVariant = idsVariantContainer;
            jsonParameters.Set(_T("ids"), idsVariant);
        WPEFramework::Core::JSON::VariantContainer jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.contentAccess", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.contentAccess is successfully invoked");

        }

        if (err != nullptr) {
            *err = status;
        }

        return;
    }

    /* entitlements - Inform the platform of the users latest entitlements w/in this app. */
    bool DiscoveryImpl::entitlements( const std::vector<Entertainment::Entitlement>& entitlements, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;

        JsonObject jsonParameters;
        WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Variant> entitlementsArray;
            for (auto& element : entitlements) {
                Firebolt::Entertainment::JsonData_Entitlement entitlementsContainer;
                {
                        entitlementsContainer.EntitlementId = element.entitlementId;
                        if (element.startTime.has_value()) {
                            entitlementsContainer.StartTime = element.startTime.value();
                        }
                        if (element.endTime.has_value()) {
                            entitlementsContainer.EndTime = element.endTime.value();
                        }
                }
                string entitlementsStr;
                entitlementsContainer.ToString(entitlementsStr);
                WPEFramework::Core::JSON::VariantContainer entitlementsVariantContainer(entitlementsStr);
                WPEFramework::Core::JSON::Variant entitlementsVariant = entitlementsVariantContainer;
                entitlementsArray.Add() = entitlementsVariant;
            }
            WPEFramework::Core::JSON::Variant entitlementsVariant;
            entitlementsVariant.Array(entitlementsArray);
            jsonParameters.Set(_T("entitlements"), entitlementsVariant);
        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.entitlements", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.entitlements is successfully invoked");
            success = jsonResult.Value();
        }

        if (err != nullptr) {
            *err = status;
        }

        return success;
    }

    /* entityInfo - Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow. Includes information about the program entity and its relevant associated entities, such as extras, previews, and, in the case of TV series, seasons and episodes.

See the `EntityInfo` and `WayToWatch` data structures below for more information.

The app only needs to implement Pull support for `entityInfo` at this time. */
    bool DiscoveryImpl::entityInfo( const EntityInfoResult& result, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;
        string correlationId = "";
        JsonObject jsonParameters;
        WPEFramework::Core::JSON::Variant correlationIdVariant(correlationId);
            jsonParameters.Set(_T("correlationId"), correlationIdVariant);
            auto element = result;
            JsonData_EntityInfoResult resultContainer;
            {
                resultContainer.Expires = element.expires;
                {
                    {
                        if (element.entity.identifiers.assetId.has_value()) {
                            resultContainer.Entity.Identifiers.AssetId = element.entity.identifiers.assetId.value();
                        }
                        if (element.entity.identifiers.entityId.has_value()) {
                            resultContainer.Entity.Identifiers.EntityId = element.entity.identifiers.entityId.value();
                        }
                        if (element.entity.identifiers.seasonId.has_value()) {
                            resultContainer.Entity.Identifiers.SeasonId = element.entity.identifiers.seasonId.value();
                        }
                        if (element.entity.identifiers.seriesId.has_value()) {
                            resultContainer.Entity.Identifiers.SeriesId = element.entity.identifiers.seriesId.value();
                        }
                        if (element.entity.identifiers.appContentData.has_value()) {
                            resultContainer.Entity.Identifiers.AppContentData = element.entity.identifiers.appContentData.value();
                        }
                    }
                    resultContainer.Entity.Title = element.entity.title;
                    resultContainer.Entity.EntityType = element.entity.entityType;
                    if (element.entity.programType.has_value()) {
                        resultContainer.Entity.ProgramType = element.entity.programType.value();
                    }
                    if (element.entity.musicType.has_value()) {
                        resultContainer.Entity.MusicType = element.entity.musicType.value();
                    }
                    if (element.entity.synopsis.has_value()) {
                        resultContainer.Entity.Synopsis = element.entity.synopsis.value();
                    }
                    if (element.entity.seasonNumber.has_value()) {
                        resultContainer.Entity.SeasonNumber = element.entity.seasonNumber.value();
                    }
                    if (element.entity.seasonCount.has_value()) {
                        resultContainer.Entity.SeasonCount = element.entity.seasonCount.value();
                    }
                    if (element.entity.episodeNumber.has_value()) {
                        resultContainer.Entity.EpisodeNumber = element.entity.episodeNumber.value();
                    }
                    if (element.entity.episodeCount.has_value()) {
                        resultContainer.Entity.EpisodeCount = element.entity.episodeCount.value();
                    }
                    if (element.entity.releaseDate.has_value()) {
                        resultContainer.Entity.ReleaseDate = element.entity.releaseDate.value();
                    }
                    if (element.entity.contentRatings.has_value()) {
                        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_ContentRating> contentRatingsArray;
                        std::vector<Entertainment::ContentRating> contentRatings = element.entity.contentRatings.value();
                        for (auto& element : contentRatings) {
                            Firebolt::Entertainment::JsonData_ContentRating contentRatingsContainer;
                            {
                                contentRatingsContainer.Scheme = element.scheme;
                                contentRatingsContainer.Rating = element.rating;
                                if (element.advisories.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> advisoriesArray;
                                    std::vector<std::string> advisories = element.advisories.value();
                                    for (auto& element : advisories) {
                                        advisoriesArray.Add() = element;
                                    }
                                    contentRatingsContainer.Advisories = advisoriesArray;
                                }
                            }
                            contentRatingsArray.Add() = contentRatingsContainer;
                        }
                        resultContainer.Entity.ContentRatings = contentRatingsArray;
                    }
                    if (element.entity.waysToWatch.has_value()) {
                        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatch> waysToWatchArray;
                        std::vector<Entertainment::WayToWatch> waysToWatch = element.entity.waysToWatch.value();
                        for (auto& element : waysToWatch) {
                            Firebolt::Entertainment::JsonData_WayToWatch waysToWatchContainer;
                            {
                                {
                                    if (element.identifiers.assetId.has_value()) {
                                        waysToWatchContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                    }
                                    if (element.identifiers.entityId.has_value()) {
                                        waysToWatchContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                    }
                                    if (element.identifiers.seasonId.has_value()) {
                                        waysToWatchContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                    }
                                    if (element.identifiers.seriesId.has_value()) {
                                        waysToWatchContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                    }
                                    if (element.identifiers.appContentData.has_value()) {
                                        waysToWatchContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                    }
                                }
                                if (element.expires.has_value()) {
                                    waysToWatchContainer.Expires = element.expires.value();
                                }
                                if (element.entitled.has_value()) {
                                    waysToWatchContainer.Entitled = element.entitled.value();
                                }
                                if (element.entitledExpires.has_value()) {
                                    waysToWatchContainer.EntitledExpires = element.entitledExpires.value();
                                }
                                if (element.offeringType.has_value()) {
                                    waysToWatchContainer.OfferingType = element.offeringType.value();
                                }
                                if (element.hasAds.has_value()) {
                                    waysToWatchContainer.HasAds = element.hasAds.value();
                                }
                                if (element.price.has_value()) {
                                    waysToWatchContainer.Price = element.price.value();
                                }
                                if (element.videoQuality.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatchVideoQuality> videoQualityArray;
                                    std::vector<Entertainment::WayToWatchVideoQuality> videoQuality = element.videoQuality.value();
                                    for (auto& element : videoQuality) {
                                        videoQualityArray.Add() = element;
                                    }
                                    waysToWatchContainer.VideoQuality = videoQualityArray;
                                }
                                WPEFramework::Core::JSON::ArrayType<Firebolt::Types::JsonData_AudioProfile> audioProfileArray;
                                std::vector<Types::AudioProfile> audioProfile = element.audioProfile;
                                for (auto& element : audioProfile) {
                                    audioProfileArray.Add() = element;
                                }
                                waysToWatchContainer.AudioProfile = audioProfileArray;
                                if (element.audioLanguages.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioLanguagesArray;
                                    std::vector<std::string> audioLanguages = element.audioLanguages.value();
                                    for (auto& element : audioLanguages) {
                                        audioLanguagesArray.Add() = element;
                                    }
                                    waysToWatchContainer.AudioLanguages = audioLanguagesArray;
                                }
                                if (element.closedCaptions.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> closedCaptionsArray;
                                    std::vector<std::string> closedCaptions = element.closedCaptions.value();
                                    for (auto& element : closedCaptions) {
                                        closedCaptionsArray.Add() = element;
                                    }
                                    waysToWatchContainer.ClosedCaptions = closedCaptionsArray;
                                }
                                if (element.subtitles.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> subtitlesArray;
                                    std::vector<std::string> subtitles = element.subtitles.value();
                                    for (auto& element : subtitles) {
                                        subtitlesArray.Add() = element;
                                    }
                                    waysToWatchContainer.Subtitles = subtitlesArray;
                                }
                                if (element.audioDescriptions.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioDescriptionsArray;
                                    std::vector<std::string> audioDescriptions = element.audioDescriptions.value();
                                    for (auto& element : audioDescriptions) {
                                        audioDescriptionsArray.Add() = element;
                                    }
                                    waysToWatchContainer.AudioDescriptions = audioDescriptionsArray;
                                }
                            }
                            waysToWatchArray.Add() = waysToWatchContainer;
                        }
                        resultContainer.Entity.WaysToWatch = waysToWatchArray;
                    }
                }
                if (element.related.has_value()) {
                    WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_EntityInfo> relatedArray;
                    std::vector<Entertainment::EntityInfo> related = element.related.value();
                    for (auto& element : related) {
                        Firebolt::Entertainment::JsonData_EntityInfo relatedContainer;
                        {
                            {
                                if (element.identifiers.assetId.has_value()) {
                                    relatedContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                }
                                if (element.identifiers.entityId.has_value()) {
                                    relatedContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                }
                                if (element.identifiers.seasonId.has_value()) {
                                    relatedContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                }
                                if (element.identifiers.seriesId.has_value()) {
                                    relatedContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                }
                                if (element.identifiers.appContentData.has_value()) {
                                    relatedContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                }
                            }
                            relatedContainer.Title = element.title;
                            relatedContainer.EntityType = element.entityType;
                            if (element.programType.has_value()) {
                                relatedContainer.ProgramType = element.programType.value();
                            }
                            if (element.musicType.has_value()) {
                                relatedContainer.MusicType = element.musicType.value();
                            }
                            if (element.synopsis.has_value()) {
                                relatedContainer.Synopsis = element.synopsis.value();
                            }
                            if (element.seasonNumber.has_value()) {
                                relatedContainer.SeasonNumber = element.seasonNumber.value();
                            }
                            if (element.seasonCount.has_value()) {
                                relatedContainer.SeasonCount = element.seasonCount.value();
                            }
                            if (element.episodeNumber.has_value()) {
                                relatedContainer.EpisodeNumber = element.episodeNumber.value();
                            }
                            if (element.episodeCount.has_value()) {
                                relatedContainer.EpisodeCount = element.episodeCount.value();
                            }
                            if (element.releaseDate.has_value()) {
                                relatedContainer.ReleaseDate = element.releaseDate.value();
                            }
                            if (element.contentRatings.has_value()) {
                                WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_ContentRating> contentRatingsArray;
                                std::vector<Entertainment::ContentRating> contentRatings = element.contentRatings.value();
                                for (auto& element : contentRatings) {
                                    Firebolt::Entertainment::JsonData_ContentRating contentRatingsContainer;
                                    {
                                        contentRatingsContainer.Scheme = element.scheme;
                                        contentRatingsContainer.Rating = element.rating;
                                        if (element.advisories.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> advisoriesArray;
                                            std::vector<std::string> advisories = element.advisories.value();
                                            for (auto& element : advisories) {
                                                advisoriesArray.Add() = element;
                                            }
                                            contentRatingsContainer.Advisories = advisoriesArray;
                                        }
                                    }
                                    contentRatingsArray.Add() = contentRatingsContainer;
                                }
                                relatedContainer.ContentRatings = contentRatingsArray;
                            }
                            if (element.waysToWatch.has_value()) {
                                WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatch> waysToWatchArray;
                                std::vector<Entertainment::WayToWatch> waysToWatch = element.waysToWatch.value();
                                for (auto& element : waysToWatch) {
                                    Firebolt::Entertainment::JsonData_WayToWatch waysToWatchContainer;
                                    {
                                        {
                                            if (element.identifiers.assetId.has_value()) {
                                                waysToWatchContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                            }
                                            if (element.identifiers.entityId.has_value()) {
                                                waysToWatchContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                            }
                                            if (element.identifiers.seasonId.has_value()) {
                                                waysToWatchContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                            }
                                            if (element.identifiers.seriesId.has_value()) {
                                                waysToWatchContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                            }
                                            if (element.identifiers.appContentData.has_value()) {
                                                waysToWatchContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                            }
                                        }
                                        if (element.expires.has_value()) {
                                            waysToWatchContainer.Expires = element.expires.value();
                                        }
                                        if (element.entitled.has_value()) {
                                            waysToWatchContainer.Entitled = element.entitled.value();
                                        }
                                        if (element.entitledExpires.has_value()) {
                                            waysToWatchContainer.EntitledExpires = element.entitledExpires.value();
                                        }
                                        if (element.offeringType.has_value()) {
                                            waysToWatchContainer.OfferingType = element.offeringType.value();
                                        }
                                        if (element.hasAds.has_value()) {
                                            waysToWatchContainer.HasAds = element.hasAds.value();
                                        }
                                        if (element.price.has_value()) {
                                            waysToWatchContainer.Price = element.price.value();
                                        }
                                        if (element.videoQuality.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatchVideoQuality> videoQualityArray;
                                            std::vector<Entertainment::WayToWatchVideoQuality> videoQuality = element.videoQuality.value();
                                            for (auto& element : videoQuality) {
                                                videoQualityArray.Add() = element;
                                            }
                                            waysToWatchContainer.VideoQuality = videoQualityArray;
                                        }
                                        WPEFramework::Core::JSON::ArrayType<Firebolt::Types::JsonData_AudioProfile> audioProfileArray;
                                        std::vector<Types::AudioProfile> audioProfile = element.audioProfile;
                                        for (auto& element : audioProfile) {
                                            audioProfileArray.Add() = element;
                                        }
                                        waysToWatchContainer.AudioProfile = audioProfileArray;
                                        if (element.audioLanguages.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioLanguagesArray;
                                            std::vector<std::string> audioLanguages = element.audioLanguages.value();
                                            for (auto& element : audioLanguages) {
                                                audioLanguagesArray.Add() = element;
                                            }
                                            waysToWatchContainer.AudioLanguages = audioLanguagesArray;
                                        }
                                        if (element.closedCaptions.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> closedCaptionsArray;
                                            std::vector<std::string> closedCaptions = element.closedCaptions.value();
                                            for (auto& element : closedCaptions) {
                                                closedCaptionsArray.Add() = element;
                                            }
                                            waysToWatchContainer.ClosedCaptions = closedCaptionsArray;
                                        }
                                        if (element.subtitles.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> subtitlesArray;
                                            std::vector<std::string> subtitles = element.subtitles.value();
                                            for (auto& element : subtitles) {
                                                subtitlesArray.Add() = element;
                                            }
                                            waysToWatchContainer.Subtitles = subtitlesArray;
                                        }
                                        if (element.audioDescriptions.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioDescriptionsArray;
                                            std::vector<std::string> audioDescriptions = element.audioDescriptions.value();
                                            for (auto& element : audioDescriptions) {
                                                audioDescriptionsArray.Add() = element;
                                            }
                                            waysToWatchContainer.AudioDescriptions = audioDescriptionsArray;
                                        }
                                    }
                                    waysToWatchArray.Add() = waysToWatchContainer;
                                }
                                relatedContainer.WaysToWatch = waysToWatchArray;
                            }
                        }
                        relatedArray.Add() = relatedContainer;
                    }
                    resultContainer.Related = relatedArray;
                }
            }
            string resultStr;
            resultContainer.ToString(resultStr);
            WPEFramework::Core::JSON::VariantContainer resultVariantContainer(resultStr);
            WPEFramework::Core::JSON::Variant resultVariant = resultVariantContainer;
            jsonParameters.Set(_T("result"), resultVariant);
        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.entityInfo", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.entityInfo is successfully invoked");
            success = jsonResult.Value();
        }


        if (err != nullptr) {
            *err = status;
        }

        return success;
    }

    /* launch - Launch or foreground the specified app, and optionally instructs it to navigate to the specified user action. 
 For the Primary Experience, the appId can be any one of:  

 - xrn:firebolt:application-type:main 

 - xrn:firebolt:application-type:settings */
    bool DiscoveryImpl::launch( const std::string& appId, const std::optional<std::string>& intent, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;

        JsonObject jsonParameters;
        WPEFramework::Core::JSON::Variant appIdVariant(appId);
            jsonParameters.Set(_T("appId"), appIdVariant);
            if (intent.has_value()) {
                WPEFramework::Core::JSON::Variant intentVariant(intent.value());
                jsonParameters.Set(_T("intent"), intentVariant);
            }
        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.launch", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.launch is successfully invoked");
            success = jsonResult.Value();
        }

        if (err != nullptr) {
            *err = status;
        }

        return success;
    }

    /* policy - get the discovery policy */
    DiscoveryPolicy DiscoveryImpl::policy( Firebolt::Error *err ) const
    {
        const string method = _T("discovery.policy");
        
        
        Firebolt::Discovery::JsonData_DiscoveryPolicy jsonResult;
        DiscoveryPolicy policy;
        
        Firebolt::Error status = FireboltSDK::Properties::Get(method, jsonResult);
        if (status == Firebolt::Error::None) {
            DiscoveryPolicy policyResult;
            policyResult.enableRecommendations = jsonResult.EnableRecommendations.Value();
            policyResult.shareWatchHistory = jsonResult.ShareWatchHistory.Value();
            policyResult.rememberWatchedPrograms = jsonResult.RememberWatchedPrograms.Value();
            policy = policyResult;
        }
        if (err != nullptr) {
            *err = status;
        }

        return policy;
    }

    /* provide - undefined */
    void DiscoveryImpl::provide( const std::optional<bool>& enabled, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;


        JsonObject jsonParameters;
        if (enabled.has_value()) {
                WPEFramework::Core::JSON::Variant enabledVariant(enabled.value());
                jsonParameters.Set(_T("enabled"), enabledVariant);
            }
        WPEFramework::Core::JSON::VariantContainer jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.provide", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.provide is successfully invoked");

        }

        if (err != nullptr) {
            *err = status;
        }

        return;
    }

    /* purchasedContent - Return content purchased by the user, such as rentals and electronic sell through purchases.

The app should return the user's 100 most recent purchases in `entries`. The total count of purchases must be provided in `count`. If `count` is greater than the total number of `entries`, the UI may provide a link into the app to see the complete purchase list.

The `EntityInfo` object returned is not required to have `waysToWatch` populated, but it is recommended that it do so in case the UI wants to surface additional information on the purchases screen.

The app should implement both Push and Pull methods for `purchasedContent`.

The app should actively push `purchasedContent` when:

*  The app becomes Active.
*  When the state of the purchasedContent set has changed.
*  The app goes into Inactive or Background state, if there is a chance a change event has been missed. */
    bool DiscoveryImpl::purchasedContent( const PurchasedContentResult& result, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;
        string correlationId = "";
        JsonObject jsonParameters;
        WPEFramework::Core::JSON::Variant correlationIdVariant(correlationId);
            jsonParameters.Set(_T("correlationId"), correlationIdVariant);
            auto element = result;
            JsonData_PurchasedContentResult resultContainer;
            {
                resultContainer.Expires = element.expires;
                resultContainer.TotalCount = element.totalCount;
                WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_EntityInfo> entriesArray;
                std::vector<Entertainment::EntityInfo> entries = element.entries;
                for (auto& element : entries) {
                    Firebolt::Entertainment::JsonData_EntityInfo entriesContainer;
                    {
                        {
                            if (element.identifiers.assetId.has_value()) {
                                entriesContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                            }
                            if (element.identifiers.entityId.has_value()) {
                                entriesContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                            }
                            if (element.identifiers.seasonId.has_value()) {
                                entriesContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                            }
                            if (element.identifiers.seriesId.has_value()) {
                                entriesContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                            }
                            if (element.identifiers.appContentData.has_value()) {
                                entriesContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                            }
                        }
                        entriesContainer.Title = element.title;
                        entriesContainer.EntityType = element.entityType;
                        if (element.programType.has_value()) {
                            entriesContainer.ProgramType = element.programType.value();
                        }
                        if (element.musicType.has_value()) {
                            entriesContainer.MusicType = element.musicType.value();
                        }
                        if (element.synopsis.has_value()) {
                            entriesContainer.Synopsis = element.synopsis.value();
                        }
                        if (element.seasonNumber.has_value()) {
                            entriesContainer.SeasonNumber = element.seasonNumber.value();
                        }
                        if (element.seasonCount.has_value()) {
                            entriesContainer.SeasonCount = element.seasonCount.value();
                        }
                        if (element.episodeNumber.has_value()) {
                            entriesContainer.EpisodeNumber = element.episodeNumber.value();
                        }
                        if (element.episodeCount.has_value()) {
                            entriesContainer.EpisodeCount = element.episodeCount.value();
                        }
                        if (element.releaseDate.has_value()) {
                            entriesContainer.ReleaseDate = element.releaseDate.value();
                        }
                        if (element.contentRatings.has_value()) {
                            WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_ContentRating> contentRatingsArray;
                            std::vector<Entertainment::ContentRating> contentRatings = element.contentRatings.value();
                            for (auto& element : contentRatings) {
                                Firebolt::Entertainment::JsonData_ContentRating contentRatingsContainer;
                                {
                                    contentRatingsContainer.Scheme = element.scheme;
                                    contentRatingsContainer.Rating = element.rating;
                                    if (element.advisories.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> advisoriesArray;
                                        std::vector<std::string> advisories = element.advisories.value();
                                        for (auto& element : advisories) {
                                            advisoriesArray.Add() = element;
                                        }
                                        contentRatingsContainer.Advisories = advisoriesArray;
                                    }
                                }
                                contentRatingsArray.Add() = contentRatingsContainer;
                            }
                            entriesContainer.ContentRatings = contentRatingsArray;
                        }
                        if (element.waysToWatch.has_value()) {
                            WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatch> waysToWatchArray;
                            std::vector<Entertainment::WayToWatch> waysToWatch = element.waysToWatch.value();
                            for (auto& element : waysToWatch) {
                                Firebolt::Entertainment::JsonData_WayToWatch waysToWatchContainer;
                                {
                                    {
                                        if (element.identifiers.assetId.has_value()) {
                                            waysToWatchContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                        }
                                        if (element.identifiers.entityId.has_value()) {
                                            waysToWatchContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                        }
                                        if (element.identifiers.seasonId.has_value()) {
                                            waysToWatchContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                        }
                                        if (element.identifiers.seriesId.has_value()) {
                                            waysToWatchContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                        }
                                        if (element.identifiers.appContentData.has_value()) {
                                            waysToWatchContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                        }
                                    }
                                    if (element.expires.has_value()) {
                                        waysToWatchContainer.Expires = element.expires.value();
                                    }
                                    if (element.entitled.has_value()) {
                                        waysToWatchContainer.Entitled = element.entitled.value();
                                    }
                                    if (element.entitledExpires.has_value()) {
                                        waysToWatchContainer.EntitledExpires = element.entitledExpires.value();
                                    }
                                    if (element.offeringType.has_value()) {
                                        waysToWatchContainer.OfferingType = element.offeringType.value();
                                    }
                                    if (element.hasAds.has_value()) {
                                        waysToWatchContainer.HasAds = element.hasAds.value();
                                    }
                                    if (element.price.has_value()) {
                                        waysToWatchContainer.Price = element.price.value();
                                    }
                                    if (element.videoQuality.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatchVideoQuality> videoQualityArray;
                                        std::vector<Entertainment::WayToWatchVideoQuality> videoQuality = element.videoQuality.value();
                                        for (auto& element : videoQuality) {
                                            videoQualityArray.Add() = element;
                                        }
                                        waysToWatchContainer.VideoQuality = videoQualityArray;
                                    }
                                    WPEFramework::Core::JSON::ArrayType<Firebolt::Types::JsonData_AudioProfile> audioProfileArray;
                                    std::vector<Types::AudioProfile> audioProfile = element.audioProfile;
                                    for (auto& element : audioProfile) {
                                        audioProfileArray.Add() = element;
                                    }
                                    waysToWatchContainer.AudioProfile = audioProfileArray;
                                    if (element.audioLanguages.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioLanguagesArray;
                                        std::vector<std::string> audioLanguages = element.audioLanguages.value();
                                        for (auto& element : audioLanguages) {
                                            audioLanguagesArray.Add() = element;
                                        }
                                        waysToWatchContainer.AudioLanguages = audioLanguagesArray;
                                    }
                                    if (element.closedCaptions.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> closedCaptionsArray;
                                        std::vector<std::string> closedCaptions = element.closedCaptions.value();
                                        for (auto& element : closedCaptions) {
                                            closedCaptionsArray.Add() = element;
                                        }
                                        waysToWatchContainer.ClosedCaptions = closedCaptionsArray;
                                    }
                                    if (element.subtitles.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> subtitlesArray;
                                        std::vector<std::string> subtitles = element.subtitles.value();
                                        for (auto& element : subtitles) {
                                            subtitlesArray.Add() = element;
                                        }
                                        waysToWatchContainer.Subtitles = subtitlesArray;
                                    }
                                    if (element.audioDescriptions.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioDescriptionsArray;
                                        std::vector<std::string> audioDescriptions = element.audioDescriptions.value();
                                        for (auto& element : audioDescriptions) {
                                            audioDescriptionsArray.Add() = element;
                                        }
                                        waysToWatchContainer.AudioDescriptions = audioDescriptionsArray;
                                    }
                                }
                                waysToWatchArray.Add() = waysToWatchContainer;
                            }
                            entriesContainer.WaysToWatch = waysToWatchArray;
                        }
                    }
                    entriesArray.Add() = entriesContainer;
                }
                resultContainer.Entries = entriesArray;
            }
            string resultStr;
            resultContainer.ToString(resultStr);
            WPEFramework::Core::JSON::VariantContainer resultVariantContainer(resultStr);
            WPEFramework::Core::JSON::Variant resultVariant = resultVariantContainer;
            jsonParameters.Set(_T("result"), resultVariant);
        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.purchasedContent", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.purchasedContent is successfully invoked");
            success = jsonResult.Value();
        }


        if (err != nullptr) {
            *err = status;
        }

        return success;
    }

    /* signIn - Inform the platform that your user is signed in, for increased visibility in search & discovery. Sign-in state is used separately from what content can be access through entitlements and availabilities. Sign-in state may be used when deciding whether to choose this app to handle a user intent. For instance, if the user tries to launch something generic like playing music from an artist, only a signed-in app will be chosen. If the user wants to tune to a channel, only a signed-in app will be chosen to handle that intent. While signIn can optionally include entitlements as those typically change at signIn time, it is recommended to make a separate call to Discovery.contentAccess for entitlements. signIn is not only for when a user explicitly enters login credentials. If an app does not require any credentials from the user to consume content, such as in a free app, then the app should call signIn immediately on launch. */
   static void signInDispatcher(const void* result) {
        // Accessing Metrics methods using singleton Instance
        Firebolt::IFireboltAccessor::Instance().MetricsInterface().signIn();
    }
    /* signIn - Inform the platform that your user is signed in, for increased visibility in search & discovery. Sign-in state is used separately from what content can be access through entitlements and availabilities. Sign-in state may be used when deciding whether to choose this app to handle a user intent. For instance, if the user tries to launch something generic like playing music from an artist, only a signed-in app will be chosen. If the user wants to tune to a channel, only a signed-in app will be chosen to handle that intent. While signIn can optionally include entitlements as those typically change at signIn time, it is recommended to make a separate call to Discovery.contentAccess for entitlements. signIn is not only for when a user explicitly enters login credentials. If an app does not require any credentials from the user to consume content, such as in a free app, then the app should call signIn immediately on launch. */
    bool DiscoveryImpl::signIn( const std::optional<std::vector<Entertainment::Entitlement>>& entitlements, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;

        JsonObject jsonParameters;
        WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Variant> entitlementsArray;
            if (entitlements.has_value()) {
                for (auto& element : entitlements.value()) {
                    Firebolt::Entertainment::JsonData_Entitlement entitlementsContainer;
                    {
                            entitlementsContainer.EntitlementId = element.entitlementId;
                            if (element.startTime.has_value()) {
                                entitlementsContainer.StartTime = element.startTime.value();
                            }
                            if (element.endTime.has_value()) {
                                entitlementsContainer.EndTime = element.endTime.value();
                            }
                    }
                    string entitlementsStr;
                    entitlementsContainer.ToString(entitlementsStr);
                    WPEFramework::Core::JSON::VariantContainer entitlementsVariantContainer(entitlementsStr);
                    WPEFramework::Core::JSON::Variant entitlementsVariant = entitlementsVariantContainer;
                    entitlementsArray.Add() = entitlementsVariant;
                }
            }
            WPEFramework::Core::JSON::Variant entitlementsVariant;
            entitlementsVariant.Array(entitlementsArray);
            jsonParameters.Set(_T("entitlements"), entitlementsVariant);
        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.signIn", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.signIn is successfully invoked");
            success = jsonResult.Value();
            WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job = WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(WPEFramework::Core::ProxyType<FireboltSDK::Worker>::Create(signInDispatcher, nullptr));
            WPEFramework::Core::IWorkerPool::Instance().Submit(job);
        }

        if (err != nullptr) {
            *err = status;
        }

        return success;
    }

    /* signOut - Inform the platform that your user has signed out. See `Discovery.signIn` for more details on how the sign-in state is used.signOut will NOT clear entitlements, the app should make a separate call to Discovery.clearContentAccess. Apps should also call signOut when a login token has expired and the user is now in a signed-out state. */
   static void signOutDispatcher(const void* result) {
        // Accessing Metrics methods using singleton Instance
        Firebolt::IFireboltAccessor::Instance().MetricsInterface().signOut();
    }
    /* signOut - Inform the platform that your user has signed out. See `Discovery.signIn` for more details on how the sign-in state is used.signOut will NOT clear entitlements, the app should make a separate call to Discovery.clearContentAccess. Apps should also call signOut when a login token has expired and the user is now in a signed-out state. */
    bool DiscoveryImpl::signOut( Firebolt::Error *err )  const
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;

        JsonObject jsonParameters;

        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.signOut", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.signOut is successfully invoked");
            success = jsonResult.Value();
            WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job = WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(WPEFramework::Core::ProxyType<FireboltSDK::Worker>::Create(signOutDispatcher, nullptr));
            WPEFramework::Core::IWorkerPool::Instance().Submit(job);
        }

        if (err != nullptr) {
            *err = status;
        }

        return success;
    }

    /* watchNext - Suggest a call-to-action for this app on the platform home screen */
    bool DiscoveryImpl::watchNext( const std::string& title, const Entertainment::ContentIdentifiers& identifiers, const std::optional<std::string>& expires, const std::optional<Images>& images, Firebolt::Error *err ) 
    {
        Firebolt::Error status = Firebolt::Error::NotConnected;
        bool success = false;

        JsonObject jsonParameters;
        WPEFramework::Core::JSON::Variant titleVariant(title);
            jsonParameters.Set(_T("title"), titleVariant);
            auto element = identifiers;
            Firebolt::Entertainment::JsonData_ContentIdentifiers identifiersContainer;
            {
                if (element.assetId.has_value()) {
                    identifiersContainer.AssetId = element.assetId.value();
                }
                if (element.entityId.has_value()) {
                    identifiersContainer.EntityId = element.entityId.value();
                }
                if (element.seasonId.has_value()) {
                    identifiersContainer.SeasonId = element.seasonId.value();
                }
                if (element.seriesId.has_value()) {
                    identifiersContainer.SeriesId = element.seriesId.value();
                }
                if (element.appContentData.has_value()) {
                    identifiersContainer.AppContentData = element.appContentData.value();
                }
            }
            string identifiersStr;
            identifiersContainer.ToString(identifiersStr);
            WPEFramework::Core::JSON::VariantContainer identifiersVariantContainer(identifiersStr);
            WPEFramework::Core::JSON::Variant identifiersVariant = identifiersVariantContainer;
            jsonParameters.Set(_T("identifiers"), identifiersVariant);
            if (expires.has_value()) {
                WPEFramework::Core::JSON::Variant expiresVariant(expires.value());
                jsonParameters.Set(_T("expires"), expiresVariant);
            }
            if (images.has_value()) {
                WPEFramework::Core::JSON::VariantContainer imagesContainer;
                imagesContainer.FromString(images.value());
                WPEFramework::Core::JSON::Variant imagesVariant(imagesContainer);
                jsonParameters.Set(_T("images"), imagesVariant);
            }
    
        WPEFramework::Core::JSON::Boolean jsonResult;
        status = FireboltSDK::Gateway::Instance().Request("discovery.watchNext", jsonParameters, jsonResult);
        if (status == Firebolt::Error::None) {
            FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.watchNext is successfully invoked");
            success = jsonResult.Value();
        }

        if (err != nullptr) {
            *err = status;
        }

        return success;
    }


    // Events
    /* onNavigateTo - listen to `navigateTo` events */
    static void onNavigateToInnerCallback( void* notification, const void* userData, void* jsonResponse )
    {
        WPEFramework::Core::ProxyType<FireboltSDK::JSON::String>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<FireboltSDK::JSON::String>*>(jsonResponse));

        ASSERT(proxyResponse.IsValid() == true);

        if (proxyResponse.IsValid() == true) {
            std::string result;


            result = proxyResponse->Value();
            proxyResponse.Release();

            IDiscovery::IOnNavigateToNotification& notifier = *(reinterpret_cast<IDiscovery::IOnNavigateToNotification*>(notification));
            notifier.onNavigateTo(result);
        }
    }
    void DiscoveryImpl::subscribe( IDiscovery::IOnNavigateToNotification& notification, Firebolt::Error *err )
    {
        const string eventName = _T("discovery.onNavigateTo");
        Firebolt::Error status = Firebolt::Error::None;

        JsonObject jsonParameters;

        status = FireboltSDK::Event::Instance().Subscribe<FireboltSDK::JSON::String>(eventName, jsonParameters, onNavigateToInnerCallback, reinterpret_cast<void*>(&notification), nullptr);

        if (err != nullptr) {
            *err = status;
        }
    }
    void DiscoveryImpl::unsubscribe( IDiscovery::IOnNavigateToNotification& notification, Firebolt::Error *err )
    {
        Firebolt::Error status = FireboltSDK::Event::Instance().Unsubscribe(_T("discovery.onNavigateTo"), reinterpret_cast<void*>(&notification));

        if (err != nullptr) {
            *err = status;
        }
    }



    /* onPolicyChanged - get the discovery policy */
    static void onPolicyChangedInnerCallback( void* notification, const void* userData, void* jsonResponse )
    {
        WPEFramework::Core::ProxyType<Firebolt::Discovery::JsonData_DiscoveryPolicy>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<Firebolt::Discovery::JsonData_DiscoveryPolicy>*>(jsonResponse));

        ASSERT(proxyResponse.IsValid() == true);

        if (proxyResponse.IsValid() == true) {
            DiscoveryPolicy result;

            result.enableRecommendations = proxyResponse->EnableRecommendations;
            result.shareWatchHistory = proxyResponse->ShareWatchHistory;
            result.rememberWatchedPrograms = proxyResponse->RememberWatchedPrograms;

            proxyResponse.Release();

            IDiscovery::IOnPolicyChangedNotification& notifier = *(reinterpret_cast<IDiscovery::IOnPolicyChangedNotification*>(notification));
            notifier.onPolicyChanged(result);
        }
    }
    void DiscoveryImpl::subscribe( IDiscovery::IOnPolicyChangedNotification& notification, Firebolt::Error *err )
    {
        const string eventName = _T("discovery.onPolicyChanged");
        Firebolt::Error status = Firebolt::Error::None;

        JsonObject jsonParameters;

        status = FireboltSDK::Event::Instance().Subscribe<Firebolt::Discovery::JsonData_DiscoveryPolicy>(eventName, jsonParameters, onPolicyChangedInnerCallback, reinterpret_cast<void*>(&notification), nullptr);

        if (err != nullptr) {
            *err = status;
        }
    }
    void DiscoveryImpl::unsubscribe( IDiscovery::IOnPolicyChangedNotification& notification, Firebolt::Error *err )
    {
        Firebolt::Error status = FireboltSDK::Event::Instance().Unsubscribe(_T("discovery.onPolicyChanged"), reinterpret_cast<void*>(&notification));

        if (err != nullptr) {
            *err = status;
        }
    }



    /* onPullEntityInfo - Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow. Includes information about the program entity and its relevant associated entities, such as extras, previews, and, in the case of TV series, seasons and episodes.

See the `EntityInfo` and `WayToWatch` data structures below for more information.

The app only needs to implement Pull support for `entityInfo` at this time. */
    static void onPullEntityInfoInnerCallback( void* notification, const void* userData, void* jsonResponse )
    {
        WPEFramework::Core::ProxyType<Firebolt::Discovery::JsonData_EntityInfoFederatedRequest>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<Firebolt::Discovery::JsonData_EntityInfoFederatedRequest>*>(jsonResponse));

        ASSERT(proxyResponse.IsValid() == true);

        if (proxyResponse.IsValid() == true) {
            JsonData_EntityInfoParameters jsonResult = proxyResponse->Parameters;
            EntityInfoParameters entityInfoParameters;
            EntityInfoParameters entityInfoParametersResult;
            entityInfoParametersResult.entityId = jsonResult.EntityId.Value();
            if (jsonResult.AssetId.IsSet()) {
                entityInfoParametersResult.assetId = jsonResult.AssetId.Value();
            }
            entityInfoParameters = entityInfoParametersResult;

            IDiscovery::IOnPullEntityInfoNotification& notifier = *(reinterpret_cast<IDiscovery::IOnPullEntityInfoNotification*>(notification));
            EntityInfoResult element = notifier.onPullEntityInfo(entityInfoParameters);
            Firebolt::Error status = Firebolt::Error::NotConnected;
            JsonObject jsonParameters;
            WPEFramework::Core::JSON::Variant CorrelationId = proxyResponse->CorrelationId.Value();
            jsonParameters.Set(_T("correlationId"), CorrelationId);
            JsonData_EntityInfoResult Container;
            {
                {
                        Container.Expires = element.expires;
                        {
                            {
                                if (element.entity.identifiers.assetId.has_value()) {
                                    Container.Entity.Identifiers.AssetId = element.entity.identifiers.assetId.value();
                                }
                                if (element.entity.identifiers.entityId.has_value()) {
                                    Container.Entity.Identifiers.EntityId = element.entity.identifiers.entityId.value();
                                }
                                if (element.entity.identifiers.seasonId.has_value()) {
                                    Container.Entity.Identifiers.SeasonId = element.entity.identifiers.seasonId.value();
                                }
                                if (element.entity.identifiers.seriesId.has_value()) {
                                    Container.Entity.Identifiers.SeriesId = element.entity.identifiers.seriesId.value();
                                }
                                if (element.entity.identifiers.appContentData.has_value()) {
                                    Container.Entity.Identifiers.AppContentData = element.entity.identifiers.appContentData.value();
                                }
                            }
                            Container.Entity.Title = element.entity.title;
                            Container.Entity.EntityType = element.entity.entityType;
                            if (element.entity.programType.has_value()) {
                                Container.Entity.ProgramType = element.entity.programType.value();
                            }
                            if (element.entity.musicType.has_value()) {
                                Container.Entity.MusicType = element.entity.musicType.value();
                            }
                            if (element.entity.synopsis.has_value()) {
                                Container.Entity.Synopsis = element.entity.synopsis.value();
                            }
                            if (element.entity.seasonNumber.has_value()) {
                                Container.Entity.SeasonNumber = element.entity.seasonNumber.value();
                            }
                            if (element.entity.seasonCount.has_value()) {
                                Container.Entity.SeasonCount = element.entity.seasonCount.value();
                            }
                            if (element.entity.episodeNumber.has_value()) {
                                Container.Entity.EpisodeNumber = element.entity.episodeNumber.value();
                            }
                            if (element.entity.episodeCount.has_value()) {
                                Container.Entity.EpisodeCount = element.entity.episodeCount.value();
                            }
                            if (element.entity.releaseDate.has_value()) {
                                Container.Entity.ReleaseDate = element.entity.releaseDate.value();
                            }
                            if (element.entity.contentRatings.has_value()) {
                                WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_ContentRating> contentRatingsArray;
                                std::vector<Entertainment::ContentRating> contentRatings = element.entity.contentRatings.value();
                                for (auto& element : contentRatings) {
                                    Firebolt::Entertainment::JsonData_ContentRating contentRatingsContainer;
                                    {
                                        contentRatingsContainer.Scheme = element.scheme;
                                        contentRatingsContainer.Rating = element.rating;
                                        if (element.advisories.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> advisoriesArray;
                                            std::vector<std::string> advisories = element.advisories.value();
                                            for (auto& element : advisories) {
                                                advisoriesArray.Add() = element;
                                            }
                                            contentRatingsContainer.Advisories = advisoriesArray;
                                        }
                                    }
                                    contentRatingsArray.Add() = contentRatingsContainer;
                                }
                                Container.Entity.ContentRatings = contentRatingsArray;
                            }
                            if (element.entity.waysToWatch.has_value()) {
                                WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatch> waysToWatchArray;
                                std::vector<Entertainment::WayToWatch> waysToWatch = element.entity.waysToWatch.value();
                                for (auto& element : waysToWatch) {
                                    Firebolt::Entertainment::JsonData_WayToWatch waysToWatchContainer;
                                    {
                                        {
                                            if (element.identifiers.assetId.has_value()) {
                                                waysToWatchContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                            }
                                            if (element.identifiers.entityId.has_value()) {
                                                waysToWatchContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                            }
                                            if (element.identifiers.seasonId.has_value()) {
                                                waysToWatchContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                            }
                                            if (element.identifiers.seriesId.has_value()) {
                                                waysToWatchContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                            }
                                            if (element.identifiers.appContentData.has_value()) {
                                                waysToWatchContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                            }
                                        }
                                        if (element.expires.has_value()) {
                                            waysToWatchContainer.Expires = element.expires.value();
                                        }
                                        if (element.entitled.has_value()) {
                                            waysToWatchContainer.Entitled = element.entitled.value();
                                        }
                                        if (element.entitledExpires.has_value()) {
                                            waysToWatchContainer.EntitledExpires = element.entitledExpires.value();
                                        }
                                        if (element.offeringType.has_value()) {
                                            waysToWatchContainer.OfferingType = element.offeringType.value();
                                        }
                                        if (element.hasAds.has_value()) {
                                            waysToWatchContainer.HasAds = element.hasAds.value();
                                        }
                                        if (element.price.has_value()) {
                                            waysToWatchContainer.Price = element.price.value();
                                        }
                                        if (element.videoQuality.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatchVideoQuality> videoQualityArray;
                                            std::vector<Entertainment::WayToWatchVideoQuality> videoQuality = element.videoQuality.value();
                                            for (auto& element : videoQuality) {
                                                videoQualityArray.Add() = element;
                                            }
                                            waysToWatchContainer.VideoQuality = videoQualityArray;
                                        }
                                        WPEFramework::Core::JSON::ArrayType<Firebolt::Types::JsonData_AudioProfile> audioProfileArray;
                                        std::vector<Types::AudioProfile> audioProfile = element.audioProfile;
                                        for (auto& element : audioProfile) {
                                            audioProfileArray.Add() = element;
                                        }
                                        waysToWatchContainer.AudioProfile = audioProfileArray;
                                        if (element.audioLanguages.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioLanguagesArray;
                                            std::vector<std::string> audioLanguages = element.audioLanguages.value();
                                            for (auto& element : audioLanguages) {
                                                audioLanguagesArray.Add() = element;
                                            }
                                            waysToWatchContainer.AudioLanguages = audioLanguagesArray;
                                        }
                                        if (element.closedCaptions.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> closedCaptionsArray;
                                            std::vector<std::string> closedCaptions = element.closedCaptions.value();
                                            for (auto& element : closedCaptions) {
                                                closedCaptionsArray.Add() = element;
                                            }
                                            waysToWatchContainer.ClosedCaptions = closedCaptionsArray;
                                        }
                                        if (element.subtitles.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> subtitlesArray;
                                            std::vector<std::string> subtitles = element.subtitles.value();
                                            for (auto& element : subtitles) {
                                                subtitlesArray.Add() = element;
                                            }
                                            waysToWatchContainer.Subtitles = subtitlesArray;
                                        }
                                        if (element.audioDescriptions.has_value()) {
                                            WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioDescriptionsArray;
                                            std::vector<std::string> audioDescriptions = element.audioDescriptions.value();
                                            for (auto& element : audioDescriptions) {
                                                audioDescriptionsArray.Add() = element;
                                            }
                                            waysToWatchContainer.AudioDescriptions = audioDescriptionsArray;
                                        }
                                    }
                                    waysToWatchArray.Add() = waysToWatchContainer;
                                }
                                Container.Entity.WaysToWatch = waysToWatchArray;
                            }
                        }
                        if (element.related.has_value()) {
                            WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_EntityInfo> relatedArray;
                            std::vector<Entertainment::EntityInfo> related = element.related.value();
                            for (auto& element : related) {
                                Firebolt::Entertainment::JsonData_EntityInfo relatedContainer;
                                {
                                    {
                                        if (element.identifiers.assetId.has_value()) {
                                            relatedContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                        }
                                        if (element.identifiers.entityId.has_value()) {
                                            relatedContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                        }
                                        if (element.identifiers.seasonId.has_value()) {
                                            relatedContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                        }
                                        if (element.identifiers.seriesId.has_value()) {
                                            relatedContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                        }
                                        if (element.identifiers.appContentData.has_value()) {
                                            relatedContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                        }
                                    }
                                    relatedContainer.Title = element.title;
                                    relatedContainer.EntityType = element.entityType;
                                    if (element.programType.has_value()) {
                                        relatedContainer.ProgramType = element.programType.value();
                                    }
                                    if (element.musicType.has_value()) {
                                        relatedContainer.MusicType = element.musicType.value();
                                    }
                                    if (element.synopsis.has_value()) {
                                        relatedContainer.Synopsis = element.synopsis.value();
                                    }
                                    if (element.seasonNumber.has_value()) {
                                        relatedContainer.SeasonNumber = element.seasonNumber.value();
                                    }
                                    if (element.seasonCount.has_value()) {
                                        relatedContainer.SeasonCount = element.seasonCount.value();
                                    }
                                    if (element.episodeNumber.has_value()) {
                                        relatedContainer.EpisodeNumber = element.episodeNumber.value();
                                    }
                                    if (element.episodeCount.has_value()) {
                                        relatedContainer.EpisodeCount = element.episodeCount.value();
                                    }
                                    if (element.releaseDate.has_value()) {
                                        relatedContainer.ReleaseDate = element.releaseDate.value();
                                    }
                                    if (element.contentRatings.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_ContentRating> contentRatingsArray;
                                        std::vector<Entertainment::ContentRating> contentRatings = element.contentRatings.value();
                                        for (auto& element : contentRatings) {
                                            Firebolt::Entertainment::JsonData_ContentRating contentRatingsContainer;
                                            {
                                                contentRatingsContainer.Scheme = element.scheme;
                                                contentRatingsContainer.Rating = element.rating;
                                                if (element.advisories.has_value()) {
                                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> advisoriesArray;
                                                    std::vector<std::string> advisories = element.advisories.value();
                                                    for (auto& element : advisories) {
                                                        advisoriesArray.Add() = element;
                                                    }
                                                    contentRatingsContainer.Advisories = advisoriesArray;
                                                }
                                            }
                                            contentRatingsArray.Add() = contentRatingsContainer;
                                        }
                                        relatedContainer.ContentRatings = contentRatingsArray;
                                    }
                                    if (element.waysToWatch.has_value()) {
                                        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatch> waysToWatchArray;
                                        std::vector<Entertainment::WayToWatch> waysToWatch = element.waysToWatch.value();
                                        for (auto& element : waysToWatch) {
                                            Firebolt::Entertainment::JsonData_WayToWatch waysToWatchContainer;
                                            {
                                                {
                                                    if (element.identifiers.assetId.has_value()) {
                                                        waysToWatchContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                                    }
                                                    if (element.identifiers.entityId.has_value()) {
                                                        waysToWatchContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                                    }
                                                    if (element.identifiers.seasonId.has_value()) {
                                                        waysToWatchContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                                    }
                                                    if (element.identifiers.seriesId.has_value()) {
                                                        waysToWatchContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                                    }
                                                    if (element.identifiers.appContentData.has_value()) {
                                                        waysToWatchContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                                    }
                                                }
                                                if (element.expires.has_value()) {
                                                    waysToWatchContainer.Expires = element.expires.value();
                                                }
                                                if (element.entitled.has_value()) {
                                                    waysToWatchContainer.Entitled = element.entitled.value();
                                                }
                                                if (element.entitledExpires.has_value()) {
                                                    waysToWatchContainer.EntitledExpires = element.entitledExpires.value();
                                                }
                                                if (element.offeringType.has_value()) {
                                                    waysToWatchContainer.OfferingType = element.offeringType.value();
                                                }
                                                if (element.hasAds.has_value()) {
                                                    waysToWatchContainer.HasAds = element.hasAds.value();
                                                }
                                                if (element.price.has_value()) {
                                                    waysToWatchContainer.Price = element.price.value();
                                                }
                                                if (element.videoQuality.has_value()) {
                                                    WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatchVideoQuality> videoQualityArray;
                                                    std::vector<Entertainment::WayToWatchVideoQuality> videoQuality = element.videoQuality.value();
                                                    for (auto& element : videoQuality) {
                                                        videoQualityArray.Add() = element;
                                                    }
                                                    waysToWatchContainer.VideoQuality = videoQualityArray;
                                                }
                                                WPEFramework::Core::JSON::ArrayType<Firebolt::Types::JsonData_AudioProfile> audioProfileArray;
                                                std::vector<Types::AudioProfile> audioProfile = element.audioProfile;
                                                for (auto& element : audioProfile) {
                                                    audioProfileArray.Add() = element;
                                                }
                                                waysToWatchContainer.AudioProfile = audioProfileArray;
                                                if (element.audioLanguages.has_value()) {
                                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioLanguagesArray;
                                                    std::vector<std::string> audioLanguages = element.audioLanguages.value();
                                                    for (auto& element : audioLanguages) {
                                                        audioLanguagesArray.Add() = element;
                                                    }
                                                    waysToWatchContainer.AudioLanguages = audioLanguagesArray;
                                                }
                                                if (element.closedCaptions.has_value()) {
                                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> closedCaptionsArray;
                                                    std::vector<std::string> closedCaptions = element.closedCaptions.value();
                                                    for (auto& element : closedCaptions) {
                                                        closedCaptionsArray.Add() = element;
                                                    }
                                                    waysToWatchContainer.ClosedCaptions = closedCaptionsArray;
                                                }
                                                if (element.subtitles.has_value()) {
                                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> subtitlesArray;
                                                    std::vector<std::string> subtitles = element.subtitles.value();
                                                    for (auto& element : subtitles) {
                                                        subtitlesArray.Add() = element;
                                                    }
                                                    waysToWatchContainer.Subtitles = subtitlesArray;
                                                }
                                                if (element.audioDescriptions.has_value()) {
                                                    WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioDescriptionsArray;
                                                    std::vector<std::string> audioDescriptions = element.audioDescriptions.value();
                                                    for (auto& element : audioDescriptions) {
                                                        audioDescriptionsArray.Add() = element;
                                                    }
                                                    waysToWatchContainer.AudioDescriptions = audioDescriptionsArray;
                                                }
                                            }
                                            waysToWatchArray.Add() = waysToWatchContainer;
                                        }
                                        relatedContainer.WaysToWatch = waysToWatchArray;
                                    }
                                }
                                relatedArray.Add() = relatedContainer;
                            }
                            Container.Related = relatedArray;
                        }
                    }
            }
            string resultStr;
            Container.ToString(resultStr);
            WPEFramework::Core::JSON::VariantContainer resultContainer(resultStr);
            WPEFramework::Core::JSON::Variant Result = resultContainer;
            jsonParameters.Set(_T("result"), Result);
            {
                WPEFramework::Core::JSON::Boolean jsonResult;

                status = FireboltSDK::Gateway::Instance().Request("discovery.entityInfo", jsonParameters, jsonResult);
                if (status == Firebolt::Error::None) {
                    FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.onPullEntityInfo is successfully pushed with status as %d", jsonResult.Value());
                }
            }

            proxyResponse.Release();
        }
    }
    void DiscoveryImpl::subscribe( IDiscovery::IOnPullEntityInfoNotification& notification, Firebolt::Error *err )
    {
        const string eventName = _T("discovery.onPullEntityInfo");
        Firebolt::Error status = Firebolt::Error::None;

        JsonObject jsonParameters;
        status = FireboltSDK::Event::Instance().Subscribe<WPEFramework::Core::JSON::VariantContainer>(eventName, jsonParameters, onPullEntityInfoInnerCallback, reinterpret_cast<void*>(&notification), nullptr);

        if (err != nullptr) {
            *err = status;
        }
    }
    void DiscoveryImpl::unsubscribe( IDiscovery::IOnPullEntityInfoNotification& notification, Firebolt::Error *err )
    {
        Firebolt::Error status = FireboltSDK::Event::Instance().Unsubscribe(_T("discovery.onPullEntityInfo"), reinterpret_cast<void*>(&notification));

        if (err != nullptr) {
            *err = status;
        }
    }

    /* onPullPurchasedContent - Return content purchased by the user, such as rentals and electronic sell through purchases.

The app should return the user's 100 most recent purchases in `entries`. The total count of purchases must be provided in `count`. If `count` is greater than the total number of `entries`, the UI may provide a link into the app to see the complete purchase list.

The `EntityInfo` object returned is not required to have `waysToWatch` populated, but it is recommended that it do so in case the UI wants to surface additional information on the purchases screen.

The app should implement both Push and Pull methods for `purchasedContent`.

The app should actively push `purchasedContent` when:

*  The app becomes Active.
*  When the state of the purchasedContent set has changed.
*  The app goes into Inactive or Background state, if there is a chance a change event has been missed. */
    static void onPullPurchasedContentInnerCallback( void* notification, const void* userData, void* jsonResponse )
    {
        WPEFramework::Core::ProxyType<Firebolt::Discovery::JsonData_PurchasedContentFederatedRequest>& proxyResponse = *(reinterpret_cast<WPEFramework::Core::ProxyType<Firebolt::Discovery::JsonData_PurchasedContentFederatedRequest>*>(jsonResponse));

        ASSERT(proxyResponse.IsValid() == true);

        if (proxyResponse.IsValid() == true) {
            JsonData_PurchasedContentParameters jsonResult = proxyResponse->Parameters;
            PurchasedContentParameters purchasedContentParameters;
            PurchasedContentParameters purchasedContentParametersResult;
            purchasedContentParametersResult.limit = jsonResult.Limit.Value();
            if (jsonResult.OfferingType.IsSet()) {
                purchasedContentParametersResult.offeringType = jsonResult.OfferingType.Value();
            }
            if (jsonResult.ProgramType.IsSet()) {
                purchasedContentParametersResult.programType = jsonResult.ProgramType.Value();
            }
            purchasedContentParameters = purchasedContentParametersResult;

            IDiscovery::IOnPullPurchasedContentNotification& notifier = *(reinterpret_cast<IDiscovery::IOnPullPurchasedContentNotification*>(notification));
            PurchasedContentResult element = notifier.onPullPurchasedContent(purchasedContentParameters);
            Firebolt::Error status = Firebolt::Error::NotConnected;
            JsonObject jsonParameters;
            WPEFramework::Core::JSON::Variant CorrelationId = proxyResponse->CorrelationId.Value();
            jsonParameters.Set(_T("correlationId"), CorrelationId);
            JsonData_PurchasedContentResult Container;
            {
                {
                        Container.Expires = element.expires;
                        Container.TotalCount = element.totalCount;
                        WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_EntityInfo> entriesArray;
                        std::vector<Entertainment::EntityInfo> entries = element.entries;
                        for (auto& element : entries) {
                            Firebolt::Entertainment::JsonData_EntityInfo entriesContainer;
                            {
                                {
                                    if (element.identifiers.assetId.has_value()) {
                                        entriesContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                    }
                                    if (element.identifiers.entityId.has_value()) {
                                        entriesContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                    }
                                    if (element.identifiers.seasonId.has_value()) {
                                        entriesContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                    }
                                    if (element.identifiers.seriesId.has_value()) {
                                        entriesContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                    }
                                    if (element.identifiers.appContentData.has_value()) {
                                        entriesContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                    }
                                }
                                entriesContainer.Title = element.title;
                                entriesContainer.EntityType = element.entityType;
                                if (element.programType.has_value()) {
                                    entriesContainer.ProgramType = element.programType.value();
                                }
                                if (element.musicType.has_value()) {
                                    entriesContainer.MusicType = element.musicType.value();
                                }
                                if (element.synopsis.has_value()) {
                                    entriesContainer.Synopsis = element.synopsis.value();
                                }
                                if (element.seasonNumber.has_value()) {
                                    entriesContainer.SeasonNumber = element.seasonNumber.value();
                                }
                                if (element.seasonCount.has_value()) {
                                    entriesContainer.SeasonCount = element.seasonCount.value();
                                }
                                if (element.episodeNumber.has_value()) {
                                    entriesContainer.EpisodeNumber = element.episodeNumber.value();
                                }
                                if (element.episodeCount.has_value()) {
                                    entriesContainer.EpisodeCount = element.episodeCount.value();
                                }
                                if (element.releaseDate.has_value()) {
                                    entriesContainer.ReleaseDate = element.releaseDate.value();
                                }
                                if (element.contentRatings.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_ContentRating> contentRatingsArray;
                                    std::vector<Entertainment::ContentRating> contentRatings = element.contentRatings.value();
                                    for (auto& element : contentRatings) {
                                        Firebolt::Entertainment::JsonData_ContentRating contentRatingsContainer;
                                        {
                                            contentRatingsContainer.Scheme = element.scheme;
                                            contentRatingsContainer.Rating = element.rating;
                                            if (element.advisories.has_value()) {
                                                WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> advisoriesArray;
                                                std::vector<std::string> advisories = element.advisories.value();
                                                for (auto& element : advisories) {
                                                    advisoriesArray.Add() = element;
                                                }
                                                contentRatingsContainer.Advisories = advisoriesArray;
                                            }
                                        }
                                        contentRatingsArray.Add() = contentRatingsContainer;
                                    }
                                    entriesContainer.ContentRatings = contentRatingsArray;
                                }
                                if (element.waysToWatch.has_value()) {
                                    WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatch> waysToWatchArray;
                                    std::vector<Entertainment::WayToWatch> waysToWatch = element.waysToWatch.value();
                                    for (auto& element : waysToWatch) {
                                        Firebolt::Entertainment::JsonData_WayToWatch waysToWatchContainer;
                                        {
                                            {
                                                if (element.identifiers.assetId.has_value()) {
                                                    waysToWatchContainer.Identifiers.AssetId = element.identifiers.assetId.value();
                                                }
                                                if (element.identifiers.entityId.has_value()) {
                                                    waysToWatchContainer.Identifiers.EntityId = element.identifiers.entityId.value();
                                                }
                                                if (element.identifiers.seasonId.has_value()) {
                                                    waysToWatchContainer.Identifiers.SeasonId = element.identifiers.seasonId.value();
                                                }
                                                if (element.identifiers.seriesId.has_value()) {
                                                    waysToWatchContainer.Identifiers.SeriesId = element.identifiers.seriesId.value();
                                                }
                                                if (element.identifiers.appContentData.has_value()) {
                                                    waysToWatchContainer.Identifiers.AppContentData = element.identifiers.appContentData.value();
                                                }
                                            }
                                            if (element.expires.has_value()) {
                                                waysToWatchContainer.Expires = element.expires.value();
                                            }
                                            if (element.entitled.has_value()) {
                                                waysToWatchContainer.Entitled = element.entitled.value();
                                            }
                                            if (element.entitledExpires.has_value()) {
                                                waysToWatchContainer.EntitledExpires = element.entitledExpires.value();
                                            }
                                            if (element.offeringType.has_value()) {
                                                waysToWatchContainer.OfferingType = element.offeringType.value();
                                            }
                                            if (element.hasAds.has_value()) {
                                                waysToWatchContainer.HasAds = element.hasAds.value();
                                            }
                                            if (element.price.has_value()) {
                                                waysToWatchContainer.Price = element.price.value();
                                            }
                                            if (element.videoQuality.has_value()) {
                                                WPEFramework::Core::JSON::ArrayType<Firebolt::Entertainment::JsonData_WayToWatchVideoQuality> videoQualityArray;
                                                std::vector<Entertainment::WayToWatchVideoQuality> videoQuality = element.videoQuality.value();
                                                for (auto& element : videoQuality) {
                                                    videoQualityArray.Add() = element;
                                                }
                                                waysToWatchContainer.VideoQuality = videoQualityArray;
                                            }
                                            WPEFramework::Core::JSON::ArrayType<Firebolt::Types::JsonData_AudioProfile> audioProfileArray;
                                            std::vector<Types::AudioProfile> audioProfile = element.audioProfile;
                                            for (auto& element : audioProfile) {
                                                audioProfileArray.Add() = element;
                                            }
                                            waysToWatchContainer.AudioProfile = audioProfileArray;
                                            if (element.audioLanguages.has_value()) {
                                                WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioLanguagesArray;
                                                std::vector<std::string> audioLanguages = element.audioLanguages.value();
                                                for (auto& element : audioLanguages) {
                                                    audioLanguagesArray.Add() = element;
                                                }
                                                waysToWatchContainer.AudioLanguages = audioLanguagesArray;
                                            }
                                            if (element.closedCaptions.has_value()) {
                                                WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> closedCaptionsArray;
                                                std::vector<std::string> closedCaptions = element.closedCaptions.value();
                                                for (auto& element : closedCaptions) {
                                                    closedCaptionsArray.Add() = element;
                                                }
                                                waysToWatchContainer.ClosedCaptions = closedCaptionsArray;
                                            }
                                            if (element.subtitles.has_value()) {
                                                WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> subtitlesArray;
                                                std::vector<std::string> subtitles = element.subtitles.value();
                                                for (auto& element : subtitles) {
                                                    subtitlesArray.Add() = element;
                                                }
                                                waysToWatchContainer.Subtitles = subtitlesArray;
                                            }
                                            if (element.audioDescriptions.has_value()) {
                                                WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> audioDescriptionsArray;
                                                std::vector<std::string> audioDescriptions = element.audioDescriptions.value();
                                                for (auto& element : audioDescriptions) {
                                                    audioDescriptionsArray.Add() = element;
                                                }
                                                waysToWatchContainer.AudioDescriptions = audioDescriptionsArray;
                                            }
                                        }
                                        waysToWatchArray.Add() = waysToWatchContainer;
                                    }
                                    entriesContainer.WaysToWatch = waysToWatchArray;
                                }
                            }
                            entriesArray.Add() = entriesContainer;
                        }
                        Container.Entries = entriesArray;
                    }
            }
            string resultStr;
            Container.ToString(resultStr);
            WPEFramework::Core::JSON::VariantContainer resultContainer(resultStr);
            WPEFramework::Core::JSON::Variant Result = resultContainer;
            jsonParameters.Set(_T("result"), Result);
            {
                WPEFramework::Core::JSON::Boolean jsonResult;

                status = FireboltSDK::Gateway::Instance().Request("discovery.purchasedContent", jsonParameters, jsonResult);
                if (status == Firebolt::Error::None) {
                    FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Discovery.onPullPurchasedContent is successfully pushed with status as %d", jsonResult.Value());
                }
            }

            proxyResponse.Release();
        }
    }
    void DiscoveryImpl::subscribe( IDiscovery::IOnPullPurchasedContentNotification& notification, Firebolt::Error *err )
    {
        const string eventName = _T("discovery.onPullPurchasedContent");
        Firebolt::Error status = Firebolt::Error::None;

        JsonObject jsonParameters;
        status = FireboltSDK::Event::Instance().Subscribe<WPEFramework::Core::JSON::VariantContainer>(eventName, jsonParameters, onPullPurchasedContentInnerCallback, reinterpret_cast<void*>(&notification), nullptr);

        if (err != nullptr) {
            *err = status;
        }
    }
    void DiscoveryImpl::unsubscribe( IDiscovery::IOnPullPurchasedContentNotification& notification, Firebolt::Error *err )
    {
        Firebolt::Error status = FireboltSDK::Event::Instance().Unsubscribe(_T("discovery.onPullPurchasedContent"), reinterpret_cast<void*>(&notification));

        if (err != nullptr) {
            *err = status;
        }
    }


} //namespace ${info.Title}
}${end.if.implementations}

${if.enums}

namespace WPEFramework {

/* ${ENUM_IMPLEMENTATIONS} */
}${end.if.enums}

