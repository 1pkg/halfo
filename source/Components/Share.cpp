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

	void onShareState(const sdkbox::SocialShareResponse& response) override
	{
		switch (response.state)
		{
			case sdkbox::SocialShareState::SocialShareStateSuccess:
				cocos2d::MessageBox("Tw::SocialShareStateSuccess", "debug");
				break;

			case sdkbox::SocialShareState::SocialShareStateFail:
				cocos2d::MessageBox(("Tw::SocialShareStateFail, msg:" + response.error).data(), "debug");
				break;

			case sdkbox::SocialShareState::SocialShareStateCancelled:
				cocos2d::MessageBox("Tw::onShareStateSocialShareStateCancelled", "debug");
				break;
		}
	}
};

class FacebookListener : public sdkbox::FacebookListener
{
public:

	void onSharedSuccess(const std::string & message) override
	{
		cocos2d::MessageBox(("FB::onSharedSuccess, msg:" + message).data(), "debug");
	}
	void onSharedFailed(const std::string & message) override
	{
		cocos2d::MessageBox(("FB::onSharedFailed, msg:" + message).data(), "debug");
	}
	void onSharedCancel() override
	{
		cocos2d::MessageBox("FB::onSharedCancel", "debug");
	}
	void onLogin(bool isLogin, const std::string & msg) override {}
    void onAPI(const std::string& key, const std::string & jsonData) override {}
    void onPermission(bool isLogin, const std::string & msg) override {}
    void onFetchFriends(bool ok, const std::string & msg) override {}
    void onRequestInvitableFriends(const sdkbox::FBInvitableFriendsInfo & friends) override {}
    void onInviteFriendsWithInviteIdsResult(bool result, const std::string & msg) override {}
    void onInviteFriendsResult(bool result, const std::string & msg) override {}
    void onGetUserInfo(const sdkbox::FBGraphUser & userInfo) override {}
    void onAskGiftResult(bool result, const std::string & msg) override {}
};

class ReviewListener : public sdkbox::ReviewListener
{
public:

	void onDisplayAlert() override
	{
		cocos2d::MessageBox("Rw::onDisplayAlert", "debug");
	}
	void onDeclineToRate() override
	{
		cocos2d::MessageBox("Rw::onDeclineToRate", "debug");
	}
	void onRate() override
	{
		cocos2d::MessageBox("Rw::onRate", "debug");
	}
	void onRemindLater() override
	{
		cocos2d::MessageBox("Rw::onRemindLater", "debug");
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
		static std::unique_ptr<FacebookListener> listener(new FacebookListener());
		sdkbox::PluginFacebook::setListener(listener.get());
		sdkbox::FBShareInfo share;
		share.type = sdkbox::FB_LINK;
		share.title = "halfo";
		share.text = "Test";
		share.link = "http://www.sdkbox.com";
		sdkbox::PluginFacebook::dialog(share);
		return;
	}

	if (platform == SHARE_REVIEW)
	{
		static std::unique_ptr<ReviewListener> listener(new ReviewListener());
		sdkbox::PluginReview::setListener(listener.get());
		sdkbox::PluginReview::setTitle("custom title");
		sdkbox::PluginReview::setMessage("custom message");
		sdkbox::PluginReview::setCancelButtonTitle("custom cancel");
		sdkbox::PluginReview::setRateButtonTitle("custom rate");
		sdkbox::PluginReview::setRateLaterButtonTitle("custom rate later");
		sdkbox::PluginReview::show(true);
		return;
	}
}

}