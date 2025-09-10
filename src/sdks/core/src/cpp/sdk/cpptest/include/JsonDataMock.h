#pragma once

#include "TypesPriv.h"

// namespace FireboltSDK
// {
//     namespace JSON
//     {
//         class String;
//     }
// }

namespace Firebolt
{
    namespace Advertising
    {
        class JsonData_AdPolicy;
        class JsonData_AdvertisingId;
        class JsonData_AdFrameworkConfig;
        class JsonData_DeviceAttributes;
        // class JsonData_AdFrameworkConfig : public WPEFramework::Core::JSON::VariantContainer
        // {
        // };
        // class JsonData_DeviceAttributes : public WPEFramework::Core::JSON::VariantContainer
        // {
        // };
    }

    namespace Accessibility
    {
        class JsonData_ClosedCaptionsSettings;
        class JsonData_VoiceGuidanceSettings;
        class JsonData_AudioDescriptionSettings;
    }

    namespace Authentication
    {
        class JsonData_Token;
    }

    namespace Capabilities
    {
        class JsonData_CapabilityInfo;
    }

    namespace Device
    {
        class JsonData_AudioProfiles;
        class JsonData_HDCPVersionMap;
        class JsonData_HDRFormatMap;
        class JsonData_NetworkInfoResult;
        class JsonData_Resolution;
        // class JsonData_Resolution : public WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::DecSInt32>
        // {
        // };
        class JsonData_DeviceVersion;
    }

    namespace Discovery
    {
        class JsonData_DiscoveryPolicy;
    }

    namespace Localization
    {
        class JsonData_Info;
        class JsonData_LatLon ;
        // class JsonData_Info : public WPEFramework::Core::JSON::VariantContainer
        // {
        // };
        // class JsonData_LatLon : public WPEFramework::Core::JSON::ArrayType<WPEFramework::Core::JSON::Float>
        // {
        // };
    }

    namespace Parameters
    {
        class JsonData_AppInitialization;
    }

    namespace Types
    {
        class JsonData_FlatMap;
        class JsonData_BooleanMap;
        // class JsonData_FlatMap : public WPEFramework::Core::JSON::VariantContainer
        // {
        // };
        // class JsonData_BooleanMap : public WPEFramework::Core::JSON::VariantContainer
        // {
        // };
    }

}
