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
	
	cocos2d::EventListenerTouchOneByOne * _touch;
	cocos2d::EventListenerPhysicsContact * _physic;
	cocos2d::Layer * _layer;

	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _pool;
};

}

#endif