#include "Over.hpp"
#include "Application/Main.hpp"

namespace Scenes
{

cocos2d::Scene *
Over::instantiate()
{
    cocos2d::Scene * scene = cocos2d::Scene::create();
	Over * over = new Over();
	over->autorelease();
	scene->addChild(over);
    return scene;
}

Over::Over()
	: _restart(cocos2d::ui::Button::create()),
	_exit(cocos2d::ui::Button::create())
{
	initWithColor(cocos2d::Color4B::GRAY);

	_restart->setTitleText("Act");
	_restart->setPosition(cocos2d::Vec2(400.0f, 600.0f));
	addChild(_restart);
	_restart->addTouchEventListener(
		[](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
					case cocos2d::ui::Widget::TouchEventType::BEGAN:
						Application::Main::instance().act();
						break;

					default: break;
			}
		}
	);

	_exit->setTitleText("End");
	_exit->setPosition(cocos2d::Vec2(400.0f, 400.0f));
	_exit->addTouchEventListener(
		[](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
					case cocos2d::ui::Widget::TouchEventType::BEGAN:
						Application::Main::instance().end();
						break;

					default: break;
			}
		}
	);
	addChild(_exit);
}

Over::~Over()
{
	_restart->removeFromParentAndCleanup(true);
	_exit->removeFromParentAndCleanup(true);
}

}