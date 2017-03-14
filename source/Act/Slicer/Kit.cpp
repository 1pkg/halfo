#include "Kit.hpp"
#include "Scenes/Act.hpp"
#include "Objects/Figure.hpp"
#include "Objects/Hammer.hpp"
#include "Objects/Anvil.hpp"

namespace Act
{

namespace Slicer
{

Kit::Kit(Scenes::Act * act)
	: _hammer(new Objects::Hammer()), 
	_anvil(new Objects::Anvil()),
	_touchSensor(cocos2d::EventListenerTouchOneByOne::create()),
	_physicSensor(cocos2d::EventListenerPhysicsContact::create()),
	_act(act)
{
	_touchSensor->onTouchBegan =
		[this](cocos2d::Touch * touch, cocos2d::Event * event) -> bool
		{
			slice();
			_hammer->downward();
			return true;
		};
	_touchSensor->onTouchEnded =
		[this](cocos2d::Touch * touch, cocos2d::Event * event)
		{
			_hammer->upward();
		};
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchSensor, _act);

	_physicSensor->onContactBegin = std::bind(&Kit::contact, this, std::placeholders::_1);
	_act->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_physicSensor, _act);

	_hammer->view()->attach(_act);
	_anvil->view()->attach(_act);
}

Kit::~Kit()
{
	_act->getEventDispatcher()->removeEventListener(_touchSensor);
	_act->getEventDispatcher()->removeEventListener(_physicSensor);
}

void
Kit::update(float dt)
{
	return;
}

void
Kit::slice() const
{
	std::vector<Objects::Figure *> figures = _act->transpoter()->find(Master::instance().get<Components::Metric>().slice());
	for (Objects::Figure * figure : figures)
	{
		std::pair<std::unique_ptr<Objects::Figure>, std::unique_ptr<Objects::Figure>> slice = figure->slice(Master::instance().get<Components::Metric>().slice());
		float
			  firstArea = slice.first->area(), secondArea = slice.second->area(),
			  deltaArea = Master::instance().get<Components::Metric>().absolute(Master::instance().get<Components::Metric>().absolute(DELTA_AREA)),
			  limitArea = Master::instance().get<Components::Metric>().absolute(Master::instance().get<Components::Metric>().absolute(LIMIT_AREA));
		if (firstArea < limitArea || secondArea < limitArea)
			continue;

		if (abs(firstArea - secondArea) < deltaArea)
			_act->cleaner()->increase();
		else
			_act->cleaner()->reset();

		cocos2d::Vec2 firstImpuls = cocos2d::Vec2(Master::instance().get<Components::Metric>().reliative(-X_IMPULS), Master::instance().get<Components::Metric>().reliative(-Y_IMPULS));
		slice.first->view()->attach(_act);
		slice.first->view()->setPosition(figure->view()->getPosition());
		slice.first->view()->body()->applyImpulse(firstImpuls);
		_act->cleaner()->attach(std::move(slice.first));
		slice.first.release();

		cocos2d::Vec2 secondImpuls = cocos2d::Vec2(Master::instance().get<Components::Metric>().reliative(X_IMPULS), Master::instance().get<Components::Metric>().reliative(-Y_IMPULS));
		slice.second->view()->attach(_act);
		slice.second->view()->setPosition(figure->view()->getPosition());
		slice.second->view()->body()->applyImpulse(secondImpuls);
		_act->cleaner()->attach(std::move(slice.second));
		slice.second.release();

		_act->transpoter()->release(figure);
	}
}

bool
Kit::contact(cocos2d::PhysicsContact & contact) const
{
	cocos2d::PhysicsBody * first = contact.getShapeA()->getBody(), * second = contact.getShapeB()->getBody();
	Objects::Figure * figure;
	/*
		Fill figures from permanent pool of Transporter::Kit and move to Cleaner::Kit on contact with anvel or hammer.
		Set contact result to true.
	*/
	if ((figure = _act->transpoter()->find(first)) && (second == _hammer->view()->body() || second == _anvil->view()->body()))
	{
		_act->cleaner()->reset();
		figure->fill();
		_act->cleaner()->attach(
			std::move(
				_act->transpoter()->release(figure)
			)
		);
		return true;
	}

	if ((figure = _act->transpoter()->find(second)) && (first == _hammer->view()->body() || first == _anvil->view()->body()))
	{
		_act->cleaner()->reset();
		figure->fill();
		_act->cleaner()->attach(
			std::move(
				_act->transpoter()->release(figure)
			)
		);
		return true;
	}

	/*
		Figures from Cleaner::Kit pool on contact with anvel or hammer.
		Set contact result to true.
	*/
	if (_act->cleaner()->find(first) && (second == _hammer->view()->body() || second == _anvil->view()->body()))
		return true;

	if (_act->cleaner()->find(second) && (first == _hammer->view()->body() || first == _anvil->view()->body()))
		return true;

	return contact.getResult();
}

}

}