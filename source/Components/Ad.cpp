#include "constants.hpp"
#include "functions.hpp"
#include "Ad.hpp"
#include <plugins/Sdkbox.hpp>
#include <plugins/PluginSdkboxAds.hpp>
#include <plugins/PluginAdMob.hpp>
#include <plugins/PluginChartboost.hpp>

namespace Components
{

class AdListener : public sdkbox::PluginSdkboxAdsListener
{
public:

	void onAdAction(const std::string & unit, const std::string & place, sdkbox::AdActionType type) override
	{
		cocos2d::MessageBox(("Add::onAdAction unit:" + unit + " place:" + place + " type:" + to_string((int)type)).data(), "debug");
	}

	void onRewardAction(const std::string & unit, const std::string & place, float reward, bool succeed)
	{

	}

};

void
Ad::initialize()
{
	static std::unique_ptr<AdListener> listener(new AdListener());
	sdkbox::PluginSdkboxAds::init();
	sdkbox::PluginSdkboxAds::setListener(listener.get());
}

void
Ad::ad(const std::string & unit, const std::string & place)
{
	sdkbox::PluginSdkboxAds::playAd(unit, place);
}

void
Ad::placement(const std::string & placement)
{
	sdkbox::PluginSdkboxAds::placement(placement);
}

}