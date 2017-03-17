#include "components.hpp"
#include "Checkbox.hpp"

namespace Ui
{

Checkbox::Checkbox(std::string title)
{
	cocos2d::Size size = Master::instance().get<Components::Metric>().checkbox();
	cocos2d::Texture2D * checkbox = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("checkbox", Components::Resource::Type::TEXTURE), "checkbox");
	cocos2d::Texture2D * clicked = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("checkbox-clicked", Components::Resource::Type::TEXTURE), "checkbox-clicked");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(checkbox, cocos2d::Rect(cocos2d::Vec2::ZERO, COMMON_TEXTURE_SIZE)), "checkbox");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(clicked, cocos2d::Rect(cocos2d::Vec2::ZERO,COMMON_TEXTURE_SIZE)), "checkbox-clicked");
	_checkbox = cocos2d::ui::CheckBox::create("checkbox", "", "checkbox-clicked", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	_checkbox->setTouchEnabled(true);
	_checkbox->setScaleX(size.width / COMMON_TEXTURE_SIZE.width);
	_checkbox->setScaleY(size.height / COMMON_TEXTURE_SIZE.height);
	std::function<void(cocos2d::Ref * sender, cocos2d::ui::CheckBox::EventType type)> callback =
	[this](cocos2d::Ref * sender, cocos2d::ui::CheckBox::EventType type)
	{
		if (change)
			change(type == cocos2d::ui::CheckBox::EventType::SELECTED);
		return;
	};
	_checkbox->addEventListener(callback);
	const std::string & font = Master::instance().get<Components::Font>().get();
	_label = cocos2d::Label::createWithTTF(title, font, SMALL_FONT_SIZE);
}

Checkbox::~Checkbox()
{
	_checkbox->removeFromParentAndCleanup(true);
	_label->removeFromParentAndCleanup(true);
}

void
Checkbox::attach(cocos2d::Layer * layer)
{
	if (_checkbox->getParent() || _label->getParent())
		return;

	layer->addChild(_checkbox);
	layer->addChild(_label);
}

cocos2d::Vec2
Checkbox::getPosition() const
{
	return _checkbox->getPosition();
}

void
Checkbox::setPosition(cocos2d::Vec2 position)
{
	_checkbox->setPosition(position);
	_label->setPosition(position);
}

bool
Checkbox::state()
{
	return _checkbox->isSelected();
}

}