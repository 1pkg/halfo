#ifndef APPLICATION_METRIC
#define APPLICATION_METRIC

#include <cocos2d.h>

namespace Application
{

class Metric
{
public:

	static Metric & instance();
	float absolute(float reliative) const;
	float reliative(float absolute) const;
	cocos2d::Vec2 origin() const;
	cocos2d::Size size() const;
	cocos2d::Vec2 center() const;
	cocos2d::Vec2 spawn(bool side) const;
	std::pair<cocos2d::Vec2, cocos2d::Vec2> anvil() const;
	std::pair<cocos2d::Vec2, cocos2d::Vec2> hammer() const;

private:

	Metric();
	cocos2d::Size _size;
	cocos2d::Vec2 _origin;
	float _scale;
};

}

#endif