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

	const float HIT_TIME = 0.05f;
	const float
		LIMIT_AREA = 1000.0f,
		DELTA_AREA = 15000.0f;
	const float
		X_IMPULS = 25000.0f,
		Y_IMPULS = 25000.0f;

	bool putDown();
	void putUp();
	void slice() const;
	bool contact(cocos2d::PhysicsContact & contact) const;
	cocos2d::DrawNode * _anvil, * _hammer;
	cocos2d::EventListenerTouchOneByOne * _touchSensor;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	Application::Act * _act;
};

}

#endif