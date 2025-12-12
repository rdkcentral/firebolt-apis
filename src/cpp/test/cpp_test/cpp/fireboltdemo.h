#pragma once
#include <string>
#include <vector>
#include "firebolt/firebolt.h"
#include <firebolt/json_types.h>

#include <iostream>

class IFireboltDemo 
{
public:
    
    IFireboltDemo();
    virtual ~IFireboltDemo() = default;

    int chooseOption();
    virtual void runOption(const int index) = 0;

protected:
    void paramFromConsole(const std::string& name, const std::string& def, std::string& value);
    int chooseFromList(const std::vector<std::string>& options, const std::string& prompt);

    void loadRpc();

    template <typename T>
    bool validateResult(const Firebolt::Result<T>& result) const {
        return doValidateResult(result.error());
    }

    bool validateResult(const Firebolt::Result<void>& result) const {
        return doValidateResult(result.error());
    }

    template <typename T>
    T chooseEnumFromList(const Firebolt::JSON::EnumType<T>& enumType, const std::string& prompt) {
    std::vector<std::string> options;
    for (const auto& pair : enumType) {
        options.push_back(pair.first);
        std::cout << "Option: " << pair.first << std::endl;
    }

    int choice = chooseFromList(options, prompt);

    return enumType.at(options[choice]);
    }

    template <typename T>
    std::string stringFromEnum(Firebolt::JSON::EnumType<T> enumType, T value) {
    for (const auto& pair : enumType) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return {};
}

    std::vector<std::string> methodsFromRpc(const std::string& interfaceName);

    static nlohmann::json json_;

    std::vector<std::string> names_;
    std::vector<std::string> descriptions_;

private:
    bool doValidateResult(Firebolt::Error error) const {
        if (error != Firebolt::Error::None) {
            std::cout << "Operation failed with error: " << static_cast<int>(error) << std::endl;
            return false;
        }
        std::cout << "Operation succeeded." << std::endl;
        return true;
}

};
