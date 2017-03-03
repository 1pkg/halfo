#ifndef TRANSPORTER_KIT
#define TRANSPORTER_KIT

#include "include.hpp"
#include "Architector.hpp"

namespace Scenes{class Act;}
namespace Objects{class Figure; class Edge;}
namespace Transporter
{

class Kit : public Application::Kit
{
public:

	Kit(Scenes::Act * act);
	~Kit();
	void update(float delta) override;
	std::vector<Objects::Figure *>
		find(const std::array<cocos2d::Vec2, 2> & line) const;
	Objects::Figure *
		find(cocos2d::PhysicsBody * body) const;
	std::unique_ptr<Objects::Figure>
		release(Objects::Figure * figure);

private:

	const float SPAWN_TIME = 0.5f;
	const float REFRESH_TIME = 100.0f;

	bool contact(cocos2d::PhysicsContact & contact);
	Architector _architector;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _prepool, _pool;
	std::unique_ptr<Objects::Edge> _edge;
	cocos2d::EventListenerPhysicsContact * _sensor;
	Scenes::Act * _act;
};

}

#endif