#include "Figure.hpp"
#include "Application/Metric.hpp"

namespace Views
{

Figure::Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		cocos2d::Color4F color,
		bool hollow
)
	: _node(cocos2d::DrawNode::create())
{
	_node->drawPolygon(
		pattern,
		size,
		color,
		LINE_WIDHT,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createPolygon(
			pattern,
			size
		);
	body->setVelocityLimit(LINEAR_VELOCITY_LIMIT);
	body->setAngularVelocityLimit(ANGULAR_VELOCITY_LIMIT);
	_node->setPhysicsBody(body);
	setHollow(hollow);
}

Figure::~Figure()
{
	_node->removeFromParentAndCleanup(true);
}

void
Figure::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

cocos2d::PhysicsBody *
Figure::body() const
{
	return _node->getPhysicsBody();
}

cocos2d::Vec2
Figure::getPosition() const
{
	return _node->getPosition();
}

void
Figure::setPosition(cocos2d::Vec2 position)
{
	_node->setPosition(position);
}

float
Figure::getRotation() const
{
	return _node->getRotation();
}

void
Figure::setRotation(float angle) const
{
	_node->setRotation(angle);
}

void
Figure::setHollow(bool hollow)
{
	cocos2d::PhysicsBody * body = _node->getPhysicsBody();
	body->setGravityEnable(!hollow);
	body->setDynamic(true);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setVelocity(cocos2d::Vec2::ZERO);
}

}