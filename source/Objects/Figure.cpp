#include "Figure.hpp"

#define SLICE_DELTA 0.001f

namespace Objects
{

Figure::Figure(const cocos2d::Vec2 * pattern, std::size_t size, float angle, bool hollow)
	: _pattern(pattern, pattern + size),
	_hollow(hollow),
	_view(new Views::Object::Figure(_pattern.data(), _pattern.size(), angle, _hollow))
{
}

Views::Object::Figure *
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
Figure::intersect(const std::array<cocos2d::Vec2, 2> & line) const
{
	std::vector<cocos2d::Vec2> vector = rotate(_pattern);
	for (size_t i = 0; i < vector.size(); ++i)
	{
		/*
			Iterate throught polygon edge segments.
			Where first and second two point of this edge segments.
		*/
		cocos2d::Vec2 first = vector[i] + view()->getPosition();
		cocos2d::Vec2 second = vector[i == vector.size() - 1 ? 0 : i + 1] + view()->getPosition();

		/*
			Line–line intersection.
			Where L1(P1(x1, y1), P2(x2, y2)), L2(P3(x3, y3), P4(x4, y4)).
			Px = ((x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4)).
			Py = ((x1y2 - y1x2)(y3 - y4) - (y1 - y2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4)).
			If divider = 0, point doesnt exists.
		*/
		float determinant = (first.x - second.x) * (line[0].y - line[1].y) - (first.y - second.y) * (line[0].x - line[1].x);
		if (determinant == 0)
			continue;

		float x = ((first.x * second.y - first.y * second.x) * (line[0].x - line[1].x) - (first.x - second.x) * (line[0].x * line[1].y - line[0].y * line[1].x)) / determinant;
		float y = ((first.x * second.y - first.y * second.x) * (line[0].y - line[1].y) - (first.y - second.y) * (line[0].x * line[1].y - line[0].y * line[1].x)) / determinant;

		/*
			Rectangle for edge segment.
		*/
		cocos2d::Vec2 position = cocos2d::Vec2((first.x < second.x ? first.x : second.x) - SLICE_DELTA,(first.y < second.y ? first.y : second.y) - SLICE_DELTA);
		cocos2d::Size dimension = cocos2d::Size(abs(first.x - second.x) + SLICE_DELTA, abs(first.y - second.y) + SLICE_DELTA);

		/*
			Rectangle for intersect line.
		*/
		cocos2d::Vec2 lposition = cocos2d::Vec2((line[0].x < line[1].x ? line[0].x : line[1].x) - SLICE_DELTA, (line[0].y < line[1].y ? line[0].y : line[1].y) - SLICE_DELTA);
		cocos2d::Size ldimension = cocos2d::Size(abs(line[0].x - line[1].x) + SLICE_DELTA, abs(line[0].y - line[1].y) + SLICE_DELTA);
		if (cocos2d::Rect(position, dimension).containsPoint(cocos2d::Vec2(x, y))) // && cocos2d::Rect(lposition, ldimension).containsPoint(cocos2d::Vec2(x, y))
			return true;
	}
	return false;
}

std::pair<std::unique_ptr<Figure>, std::unique_ptr<Figure>>
Figure::slice(const std::array<cocos2d::Vec2, 2> & line) const
{
	/*
		Vector left represent pattern for left side figure, vector right - right side figure.
	*/
	std::vector<cocos2d::Vec2> left, right;
	std::vector<cocos2d::Vec2> vector = rotate(_pattern);
	for (size_t i = 0; i < vector.size(); ++i)
	{
		/*
			Iterate throught polygon edge segments.
			Where first and second two point of this edge segments.
		*/
		cocos2d::Vec2 first = vector[i] + view()->getPosition();
		cocos2d::Vec2 second = vector[i == vector.size() - 1 ? 0 : i + 1] + view()->getPosition();

		if (first.x < line[0].x)
			left.push_back(first - view()->getPosition());
		else
			right.push_back(first - view()->getPosition());

		/*
			Line–line intersection.
			Where L1(P1(x1, y1), P2(x2, y2)), L2(P3(x3, y3), P4(x4, y4)).
			Px = ((x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4)).
			Py = ((x1y2 - y1x2)(y3 - y4) - (y1 - y2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4)).
			If divider = 0, point doesnt exists.
		*/
		float divider = (first.x - second.x) * (line[0].y - line[1].y) - (first.y - second.y) * (line[0].x - line[1].x);
		if (divider == 0)
			continue;

		float x = ((first.x * second.y - first.y * second.x) * (line[0].x - line[1].x) - (first.x - second.x) * (line[0].x * line[1].y - line[0].y * line[1].x)) / divider;
		float y = ((first.x * second.y - first.y * second.x) * (line[0].y - line[1].y) - (first.y - second.y) * (line[0].x * line[1].y - line[0].y * line[1].x)) / divider;

		/*
			Rectangle for edge segment.
		*/
		cocos2d::Vec2 position = cocos2d::Vec2((first.x < second.x ? first.x : second.x) - SLICE_DELTA, (first.y < second.y ? first.y : second.y) - SLICE_DELTA);
		cocos2d::Size dimension = cocos2d::Size(abs(first.x - second.x) + SLICE_DELTA, abs(first.y - second.y) + SLICE_DELTA);

		/*
			Rectangle for intersect line.
		*/
		cocos2d::Vec2 lposition = cocos2d::Vec2((line[0].x < line[1].x ? line[0].x : line[1].x) - SLICE_DELTA, (line[0].y < line[1].y ? line[0].y : line[1].y) - SLICE_DELTA);
		cocos2d::Size ldimension = cocos2d::Size(abs(line[0].x - line[1].x) + SLICE_DELTA, abs(line[0].y - line[1].y) + SLICE_DELTA);

		if (cocos2d::Rect(position, dimension).containsPoint(cocos2d::Vec2(x, y)))	// && cocos2d::Rect(lposition, ldimension).containsPoint(cocos2d::Vec2(x, y))
		{
			left.push_back(cocos2d::Vec2(x, y) - view()->getPosition());
			right.push_back(cocos2d::Vec2(x, y) - view()->getPosition());
		}
	}
	return std::pair<std::unique_ptr<Figure>,std::unique_ptr<Figure>>(
		std::move(std::unique_ptr<Figure>(new Figure(left.data(), left.size(), view()->getRotation(), false))),
		std::move(std::unique_ptr<Figure>(new Figure(right.data(), right.size(), view()->getRotation(), false))
	));
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

std::vector<cocos2d::Vec2>
Figure::rotate(const std::vector<cocos2d::Vec2> & vector) const
{
	std::vector<cocos2d::Vec2> result(vector.size());
	float rotation = CC_DEGREES_TO_RADIANS(view()->getRotation());
	for (std::size_t i = 0; i < vector.size(); ++i)
		result[i] = cocos2d::Vec2(cos(rotation) * (vector[i].x) + sin(rotation) * (vector[i].y), -sin(rotation) * (vector[i].x) + cos(rotation) * (vector[i].y));
	return result;
}

}