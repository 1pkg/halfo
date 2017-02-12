#ifndef APPLICATION_METRIC
#define APPLICATION_METRIC

#include <cocos2d.h>

namespace Application
{

class Metric
{
public:

	const cocos2d::Size COMMON_SIZE = cocos2d::Size(1920, 1080);

	static Metric & instance();
	float absolute(float reliative) const;
	cocos2d::Vec2 absolute(cocos2d::Vec2 reliative) const;
	cocos2d::Size absolute(cocos2d::Size reliative) const;
	float reliative(float absolute) const;
	cocos2d::Vec2 reliative(cocos2d::Vec2 absolute) const;
	cocos2d::Size reliative(cocos2d::Size absolute) const;
	cocos2d::Vec2 origin() const;
	cocos2d::Size size() const;
	cocos2d::Vec2 center() const;
	cocos2d::Vec2 anchor() const;
	cocos2d::Vec2 spawn(bool side) const;
	cocos2d::Size constraint() const;
	cocos2d::Vec2 score() const;
	cocos2d::Vec2 combo() const;
	float lenght() const;
	const std::pair<cocos2d::Vec2, cocos2d::Vec2> & anvil() const;
	const std::pair<cocos2d::Vec2, cocos2d::Vec2> & hammer() const;

private:

	Metric();
	cocos2d::Size _size;
	cocos2d::Vec2 _origin, _anchor;
	std::pair<cocos2d::Vec2, cocos2d::Vec2> _anvil, _hammer;
	cocos2d::Vec2 _lspawn, _rspawn;
	cocos2d::Size _spawn;
	cocos2d::Vec2 _score, _combo;
	float _scale;
};

}

#endif