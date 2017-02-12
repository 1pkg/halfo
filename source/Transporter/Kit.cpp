#include "Kit.hpp"
#include "Application/Act.hpp"
#include "Objects/Figure.hpp"

namespace Transporter
{

Kit::Kit(Application::Act * act)
	: _edge(cocos2d::Node::create()),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	/*			Edge			*/
	const std::array<
		cocos2d::Vec2, 4
	> & vector = Application::Metric::instance().transporterEdge();
	cocos2d::PhysicsBody * body =
		cocos2d::PhysicsBody::createEdgeChain(vector.data(), vector.size());
	body->setDynamic(false);
	body->setContactTestBitmask(DEFAULT_PHYSICS_MASK);
	_edge->setPhysicsBody(body);
	_act->addChild(_edge);

	/*			Sensor			*/
	_sensor->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		return this->contact(contact);
	};
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_sensor, _act);
}

Kit::~Kit()
{
	_edge->removeFromParentAndCleanup(true);
	_act->getEventDispatcher()->removeEventListener(_sensor);
}

void
Kit::update(float dt)
{
	static float
		spawn = 0.0f, refresh = 0.0f;
	spawn += dt, refresh += dt;

	if (spawn >= SPAWN_TIME)
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

	if (refresh >= REFRESH_TIME)
	{
		_architector.refresh();
		refresh = 0.0f;
	}
}

std::vector<Objects::Figure *>
Kit::find(std::pair<cocos2d::Vec2, cocos2d::Vec2> line)
{
	std::vector<Objects::Figure *> result;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if ((*it).second->intersect(line))
			result.push_back(it->second.get());
		++it;
	}
	return result;
}

std::unique_ptr<Objects::Figure>
Kit::release(cocos2d::PhysicsBody * body)
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _pool.find(body);
	if (it == _pool.end())
		return nullptr;

	std::unique_ptr<Objects::Figure>
		figure = std::move((*it).second);
	_pool.erase(it);
	return figure;
}

void
Kit::release(Objects::Figure * figure)
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if ((*it).second.get() == figure)
		{
			_pool.erase(it);
			return;
		}
		++it;
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();
	if (_pool.find(first) != _pool.end() && second == _edge->getPhysicsBody())
	{
		_act->cleaner()->reset();
		_pool.find(first)->second->fill();
		_act->cleaner()->attach(
			std::move(_pool.find(first)->second)
		);
		_pool.erase(_pool.find(first));
		return true;
	}
	if (_pool.find(second) != _pool.end() && first == _edge->getPhysicsBody())
	{
		_act->cleaner()->reset();
		_pool.find(second)->second->fill();
		_act->cleaner()->attach(
			std::move(_pool.find(second)->second)
		);
		_pool.erase(_pool.find(second));
		return true;
	}

	if (_act->cleaner()->find(first) && second == _edge->getPhysicsBody())
		return true;

	if (_act->cleaner()->find(second) && first == _edge->getPhysicsBody())
		return true;

	return contact.getResult();
}

}