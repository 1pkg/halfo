#include "View.hpp"
#include "Scene.hpp"
#include <cocos2d.h>

namespace Application
{

void
View::attach(Scene * scene)
{
	if(node() && !node()->getParent())
		scene->append(this);
}

cocos2d::Node *
View::node() const
{
	return nullptr;
}

void
View::run(cocos2d::Action * action)
{
	if(node())
		node()->runAction(action);
}

cocos2d::PhysicsBody *
View::body() const
{
	return node() ? node()->getPhysicsBody() : nullptr;
}

cocos2d::Vec2
View::getPosition() const
{
	return node() ? node()->getPosition() : cocos2d::Vec2::ZERO;
}

void
View::setPosition(cocos2d::Vec2 position)
{
	if(node())
		node()->setPosition(position);
}

float
View::getRotation() const
{
	return node() ? node()->getRotation() : 0.0f;
}

void
View::setRotation(float angle)
{
	if(node())
		node()->setRotation(angle);
}

cocos2d::Size
View::getContentSize() const
{
	return node() ? node()->getContentSize() : cocos2d::Size::ZERO;
}

void
View::setContentSize(cocos2d::Size size)
{
	if(node())
		node()->setContentSize(size);
}

void
View::setScale(float scale)
{
	if(node())
		node()->setScale(scale);
}

}