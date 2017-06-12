#ifndef PLAY_CLEANER_KIT
#define PLAY_CLEANER_KIT

#include "include.hpp"

namespace Scenes{class Play;}
namespace Objects{class Figure; class Platform; class Over;}
namespace Play
{

namespace Cleaner
{

class Kit : public Application::Kit
{
public:

	Kit(Scenes::Play * play);
	~Kit();
	void update(float delta) override;
	void attach(std::unique_ptr<Objects::Figure> figure);
    Objects::Figure * find(cocos2d::PhysicsBody * body) const;

private:

	void clean();
	void inspection(float delta);
	bool contact(cocos2d::PhysicsContact & contact) const;
	unsigned int _combo, _result, _time;
	std::unordered_map<cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>> _pool;
	std::unique_ptr<Objects::Platform> _platform;
	std::unique_ptr<Objects::Over> _over;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	cocos2d::EventDispatcher * _dispatcher;
	Scenes::Play * _play;
};

}

}

#endif