#include "components.hpp"
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
	_view->run(cocos2d::MoveBy::create(PLATFORM_STEP_TIME, Master::instance().get<Components::Metric>().step()));
}

void
Platform::downward()
{
	_view->run(cocos2d::MoveBy::create(PLATFORM_STEP_TIME, -Master::instance().get<Components::Metric>().step()));
}

}