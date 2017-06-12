#include "components.hpp"
#include "Kit.hpp"
#include "Scenes/Play.hpp"
#include "Objects/Figure.hpp"
#include "Objects/Blade.hpp"
#include "Objects/Anvil.hpp"

namespace Play
{

namespace Slicer
{

Kit::Kit(Scenes::Play * play)
	: _blade(new Objects::Blade()), 
	_anvil(new Objects::Anvil()),
	_touchSensor(cocos2d::EventListenerTouchOneByOne::create()),
	_physicSensor(cocos2d::EventListenerPhysicsContact::create()),
	_dispatcher(((cocos2d::Scene *)(*play))->getEventDispatcher()),
	_play(play)
{
	_touchSensor->onTouchBegan =
	[this](cocos2d::Touch * touch, cocos2d::Event * event) -> bool
	{
		_play->transpoter()->walk(std::bind(&Kit::slice, this, std::placeholders::_1));
		_blade->run("down");
		return true;
	};
	_touchSensor->onTouchEnded =
	[this](cocos2d::Touch * touch, cocos2d::Event * event)
	{
		_blade->run("up");
	};
	_dispatcher->addEventListenerWithSceneGraphPriority(_touchSensor, *_play);

	_physicSensor->onContactBegin = std::bind(&Kit::contact, this, std::placeholders::_1);
	_dispatcher->addEventListenerWithSceneGraphPriority(_physicSensor, *_play);

	_blade->view()->attach(_play);
	_anvil->view()->attach(_play);
}

Kit::~Kit()
{
	_dispatcher->removeEventListener(_touchSensor);
	_dispatcher->removeEventListener(_physicSensor);
}

bool
Kit::slice(const Application::Object * object) const
{
	const Objects::Figure * figure = dynamic_cast<const Objects::Figure *>(object);
	auto slice = Master::instance().get<Components::Metric>().slice();
	std::vector<std::unique_ptr<Objects::Figure>> list =
		Master::instance().get<Components::Splitter>().split(figure, cocos2d::Line(slice[0], slice[1]));
	if (list.size() <= 1)
		return true;

	for (std::unique_ptr<Objects::Figure> & figure : list)
	{
		figure->view()->attach(_play);
		_play->cleaner()->attach(std::move(figure));
		figure.release();
	}
	list.clear();
	_play->transpoter()->release(figure);
	return false; // todo
}

bool
Kit::contact(cocos2d::PhysicsContact & contact) const
{
	cocos2d::PhysicsBody
		* first = contact.getShapeA()->getBody(),
		* second = contact.getShapeB()->getBody();
	Objects::Figure * figure;

	/*
		Fill figures from permanent pool of Transporter::Kit and move to Cleaner::Kit on contact with anvel or blade.
		Set contact result to true.
	*/
	if ((figure = _play->transpoter()->find(first)) && (second == _blade->view()->body() || second == _anvil->view()->body()))
	{
		figure->fill();
		_play->cleaner()->attach(std::move(
			_play->transpoter()->release(figure)
		));
		return true;
	}
	if ((figure = _play->transpoter()->find(second)) && (first == _blade->view()->body() || first == _anvil->view()->body()))
	{
		figure->fill();
		_play->cleaner()->attach(std::move(
			_play->transpoter()->release(figure)
		));
		return true;
	}

	/*
		Figures from Cleaner::Kit pool on contact with anvel or blade.
		Set contact result to true.
	*/
	if (_play->cleaner()->find(first) && (second == _blade->view()->body() || second == _anvil->view()->body()))
		return true;

	if (_play->cleaner()->find(second) && (first == _blade->view()->body() || first == _anvil->view()->body()))
		return true;

	return contact.getResult();
}

}

}