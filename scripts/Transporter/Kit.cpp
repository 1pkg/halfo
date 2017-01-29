#include "Kit.hpp"
#include "Objects\Figure.hpp"
#include "Views\Figure.hpp"

namespace Transporter
{

Kit::Kit(cocos2d::Layer * layer)
	: _layer(layer), _touch(cocos2d::EventListenerTouchOneByOne::create()), _physic(cocos2d::EventListenerPhysicsContact::create())
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeBox(size);
	body->setCategoryBitmask(0x4);
	body->setCollisionBitmask(0x3);
	body->setContactTestBitmask(0x3);
	_layer->setPhysicsBody(body);

	std::pair<cocos2d::Vec2, cocos2d::Vec2> line(cocos2d::Vec2(size.width / 2.0f, 0.0f), cocos2d::Vec2(size.width / 2.0f, size.height));
	cocos2d::DrawNode * node = cocos2d::DrawNode::create();
	node->drawLine(
		line.first,
		line.second,
		cocos2d::Color4F::RED
	);
	_layer->addChild(node);

	_touch->onTouchBegan = [this, line](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto it = _pool.begin();
		while (it != _pool.end())
			if ((*it).second->intersect(line))
			{
				auto figures = (*it).second->divide(line);
				figures.first->render()->attach(_layer);
				figures.first->view()->setPosition((*it).second->view()->getPosition());
				figures.first.release();
				figures.second->render()->attach(_layer);
				figures.second->view()->setPosition((*it).second->view()->getPosition());
				figures.second.release();
				it = _pool.erase(it);
			}
			else
				++it;

		return false;
	};
	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_touch, 1);

	_physic->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		cocos2d::PhysicsBody * first = contact.getShapeA()->getBody();
		cocos2d::PhysicsBody * second = contact.getShapeB()->getBody();
		if (_pool.find(first) != _pool.end() && second == _layer->getPhysicsBody())
		{
			_pool.find(first)->second->fill();
			_pool.find(first)->second.release();
			_pool.erase(_pool.find(first));
		}

		if (_pool.find(second) != _pool.end() && first == _layer->getPhysicsBody())
		{
			_pool.find(second)->second->fill();
			_pool.find(second)->second.release();
			_pool.erase(_pool.find(second));
		}

		return false;
	};
	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_physic, 1);
}

void
Kit::update(float dt)
{
	static float zi = 0.0f;
	zi += dt;
	if (zi < 5.0f)
		return;

	zi = 0.0f;
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	std::vector<cocos2d::Vec2> pattern;
	pattern.push_back(cocos2d::Vec2(0.0f, 0.0f));
	pattern.push_back(cocos2d::Vec2(100.0f, 100.0f));
	pattern.push_back(cocos2d::Vec2(200.0f, 0.0f));
	Objects::Figure * figure = new Objects::Figure(
		pattern,
		cocos2d::Color4F::GREEN,
		cocos2d::PhysicsMaterial(1.0f, 0.5f, 0.5f)
	);
	figure->render()->attach(_layer);
	figure->view()->setPosition(cocos2d::Vec2(size.width / 6.0f, size.height / 2.0f));
	figure->view()->body()->setVelocity(cocos2d::Vec2(50.0f, 0.0f));
	_pool.insert(
		std::pair<
			cocos2d::PhysicsBody *,
			std::unique_ptr<Objects::Figure>
		>(
			figure->view()->body(),
			std::move(std::unique_ptr<Objects::Figure>(figure))
		)
	);
}

}