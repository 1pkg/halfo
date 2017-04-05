#include "components.hpp"
#include "Anvil.hpp"

namespace Views
{

namespace Object
{

Anvil::Anvil()
{
	const cocos2d::Rect & rect = Master::instance().get<Components::Metric>().anvil();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(rect.origin, rect.origin + rect.size, cocos2d::Color4F::BLACK);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeSegment(rect.origin, rect.origin + rect.size);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_draw->setPhysicsBody(body);
}

cocos2d::Node *
Anvil::node() const
{
	return _draw;
}

}

}