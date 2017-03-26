#include "constants.hpp"
#include "Notification.hpp"
#include <plugins/Sdkbox.hpp>
#include <plugins/PluginOneSignal.hpp>
namespace Components
{

void
Notification::initialize()
{
	sdkbox::PluginOneSignal::init();
	sdkbox::PluginOneSignal::sendTag("key", "value");
	sdkbox::PluginOneSignal::idsAvailable();
	sdkbox::PluginOneSignal::setSubscription(true);
}

}