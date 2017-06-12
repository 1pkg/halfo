#include "components.hpp"
#include "Kit.hpp"
#include "Scenes/Play.hpp"
#include "Objects/Figure.hpp"
#include "Objects/Platform.hpp"
#include "Objects/Over.hpp"

namespace Play
{

namespace Cleaner
{

Kit::Kit(Scenes::Play * play)
	: _combo(0), _result(0), _time(0),
	_platform(new Objects::Platform()),
	_over(new Objects::Over()),
	_physicSensor(cocos2d::EventListenerPhysicsContact::create()),
	_dispatcher(((cocos2d::Scene *)(*play))->getEventDispatcher()),
	_play(play)
{
	_physicSensor->onContactBegin = std::bind(&Kit::contact, this, std::placeholders::_1);
	_dispatcher->addEventListenerWithSceneGraphPriority(_physicSensor, *_play);

	_platform->view()->attach(_play);
	_over->view()->attach(_play);

	Master::instance().sheduler()->schedule(std::bind(&Kit::inspection, this, std::placeholders::_1), this, 5.0f, false, "Play::Cleaner::Kit::inspection");
}

Kit::~Kit()
{
	_dispatcher->removeEventListener(_physicSensor);

	Master::instance().sheduler()->unschedule("Play::Cleaner::Kit::inspection", this);
}

void
Kit::update(float dt)
{
	++_time;
}

void
Kit::attach(std::unique_ptr<Objects::Figure> figure)
{
	_pool.insert(std::pair<
		cocos2d::PhysicsBody *,std::unique_ptr<Objects::Figure>
	>(figure->view()->body(), std::move(figure)));
}

Objects::Figure *
Kit::find(cocos2d::PhysicsBody * body) const
{
	std::unordered_map<
		cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>
	>::const_iterator it = _pool.find(body);
	if (it != _pool.end())
		return (*it).second.get();
	return nullptr;
}

void
Kit::clean()
{
	std::unordered_map<
		cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>
	>::iterator it;
	unsigned int count = cocos2d::RandomHelper::random_int<unsigned int>(1, 3);
	if (count <= _pool.size())
	{
		it = _pool.begin();
		for (unsigned int i = 0; i < count; ++i)
			it = _pool.erase(it);
	}
	else
		_pool.clear();
}

void
Kit::inspection(float delta)
{
	std::unordered_map<
		cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>
	>::const_iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if (
			abs(it->second->view()->body()->getVelocity().y) < 0.01f &&
			it->second->view()->getPosition().y >= Master::instance().get<Components::Metric>().over()[0].y
		)
		{
			Master::instance().get<Components::Statistic>().update(Result(_result, _time, 0));
			Master::instance().scene(Master::SCENE_OVER);
			return;
		}
		++it;
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact) const
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();

	/*
		Figures from lpool or rpool on contact with platform edge.
		Set contact result to true.
	*/
	return contact.getResult() ||
		(_pool.find(first) != _pool.end() && _pool.find(second) != _pool.end()) ||
		(_pool.find(first) != _pool.end() && _platform->view()->body() == second) ||
		(_pool.find(second) != _pool.end() && _platform->view()->body() == first);
}

}

}