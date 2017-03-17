#include "components.hpp"
#include "Figure.hpp"

namespace Views
{

Figure::Figure(const cocos2d::Vec2 * pattern, std::size_t size, float angle, bool hollow)
{
	cocos2d::Size spawn = Master::instance().get<Components::Metric>().spawn();
	const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_FIGURE_RESOURCE);
	cocos2d::Texture2D * texture = Master::instance().get<Components::Texture>().get(Master::instance().get<Components::Resource>().get(resource, Components::Resource::Type::TEXTURE), resource);
	_sprite = cocos2d::Sprite::createWithTexture(texture);
	_sprite->setContentSize(spawn);
	_sprite->setRotation(angle);
	_stencil = cocos2d::DrawNode::create();
    _stencil->drawPolygon(pattern, size, cocos2d::Color4F::BLACK, 0.0f, cocos2d::Color4F::BLACK);
	_clipper = cocos2d::ClippingNode::create();
	_clipper->setStencil(_stencil);
	_clipper->addChild(_sprite);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createPolygon(pattern, size);
	body->setDynamic(true);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	body->setGravityEnable(!hollow);
	_clipper->setPhysicsBody(body);
}

Figure::~Figure()
{
	_clipper->removeFromParentAndCleanup(true);
}

void
Figure::attach(cocos2d::Layer * layer)
{
	if (_clipper->getParent())
		return;

	layer->addChild(_clipper);
}

cocos2d::PhysicsBody *
Figure::body() const
{
	return _clipper->getPhysicsBody();
}

cocos2d::Vec2
Figure::getPosition() const
{
	return _clipper->getPosition();
}

void
Figure::setPosition(cocos2d::Vec2 position)
{
	_clipper->setPosition(position);
}

float
Figure::getRotation() const
{
	return _clipper->getRotation();
}

void
Figure::setRotation(float angle) const
{
	_clipper->setRotation(angle);
}

}