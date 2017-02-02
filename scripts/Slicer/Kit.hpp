#ifndef SLICER_KIT
#define SLICER_KIT

#include "Application/Kit.hpp"
#include <cocos2d.h>

class Act;
namespace Objects{class Figure;}
namespace Slicer
{

class Kit : public Application::Kit
{
public:

	Kit(Act * act);
	~Kit();
	void update(float delta) override;

private:

	void slice();
	Act * _act;
	cocos2d::DrawNode * _anvil, * _hammer;
	cocos2d::EventListenerTouchOneByOne * _sensor;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _pool;
};

}

#endif