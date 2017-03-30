#include "components.hpp"
#include "Button.hpp"

namespace Views
{

namespace Ui
{

Button::Button(std::string title, bool primary)
{
	cocos2d::Size size = Master::instance().get<Components::Metric>().button(primary);
	if (primary)
	{
		_button = cocos2d::ui::Button::create("primary-button", "primary-button-clicked", "", cocos2d::ui::Widget::TextureResType::PLIST);
		_button->setTitleFontSize(MEDIUM_FONT_SIZE * 3.0f);
	}
	else
	{
		_button = cocos2d::ui::Button::create("secondary-button", "secondary-button-clicked", "", cocos2d::ui::Widget::TextureResType::PLIST);
		_button->setTitleFontSize(SMALL_FONT_SIZE * 3.0f);
	}
	_button->setTouchEnabled(true);
	_button->setScaleX(size.width / COMMON_TEXTURE_SIZE.width);
	_button->setScaleY(size.height / COMMON_TEXTURE_SIZE.height);
	std::function<void(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)> callback =
	[this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::BEGAN && click)
			click();
		return;
	};
	_button->addTouchEventListener(callback);
	const std::string & font = Master::instance().get<Components::Font>().get("font");
	_button->setTitleFontName(font);
	_button->setTitleText(title);
	_node = _button;
}

}

}