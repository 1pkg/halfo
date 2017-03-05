#include "Hammer.hpp"
#include "Helpers/Texture.hpp"

namespace Views
{

Hammer::Hammer()
{
	cocos2d::Rect hammer = Master::instance().metric().hammer();
	const std::string & skin = Master::instance().setting().get(Components::Setting::HAMMER_SKIN);
	const cocos2d::Data & data = Master::instance().resource().get(skin);
	cocos2d::Texture2D * texture = Helpers::Texture::intance().get(skin, data);
	_sprite = cocos2d::Sprite::createWithTexture(texture);
	_sprite->setContentSize(hammer.size);
	_sprite->setPosition(hammer.origin);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createBox(hammer.size);
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