#include <string>
#include <vector>
#include <iostream>
#include "deviceDemo.h"

#include "json_types/jsondata_device_types.h"

using namespace Firebolt;
using namespace Firebolt::Device;

DeviceDemo::DeviceDemo() : IFireboltDemo() 
{
     methodsFromRpc("Device");
}

void DeviceDemo::runOption(const int index) {
    std::string key = names_[index];

    if (key == "Device.class") {
        Result<DeviceClass> r = 
            Firebolt::IFireboltAccessor::Instance().DeviceInterface().deviceClass();
        if (validateResult(r)) {
            std::cout << "Device Class: " << stringFromEnum(
                Firebolt::Device::JsonData::DeviceClassEnum, r.value()) << std::endl;
        }
    } else if (key == "Device.uptime") {
        Result<uint32_t> r = 
            Firebolt::IFireboltAccessor::Instance().DeviceInterface().uptime();
        if (validateResult(r)) {
            std::cout << "Device Uptime (seconds): " << r.value() << std::endl;
        }
    } else if (key == "Device.timeInActiveState") {
        Result<uint32_t> r = 
            Firebolt::IFireboltAccessor::Instance().DeviceInterface().timeInActiveState();
        if (validateResult(r)) {
            std::cout << "Device Time In Active State (seconds): " << r.value() << std::endl;
        }
    } else if (key == "Device.chipsetId") {
        Result<std::string> r = 
            Firebolt::IFireboltAccessor::Instance().DeviceInterface().chipsetId();
        if (validateResult(r)) {
            std::cout << "Device Chipset ID: " << r.value() << std::endl;
        }
    } else if (key == "Device.uid") {
        Result<std::string> r = 
            Firebolt::IFireboltAccessor::Instance().DeviceInterface().uid();
        if (validateResult(r)) {
            std::cout << "Device UID: " << r.value() << std::endl;
        }
    }
}
