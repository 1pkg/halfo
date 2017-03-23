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
	_score(new Views::Ui::Label(MEDIUM_FONT_SIZE)),
	_platform(new Objects::Platform()),
	_over(new Objects::Over()),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_play(play)
{
	_score->setPosition(Master::instance().get<Components::Metric>().center() * 1.0f / 4.0f);
	_score->setText("0");
	_score->attach(_play);

	_sensor->onContactBegin = std::bind(&Kit::contact, this, std::placeholders::_1);
	_play->eventDispatcher()->addEventListenerWithFixedPriority(_sensor, 1);

	_platform->view()->attach(_play);
	_over->view()->attach(_play);

	Master::instance().sheduler()->schedule(std::bind(&Kit::inspection, this, std::placeholders::_1), this, INSPECTION_TIME, false, "Play::Cleaner::Kit::inspection");
}

Kit::~Kit()
{
	_play->eventDispatcher()->removeEventListener(_sensor);

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
	_pool.insert(std::pair<cocos2d::PhysicsBody *,std::unique_ptr<Objects::Figure>>(figure->view()->body(), std::move(figure)));
	_result += scale();
	_score->setText(to_string(_result));
}

Objects::Figure *
Kit::find(cocos2d::PhysicsBody * body) const
{
	std::unordered_map<cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>>::const_iterator it = _pool.find(body);
	if (it != _pool.end())
		return (*it).second.get();
	return nullptr;
}

void
Kit::increase()
{
	if (_combo >= COMBO_LIMIT)
		return;

	++_combo;
	if (_combo >= COMBO_PROOF)
		clean();

	_platform->run("down");
}

void
Kit::reset()
{
	_combo = _combo < COMBO_PROOF ? 0 : _combo - COMBO_PROOF;
	_platform->run("up");
}

unsigned int
Kit::scale() const
{
	return 1 + static_cast<unsigned int>(std::floor(_combo / SCALE_KOEFICIENT));
}

void
Kit::clean()
{
	std::unordered_map<cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>>::iterator it;
	unsigned int count = cocos2d::RandomHelper::random_int<unsigned int>(FIGURE_CLEAN_LIMIT.first, FIGURE_CLEAN_LIMIT.second);
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
	std::unordered_map<cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>>::const_iterator it = _pool.begin();
	while (it != _pool.end())
	{
		if (
			abs(it->second->view()->body()->getVelocity().y) < REST_SPEAD_DELTA &&
			it->second->intersect(Master::instance().get<Components::Metric>().over())
		)
		{
			Master::instance().get<Components::Statistic>().update(Result(_result, _time, 0));
			Master::instance().scene("Over");
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
		_pool.find(first) != _pool.end() && _pool.find(second) != _pool.end() ||
		_pool.find(first) != _pool.end() && _platform->view()->body() == second ||
		_pool.find(second) != _pool.end() && _platform->view()->body() == first;
}

}

}