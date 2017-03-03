#include "Platform.hpp"

namespace Views
{

Platform::Platform()
	: _node(cocos2d::DrawNode::create())
{
	const std::array<
		cocos2d::Vec2, 2
	> & platform = Master::instance().metric().platform();
	_node->drawLine(
		platform[0],
		platform[1],
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createEdgeSegment(platform[0], platform[1]);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_node->setPhysicsBody(body);
}

Platform::~Platform()
{
	_node->removeFromParentAndCleanup(true);
}

void
Platform::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

cocos2d::PhysicsBody *
Platform::body() const
{
	return _node->getPhysicsBody();
}

void
Platform::run(cocos2d::Action * action)
{
	_node->runAction(action);
}

}