#include "components.hpp"
#include "Platform.hpp"

namespace Views
{

namespace Object
{

Platform::Platform()
{
	cocos2d::Rect rect = Master::instance().get<Components::Metric>().platform();
	_draw = cocos2d::DrawNode::create();
	_draw->drawLine(rect.origin, rect.origin + rect.size, cocos2d::Color4F::BLACK);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeSegment(rect.origin, rect.origin + rect.size);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_draw->setPhysicsBody(body);
}

cocos2d::Node *
Platform::node() const
{
	return _draw;
}

}

}