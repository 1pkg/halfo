#include "Metric.hpp"

namespace Components
{

Metric::Metric(cocos2d::Size size, cocos2d::Vec2 origin)
	: _size(size),
	_origin(origin)
{
}

void
Metric::initialize()
{
	_scale = (_size.width / COMMON_SIZE.width + _size.height / COMMON_SIZE.height) / 2.0f;
	_lspawn = cocos2d::Vec2(-_size.width / 6.0f, _size.height / 6.0f * 5.0f) + _origin,
	_rspawn = cocos2d::Vec2(_size.width + _size.width / 6.0f, _size.height / 6.0f * 5.0f) + _origin,
	_spawn = cocos2d::Size(_size.width / 6.0f, _size.height / 6.0f);
	_hammer = cocos2d::Rect(cocos2d::Vec2(_size.width / 2.0f, _size.height / 6.0f * 7.0f) + _origin, cocos2d::Size(_size.width / 12.0f, _size.height / 3.0f));

	_score = cocos2d::Vec2(_size.width / 10.0f * 8.0f, _size.height / 10.0f * 8.0f) + _origin;

	_slice = {{
		cocos2d::Vec2(_size.width / 2.0f, _size.height / 3.0f * 2.0f) + _origin,
		cocos2d::Vec2(_size.width / 2.0f, _size.height) + _origin
	}},
	_anvil = {{
		cocos2d::Vec2(_size.width / 2.0f, -_size.height * 3.0f) + _origin,
		cocos2d::Vec2(_size.width / 2.0f, _size.height / 3.0f * 2.0f) + _origin
	}},
	_edge = {{
		_origin - cocos2d::Vec2(0.0f, _size.height * 3.0f),
		cocos2d::Vec2(0.0f, _size.height) + _origin,
		cocos2d::Vec2(_size.width,_size.height) + _origin,
		cocos2d::Vec2(_size.width, 0.0f) - cocos2d::Vec2(0.0f, _size.height * 3.0f) + _origin
	}},
	_platform = {{
		_origin,
		cocos2d::Vec2(_size.width, 0.0f) + _origin
	}},
	_over = {{
		cocos2d::Vec2(0.0f, _size.height / 3.0f * 2.0f) + _origin,
		cocos2d::Vec2(_size.width, _size.height / 3.0f * 2.0f) + _origin
	}};
}

float
Metric::absolute(float reliative) const
{
	return reliative * _scale;
}

float
Metric::absolute2(float reliative) const
{
	return absolute(absolute(reliative));
}

float
Metric::absolute3(float reliative) const
{
	return absolute(absolute(absolute(reliative)));
}

cocos2d::Vec2
Metric::absolute(cocos2d::Vec2 reliative) const
{
	return cocos2d::Vec2(absolute(reliative.x), absolute(reliative.y));
}

cocos2d::Size
Metric::absolute(cocos2d::Size reliative) const
{
	return cocos2d::Size(absolute(reliative.width), absolute(reliative.height));
}

float
Metric::reliative(float absolute) const
{
	return absolute / _scale;
}

float
Metric::reliative2(float absolute) const
{
	return reliative(reliative(absolute));
}

float
Metric::reliative3(float absolute) const
{
	return reliative(reliative(reliative(absolute)));
}

cocos2d::Vec2
Metric::reliative(cocos2d::Vec2 absolute) const
{
	return cocos2d::Vec2(reliative(absolute.x),reliative(absolute.y));
}

cocos2d::Size
Metric::reliative(cocos2d::Size absolute) const
{
	return cocos2d::Size(reliative(absolute.width), reliative(absolute.height));
}

cocos2d::Vec2
Metric::origin() const
{
	return _origin;
}

cocos2d::Size
Metric::size() const
{
	return _size;
}

cocos2d::Vec2
Metric::center() const
{
	return _size / 2.0f;
}

cocos2d::Vec2
Metric::spawn(bool side) const
{
	return side ? _rspawn : _lspawn;
}

cocos2d::Size
Metric::spawn() const
{
	return _spawn;
}

cocos2d::Vec2
Metric::score() const
{
	return _score;
}

cocos2d::Rect
Metric::hammer() const
{
	return _hammer;
}

float
Metric::anvilLength() const
{
	return _size.height / 3.0f * 2.0f;
}

const std::array<cocos2d::Vec2, 2> &
Metric::slice() const
{
	return _slice;
}

const std::array<cocos2d::Vec2, 2> &
Metric::anvil() const
{
	return _anvil;
}

const std::array<cocos2d::Vec2, 4> &
Metric::edge() const
{
	return _edge;
}

const std::array<cocos2d::Vec2, 2> &
Metric::platform() const
{
	return _platform;
}

const std::array<cocos2d::Vec2, 2> &
Metric::over() const
{
	return _over;
}

}