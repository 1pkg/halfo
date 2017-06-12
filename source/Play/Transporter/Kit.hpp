#ifndef PLAY_TRANSPORTER_KIT
#define PLAY_TRANSPORTER_KIT

#include "include.hpp"

namespace Scenes{class Play;}
namespace Objects{class Figure; class Edge;}
namespace Play
{

namespace Transporter
{

class Kit : public Application::Kit
{
public:

	Kit(Scenes::Play * play);
	~Kit();
	void update(float delta) override;
	void walk(std::function<bool(const Application::Object *)> callback) override;
	Objects::Figure * find(cocos2d::PhysicsBody * body) const;
	std::unique_ptr<Objects::Figure> release(const Objects::Figure * figure);

private:

	bool contact(cocos2d::PhysicsContact & contact);
	std::unordered_map<
		cocos2d::PhysicsBody *, std::unique_ptr<Objects::Figure>
	> _prepool, _pool;
	std::unique_ptr<Objects::Edge> _edge;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	cocos2d::EventDispatcher * _dispatcher;
	Scenes::Play * _play;
};

}

}

#endif