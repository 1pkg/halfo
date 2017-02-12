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

	const float LIMIT_AREA = 500.0f;
	const float DELTA_AREA = 5000.0f;
	const float X_IMPULS = 1000.0f;
	const float Y_IMPULS = 500.0f;

	Kit(Act * act);
	~Kit();
	void update(float delta) override;

private:

	void slice();
	bool contact(cocos2d::PhysicsContact & contact);
	cocos2d::DrawNode * _anvil, * _hammer;
	cocos2d::EventListenerTouchOneByOne * _touchSensor;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	Act * _act;
};

}

#endif