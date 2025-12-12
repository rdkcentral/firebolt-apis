#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "fireboltdemo.h"
#include "utils.h"
#include "firebolt-open-rpc_json.h"

nlohmann::json IFireboltDemo::json_;

#ifndef UT_OPEN_RPC_FILE
#define UT_OPEN_RPC_FILE "firebolt-open-rpc.json"
#endif

IFireboltDemo::IFireboltDemo() {
    loadRpc();
}

void IFireboltDemo::paramFromConsole(const std::string& name, const std::string& def, std::string& value)
{
    std::cout << "Enter " << name << " (default: " << def << "): ";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
        value = def;
    } else {
        value = input;
    }
}

int getOption(int n) {
    std::string input;
    
    while (true) {
        std::cout << "Select option or 'q' to go back: ";
        std::cin >> input;
        
        // Check if user wants to quit
        if (input.length() == 1 && std::tolower(input[0]) == 'q') {
            return -1;
        }
        
        // Try to convert to integer
        try {
            int num = std::stoi(input);
            
            // Check if number is in valid range
            if (num >= 0 && num <= n) {
                return num;
            } else {
                std::cout << "Please enter a number between 0 and " << n << "." << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a number or 'q'." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Number too large. Please enter a number between 0 and " << n << "." << std::endl;
        }
    }
}

int IFireboltDemo::chooseFromList(const std::vector<std::string>& options, const std::string& prompt)
{
    std::cout << prompt << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i << ": " << options[i] << std::endl;
    }

    int choice = getOption(static_cast<int>(options.size() - 1));

    return choice;
}

int IFireboltDemo::chooseOption() {
    return chooseFromList(names_, "Choose a method to run:");
}

void IFireboltDemo::loadRpc() {
    
   // if (json_.is_null()) {
    //    std::string filename = UT_OPEN_RPC_FILE;
     //   std::ifstream file(filename);
      //  if (!file.is_open())
       // {
        //    throw std::runtime_error("Could not open file: " + filename);
       // }

       // file >> json_;
    json_ = nlohmann::json::parse(JSON_DATA);   
}


std::vector<std::string> IFireboltDemo::methodsFromRpc(const std::string& interfaceName)  {
    std::vector<std::string> methodNames;

    std::string interfaceStr = interfaceName + ".";
        for (const auto& method : json_["methods"])
    {
        if (method.contains("name") && method["name"].get<std::string>().rfind(interfaceStr, 0) == 0)
        {
              
                names_.push_back(method["name"]);//.get<std::string>());
                descriptions_.push_back(method["summary"]);//.get<std::string>());
                  std::cout << "Found method: " << names_.back() << ":" << descriptions_.back()  << std::endl;
        }
    }

    return methodNames;
}   

