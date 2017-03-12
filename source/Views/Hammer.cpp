#include "Hammer.hpp"

namespace Views
{

Hammer::Hammer()
{
	cocos2d::Rect hammer = Master::instance().get<Components::Metric>().hammer();
	const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_HAMMER_RESOURCE);
	cocos2d::Texture2D * texture = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get(resource, Components::Resource::Type::TEXTURE), resource);
	_sprite = cocos2d::Sprite::createWithTexture(texture);
	_sprite->setContentSize(hammer.size);
	_sprite->setPosition(hammer.origin);
	cocos2d::PhysicsBody * body = Master::instance().get<Components::Body>().get(Master::instance().get<Components::Resource>().get(resource, Components::Resource::Type::BODY), _sprite);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_sprite->setPhysicsBody(body);
}

Hammer::~Hammer()
{
	_sprite->removeFromParentAndCleanup(true);
}

void
Hammer::attach(cocos2d::Layer * layer)
{
	if (_sprite->getParent())
		return;

	layer->addChild(_sprite);
}

cocos2d::PhysicsBody *
Hammer::body() const
{
	return _sprite->getPhysicsBody();
}

void
Hammer::run(cocos2d::Action * action)
{
	_sprite->runAction(action);
}

}