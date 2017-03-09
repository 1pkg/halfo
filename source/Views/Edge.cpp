#include "Edge.hpp"

namespace Views
{

Edge::Edge()
{
	const std::array<cocos2d::Vec2, 4> & edge = Master::instance().get<Components::Metric>().edge();
	_draw = cocos2d::DrawNode::create();
	_draw->drawPoly(edge.data(), edge.size(), false,cocos2d::Color4F::BLACK);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeChain(edge.data(), edge.size());
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_draw->setPhysicsBody(body);
}

Edge::~Edge()
{
	_draw->removeFromParentAndCleanup(true);
}

void
Edge::attach(cocos2d::Layer * layer)
{
	if (_draw->getParent())
		return;

	layer->addChild(_draw);
}

cocos2d::PhysicsBody *
Edge::body() const
{
	return _draw->getPhysicsBody();
}

}