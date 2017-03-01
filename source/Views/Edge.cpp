#include "Edge.hpp"

namespace Views
{

Edge::Edge()
	: _node(cocos2d::DrawNode::create())
{
	const std::array<
		cocos2d::Vec2, 4
	> & edge = Application::Main::instance().metric().edge();
	_node->drawPoly(
		edge.data(),
		edge.size(),
		false,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createEdgeChain(edge.data(), edge.size());
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_node->setPhysicsBody(body);
}

Edge::~Edge()
{
	_node->removeFromParentAndCleanup(true);
}

void
Edge::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

cocos2d::PhysicsBody *
Edge::body() const
{
	return _node->getPhysicsBody();
}

}