#include "Platform.hpp"

namespace Views
{

Platform::Platform()
{
	cocos2d::Rect platform = Master::instance().get<Components::Metric>().platform();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(platform.origin, platform.origin + platform.size, cocos2d::Color4F::BLACK);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeSegment(platform.origin, platform.origin + platform.size);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_draw->setPhysicsBody(body);
}

Platform::~Platform()
{
	_draw->removeFromParentAndCleanup(true);
}

void
Platform::attach(cocos2d::Layer * layer)
{
	if (_draw->getParent())
		return;

	layer->addChild(_draw);
}

cocos2d::PhysicsBody *
Platform::body() const
{
	return _draw->getPhysicsBody();
}

void
Platform::run(cocos2d::Action * action)
{
	_draw->runAction(action);
}

}