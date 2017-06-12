#include "components.hpp"
#include "Figure.hpp"

namespace Views
{

namespace Object
{

Figure::Figure(const cocos2d::Polygon & pattern, float angle, bool hollow)
{
	cocos2d::Size spawn = Master::instance().get<Components::Metric>().spawn();
	const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_FIGURE_RESOURCE);
	cocos2d::SpriteFrame * spriteFrame = Master::instance().get<Components::SpriteFrame>().get(resource);
	_sprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
	_sprite->setContentSize(spawn);
	_sprite->setRotation(angle);
	_stencil = cocos2d::DrawNode::create();
    _stencil->drawPolygon(pattern.data(), pattern.size(), cocos2d::Color4F::BLACK, 0.0f, cocos2d::Color4F::BLACK);
	_clipper = cocos2d::ClippingNode::create();
	_clipper->setStencil(_stencil);
	_clipper->addChild(_sprite);
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::create();
	std::vector<std::array<cocos2d::Vec2, 3>> triangles = Master::instance().get<Components::Triangulator>().triangulate(pattern);
	for (std::array<cocos2d::Vec2, 3> triangle : triangles)
		body->addShape(cocos2d::PhysicsShapePolygon::create(triangle.data(), triangle.size()));
	body->setDynamic(true);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	body->setGravityEnable(!hollow);
	_clipper->setPhysicsBody(body);
}

Figure::~Figure()
{
	_clipper->setVisible(false);
	_clipper->getPhysicsBody()->setEnabled(false);
}

cocos2d::Node *
Figure::node() const
{
	return _clipper;
}

}

}