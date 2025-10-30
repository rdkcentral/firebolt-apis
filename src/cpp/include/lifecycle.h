#pragma once

#include <functional>
#include <string>
#include <types/fb-errors.h>
#include <types/types.h>

namespace Firebolt::Lifecycle
{

/**
 * @brief The application lifecycle state
 */
enum class LifecycleState
{
    INITIALIZING,
    ACTIVE,
    PAUSED,
    SUSPENDED,
    HIBERNATED,
    TERMINATING,
};

/**
 * @brief The application close type
 */
enum class CloseType
{
    DEACTIVATE,
    UNLOAD,
    KILL_RELOAD,
    KILL_REACTIVATE,
};

class ILifecycle
{
public:
    virtual ~ILifecycle() = default;

    /**
     * @brief Request that the platform move your app out of focus
     *
     * @param[in] reason The reason the app is requesting to be closed
     */
    virtual Result<void> close(const CloseType &type) const = 0;

    /**
     * @brief Get the current lifecycle state of the application
     *
     * @retval The current lifecycle state or error
     */
    virtual Result<LifecycleState> getCurrentState() const = 0;

    /**
     * @brief Subscribe on the change of Lifecycle state
     *
     * @param notification : The callback function
     *
     * @retval The subscriptionId or error
     */
    virtual Result<SubscriptionId>
    subscribeOnStateChanged(std::function<void(const LifecycleState& oldState, const LifecycleState& newState)>&& notification) = 0;

    /**
     * @brief Remove subscriber from subscribers list. This method is generic for
     *        all subscriptions
     *
     * @param[in] id                  : The subscription id
     *
     * @retval The status
     */
    virtual Result<void> unsubscribe(SubscriptionId id) = 0;

    /**
     * @brief Remove all active subscriptions from subscribers list.
     */
    virtual void unsubscribeAll() = 0;
};
} // namespace Firebolt::Lifecycle