#include "Metric.hpp"

namespace Application
{

Metric::Metric()
	: _size(cocos2d::Director::getInstance()->getVisibleSize()),
	_origin(cocos2d::Director::getInstance()->getVisibleOrigin())
{
	cocos2d::Size common(1920, 1080);
	_scale = (_size.width / common.width + _size.height / common.height) / 2;
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

float
Metric::reliative(float absolute) const
{
	return absolute / _scale;
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
	return cocos2d::Vec2(
		(side ? _size.width - _size.width / 3.0f : _size.width / 3.0f ),
		 _size.height / 6.0f * 5.0f
	);
}

std::pair<cocos2d::Vec2, cocos2d::Vec2>
Metric::anvil() const
{
	return std::pair<cocos2d::Vec2, cocos2d::Vec2>(
		cocos2d::Vec2(_size.width / 2.0f, 0.0f),
		cocos2d::Vec2(_size.width / 2.0f, _size.height / 3.0f * 2.0f)
	);
}

std::pair<cocos2d::Vec2, cocos2d::Vec2>
Metric::hammer() const
{
	return std::pair<cocos2d::Vec2, cocos2d::Vec2>(
		cocos2d::Vec2(_size.width / 2.0f, _size.height / 3.0f * 2.0f),
		cocos2d::Vec2(_size.width / 2.0f, _size.height)
	);
}

}