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

	Kit(Act * act);
	~Kit();
	void update(float delta) override;
	std::vector<Objects::Figure *>
		find(std::pair<cocos2d::Vec2, cocos2d::Vec2> line);
	void release(Objects::Figure * figure);

private:

	bool contact(cocos2d::PhysicsContact & contact);
	Architector _architector;
	Act * _act;
	cocos2d::EventListenerPhysicsContact * _sensor;
	cocos2d::Node * _node;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _pool;
};

}

#endif