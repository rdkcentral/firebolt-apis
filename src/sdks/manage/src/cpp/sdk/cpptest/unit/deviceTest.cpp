#include "unit.h"

class DeviceTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct DeviceNameSettings : public Firebolt::Device::IDevice::IOnDeviceNameChangedNotification
{
    void onDeviceNameChanged(const std::string &) override;
};

void DeviceNameSettings::onDeviceNameChanged(const std::string &name)
{
    std::cout << "onDeviceNameChanged event fired";
}

TEST_F(DeviceTest, subscribeOnDeviceNameChanged)
{
    DeviceNameSettings deviceNameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(deviceNameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to DeviceNameSettings";
}

TEST_F(DeviceTest, unsubscribeOnDeviceNameChanged)
{
    DeviceNameSettings deviceNameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(deviceNameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to DeviceNameSettings";
}

struct NameSettings : public Firebolt::Device::IDevice::IOnNameChangedNotification
{
    void onNameChanged(const std::string &) override;
};

void NameSettings::onNameChanged(const std::string &name)
{
    std::cout << "onNameChanged event fired";
}

TEST_F(DeviceTest, subscribeOnNameChanged)
{
    NameSettings nameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().subscribe(nameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to NameSettings";
}

TEST_F(DeviceTest, unsubscribeOnNameChanged)
{
    NameSettings nameSettings;
    Firebolt::IFireboltAccessor::Instance().DeviceInterface().unsubscribe(nameSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to NameSettings";
}
