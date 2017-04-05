#include "components.hpp"
#include "Button.hpp"

namespace Views
{

namespace Ui
{

Button::Button(const std::string & icon, const std::string & title, std::function<void()> click)
{
	std::string primary = "icon-" + icon  + "-primary";
	std::string active = "icon-" + icon  + "-active";
	std::string disable = "icon-" + icon  + "-disable";
	cocos2d::ui::Button * button = cocos2d::ui::Button::create(primary, active, disable, cocos2d::ui::Widget::TextureResType::PLIST);
	std::function<void(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)> callback =
	[click](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::BEGAN)
			click();
	};
	button->addTouchEventListener(callback);

	std::string font = Master::instance().get<Components::Font>().get(Components::Font::EARTH_2073);
	cocos2d::Label * label = cocos2d::Label::createWithTTF(title, font, Components::Font::LARGE_SIZE);
	label->setColor(cocos2d::Color3B::BLACK);
	
	_layout = cocos2d::ui::Layout::create();
	_layout->setContentSize(button->getContentSize() + cocos2d::Size(0.0f, label->getContentSize().height));
	_layout->addChild(button);
	button->setPosition(cocos2d::Vec2(_layout->getContentSize().width * 0.5f, _layout->getContentSize().height - button->getContentSize().height * 0.5f));
	_layout->addChild(label);
	label->setPosition(cocos2d::Vec2(_layout->getContentSize().width * 0.5f, label->getContentSize().height * 0.5f));
}

cocos2d::Node *
Button::node() const
{
	return _layout;
}

}

}