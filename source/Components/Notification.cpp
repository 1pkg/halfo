#include "constants.hpp"
#include "Notification.hpp"
#include <plugins/Sdkbox.hpp>
#include <plugins/PluginOneSignal.hpp>

namespace Components
{

class NotificationListener : public sdkbox::OneSignalListener
{
public:

	void onSendTag(bool success, const std::string& key, const std::string& message) override
	{
		return;
	}
    void onGetTags(const std::string& jsonString) override
	{
		return;
	}
    void onIdsAvailable(const std::string& userId, const std::string& pushToken) override
	{
		return;
	}
    void onPostNotification(bool success, const std::string& message) override
	{
		return;
	}
    void onNotification(bool isActive, const std::string & message, const std::string & additionalData) override
	{
		std::stringstream stream;
		stream << "Component::Notification::onNotification" << "\nmessage: " << message;
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
    void onNotificationOpened(const std::string & message) override
	{
		return;
	}
};

void
Notification::initialize()
{
	static std::unique_ptr<NotificationListener> listener(new NotificationListener());
	sdkbox::PluginOneSignal::init();
	sdkbox::PluginOneSignal::setSubscription(true);
}

}