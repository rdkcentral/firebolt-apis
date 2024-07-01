
#include "${info.title.lowercase}_impl.h"
#include "${info.title.lowercase}.h"
#include "metrics_impl.h"


${if.implementations}
namespace Firebolt {
namespace ${info.Title} {
${if.providers}
/* ${PROVIDERS} */${end.if.providers}


/* ready - Notify the platform that the app is ready */
static void readyDispatcher(const void* result) {
    Metrics::MetricsImpl::ready();
}
/* ready - Notify the platform that the app is ready */
void ${info.Title}Impl::ready(Firebolt::Error *err) 
{
        Firebolt::Error status = Firebolt::Error::NotConnected;

        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {

            JsonObject jsonParameters;
    
            WPEFramework::Core::JSON::VariantContainer jsonResult;
            status = transport->Invoke("lifecycle.ready", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Lifecycle.ready is successfully invoked");
    
                WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch> job = WPEFramework::Core::ProxyType<WPEFramework::Core::IDispatch>(WPEFramework::Core::ProxyType<FireboltSDK::Worker>::Create(readyDispatcher, nullptr));
                WPEFramework::Core::IWorkerPool::Instance().Submit(job);
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }

        return;
}


/* finished - Notify the platform that the app is done unloading */
void ${info.Title}Impl::finished(Firebolt::Error *err) 
{
    Firebolt::Error status = Firebolt::Error::NotConnected;

        FireboltSDK::Transport<WPEFramework::Core::JSON::IElement>* transport = FireboltSDK::Accessor::Instance().GetTransport();
        if (transport != nullptr) {
        
            JsonObject jsonParameters;
    
            WPEFramework::Core::JSON::VariantContainer jsonResult;
            status = transport->Invoke("lifecycle.finished", jsonParameters, jsonResult);
            if (status == Firebolt::Error::None) {
                FIREBOLT_LOG_INFO(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Lifecycle.finished is successfully invoked");
    
            }

        } else {
            FIREBOLT_LOG_ERROR(FireboltSDK::Logger::Category::OpenRPC, FireboltSDK::Logger::Module<FireboltSDK::Accessor>(), "Error in getting Transport err = %d", status);
        }
    

        return;
}



// Methods
/* ${METHODS} */

// Events
/* ${EVENTS} */

}//namespace Lifecycle
}${end.if.implementations}
${if.enums}

namespace WPEFramework {

/* ${ENUMS} */
}${end.if.enums}

 



