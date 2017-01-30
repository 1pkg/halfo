#include "Kit.hpp"
#include "Objects\Figure.hpp"
#include "Views\Figure.hpp"

namespace Transporter
{

Kit::Kit(cocos2d::Layer * layer)
	: _layer(layer),
	_touchSensor(cocos2d::EventListenerTouchOneByOne::create()),
	_physicSensor(cocos2d::EventListenerPhysicsContact::create())
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

	_touchSensor->onTouchBegan = [this, line](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		return this->touch(touch, event, line);
	};
	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_touchSensor, 1);

	_physicSensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_layer->getEventDispatcher()->addEventListenerWithFixedPriority(_physicSensor, 1);
}

void
Kit::update(float dt)
{
	static float zi = 0.0f;
	zi += dt;
	if (zi < 2.0f)
		return;

	render();
	zi = 0.0f;
}

void
Kit::render()
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	std::vector<cocos2d::Vec2> pattern;
	pattern.push_back(cocos2d::Vec2::ZERO);
	std::size_t vsize = 3 + std::rand() % 1;
	for (std::size_t i = 0; i < vsize; ++i)
		pattern.push_back(
			cocos2d::Vec2(
				pattern.back().x + (std::rand() % 200 - 50),
				pattern.back().y + (std::rand() % 300 - 100)
			)
		);
	Objects::Figure * figure = new Objects::Figure(
		pattern,
		cocos2d::Color4F::GREEN,
		cocos2d::PhysicsMaterial(1.0f, 0.5f, 0.5f)
	);
	figure->render()->attach(_layer);

	figure->view()->setPosition(cocos2d::Vec2(size.width / 8.0f, size.height / 2.0f));
	figure->view()->body()->setVelocity(cocos2d::Vec2(50.0f + std::rand() % 150, 0.0f));

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

bool
Kit::touch(cocos2d::Touch * touch, cocos2d::Event * event, std::pair<cocos2d::Vec2, cocos2d::Vec2> line)
{
	auto it = _pool.begin();
	while (it != _pool.end())
		if ((*it).second->intersect(line))
		{
			auto figures = (*it).second->divide(line);
			figures.first->render()->attach(_layer);
			figures.first->view()->setPosition((*it).second->view()->getPosition());
			figures.first->view()->body()->applyImpulse((cocos2d::Vec2(-30000.0f, -10000.0f)));
			figures.first.release();
			figures.second->render()->attach(_layer);
			figures.second->view()->setPosition((*it).second->view()->getPosition());
			figures.second->view()->body()->applyImpulse((cocos2d::Vec2(20000.0f, -20000.0f)));
			figures.second.release();
			it = _pool.erase(it);
		}
		else
			++it;

	return false;
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
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

	return true;
}

}