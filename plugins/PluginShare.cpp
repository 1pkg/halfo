#include "PluginShare.hpp"

namespace sdkbox
{

ShareListener * _listener;

bool
PluginShare::init(const char * jsonconfig)
{
	return true;
}

void
PluginShare::setListener(ShareListener * listener)
{
	_listener = listener;
}

void
PluginShare::share(const SocialShareInfo & info)
{
	SocialShareResponse response;
	response.state =  SocialShareState::SocialShareStateSuccess;
	_listener->onShareState(response);
}

}