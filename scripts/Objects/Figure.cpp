#include "Figure.hpp"
#include "Views\Figure.hpp"

namespace Objects
{

Figure::Figure(
		std::vector<cocos2d::Vec2> pattern,
		cocos2d::Color4F color,
		cocos2d::PhysicsMaterial material,
		bool hollow
)
	: _pattern(pattern), _color(color), _material(material), _hollow(hollow)
{
}

Application::View *
Figure::render()
{
	using namespace Views;
	if (!_view)
		_view.reset(
			new Views::Figure(_pattern, _color, _material, _hollow)
		);

	return _view.get();
}

Views::Figure *
Figure::view() const
{
	return _view.get();
}

bool
Figure::intersect(std::pair<cocos2d::Vec2, cocos2d::Vec2> line) const
{
	cocos2d::Vec2 left = _pattern[0], right = _pattern[0];
	for (cocos2d::Vec2 point : _pattern)
	{
		if (point.x < left.x)
			left = point;

		if (point.x > right.x)
			right = point;
	}

	return
		(left + view()->getPosition()).x <= line.first.x &&
		(right + view()->getPosition()).x >= line.first.x;

}

std::pair<
	std::unique_ptr<Figure>,
	std::unique_ptr<Figure>
>
Figure::divide(std::pair<cocos2d::Vec2, cocos2d::Vec2> line) const
{
	std::vector<cocos2d::Vec2> left, right;
	for (size_t i = 0; i < _pattern.size(); ++i)
	{
		cocos2d::Vec2 first = _pattern[i] + view()->getPosition();
		cocos2d::Vec2 second = _pattern[i == _pattern.size() - 1 ? 0 : i + 1] + view()->getPosition();

		if (first.x < line.first.x)
			left.push_back(first - view()->getPosition());
		else
			right.push_back(first - view()->getPosition());

		float determinant = 
			(first.x - second.x) * (line.first.y - line.second.y) -
			(first.y - second.y) * (line.first.x - line.second.x);
		if (determinant == 0)
			continue;

		float x =
			((first.x * second.y - first.y * second.x) * (line.first.x - line.second.x) -
			(first.x - second.x) * (line.first.x * line.second.y - line.first.y * line.second.x))
			/ determinant;

		float y =
			((first.x * second.y - first.y * second.x) * (line.first.y - line.second.y) -
			(first.y - second.y) * (line.first.x * line.second.y - line.first.y * line.second.x))
			/ determinant;

		cocos2d::Vec2 position = cocos2d::Vec2(
			first.x < second.x ? first.x : second.x,
			first.y < second.y ? first.y : second.y
		);
		cocos2d::Size dimension = cocos2d::Size(
			abs(first.x - second.x),
			abs(first.y - second.y)
		);
		cocos2d::Rect rect(position, dimension);
		if (rect.containsPoint(cocos2d::Vec2(x, y)))
		{
			left.push_back(cocos2d::Vec2(x, y) - view()->getPosition());
			right.push_back(cocos2d::Vec2(x, y) - view()->getPosition());
		}
	}

	return std::pair<
		std::unique_ptr<Figure>,
		std::unique_ptr<Figure>
	>(
		std::move(std::unique_ptr<Figure>(new Figure(left, _color, _material, false))),
		std::move(std::unique_ptr<Figure>(new Figure(right, _color, _material, false)))
	);
}

void
Figure::fill()
{
	if (!_hollow)
		return;

	_hollow = false;
	view()->setHollow(_hollow);
}

}