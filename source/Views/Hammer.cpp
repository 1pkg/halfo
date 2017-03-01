#include "Hammer.hpp"

namespace Views
{

Hammer::Hammer(const std::string & skin)
	: _node(cocos2d::DrawNode::create())
{
	const std::array<
		cocos2d::Vec2, 2
	> & hammer = Application::Main::instance().metric().hammer();
	cocos2d::Vec2 delta(0.0f, Application::Main::instance().metric().hammerLength());
	_node->drawLine(
		hammer[0] + delta,
		hammer[1] + delta,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createEdgeSegment(hammer[0] + delta, hammer[1] + delta);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_node->setPhysicsBody(body);
}

Hammer::~Hammer()
{
	_node->removeFromParentAndCleanup(true);
}

void
Hammer::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

cocos2d::PhysicsBody *
Hammer::body() const
{
	return _node->getPhysicsBody();
}

void
Hammer::run(cocos2d::Action * action)
{
	_node->runAction(action);
}

}