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
	_view->run(cocos2d::MoveBy::create(STROKE_TIME, cocos2d::Vec2(0.0f, Master::instance().get<Components::Metric>("metric").hammer().size.height)));
}

void
Hammer::downward()
{
	_view->run(cocos2d::MoveBy::create(STROKE_TIME, cocos2d::Vec2(0.0f, -Master::instance().get<Components::Metric>("metric").hammer().size.height)));
}

}