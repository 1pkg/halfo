#include "components.hpp"
#include "Separator.hpp"

namespace Views
{

namespace Ui
{

Separator::Separator(cocos2d::Vec2 first, cocos2d::Vec2 second)
{
	_layout = cocos2d::ui::Layout::create();
	cocos2d::DrawNode * draw = cocos2d::DrawNode::create();
	glLineWidth(6.0f);
	draw->drawLine(first, second, cocos2d::Color4F::BLACK);
	_layout->addChild(draw);
	if (first.y - second.y == 0)
		_layout->setContentSize(cocos2d::Size(first.x - second.x, 6.0f));
	else
		_layout->setContentSize(cocos2d::Size(6.0f, first.y - second.y));
	draw->setPosition(_layout->getContentSize() * 0.5f);
}

cocos2d::Node *
Separator::node() const
{
	return _layout;
}

}

}