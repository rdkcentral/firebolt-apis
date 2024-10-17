#include "unit.h"

class AdvertisingTest : public ::testing::Test
{
protected:
    Firebolt::Error error = Firebolt::Error::None;
};


struct SkipRestrictionChanged : public Firebolt::Advertising::IAdvertising::IOnSkipRestrictionChangedNotification
{
    void onSkipRestrictionChanged( const Firebolt::Advertising::SkipRestriction& ) override; 
};

Firebolt::Advertising::SkipRestriction newSkipRestriction;
void SkipRestrictionChanged::onSkipRestrictionChanged(const Firebolt::Advertising::SkipRestriction& skipRestriction)
{
    std::cout << "onSkipRestrictionChanged event fired";
}


TEST_F(AdvertisingTest, subscribeOnSkipRestrictionChanged)
{
    SkipRestrictionChanged skipRestrictionChanged;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().subscribe(skipRestrictionChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in subscribing to SkipRestrictionChanged";
}

TEST_F(AdvertisingTest, unsubscribeOnSkipRestrictionChanged)
{
    SkipRestrictionChanged skipRestrictionChanged;
    Firebolt::IFireboltAccessor::Instance().AdvertisingInterface().unsubscribe(skipRestrictionChanged, &error);
    EXPECT_EQ(error, Firebolt::Error::None) << "Error in unsubscribing to SkipRestrictionChanged";
}