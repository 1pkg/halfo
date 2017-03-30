#include "PluginOneSignal.hpp"

namespace sdkbox
{

bool
PluginOneSignal::init()
{
	return true;
}

void
PluginOneSignal::setListener(OneSignalListener * listener)
{
}

void
PluginOneSignal::sendTag(const std::string& key, const std::string& value)
{
}


void
PluginOneSignal::idsAvailable()
{
}

void
PluginOneSignal::setSubscription(bool enable)
{
}

}