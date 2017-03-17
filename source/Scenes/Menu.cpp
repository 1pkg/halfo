#include "components.hpp"
#include "Menu.hpp"

namespace Scenes
{

Menu *
Menu::create()
{
    Menu * menu = new (std::nothrow) Menu();
    if (menu && menu->initWithColor(cocos2d::Color4B::GRAY))
        menu->autorelease();
    else
        CC_SAFE_DELETE(menu);
    return menu;
}

Menu::Menu()
	: _play(new Ui::Button("Play", true)),
	_score(new Ui::Button("Score&Achives", false)),
	_purchape(new Ui::Button("Purchape", false)),
	_settings(new Ui::Button("Settings", false)),
	_credits(new Ui::Button("Credits", false))
{
	_play->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_ACT);
	_play->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.4f));
	_play->attach(this);

	_score->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.2f));
	_score->attach(this);

	_purchape->setPosition(Master::instance().get<Components::Metric>().center());
	_purchape->attach(this);

	_settings->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_SETTINGS);
	_settings->setPosition(Master::instance().get<Components::Metric>().center() - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.2f));
	_settings->attach(this);

	_credits->setPosition(Master::instance().get<Components::Metric>().center() - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.4f));
	_credits->attach(this);
}

}