#pragma once

#include "fireboltdemo.h"
#include "chooseInterface.h"
#include "deviceDemo.h"
#include "lifecycleDemo.h"

#include <iostream>

ChooseInterface::ChooseInterface() : IFireboltDemo() {
    for (auto& [key, value] : json_["info"]["x-module-descriptions"].items()) {
        std::cout << key << ": " << value << std::endl;
        if (key != "Internal") {      
            names_.push_back(key);
            descriptions_.push_back(value.get<std::string>());   
        }
    }

    interfaces = {
        nullptr,//new AccessibilityDemo(),
        nullptr,//new AdvertisingDemo(),
        new DeviceDemo(),
        nullptr,//new DisplayDemo(),
        new LifecycleDemo(),
        nullptr,//new LocalizationDemo(),
        nullptr,//new PresentationDemo(),
        nullptr,//new StatsDemo()
    };
}

ChooseInterface::~ChooseInterface() {
    for (auto interfacePtr : interfaces) {
        delete interfacePtr;
    }
}

void ChooseInterface::runOption(const int index) {
    IFireboltDemo* selectedInterface = interfaces[index];
    std::cout << "Running interface: " << names_[index] << std::endl;

    for(;;)
    {
        int methodIndex = selectedInterface->chooseOption();

        if (methodIndex == -1) {
            break; // Go back to interface selection
        }

        selectedInterface->runOption(methodIndex);
    } 
}


