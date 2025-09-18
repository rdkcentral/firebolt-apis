#pragma once

#include "TypesPriv.h"
#include "JsonDataMock.h"

class IProperties
{
public:
    virtual ~IProperties() = default;
    virtual Firebolt::Error Get(const std::string &propertyName, FireboltSDK::JSON::String &response) = 0;

    virtual Firebolt::Error Get(const std::string &propertyName, WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, WPEFramework::Core::JSON::Boolean &response) = 0;

    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Advertising::JsonData_AdPolicy &response) = 0;

    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Accessibility::JsonData_AudioDescriptionSettings &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &response) = 0;

    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_AudioProfiles &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_HDCPVersionMap &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_HDRFormatMap &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_NetworkInfoResult &response) = 0;
    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_Resolution &response) = 0;

    virtual Firebolt::Error Get(const std::string &propertyName, Firebolt::Discovery::JsonData_DiscoveryPolicy &response) = 0;
};