#pragma once

#include "error.h"
#include "JsonDataMock.h"


class IGateway
{
public:
    virtual ~IGateway() = default;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, FireboltSDK::JSON::String &result) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::VariantContainer &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::Variant &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::Boolean &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Authentication::JsonData_Token &result) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_AdPolicy &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_AdvertisingId &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_AdFrameworkConfig &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_DeviceAttributes &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Accessibility::JsonData_AudioDescriptionSettings &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_DeviceVersion &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_AudioProfiles &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_HDCPVersionMap &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_HDRFormatMap &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_NetworkInfoResult &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_Resolution &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::ArrayType<Firebolt::Capabilities::JsonData_CapabilityInfo> &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Discovery::JsonData_DiscoveryPolicy &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Localization::JsonData_Info &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Localization::JsonData_LatLon &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Parameters::JsonData_AppInitialization &response) = 0;

    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Types::JsonData_FlatMap &response) = 0;
    virtual Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Types::JsonData_BooleanMap &response) = 0;
};
