#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unistd.h>

#include "cpp/chooseInterface.h"



bool gConnected = false;

int main2() {

    std::cout << "Hello from WSL!" << std::endl;
    int x = 43;
    std::cout << "The answer is: " << x << std::endl;

       

    //nlohmann::json value = jsonEngine.get_value("GetDeviceInfo");

    ChooseInterface chooseInterface;
    for (;;)
    {
        int interfaceIndex = chooseInterface.chooseOption();

        if (interfaceIndex == -1) {
            break; // Exit the program
        }

        chooseInterface.runOption(interfaceIndex);
    }

    return 0;
}

void connectionChanged(const bool connected, const Firebolt::Error error)
{
    std::cout << "Change in connection: connected: " << connected << " error: " << static_cast<int>(error) << std::endl;
    gConnected = connected;
}

void createFireboltInstance(const std::string& url)
{
    Firebolt::Config config;
    config.wsUrl = url;
    config.waitTime_ms = 1000;
    config.log.level = Firebolt::LogLevel::Debug;

    gConnected = false;
    Firebolt::IFireboltAccessor::Instance().Connect(config, connectionChanged);
}

void destroyFireboltInstance()
{
    Firebolt::IFireboltAccessor::Instance().Disconnect();
}

bool waitOnConnectionReady()
{
    uint32_t waiting = 10000;
    static constexpr uint32_t SLEEPSLOT_TIME = 100;

    // Right, a wait till connection is closed is requested..
    while ((waiting > 0) && (gConnected == false))
    {

        uint32_t sleepSlot = (waiting > SLEEPSLOT_TIME ? SLEEPSLOT_TIME : waiting);
        // Right, lets sleep in slices of 100 ms
        usleep(sleepSlot);
        waiting -= sleepSlot;
    }
    return gConnected;
}

int main(int argc, char** argv)
{
    std::string url = "ws://127.0.0.1:9998";
    createFireboltInstance(url);

    std::this_thread::sleep_for(std::chrono::seconds(1));

  //  ::testing::InitGoogleTest(&argc, argv);
    if (!waitOnConnectionReady())
    {
        std::cout << "Test not able to connect with server..." << std::endl;
        return -1;
    }
    main2();
    destroyFireboltInstance();

    return 0;
}

