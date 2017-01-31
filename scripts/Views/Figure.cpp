#include "Figure.hpp"

namespace Views
{

Figure::Figure(
		std::vector<cocos2d::Vec2> pattern,
		cocos2d::Color4F color,
		cocos2d::PhysicsMaterial material,
		bool hollow
)
	: _node(cocos2d::DrawNode::create())
{
	_node->drawPolygon(
		pattern.data(),
		pattern.size(),
		color,
		3.0f,
		cocos2d::Color4F::BLACK
	);
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createPolygon(
			pattern.data(),
			pattern.size(),
			material
		);
	_node->setPhysicsBody(body);
	setHollow(hollow);
}

Figure::~Figure()
{
	_node->removeFromParentAndCleanup(true);
}

void
Figure::setHollow(bool hollow)
{
	cocos2d::PhysicsBody * body = _node->getPhysicsBody();
	body->setGravityEnable(!hollow); // hollow body doesnt affect by gravity.
	/*
		Hollow interact with another hollow, borders, shreadder, and filled.
		Filled interact with another filled, borders, and hollow.
		0b0001 - hollow mask
		0b0010 - filled mask
		0b0100 - borders mask
		0b1000 - shreadder mask
	*/
	body->setCategoryBitmask(hollow ? 0x1 : 0x2);
	body->setCollisionBitmask(hollow ? 0xF : 0x7);
	body->setContactTestBitmask(hollow ? 0xF : 0x7);
	body->setVelocity(cocos2d::Vec2::ZERO);
}

void
Figure::attach(cocos2d::Layer * layer)
{
	layer->addChild(_node);
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

cocos2d::PhysicsBody *
Figure::body() const
{
	return _node->getPhysicsBody();
}

}