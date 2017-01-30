#ifndef TRANSPORTER_POOL_HPP
#define TRANSPORTER_POOL_HPP

#include "Application\Kit.hpp"
#include <cocos2d.h>

namespace Objects{class Figure;}

namespace Transporter
{

class Kit : public Application::Kit
{
public:

	Kit(cocos2d::Layer * layer);
	void update(float delta) override;

private:

	void render();
	bool touch(cocos2d::Touch * touch, cocos2d::Event * event, std::pair<cocos2d::Vec2, cocos2d::Vec2> line);
	bool contact(cocos2d::PhysicsContact & contact);
	
	cocos2d::EventListenerTouchOneByOne * _touchSensor;
	cocos2d::EventListenerPhysicsContact * _physicSensor;
	cocos2d::Layer * _layer;

	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _pool;
};

}

#endif