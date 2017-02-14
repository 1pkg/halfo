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
		_prepool.insert(
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
Kit::find(std::pair<cocos2d::Vec2, cocos2d::Vec2> line) const
{
	std::vector<Objects::Figure *> result;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::const_iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if ((*it).second->intersect(line))
			result.push_back(it->second.get());
		++it;
	}
	return result;
}

Objects::Figure *
Kit::find(cocos2d::PhysicsBody * body) const
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::const_iterator it = _pool.find(body);
	if (it == _pool.end())
		return nullptr;

	return it->second.get();
}

std::unique_ptr<Objects::Figure>
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
			std::unique_ptr<Objects::Figure>
				figure = std::move((*it).second);
			_pool.erase(it);
			return figure;
		}
		++it;
	}
	return nullptr;
}

void
Kit::increase()
{
	_architector.increase();
}

void
Kit::reset()
{
	_architector.reset();
}

bool
Kit::contact(cocos2d::PhysicsContact & contact)
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it;
	if ((it = _prepool.find(first)) != _prepool.end() && second == _edge->getPhysicsBody())
	{
		_pool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				it->first,
				std::move(it->second)
			)
		);
		_prepool.erase(it);
		return false;
	}
	if ((it = _prepool.find(second)) != _prepool.end() && first == _edge->getPhysicsBody())
	{
		_pool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				it->first,
				std::move(it->second)
			)
		);
		_prepool.erase(it);
		return false;
	}

	if ((it = _pool.find(first)) != _pool.end() && second == _edge->getPhysicsBody())
	{
		_act->cleaner()->reset();
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}
	if ((it = _pool.find(second)) != _pool.end() && first == _edge->getPhysicsBody())
	{
		_act->cleaner()->reset();
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}

	if (_act->cleaner()->find(first) && second == _edge->getPhysicsBody())
		return true;

	if (_act->cleaner()->find(second) && first == _edge->getPhysicsBody())
		return true;

	return contact.getResult();
}

}