#include "Kit.hpp"
#include "Scenes/Act.hpp"
#include "Objects/Figure.hpp"
#include "Objects/Edge.hpp"

namespace Transporter
{

Kit::Kit(Scenes::Act * act)
	: _edge(new Objects::Edge()),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	_sensor->onContactBegin = std::bind(&Kit::contact, this, std::placeholders::_1);
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_sensor, _act);

	_edge->view()->attach(_act);
}

Kit::~Kit()
{
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
Kit::find(const std::array<cocos2d::Vec2, 2> & line) const
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

	/*
		Move to permanent pool from prepool figures provided by Architector on contact with border edge.
		Set contact result to false.
	*/
	if ((it = _prepool.find(first)) != _prepool.end() && second == _edge->view()->body())
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
	if ((it = _prepool.find(second)) != _prepool.end() && first == _edge->view()->body())
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

	/*
		Fill figures from permanent pool and move to Cleaner::Kit on contact with border edge.
		Set contact result to true.
	*/
	if ((it = _pool.find(first)) != _pool.end() && second == _edge->view()->body())
	{
		_act->cleaner()->reset();
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}
	if ((it = _pool.find(second)) != _pool.end() && first == _edge->view()->body())
	{
		_act->cleaner()->reset();
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}

	/*
		Fill figures from permanent pool and move to Cleaner::Kit on contact with each other.
		Set contact result to true.
	*/
	if (_pool.find(first) != _pool.end() && _pool.find(second) != _pool.end())
	{
		_act->cleaner()->reset();
		it = _pool.find(first);
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		it = _pool.find(second);
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}

	/*
		Fill figures from permanent pool and move to Cleaner::Kit on contact with filled figures from Cleaner::Kit pool.
		Set contact result to true.
	*/
	if ((it = _pool.find(first)) != _pool.end() && _act->cleaner()->find(second))
	{
		_act->cleaner()->reset();
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}

	if ((it = _pool.find(second)) != _pool.end() && _act->cleaner()->find(first))
	{
		_act->cleaner()->reset();
		it->second->fill();
		_act->cleaner()->attach(
			std::move(it->second)
		);
		_pool.erase(it);
		return true;
	}

	/*
		Figures from Cleaner::Kit pool on contact with border edge.
		Set contact result to true.
	*/
	if (_act->cleaner()->find(first) && second == _edge->view()->body())
		return true;

	if (_act->cleaner()->find(second) && first == _edge->view()->body())
		return true;

	return contact.getResult();
}

}