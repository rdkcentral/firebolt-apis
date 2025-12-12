#pragma once

#include "fireboltdemo.h"

class ChooseInterface : public IFireboltDemo
{
public:
    ChooseInterface();
    ~ChooseInterface();
    std::vector<std::string> methods() const {return names_;}
    
    void runOption(const int index);

private:

    std::vector<IFireboltDemo*> interfaces;
};
