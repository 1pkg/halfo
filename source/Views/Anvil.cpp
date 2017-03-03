#include "Anvil.hpp"

namespace Views
{

Anvil::Anvil()
	: _node(cocos2d::DrawNode::create())
{
	const std::array<
		cocos2d::Vec2, 2
	> & anvil = Master::instance().metric().anvil();
	_node->drawLine(
		anvil[0],
		anvil[1],
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createEdgeSegment(anvil[0], anvil[1]);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_node->setPhysicsBody(body);
}

Anvil::~Anvil()
{
	_node->removeFromParentAndCleanup(true);
}

void
Anvil::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

cocos2d::PhysicsBody *
Anvil::body() const
{
	return _node->getPhysicsBody();
}

}