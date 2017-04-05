#include "components.hpp"
#include "Edge.hpp"

namespace Views
{

namespace Object
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

cocos2d::Node *
Edge::node() const
{
	return _draw;
}

}

}