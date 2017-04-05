#include "components.hpp"
#include "Blade.hpp"

namespace Views
{

namespace Object
{

Blade::Blade()
{
	cocos2d::Rect rect = Master::instance().get<Components::Metric>().hammer();
	const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_BLADE_RESOURCE);
	cocos2d::SpriteFrame * spriteFrame = Master::instance().get<Components::SpriteFrame>().get(resource);
	_sprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
	_sprite->setContentSize(rect.size);
	_sprite->setPosition(rect.origin);
	cocos2d::PhysicsBody * body = Master::instance().get<Components::Body>().get(resource, _sprite);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_sprite->setPhysicsBody(body);
}

cocos2d::Node *
Blade::node() const
{
	return _sprite;
}

}

}