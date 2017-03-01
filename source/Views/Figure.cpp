#include "Figure.hpp"

namespace Views
{

Figure::Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		bool hollow
)
	: _node(cocos2d::DrawNode::create())
{
	_node->drawPolygon(
		pattern,
		size,
		cocos2d::Color4F::GREEN,
		0.0f,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createPolygon(pattern,size);
	body->setDynamic(true);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	body->setGravityEnable(!hollow);
	_node->setPhysicsBody(body);
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

}