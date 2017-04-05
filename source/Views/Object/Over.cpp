#include "components.hpp"
#include "Over.hpp"

namespace Views
{

namespace Object
{

Over::Over()
{
	const std::array<cocos2d::Vec2, 2> & over = Master::instance().get<Components::Metric>().over();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(over[0], over[1], cocos2d::Color4F::RED);
}

cocos2d::Node *
Over::node() const
{
	return _draw;
}

}

}