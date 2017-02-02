#include "Metric.hpp"

namespace Application
{

Metric::Metric()
	: _size(cocos2d::Director::getInstance()->getVisibleSize()),
	_origin(cocos2d::Director::getInstance()->getVisibleOrigin()),
	_scale((_size.width / COMMON_SIZE.width + _size.height / COMMON_SIZE.height) / 2.0f),
	_anvil(
		cocos2d::Vec2(_size.width / 2.0f, 0.0f),
		cocos2d::Vec2(_size.width / 2.0f, _size.height / 3.0f * 2.0f)
	),
	_hammer(
		cocos2d::Vec2(_size.width / 2.0f, _size.height / 3.0f * 2.0f),
		cocos2d::Vec2(_size.width / 2.0f, _size.height)
	),
	_lspawn(_size.width / 6.0f, _size.height / 6.0f * 5.0f),
	_rspawn(_size.width - _size.width / 6.0f, _size.height / 6.0f * 5.0f),
	_spawn(_size.width / 9.0f, _size.height / 4.5f)

{
}

Metric &
Metric::instance()
{
	static Metric metric;
	return metric;
}

float
Metric::absolute(float reliative) const
{
	return reliative * _scale;
}

cocos2d::Vec2
Metric::absolute(cocos2d::Vec2 reliative) const
{
	return cocos2d::Vec2(
		absolute(reliative.x),
		absolute(reliative.y)
	);
}

cocos2d::Size
Metric::absolute(cocos2d::Size reliative) const
{
	return cocos2d::Size(
		absolute(reliative.width),
		absolute(reliative.height)
	);
}

float
Metric::reliative(float absolute) const
{
	return absolute / _scale;
}

cocos2d::Vec2
Metric::reliative(cocos2d::Vec2 absolute) const
{
	return cocos2d::Vec2(
		reliative(absolute.x),
		reliative(absolute.y)
	);
}

cocos2d::Size
Metric::reliative(cocos2d::Size absolute) const
{
	return cocos2d::Size(
		reliative(absolute.width),
		reliative(absolute.height)
	);
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
Metric::constraint() const
{
	return _spawn;
}

float
Metric::lenght() const
{
	return _size.height / 3.0f;
}

const std::pair<cocos2d::Vec2, cocos2d::Vec2> &
Metric::anvil() const
{
	return _anvil;
}

const std::pair<cocos2d::Vec2, cocos2d::Vec2> &
Metric::hammer() const
{
	return _hammer;
}

}