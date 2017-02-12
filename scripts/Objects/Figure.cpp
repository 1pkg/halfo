#include "Figure.hpp"
#include "Application/Metric.hpp"

namespace Objects
{

Figure::Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		cocos2d::Color4F color,
		bool hollow
)
	: _pattern(pattern, pattern + size),
	_color(color),
	_hollow(hollow),
	_view(
		new Views::Figure(
			_pattern.data(),
			_pattern.size(),
			_color,
			_hollow
		)
	)
{
}

Views::Figure *
Figure::view() const
{
	return _view.get();
}

float
Figure::area() const
{
	float result = 0.0f;
	for (std::size_t i = 0; i < _pattern.size(); ++i)
	{
		cocos2d::Vec2 first = _pattern[i];
		cocos2d::Vec2 second = _pattern[i == _pattern.size() - 1 ? 0 : i + 1];

		result += first.x * second.y - first.y * second.x;
	}
	return abs(result / 2.0f);
}

bool
Figure::intersect(const std::pair<cocos2d::Vec2, cocos2d::Vec2> & line) const
{
	#ifdef FAST_FIGURE_INTERSECT
	std::vector<cocos2d::Vec2> vector = rotate(_pattern);
	cocos2d::Vec2 
		left = vector[0],
		right = vector[0],
		top = vector[0],
		bottom = vector[0];
	for (cocos2d::Vec2 point : vector)
	{
		if (point.x < left.x)
			left = point;

		if (point.x > right.x)
			right = point;

		if (point.y > top.y)
			top = point;

		if (point.y < bottom.y)
			bottom = point;
	}
	left += view()->getPosition();
	right += view()->getPosition();
	top += view()->getPosition();
	bottom += view()->getPosition();
	cocos2d::Vec2 lposition = cocos2d::Vec2(
		(line.first.x < line.second.x ? line.first.x : line.second.x) - DELTA,
		(line.first.y < line.second.y ? line.first.y : line.second.y) - DELTA
	);
	cocos2d::Size ldimension = cocos2d::Size(
		abs(line.first.x - line.second.x) + DELTA,
		abs(line.first.y - line.second.y) + DELTA
	);
	cocos2d::Vec2 fposition = cocos2d::Vec2(
		left.x,
		bottom.y
	);
	cocos2d::Size fdimension = cocos2d::Size(
		right.x - left.x,
		top.y - bottom.y
	);
	return cocos2d::Rect(lposition, ldimension).intersectsRect(cocos2d::Rect(fposition, fdimension));
	#else
	std::vector<cocos2d::Vec2> vector = rotate(_pattern);
	for (size_t i = 0; i < vector.size(); ++i)
	{
		cocos2d::Vec2 first =
			vector[i] + view()->getPosition();
		cocos2d::Vec2 second =
			vector[i == vector.size() - 1 ? 0 : i + 1] + view()->getPosition();

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
			(first.x < second.x ? first.x : second.x) - DELTA,
			(first.y < second.y ? first.y : second.y) - DELTA
		);
		cocos2d::Size dimension = cocos2d::Size(
			abs(first.x - second.x) + DELTA,
			abs(first.y - second.y) + DELTA
		);
		cocos2d::Vec2 lposition = cocos2d::Vec2(
			(line.first.x < line.second.x ? line.first.x : line.second.x) - DELTA,
			(line.first.y < line.second.y ? line.first.y : line.second.y) - DELTA
		);
		cocos2d::Size ldimension = cocos2d::Size(
			abs(line.first.x - line.second.x) + DELTA,
			abs(line.first.y - line.second.y) + DELTA
		);
		if (
			cocos2d::Rect(position, dimension).containsPoint(cocos2d::Vec2(x, y)) &&
			cocos2d::Rect(lposition, ldimension).containsPoint(cocos2d::Vec2(x, y))
		)
			return true;
	}
	return false;
	#endif
}

std::pair<
	std::unique_ptr<Figure>,
	std::unique_ptr<Figure>
>
Figure::slice(const std::pair<cocos2d::Vec2, cocos2d::Vec2> & line) const
{
	std::vector<cocos2d::Vec2> left, right;
	std::vector<cocos2d::Vec2> vector = rotate(_pattern);
	for (size_t i = 0; i < vector.size(); ++i)
	{
		cocos2d::Vec2 first = vector[i] + view()->getPosition();
		cocos2d::Vec2 second = vector[i == vector.size() - 1 ? 0 : i + 1] + view()->getPosition();

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
			(first.x < second.x ? first.x : second.x) - DELTA,
			(first.y < second.y ? first.y : second.y) - DELTA
		);
		cocos2d::Size dimension = cocos2d::Size(
			abs(first.x - second.x) + DELTA,
			abs(first.y - second.y) + DELTA
		);
		cocos2d::Vec2 lposition = cocos2d::Vec2(
			(line.first.x < line.second.x ? line.first.x : line.second.x) - DELTA,
			(line.first.y < line.second.y ? line.first.y : line.second.y) - DELTA
		);
		cocos2d::Size ldimension = cocos2d::Size(
			abs(line.first.x - line.second.x) + DELTA,
			abs(line.first.y - line.second.y) + DELTA
		);
		if (
			cocos2d::Rect(position, dimension).containsPoint(cocos2d::Vec2(x, y)) &&
			cocos2d::Rect(lposition, ldimension).containsPoint(cocos2d::Vec2(x, y))
		)
		{
			left.push_back(cocos2d::Vec2(x, y) - view()->getPosition());
			right.push_back(cocos2d::Vec2(x, y) - view()->getPosition());
		}
	}
	return std::pair<
		std::unique_ptr<Figure>,
		std::unique_ptr<Figure>
	>(
		std::move(
			std::unique_ptr<Figure>(
				new Figure(left.data(), left.size(), _color, false)
			)
		),
		std::move(
			std::unique_ptr<Figure>(
				new Figure(right.data(), right.size(), _color, false)
			)
		)
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

std::vector<cocos2d::Vec2>
Figure::rotate(const std::vector<cocos2d::Vec2> & vector) const
{
	std::vector<cocos2d::Vec2> result(vector.size());
	float rotation = CC_DEGREES_TO_RADIANS(view()->getRotation());
	for (std::size_t i = 0; i < vector.size(); ++i)
	{
		cocos2d::Vec2 point = vector[i];
		result[i] =
			cocos2d::Vec2(
			 cos(rotation) * (point.x) + sin(rotation) * (point.y),
			-sin(rotation) * (point.x) + cos(rotation) * (point.y)
		);
	}
	return result;
}

}