#ifndef COMPONENTS_METRIC
#define COMPONENTS_METRIC

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Metric : public Application::Component
{
public:

	Metric(cocos2d::Size size, cocos2d::Vec2 origin);
	void initialize() override;

	float absolute(float reliative) const;
	float absolute2(float reliative) const;
	float absolute3(float reliative) const;
	cocos2d::Vec2 absolute(cocos2d::Vec2 reliative) const;
	cocos2d::Size absolute(cocos2d::Size reliative) const;

	float reliative(float absolute) const;
	float reliative2(float absolute) const;
	float reliative3(float absolute) const;
	cocos2d::Vec2 reliative(cocos2d::Vec2 absolute) const;
	cocos2d::Size reliative(cocos2d::Size absolute) const;

	cocos2d::Vec2 origin() const;
	cocos2d::Size size() const;
	cocos2d::Vec2 center() const;
	cocos2d::Vec2 spawn(bool side) const;
	cocos2d::Size spawn() const;

	cocos2d::Vec2 score() const;

	float hammerLength() const;
	float anvilLength() const;

	const std::array<
		cocos2d::Vec2, 2
	> & hammer() const;
	const std::array<
		cocos2d::Vec2, 2
	> & anvil() const;
	const std::array<
		cocos2d::Vec2, 4
	> & edge() const;
	const std::array<
		cocos2d::Vec2, 2
	> & platform() const;
	const std::array<
		cocos2d::Vec2, 2
	> & over() const;

private:

	const cocos2d::Size COMMON_SIZE = cocos2d::Size(1920, 1080);

	float _scale;
	cocos2d::Size _size;
	cocos2d::Vec2 _origin;
	cocos2d::Vec2 _lspawn, _rspawn;
	cocos2d::Size _spawn;
	cocos2d::Vec2 _score;
	std::array<
		cocos2d::Vec2, 2
	> _anvil, _hammer;
	std::array<
		cocos2d::Vec2, 4
	> _edge;
	std::array<
		cocos2d::Vec2, 2
	> _platform;
	std::array<
		cocos2d::Vec2, 2
	> _over;
};

}

#endif