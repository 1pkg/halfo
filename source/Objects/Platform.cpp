#include "components.hpp"
#include "Platform.hpp"

namespace Objects
{

Platform::Platform()
	: _view(new Views::Object::Platform())
{
}

Views::Object::Platform *
Platform::view() const
{
	return _view.get();
}

void
Platform::run(const std::string & action)
{
	if (action == "up")
		return _view->run(cocos2d::MoveBy::create(PLATFORM_STEP_TIME, Master::instance().get<Components::Metric>().step()));

	if (action == "down")
		return _view->run(cocos2d::MoveBy::create(PLATFORM_STEP_TIME, -Master::instance().get<Components::Metric>().step()));

	Application::Object::run(action);
}

}