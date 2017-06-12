#include "Figure.hpp"

#define SLICE_DELTA 0.001f

namespace Objects
{

Figure::Figure(const cocos2d::Polygon & pattern, float angle, bool hollow)
	: _pattern(pattern),
	_hollow(hollow),
	_view(new Views::Object::Figure(pattern, angle, _hollow))
{
}

const std::vector<cocos2d::Vec2> &
Figure::pattern() const
{
	return _pattern;
}

Views::Object::Figure *
Figure::view() const
{
	return _view.get();
}

void
Figure::fill()
{
	if (!_hollow)
		return;

	_hollow = false;
	view()->body()->setGravityEnable(!_hollow);
	view()->body()->setVelocity(cocos2d::Vec2::ZERO);
}

}