#include <string>
#include <vector>
#include "fireboltdemo.h"

class LifecycleDemo : public IFireboltDemo 
{
public:
    LifecycleDemo();
    ~LifecycleDemo() = default;
    void runOption(const int index);

private:
    void triggerLifecycleStateChange();
    void printCurrentState();
    Firebolt::Lifecycle::LifecycleState currentState_;
};
