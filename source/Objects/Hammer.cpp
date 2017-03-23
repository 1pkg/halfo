#include "components.hpp"
#include "Hammer.hpp"

namespace Objects
{

Hammer::Hammer()
	: _view(new Views::Object::Hammer())
{
}

Views::Object::Hammer *
Hammer::view() const
{
	return _view.get();
}

void
Hammer::run(const std::string & action)
{
	if (action == "up")
		return _view->run(cocos2d::MoveBy::create(HAMMER_STROKE_TIME, cocos2d::Vec2(0.0f, Master::instance().get<Components::Metric>().hammer().size.height)));

	if (action == "down")
	{
		const std::string & resource = Master::instance().get<Components::Setting>().get(Components::Setting::PARAMETER_HAMMER_RESOURCE);
		Master::instance().get<Components::Audio>().play(resource);
		return _view->run(cocos2d::MoveBy::create(HAMMER_STROKE_TIME, cocos2d::Vec2(0.0f, -Master::instance().get<Components::Metric>().hammer().size.height)));
	}

	Application::Object::run(action);
}

}