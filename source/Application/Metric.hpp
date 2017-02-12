#ifndef APPLICATION_METRIC
#define APPLICATION_METRIC

#include <cocos2d.h>
#include <array>

namespace Application
{

class Metric
{
public:

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
	cocos2d::Vec2 spawn(bool side) const;
	cocos2d::Size spawn() const;

	cocos2d::Vec2 score() const;
	cocos2d::Vec2 combo() const;

	const std::pair<
		cocos2d::Vec2, cocos2d::Vec2
	> & anvil() const;
	const std::pair<
		cocos2d::Vec2, cocos2d::Vec2
	> & hammer() const;
	float hammerLength() const;

	const std::array<
		cocos2d::Vec2, 4
	> & transporterEdge() const;
	const std::array<
		cocos2d::Vec2, 2
	> & cleanerEdge() const;

private:

	const cocos2d::Size COMMON_SIZE = cocos2d::Size(1920, 1080);

	Metric();
	float _scale;
	cocos2d::Size _size;
	cocos2d::Vec2 _origin;
	cocos2d::Vec2 _lspawn, _rspawn;
	cocos2d::Size _spawn;
	cocos2d::Vec2 _score, _combo;
	std::pair<
		cocos2d::Vec2, cocos2d::Vec2
	> _anvil, _hammer;
	std::array<
		cocos2d::Vec2, 4
	> _transporterEdge;
	std::array<
		cocos2d::Vec2, 2
	> _cleanerEdge;

};

}

#endif