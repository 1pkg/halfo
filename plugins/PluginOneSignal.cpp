#include "PluginOneSignal.hpp"

namespace sdkbox
{

OneSignalListener * _listener;

bool
PluginOneSignal::init()
{
	return true;
}

void
PluginOneSignal::setListener(OneSignalListener * listener)
{
	_listener = listener;
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