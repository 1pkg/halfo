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
	_exit(cocos2d::ui::Button::create())
{
	_restart->setTitleText("Act");
	_restart->setTitleFontSize(32.0f);
	_restart->setPosition(Master::instance().get<Components::Metric>().size() / 2.0f + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height / 4.0f));
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
	_exit->setTitleFontSize(32.0f);
	_exit->setPosition(Master::instance().get<Components::Metric>().size() / 2.0f);
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

	_label = cocos2d::Label::createWithTTF("", Master::instance().get<Components::Font>().get(), 32.0f);
	_label->setString("Model:" + cocos2d::getDeviceModel() + "|Version:" + cocos2d::getDeviceVersion());
	_label->setPosition(Master::instance().get<Components::Metric>().size() / 2.0f - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height / 6.0f));
	addChild(_label);

	_score = cocos2d::Label::createWithTTF("", Master::instance().get<Components::Font>().get(), 32.0f);
	std::tuple<unsigned int, unsigned int, unsigned int> row = Master::instance().get<Components::Statistic>().table()[0];
	_score->setString("Slice:" + to_string(std::get<0>(row)) + "|Time:" + to_string(std::get<1>(row)) + "|Total:" + to_string(std::get<2>(row)));
	_score->setPosition(Master::instance().get<Components::Metric>().size() / 2.0f - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height / 4.0f));
	addChild(_score);
}

Over::~Over()
{
	_restart->removeFromParentAndCleanup(true);
	_exit->removeFromParentAndCleanup(true);
	_label->removeFromParentAndCleanup(true);
	_score->removeFromParentAndCleanup(true);
}

}