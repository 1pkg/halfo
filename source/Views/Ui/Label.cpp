#include "components.hpp"
#include "Label.hpp"

namespace Views
{

namespace Ui
{

Label::Label(const std::string & text)
{
	std::string font = Master::instance().get<Components::Font>().get(Components::Font::EARTH_2073);
	cocos2d::Label * label = cocos2d::Label::createWithTTF(text, font, Components::Font::MEDIUM_SIZE);
	label->setColor(cocos2d::Color3B::BLACK);

	_layout = cocos2d::ui::Layout::create();
	_layout->setContentSize(label->getContentSize());
	_layout->addChild(label);
	label->setPosition(label->getContentSize() * 0.5f);
}

cocos2d::Node *
Label::node() const
{
	return _layout;
}

}

}