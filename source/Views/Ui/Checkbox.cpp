#include "components.hpp"
#include "Checkbox.hpp"

namespace Views
{

namespace Ui
{

Checkbox::Checkbox(std::string title, bool state)
{
	_layout = cocos2d::ui::Layout::create();
	_layout->setContentSize(Master::instance().get<Components::Metric>().checkbox());
	_layout->addChild(cocos2d::Label::createWithTTF(title, Master::instance().get<Components::Font>().get(), MEDIUM_FONT_SIZE));

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("checkbox", Components::Resource::Type::TEXTURE), "checkbox"), cocos2d::Rect(cocos2d::Vec2::ZERO, COMMON_TEXTURE_SIZE)), "checkbox");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::createWithTexture(Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get("checkbox-clicked", Components::Resource::Type::TEXTURE), "checkbox-clicked"), cocos2d::Rect(cocos2d::Vec2::ZERO,COMMON_TEXTURE_SIZE)), "checkbox-clicked");
	cocos2d::ui::CheckBox * checkbox = cocos2d::ui::CheckBox::create("checkbox", "checkbox-clicked", cocos2d::ui::Widget::TextureResType::PLIST);
	checkbox->setSelected(state);
	std::function<void(cocos2d::Ref * sender, cocos2d::ui::CheckBox::EventType type)> callback =
	[this](cocos2d::Ref * sender, cocos2d::ui::CheckBox::EventType type)
	{
		if (change)
			change(type == cocos2d::ui::CheckBox::EventType::SELECTED);
		return;
	};
	checkbox->addEventListener(callback);
	_layout->addChild(checkbox);
	_node = _layout;
}

}

}