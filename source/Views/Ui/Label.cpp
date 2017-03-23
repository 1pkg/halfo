#include "components.hpp"
#include "Label.hpp"

namespace Views
{

namespace Ui
{

Label::Label(float fontSize)
{
	const std::string & font = Master::instance().get<Components::Font>().get();
	_label = cocos2d::Label::createWithTTF("", font, fontSize);
	_node = _label;
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

}