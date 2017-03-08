#include "Over.hpp"

namespace Views
{

Over::Over()
{
	const std::array<cocos2d::Vec2, 2> & over = Master::instance().get<Components::Metric>("metric").over();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(over[0], over[1], cocos2d::Color4F::RED);
}

Over::~Over()
{
	_draw->removeFromParentAndCleanup(true);
}

void
Over::attach(cocos2d::Layer * layer)
{
	if (_draw->getParent())
		return;

	layer->addChild(_draw);
}

}