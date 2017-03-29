#include "constants.hpp"
#include "Share.hpp"
#include <plugins/Sdkbox.hpp>
#include <plugins/PluginShare.hpp>
#include <plugins/PluginFacebook.hpp>
#include <plugins/PluginReview.hpp>

namespace Components
{

class TwitterListener : public sdkbox::ShareListener
{
public:

	void onShareState(const sdkbox::SocialShareResponse & response) override
	{
		std::stringstream stream;
		switch (response.state)
		{
			case sdkbox::SocialShareState::SocialShareStateSuccess:
				stream << "Component::Share::onShareState" << "\nstate: SocialShareStateSuccess";
				break;

			case sdkbox::SocialShareState::SocialShareStateFail:
				stream << "Component::Share::onShareState" << "state: SocialShareStateFail" << "\nmessage: " << response.error;
				break;

			case sdkbox::SocialShareState::SocialShareStateCancelled:
				stream << "Component::Share::onShareState" << "\nstate: onShareStateSocialShareStateCancelled";
				break;

			case sdkbox::SocialShareState::SocialShareStateNone:
			case sdkbox::SocialShareState::SocialShareStateUnkonw:
			case sdkbox::SocialShareState::SocialShareStateBegin:
			case sdkbox::SocialShareState::SocialShareStateSelectShow:
			case sdkbox::SocialShareState::SocialShareStateSelected:
			case sdkbox::SocialShareState::SocialShareStateSelectCancelled:
			default:
				return;
		}
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
};

class ReviewListener : public sdkbox::ReviewListener
{
public:

	void onDisplayAlert() override
	{
		std::stringstream stream;
		stream << "Component::Share::Review::onDisplayAlert";
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
	void onDeclineToRate() override
	{
		std::stringstream stream;
		stream << "Component::Share::Review::onDeclineToRate";
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
	void onRate() override
	{
		std::stringstream stream;
		stream << "Component::Share::Review::onRate";
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
	void onRemindLater() override
	{
		std::stringstream stream;
		stream << "Component::Share::Review::onRemindLater";
		cocos2d::MessageBox(stream.str().data(), "debug");
	}
};

void
Share::initialize()
{
	sdkbox::PluginShare::init();
	sdkbox::PluginFacebook::init();
	sdkbox::PluginReview::init();
}

void
Share::share(const std::string & platform) const
{
	if (platform == SHARE_TWITTER)
	{
		static std::unique_ptr<TwitterListener> listener(new TwitterListener());
		sdkbox::PluginShare::setListener(listener.get());
		sdkbox::SocialShareInfo share;
		share.platform = sdkbox::SocialPlatform::Platform_Twitter;
		share.title = "halfo";
		share.text = "Test";
		share.link = "http://www.sdkbox.com";
		share.showDialog = true;
		sdkbox::PluginShare::share(share);
		return;
	}

	if (platform == SHARE_FACEBOOK)
	{
		static std::unique_ptr<TwitterListener> listener(new TwitterListener());
		sdkbox::PluginShare::setListener(listener.get());
		sdkbox::SocialShareInfo share;
		share.platform = sdkbox::SocialPlatform::Platform_Facebook;
		share.title = "halfo";
		share.text = "Test";
		share.link = "http://www.sdkbox.com";
		share.showDialog = true;
		sdkbox::PluginShare::share(share);
		return;
	}

	if (platform == SHARE_REVIEW)
	{
		static std::unique_ptr<ReviewListener> listener(new ReviewListener());
		sdkbox::PluginReview::setListener(listener.get());
		sdkbox::PluginReview::show(true);
		return;
	}
}

}