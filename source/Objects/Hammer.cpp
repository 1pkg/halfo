#include "Hammer.hpp"

namespace Objects
{

Hammer::Hammer()
	: _view(new Views::Hammer())
{
}

Views::Hammer *
Hammer::view() const
{
	return _view.get();
}

void
Hammer::upward()
{
	_view->run(cocos2d::MoveBy::create(STROKE_TIME, cocos2d::Vec2(0.0f, Master::instance().get<Components::Metric>().hammer().size.height)));
}

void
Hammer::downward()
{
	const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_HAMMER_RESOURCE);
	Master::instance().get<Components::Audio>().play(resource);
	_view->run(cocos2d::MoveBy::create(STROKE_TIME, cocos2d::Vec2(0.0f, -Master::instance().get<Components::Metric>().hammer().size.height)));
}

}