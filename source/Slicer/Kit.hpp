#ifndef SLICER_KIT
#define SLICER_KIT

#include "include.hpp"

namespace Application{class Act;}
namespace Objects{class Figure;}
namespace Slicer
{

class Kit : public Application::Kit
{
public:

	Kit(Application::Act * act);
	~Kit();
	void update(float delta) override;

private:

	const float LIMIT_AREA = 500.0f;
	const float DELTA_AREA = 5000.0f;
	const float HIT_TIME = 0.2f;
	const float X_IMPULS = 1000.0f;
	const float Y_IMPULS = 500.0f;

	bool putDown();
	void putUp();
	void slice();
	bool contact(cocos2d::PhysicsContact & contact);
	cocos2d::DrawNode * _anvil, * _hammer;
	cocos2d::EventListenerTouchOneByOne * _touchSensor;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	Application::Act * _act;
};

}

#endif