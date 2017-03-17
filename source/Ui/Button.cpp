#include "components.hpp"
#include "Button.hpp"

namespace Ui
{

Button::Button(std::string title, bool primary)
{
	cocos2d::Size size = Master::instance().get<Components::Metric>().button(primary);
	if (primary)
	{
		cocos2d::Texture2D * primary = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("primary-button", Components::Resource::Type::TEXTURE), "primary-button");
		cocos2d::Texture2D * clicked = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("primary-button-clicked", Components::Resource::Type::TEXTURE), "primary-button-clicked");
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(primary, cocos2d::Rect(cocos2d::Vec2::ZERO, COMMON_TEXTURE_SIZE)), "primary-button");
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(clicked, cocos2d::Rect(cocos2d::Vec2::ZERO,COMMON_TEXTURE_SIZE)), "primary-button-clicked");
		_button = cocos2d::ui::Button::create("primary-button", "primary-button-clicked", "", cocos2d::ui::Widget::TextureResType::PLIST);
		_button->setTitleFontSize(MEDIUM_FONT_SIZE * 3.0f);
	}
	else
	{
		cocos2d::Texture2D * secondary = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("secondary-button", Components::Resource::Type::TEXTURE), "secondary-button");
		cocos2d::Texture2D * clicked = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("secondary-button-clicked", Components::Resource::Type::TEXTURE), "secondary-button-clicked");
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(secondary, cocos2d::Rect(cocos2d::Vec2::ZERO, COMMON_TEXTURE_SIZE)), "secondary-button");
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(clicked, cocos2d::Rect(cocos2d::Vec2::ZERO,COMMON_TEXTURE_SIZE)), "secondary-button-clicked");
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
	const std::string & font = Master::instance().get<Components::Font>().get();
	_button->setTitleFontName(font);
	_button->setTitleText(title);
}

Button::~Button()
{
	_button->removeFromParentAndCleanup(true);
}

void
Button::attach(cocos2d::Layer * layer)
{
	if (_button->getParent())
		return;

	layer->addChild(_button);
}

cocos2d::Vec2
Button::getPosition() const
{
	return _button->getPosition();
}

void
Button::setPosition(cocos2d::Vec2 position)
{
	_button->setPosition(position);
}

}