#include "Kit.hpp"
#include "Scenes/Act.hpp"
#include "Objects/Figure.hpp"
#include "Objects/Platform.hpp"
#include "Objects/Over.hpp"

namespace Cleaner
{

Kit::Kit(Scenes::Act * act)
	: _combo(0), _result(0),
	_score(cocos2d::Label::createWithTTF(std::to_string(_result), FONT_NAME, FONT_SIZE)),
	_platform(new Objects::Platform()),
	_over(new Objects::Over()),
	_sensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{

	/*
		Initialize score label.
	*/
	_score->setPosition(Application::Main::instance().metric().score());
	_act->addChild(_score);


	_sensor->onContactBegin = std::bind(&Kit::contact, this, std::placeholders::_1);
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_sensor, _act);

	_platform->view()->attach(_act);
	_over->view()->attach(_act);

	Application::Main::instance().sheduler()->schedule(
		std::bind(&Kit::inspection, this, std::placeholders::_1),
		this,
		INSPECTION_TIME,
		false,
		"Cleaner::Kit::inspection"
	);
}

Kit::~Kit()
{
	_score->removeFromParentAndCleanup(true);
	_act->getEventDispatcher()->removeEventListener(_sensor);

	Application::Main::instance().sheduler()->unschedule(
		"Cleaner::Kit::inspection",
		this
	);
}

void
Kit::update(float dt)
{
	return;
}

void
Kit::attach(std::unique_ptr<Objects::Figure> figure)
{
	if (figure->view()->getPosition().x < Application::Main::instance().metric().center().x)
		_lpool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				figure->view()->body(),
				std::move(figure)
			)
		);
	else
		_rpool.insert(
			std::pair<
				cocos2d::PhysicsBody *,
				std::unique_ptr<Objects::Figure>
			>(
				figure->view()->body(),
				std::move(figure)
			)
		);

	_result += scale();
	_score->setString(std::to_string(_result));
}

Objects::Figure *
Kit::find(cocos2d::PhysicsBody * body) const
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::const_iterator it = _lpool.find(body);
	if (it != _lpool.end())
		return (*it).second.get();

	it = _rpool.begin();
	if (it != _rpool.end())
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

	_platform->downward();
	_act->transpoter()->increase();
}

void
Kit::reset()
{
	_combo = _combo < COMBO_PROOF ? 0 : _combo - COMBO_PROOF;
	_platform->upward();
	_act->transpoter()->reset();
}

unsigned int
Kit::scale() const
{
	return 1 + static_cast<unsigned int>(std::floor(_combo / SCALE_KOEFICIENT));
}

void
Kit::clean()
{
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::iterator it;

	unsigned int lpoolCount =
		cocos2d::RandomHelper::random_int<
			unsigned int
		>(
			FIGURE_BURN_LIMIT.first,
			FIGURE_BURN_LIMIT.second
		);
	if (lpoolCount <= _lpool.size())
	{
		it = _lpool.begin();
		for (unsigned int i = 0; i < lpoolCount; ++i)
			it = _lpool.erase(it);
	}
	else
		_lpool.clear();

	unsigned int rpoolCount =
		cocos2d::RandomHelper::random_int<
			unsigned int
		>(
			FIGURE_BURN_LIMIT.first,
			FIGURE_BURN_LIMIT.second
		);
	if (rpoolCount <= _rpool.size())
	{
		it = _rpool.begin();
		for (unsigned int i = 0; i < rpoolCount; ++i)
			it = _rpool.erase(it);
	}
	else
		_rpool.clear();
}

void
Kit::inspection(float delta)
{
	float overLimit = 
		Application::Main::instance().metric().origin().y + Application::Main::instance().metric().anvilLength();
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	>::const_iterator it = _lpool.begin();
	while (it != _lpool.end())
	{

		if (
			abs(it->second->view()->body()->getVelocity().y) < DELTA &&
			it->second->intersect(Application::Main::instance().metric().over())
		)
		{
			Components::Result result(_result, 0, _result);
			Application::Main::instance().storage().update(result);
			Application::Main::instance().over();
			return;
		}
		++it;
	}

	it = _rpool.begin();;
	while (it != _rpool.end())
	{
		if (
			abs(it->second->view()->body()->getVelocity().y) < DELTA &&
			it->second->intersect(Application::Main::instance().metric().over())
		)
		{
			Components::Result result(_result, 0, _result);
			Application::Main::instance().storage().update(result);
			Application::Main::instance().over();
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
		_lpool.find(first) != _lpool.end() && _lpool.find(second) != _lpool.end() ||
		_rpool.find(first) != _rpool.end() && _rpool.find(second) != _rpool.end() ||
		_lpool.find(first) != _lpool.end() && _platform->view()->body() == second ||
		_lpool.find(second) != _lpool.end() && _platform->view()->body() == first ||
		_rpool.find(first) != _rpool.end() && _platform->view()->body() == second ||
		_rpool.find(second) != _rpool.end() && _platform->view()->body() == first;
}

}