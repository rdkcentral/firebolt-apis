#include <string>
#include <vector>
#include <iostream>
#include "lifecycleDemo.h"
#include "json_types/jsondata_lifecycle_types.h"
#include "utils.h"

using namespace Firebolt;
using namespace Firebolt::Lifecycle;

LifecycleDemo::LifecycleDemo() : IFireboltDemo()
{
    methodsFromRpc("Lifecycle2");
    names_.push_back("Trigger lifecycle state change");
    descriptions_.push_back("Simulate a lifecycle state change event from the platform.");
    currentState_ = LifecycleState::INITIALIZING;
}

void LifecycleDemo::runOption(const int index)
{
    std::string key = names_[index];

    if (key == "Lifecycle2.close")
    {
        CloseType type = chooseEnumFromList(
            Firebolt::Lifecycle::JsonData::CloseReasonEnum,
            "Choose Close Type:");
        Result<void> r =
            Firebolt::IFireboltAccessor::Instance().LifecycleInterface().close(type);
        validateResult(r);
    }
    else if (key == "Lifecycle2.state")
    {
        Result<LifecycleState> r =
        Firebolt::IFireboltAccessor::Instance().LifecycleInterface().state();
        if (validateResult(r))
        {
            currentState_ = r.value();
            printCurrentState();
        }
    }
    else if (key == "Lifecycle2.onStateChanged")
    {
        auto callback = [&](const std::vector<StateChange> &changes)
        {
            std::cout << "Lifecycle State Changes received:" << std::endl;
            for (const auto &change : changes)
            {
                std::cout << "  From " <<Firebolt::JSON::toString(Firebolt::Lifecycle::JsonData::LifecycleStateEnum, change.oldState)
                          << " to " << Firebolt::JSON::toString(Firebolt::Lifecycle::JsonData::LifecycleStateEnum, change.newState)
                          << std::endl;  
                currentState_ = change.newState; 
            }
        };
        Result<SubscriptionId> r =
            Firebolt::IFireboltAccessor::Instance().LifecycleInterface().subscribeOnStateChanged(
                std::move(callback));
        if (validateResult(r))
        {
            std::cout << "Subscribed to Lifecycle state changes with Subscription ID: " << r.value() << std::endl;
        }
    }
    else if (key == "Trigger lifecycle state change")
    {
        triggerLifecycleStateChange();
    }
    else if (key == "Lifecycle2.unsubscribe")
    {
        std::string idStr;
        paramFromConsole("Subscription ID to unsubscribe", "0", idStr);
        SubscriptionId id = static_cast<SubscriptionId>(std::stoul(idStr));
        Result<void> r =
            Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribe(id);
        validateResult(r);
    }
    else if (key == "Lifecycle2.unsubscribeAll")
    {
        Firebolt::IFireboltAccessor::Instance().LifecycleInterface().unsubscribeAll();
        std::cout << "Unsubscribed from all Lifecycle subscriptions." << std::endl;
    }
}

void LifecycleDemo::triggerLifecycleStateChange()
{
    LifecycleState newState = chooseEnumFromList(
        Firebolt::Lifecycle::JsonData::LifecycleStateEnum,
        "Choose new Lifecycle State to simulate:");
    nlohmann::json params;
    params["value"] = nlohmann::json::array();
    params["value"].push_back({
        {"newState", Firebolt::JSON::toString(Firebolt::Lifecycle::JsonData::LifecycleStateEnum, newState)},
        {"oldState", Firebolt::JSON::toString(Firebolt::Lifecycle::JsonData::LifecycleStateEnum, currentState_)}
    });
    triggerEvent("Lifecycle2.onStateChanged", params.dump());
}

void LifecycleDemo::printCurrentState()
{
  std::cout << "Current Lifecycle State: " << stringFromEnum(Firebolt::Lifecycle::JsonData::LifecycleStateEnum, currentState_) << std::endl;
}