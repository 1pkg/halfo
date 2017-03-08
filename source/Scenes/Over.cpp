#include "Over.hpp"
#include "include.hpp"

namespace Scenes
{

cocos2d::Scene *
Over::instantiate()
{
    cocos2d::Scene * scene = cocos2d::Scene::create();
	Over * over = Over::create();
	scene->addChild(over);
    return scene;
}

Over *
Over::create()
{
    Over * over = new (std::nothrow) Over();
    if (over && over->initWithColor(cocos2d::Color4B::GRAY))
        over->autorelease();
    else
        CC_SAFE_DELETE(over);
    return over;
}

Over::Over()
	: _restart(cocos2d::ui::Button::create()),
	_exit(cocos2d::ui::Button::create()),
	_label(cocos2d::Label::create())
{
	_restart->setTitleText("Act");
	_restart->setPosition(Master::instance().get<Components::Metric>("metric").size() / 2.0f + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>("metric").size().height / 8.0f));
	_restart->addTouchEventListener(
		[](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					Master::instance().scene("Act");
					break;

				default: break;
			}
		}
	);
	addChild(_restart);

	_exit->setTitleText("Exit");
	_exit->setPosition(Master::instance().get<Components::Metric>("metric").size() / 2.0f - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>("metric").size().height / 8.0f));
	_exit->addTouchEventListener(
		[](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					Master::instance().scene("Exit");
					break;

				default: break;
			}
		}
	);
	addChild(_exit);

	_label->setString("Model:" + cocos2d::getDeviceModel() + "|Version:" + cocos2d::getDeviceVersion());
	_label->setPosition(Master::instance().get<Components::Metric>("metric").size() / 2.0f - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>("metric").size().height / 4.0f));
	addChild(_label);
}

Over::~Over()
{
	_restart->removeFromParentAndCleanup(true);
	_exit->removeFromParentAndCleanup(true);
}

}