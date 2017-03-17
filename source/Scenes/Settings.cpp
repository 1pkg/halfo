#include "components.hpp"
#include "Settings.hpp"

namespace Scenes
{

Settings *
Settings::create()
{
    Settings * settings = new (std::nothrow) Settings();
    if (settings && settings->initWithColor(cocos2d::Color4B::GRAY))
        settings->autorelease();
    else
        CC_SAFE_DELETE(settings);
    return settings;
}

Settings::Settings()
	: _info(new Ui::Label(MEDIUM_FONT_SIZE))
{
	_info->setText("Identifier:" + cocos2d::getDeviceIdentifier() + "|Model:" + cocos2d::getDeviceModel() + "|Version:" + cocos2d::getDeviceVersion());
	_info->setPosition(Master::instance().get<Components::Metric>().center());
	_info->attach(this);
}

}