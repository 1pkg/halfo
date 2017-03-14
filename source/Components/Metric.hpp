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
	cocos2d::Rect hammer() const;
	cocos2d::Rect anvil() const;
	cocos2d::Rect platform() const;
	const std::array<cocos2d::Vec2, 2> & slice() const;
	const std::array<cocos2d::Vec2, 2> & over() const;
	const std::array<cocos2d::Vec2, 4> & edge() const;

private:

	float _scale;
	cocos2d::Size _size;
	cocos2d::Vec2 _origin;
	cocos2d::Vec2 _lspawn, _rspawn;
	cocos2d::Size _spawn;
	cocos2d::Rect _hammer, _anvil, _platform;
	std::array<cocos2d::Vec2, 2> _over, _slice;
	std::array<cocos2d::Vec2, 4> _edge;
};

}

#endif