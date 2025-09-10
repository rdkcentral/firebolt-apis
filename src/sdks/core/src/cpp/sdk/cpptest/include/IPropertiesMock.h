#pragma once

#include "Gateway/Gateway.h"
#include "IProperties.h"

class IPropertiesMock : public IProperties
{
    template <typename RESPONSETYPE>
    static Firebolt::Error GetImpl(const string &propertyName, RESPONSETYPE &response)
    {
        std::cout << "IPropertiesMock::GetImpl()\n";
        JsonObject parameters;
        return FireboltSDK::Gateway::Instance().Request(propertyName, parameters, response);
    }

public:
    Firebolt::Error Get(const std::string &propertyName, FireboltSDK::JSON::String &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Advertising::JsonData_AdPolicy &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Accessibility::JsonData_AudioDescriptionSettings &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_AudioProfiles &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_HDCPVersionMap &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_HDRFormatMap &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_NetworkInfoResult &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Device::JsonData_Resolution &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, Firebolt::Discovery::JsonData_DiscoveryPolicy &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> &response)
    {
        return GetImpl(propertyName, response);
    }

    Firebolt::Error Get(const std::string &propertyName, WPEFramework::Core::JSON::Boolean &response)
    {
        return GetImpl(propertyName, response);
    }
};
