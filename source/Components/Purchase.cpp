#include "Purchase.hpp"
#include <plugins/PluginIAP.hpp>

namespace Components
{

class PurchaseListener : public sdkbox::IAPListener
{
public:

	void onInitialized(bool success) override 
	{
		return;
	}
    void onSuccess(const sdkbox::Product & product) override
	{
		std::stringstream stream;
		stream << "Component::Purchase::onSuccess" << "\nproduct: " << product.id;
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
    void onFailure(const sdkbox::Product & product, const std::string & msg) override
	{
		std::stringstream stream;
		stream << "Component::Purchase::onFailure" << "\nproduct: " << product.id;
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
    void onCanceled(const sdkbox::Product & product)  override 
	{
		std::stringstream stream;
		stream << "Component::Purchase::onCanceled" << "\nproduct: " << product.id;
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
    void onRestored(const sdkbox::Product & product) override
	{
		std::stringstream stream;
		stream << "Component::Purchase::onRestored" << "\nproduct: " << product.id;
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
    void onProductRequestSuccess(const std::vector<sdkbox::Product> & products) override
	{
		return;
	}
    void onProductRequestFailure(const std::string & message) override
	{
		return;
	}
    void onRestoreComplete(bool ok, const std::string & message) override
	{
		return;
	}
};

void
Purchase::initialize()
{
	static std::unique_ptr<PurchaseListener> listener(new PurchaseListener());
	sdkbox::IAP::init();
	sdkbox::IAP::setListener(listener.get());
}

void
Purchase::purchase(const std::string & item)
{
	sdkbox::IAP::purchase(item);
}

}