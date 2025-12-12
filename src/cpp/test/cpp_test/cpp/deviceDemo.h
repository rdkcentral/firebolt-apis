#include <string>
#include <vector>
#include "fireboltdemo.h"

class DeviceDemo : public IFireboltDemo 
{
public:
    DeviceDemo();
    ~DeviceDemo() = default;
    void runOption(const int index);
};
