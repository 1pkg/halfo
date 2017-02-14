#ifndef TRANSPORTER_KIT
#define TRANSPORTER_KIT

#include "include.hpp"
#include "Architector.hpp"

namespace Application{class Act;}
namespace Objects{class Figure;}
namespace Transporter
{

class Kit : public Application::Kit
{
public:

	Kit(Application::Act * act);
	~Kit();
	void update(float delta) override;
	std::vector<Objects::Figure *>
		find(std::pair<cocos2d::Vec2, cocos2d::Vec2> line) const;
	Objects::Figure *
		find(cocos2d::PhysicsBody * body) const;
	std::unique_ptr<Objects::Figure>
		release(Objects::Figure * figure);
	void increase();
	void reset();

private:

	const float SPAWN_TIME = 5.0f;
	const float REFRESH_TIME = 100.0f;

	bool contact(cocos2d::PhysicsContact & contact);
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _prepool, _pool;
	Architector _architector;
	cocos2d::Node * _edge;
	cocos2d::EventListenerPhysicsContact * _sensor;
	Application::Act * _act;
};

}

#endif