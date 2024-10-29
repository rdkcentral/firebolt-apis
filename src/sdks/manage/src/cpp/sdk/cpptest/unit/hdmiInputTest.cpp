#include "unit.h"

class HdmiInputTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};

struct AutoLowLatencyModeCapableSettings : public Firebolt::HDMIInput::IHDMIInput::IOnAutoLowLatencyModeCapableChangedNotification
{
    void onAutoLowLatencyModeCapableChanged(const Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo &) override;
};

void AutoLowLatencyModeCapableSettings::onAutoLowLatencyModeCapableChanged(const Firebolt::HDMIInput::AutoLowLatencyModeCapableChangedInfo &info)
{
    std::cout << "onAutoLowLatencyModeCapableChanged event fired";
}

TEST_F(HdmiInputTest, subscribeOnAutoLowLatencyModeCapableChanged)
{
    AutoLowLatencyModeCapableSettings autoLowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(autoLowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AutoLowLatencyModeCapableSettings";
}

TEST_F(HdmiInputTest, unsubscribeOnAutoLowLatencyModeCapableChanged)
{
    AutoLowLatencyModeCapableSettings autoLowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(autoLowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AutoLowLatencyModeCapableSettings";
}

struct AutoLowLatencyModeSignalSettings : public Firebolt::HDMIInput::IHDMIInput::IOnAutoLowLatencyModeSignalChangedNotification
{
    void onAutoLowLatencyModeSignalChanged(const Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo &) override;
};

void AutoLowLatencyModeSignalSettings::onAutoLowLatencyModeSignalChanged(const Firebolt::HDMIInput::AutoLowLatencyModeSignalChangedInfo &info)
{
    std::cout << "onAutoLowLatencyModeSignalChanged event fired";
}

TEST_F(HdmiInputTest, subscribeOnAutoLowLatencyModeSignalChanged)
{
    AutoLowLatencyModeSignalSettings autoLowLatencySignalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(autoLowLatencySignalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to AutoLowLatencyModeSignalSettings";
}

TEST_F(HdmiInputTest, unsubscribeOnAutoLowLatencyModeSignalChanged)
{
    AutoLowLatencyModeSignalSettings autoLowLatencySignalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(autoLowLatencySignalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to AutoLowLatencyModeSignalSettings";
}

struct ConnectionSettings : public Firebolt::HDMIInput::IHDMIInput::IOnConnectionChangedNotification
{
    void onConnectionChanged(const Firebolt::HDMIInput::ConnectionChangedInfo &) override;
};

void ConnectionSettings::onConnectionChanged(const Firebolt::HDMIInput::ConnectionChangedInfo &info)
{
    std::cout << "onConnectionChanged event fired";
}

TEST_F(HdmiInputTest, subscribeOnConnectionChanged)
{
    ConnectionSettings connectionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(connectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to ConnectionSettings";
}

TEST_F(HdmiInputTest, unsubscribeOnConnectionChanged)
{
    ConnectionSettings connectionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(connectionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to ConnectionSettings";
}

struct EdidVersionSettings : public Firebolt::HDMIInput::IHDMIInput::IOnEdidVersionChangedNotification
{
    void onEdidVersionChanged(const Firebolt::HDMIInput::EDIDVersion &) override;
};

void EdidVersionSettings::onEdidVersionChanged(const Firebolt::HDMIInput::EDIDVersion &version)
{
    std::cout << "onEdidVersionChanged event fired";
}

TEST_F(HdmiInputTest, subscribeOnEdidVersionChanged)
{
    EdidVersionSettings edidVersionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe("port_name", edidVersionSettings, &error); // Replace "port_name" with actual port name
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to EdidVersionSettings";
}

TEST_F(HdmiInputTest, unsubscribeOnEdidVersionChanged)
{
    EdidVersionSettings edidVersionSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(edidVersionSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to EdidVersionSettings";
}

struct LowLatencyModeSettings : public Firebolt::HDMIInput::IHDMIInput::IOnLowLatencyModeChangedNotification
{
    void onLowLatencyModeChanged(const bool) override;
};

void LowLatencyModeSettings::onLowLatencyModeChanged(const bool mode)
{
    std::cout << "onLowLatencyModeChanged event fired";
}

TEST_F(HdmiInputTest, subscribeOnLowLatencyModeChanged)
{
    LowLatencyModeSettings lowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(lowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to LowLatencyModeSettings";
}

TEST_F(HdmiInputTest, unsubscribeOnLowLatencyModeChanged)
{
    LowLatencyModeSettings lowLatencySettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(lowLatencySettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to LowLatencyModeSettings";
}

struct SignalSettings : public Firebolt::HDMIInput::IHDMIInput::IOnSignalChangedNotification
{
    void onSignalChanged(const Firebolt::HDMIInput::SignalChangedInfo &) override;
};

void SignalSettings::onSignalChanged(const Firebolt::HDMIInput::SignalChangedInfo &info)
{
    std::cout << "onSignalChanged event fired";
}

TEST_F(HdmiInputTest, subscribeOnSignalChanged)
{
    SignalSettings signalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().subscribe(signalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SignalSettings";
}

TEST_F(HdmiInputTest, unsubscribeOnSignalChanged)
{
    SignalSettings signalSettings;
    Firebolt::IFireboltAccessor::Instance().HDMIInputInterface().unsubscribe(signalSettings, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SignalSettings";
}
