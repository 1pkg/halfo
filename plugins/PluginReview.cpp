#include "PluginReview.hpp"

namespace sdkbox
{

ReviewListener * _listener;

bool
PluginReview::init(const char * jsonconfig)
{
	return true;
}

void
PluginReview::setListener(ReviewListener * listener)
{
	_listener = listener;
}

void
PluginReview::show(bool force)
{
	if (force)
		_listener->onRate();
}

}
