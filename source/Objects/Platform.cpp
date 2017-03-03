#include "Platform.hpp"

namespace Objects
{

Platform::Platform()
	: _view(new Views::Platform())
{
}

Views::Platform *
Platform::view() const
{
	return _view.get();
}

void
Platform::upward()
{
	_view->run(
		cocos2d::MoveBy::create(
			EDGE_STEP_TIME,
			cocos2d::Vec2(0.0f, Master::instance().metric().absolute(EDGE_STEP))
		)
	);
}

void
Platform::downward()
{
	_view->run(
		cocos2d::MoveBy::create(
			EDGE_STEP_TIME,
			cocos2d::Vec2(0.0f, -Master::instance().metric().absolute(EDGE_STEP))
		)
	);
}

}