#include "Hammer.hpp"

namespace Views
{

Hammer::Hammer()
{
	cocos2d::Rect hammer = Master::instance().metric().hammer();
	std::string skin = "hammer-skin-" + Master::instance().setting().get(Components::Setting::HAMMER_SKIN);
	const cocos2d::Data & data = Master::instance().resource().get(skin);
	_image = new cocos2d::Image();
	_image->initWithImageData(data.getBytes(), data.getSize());
	cocos2d::Texture2D * texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(_image, skin);
	_node = cocos2d::Sprite::createWithTexture(texture);
	_node->setContentSize(hammer.size);
	_node->setPosition(hammer.origin);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createBox(hammer.size);
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_node->setPhysicsBody(body);
}

Hammer::~Hammer()
{
	_node->removeFromParentAndCleanup(true);
	delete _image;
}

void
Hammer::attach(cocos2d::Layer * layer)
{
	if (_node->getParent() != nullptr)
		return;

	layer->addChild(_node);
}

cocos2d::PhysicsBody *
Hammer::body() const
{
	return _node->getPhysicsBody();
}

void
Hammer::run(cocos2d::Action * action)
{
	_node->runAction(action);
}

}