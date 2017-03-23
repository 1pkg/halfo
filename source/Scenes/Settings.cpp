#include "components.hpp"
#include "Settings.hpp"

namespace Scenes
{

Settings::Settings()
	: Application::Scene(cocos2d::Scene::create()),
	_info(new Views::Ui::Label(SMALL_FONT_SIZE)),
	_path(new Views::Ui::Label(MEDIUM_FONT_SIZE))
{
	_info->setText("Identifier:" + cocos2d::getDeviceIdentifier() + "|Model:" + cocos2d::getDeviceModel() + "|Version:" + cocos2d::getDeviceVersion());
	_info->setPosition(Master::instance().get<Components::Metric>().center() - cocos2d::Vec2(0.0f, Master::instance().get<Components::Metric>().size().height * 0.3f));
	_info->attach(this);

	_path->setText(Master::instance().get<Components::File>().root());
	_path->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Vec2(0.0f, Master::instance().get<Components::Metric>().size().height * 0.3f));
	_path->attach(this);
}

}