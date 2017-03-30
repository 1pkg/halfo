#include "components.hpp"
#include "Hammer.hpp"

namespace Views
{

namespace Object
{

Hammer::Hammer()
{
	cocos2d::Rect rect = Master::instance().get<Components::Metric>().hammer();
	const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_HAMMER_RESOURCE);
	cocos2d::SpriteFrame * spriteFrame = Master::instance().get<Components::SpriteFrame>().get(resource);
	_sprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
	_sprite->setContentSize(rect.size);
	_sprite->setPosition(rect.origin);
	cocos2d::PhysicsBody * body = Master::instance().get<Components::Body>().get(resource, _sprite);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_sprite->setPhysicsBody(body);
	_node = _sprite;
}

}

}