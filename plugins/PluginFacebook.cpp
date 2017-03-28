#include "PluginFacebook.hpp"

namespace sdkbox
{

FacebookListener * _listener;

void
PluginFacebook::init()
{
}

void
PluginFacebook::setListener(FacebookListener * listener)
{
	_listener = listener;
}

void
PluginFacebook::dialog(const FBShareInfo & info)
{
	_listener->onSharedSuccess("succes");
}

}