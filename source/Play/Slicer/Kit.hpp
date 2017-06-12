#ifndef PLAY_SLICER_KIT
#define PLAY_SLICER_KIT

#include "include.hpp"

namespace Scenes{class Play;}
namespace Objects
{
	class Figure;
	class Blade;
	class Anvil;
}
namespace Play
{

namespace Slicer
{

class Kit : public Application::Kit
{
public:

	Kit(Scenes::Play * play);
	~Kit();

private:

	bool slice(const Application::Object * object) const;
	bool contact(cocos2d::PhysicsContact & contact) const;
	std::unique_ptr<Objects::Blade> _blade;
	std::unique_ptr<Objects::Anvil> _anvil;
	cocos2d::EventListenerTouchOneByOne * _touchSensor;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	cocos2d::EventDispatcher * _dispatcher;
	Scenes::Play * _play;
};

}

}

#endif