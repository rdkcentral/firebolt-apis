#pragma once

#include "IGateway.h"
#include "Transport/Transport.h"

class IGatewayMock : public IGateway
{
public:
    FireboltSDK::Transport<WPEFramework::Core::JSON::IElement> *transport;

    template <typename RESPONSE>
    Firebolt::Error RequestImpl(const std::string &method, const JsonObject &parameters, RESPONSE &response)
    {
        if (transport == nullptr)
        {
            return Firebolt::Error::NotConnected;
        }
        return transport->Invoke(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, FireboltSDK::JSON::String &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Authentication::JsonData_Token &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_AdvertisingId &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_AdFrameworkConfig &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_DeviceAttributes &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::Boolean &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Accessibility::JsonData_ClosedCaptionsSettings &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Accessibility::JsonData_VoiceGuidanceSettings &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Advertising::JsonData_AdPolicy &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Accessibility::JsonData_AudioDescriptionSettings &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::ArrayType<Firebolt::Capabilities::JsonData_CapabilityInfo> &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_AudioProfiles &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_HDCPVersionMap &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_HDRFormatMap &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_NetworkInfoResult &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_Resolution &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Device::JsonData_DeviceVersion &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::VariantContainer &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::Variant &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Discovery::JsonData_DiscoveryPolicy &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Localization::JsonData_Info &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Localization::JsonData_LatLon &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Parameters::JsonData_AppInitialization &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Types::JsonData_FlatMap &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, Firebolt::Types::JsonData_BooleanMap &response)
    {
        return RequestImpl(method, parameters, response);
    }

    Firebolt::Error Request(const std::string &method, const JsonObject &parameters, WPEFramework::Core::JSON::ArrayType<FireboltSDK::JSON::String> &response)
    {
        return RequestImpl(method, parameters, response);
    }
};
