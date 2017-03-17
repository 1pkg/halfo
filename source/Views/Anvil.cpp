#include "components.hpp"
#include "Anvil.hpp"

namespace Views
{

Anvil::Anvil()
{
	const cocos2d::Rect & anvil = Master::instance().get<Components::Metric>().anvil();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(anvil.origin, anvil.origin + anvil.size, cocos2d::Color4F::BLACK);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeSegment(anvil.origin, anvil.origin + anvil.size);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_draw->setPhysicsBody(body);
}

Anvil::~Anvil()
{
	_draw->removeFromParentAndCleanup(true);
}

void
Anvil::attach(cocos2d::Layer * layer)
{
	if (_draw->getParent())
		return;

	layer->addChild(_draw);
}

cocos2d::PhysicsBody *
Anvil::body() const
{
	return _draw->getPhysicsBody();
}

}