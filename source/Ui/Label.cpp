#include "components.hpp"
#include "Label.hpp"

namespace Ui
{

Label::Label(float fontSize)
{
	const std::string & font = Master::instance().get<Components::Font>().get();
	_label = cocos2d::Label::createWithTTF("", font, fontSize);
}

Label::~Label()
{
	_label->removeFromParentAndCleanup(true);
}

void
Label::attach(cocos2d::Layer * layer)
{
	if (_label->getParent())
		return;

	layer->addChild(_label);
}

cocos2d::Vec2
Label::getPosition() const
{
	return _label->getPosition();
}

void
Label::setPosition(cocos2d::Vec2 position)
{
	_label->setPosition(position);
}

const std::string &
Label::getText() const
{
	return _label->getString();
}

void
Label::setText(const std::string & text)
{
	_label->setString(text);
}

}