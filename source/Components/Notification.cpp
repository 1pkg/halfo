#include "constants.hpp"
#include "Notification.hpp"
#include <plugins/Sdkbox.hpp>
#include <plugins/PluginOneSignal.hpp>

namespace Components
{

class NotificationListener : public sdkbox::OneSignalListener
{
public:

    void onNotification(bool isActive, const std::string & message, const std::string & additionalData) override
	{
		cocos2d::MessageBox(("OneSignal::onNotification msg:" + message).data(), "debug");
	}

    void onNotificationOpened(const std::string & message) override
	{
		cocos2d::MessageBox(("OneSignal::onNotificationOpened msg:" + message).data(), "debug");
	}
};

void
Notification::initialize()
{
	static std::unique_ptr<NotificationListener> listener(new NotificationListener());
	sdkbox::PluginOneSignal::init();
	sdkbox::PluginOneSignal::setListener(listener.get());
	sdkbox::PluginOneSignal::sendTag("tag", "val");
	sdkbox::PluginOneSignal::idsAvailable();
	sdkbox::PluginOneSignal::setSubscription(true);
}

}