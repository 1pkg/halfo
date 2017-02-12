#ifndef TRANSPORTER_KIT
#define TRANSPORTER_KIT

#include "Application/Kit.hpp"
#include "Architector.hpp"
#include <cocos2d.h>

class Act;
namespace Objects{class Figure;}
namespace Transporter
{

class Kit : public Application::Kit
{
public:

	const float SPAWN_TIME = 5.0f;
	const float REFRESH_TIME = 100.0f;

	Kit(Act * act);
	~Kit();
	void update(float delta) override;
	std::vector<Objects::Figure *>
		find(std::pair<cocos2d::Vec2, cocos2d::Vec2> line);
	std::unique_ptr<Objects::Figure>
		release(cocos2d::PhysicsBody * body);
	void release(Objects::Figure * figure);

private:

	bool contact(cocos2d::PhysicsContact & contact);
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _pool;
	Architector _architector;
	cocos2d::Node * _edge;
	cocos2d::EventListenerPhysicsContact * _sensor;
	Act * _act;
};

}

#endif