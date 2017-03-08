#include "Anvil.hpp"

namespace Views
{

Anvil::Anvil()
{
	const std::array<cocos2d::Vec2, 2> & anvil = Master::instance().get<Components::Metric>("metric").anvil();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(anvil[0], anvil[1], cocos2d::Color4F::BLACK);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeSegment(anvil[0], anvil[1]);
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