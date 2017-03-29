#include "PluginIAP.hpp"

namespace sdkbox
{

IAPListener * _listener;

void
IAP::init(const char * jsonconfig)
{
}

void
IAP::setListener(IAPListener * listener)
{
	_listener = listener;
}

void
IAP::purchase(const std::string & item)
{
	sdkbox::Product product;
	product.name = item;
	_listener->onSuccess(product);
}

}