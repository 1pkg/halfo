#ifndef SLICER_KIT
#define SLICER_KIT

#include "include.hpp"

namespace Scenes{class Act;}
namespace Objects
{
	class Figure;
	class Hammer;
	class Anvil;
}
namespace Slicer
{

class Kit : public Application::Kit
{
public:

	Kit(Scenes::Act * act);
	~Kit();
	void update(float delta) override;

private:

	const float HIT_TIME = 0.05f;
	const float LIMIT_AREA = 1000.0f, DELTA_AREA = 15000.0f;
	const float X_IMPULS = 25000.0f, Y_IMPULS = 25000.0f;
	void slice() const;
	bool contact(cocos2d::PhysicsContact & contact) const;
	std::unique_ptr<Objects::Hammer> _hammer;
	std::unique_ptr<Objects::Anvil> _anvil;
	cocos2d::EventListenerTouchOneByOne * _touchSensor;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	Scenes::Act * _act;
};

}

#endif