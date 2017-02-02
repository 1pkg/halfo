#include "Act.hpp"
#include "Kit.hpp"
#include "Objects/Figure.hpp"
#include "Views/Figure.hpp"
#include "Application/Metric.hpp"

namespace Transporter
{

Kit::Kit(Act * act)
	: _act(act),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_node(cocos2d::Node::create())
{
	_act->addChild(_node);
	_node->setPosition(Application::Metric::instance().center());
	cocos2d::PhysicsBody * body = cocos2d::PhysicsBody::createEdgeBox(Application::Metric::instance().size());
	body->setCategoryBitmask(0x4);
	body->setCollisionBitmask(0x3);
	body->setContactTestBitmask(0x3);
	_node->setPhysicsBody(body);

	_sensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithFixedPriority(_sensor, 1);
}

Kit::~Kit()
{
	_act->getEventDispatcher()->removeEventListener(_sensor);

	_node->removeFromParentAndCleanup(true);
}

void
Kit::update(float dt)
{
	static float spawn = 0.0f, refresh = 0.0f;
	spawn += dt;
	refresh += dt;

	if (spawn >= 2.0f)
	{
		std::unique_ptr<Objects::Figure> figure = _architector.provide();
		figure->view()->attach(_act);
		_pool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				figure->view()->body(),
				std::move(figure)
			)
		);
		spawn = 0.0f;
	}

	if (refresh >= 10.0f)
	{
		_architector.refresh();
		refresh = 0.0f;
	}
}

std::vector<
	std::unique_ptr<Objects::Figure>
>
Kit::release(std::pair<cocos2d::Vec2, cocos2d::Vec2> line)
{
	std::vector<
		std::unique_ptr<Objects::Figure>
	> result;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _pool.begin();
	while (it != _pool.end())
		if ((*it).second->intersect(line))
		{
			result.push_back(std::move(it->second));
			it = _pool.erase(it);
		}
		else
		{
			++it;
		}
	return result;
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
{
	cocos2d::PhysicsBody * first = contact.getShapeA()->getBody();
	cocos2d::PhysicsBody * second = contact.getShapeB()->getBody();
	if (_pool.find(first) != _pool.end() && _pool.find(second) != _pool.end())
		return false;

	if (_pool.find(first) != _pool.end() && second == _node->getPhysicsBody())
	{
		_pool.find(first)->second->fill();
		_pool.find(first)->second.release();
		_pool.erase(_pool.find(first));
	}

	if (_pool.find(second) != _pool.end() && first == _node->getPhysicsBody())
	{
		_pool.find(second)->second->fill();
		_pool.find(second)->second.release();
		_pool.erase(_pool.find(second));
	}
	return true;
}

void
Kit::render(float delta)
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	std::vector<cocos2d::Vec2> pattern;
	pattern.push_back(cocos2d::Vec2::ZERO);
	std::size_t vsize = 3 + std::rand() % 1;
	for (std::size_t i = 0; i < vsize; ++i)
		pattern.push_back(
			cocos2d::Vec2(
				pattern.back().x + ((std::rand() % 200) - 50),
				pattern.back().y + ((std::rand() % 100) - 50)
			)
		);
	Objects::Figure * figure = new Objects::Figure(
		pattern.data(),
		pattern.size(),
		cocos2d::Color4F::GREEN,
		cocos2d::PhysicsMaterial(1.0f, 0.5f, 0.5f)
	);
	figure->view()->attach(_act);
	figure->view()->setPosition(cocos2d::Vec2(size.width / 8.0f, size.height / 1.5f));
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

}