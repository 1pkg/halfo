#ifndef COMPONENTS_BODY
#define COMPONENTS_BODY

#include "include.hpp"

namespace Components
{

class Body : public Application::Component
{
public:

	cocos2d::PhysicsBody * get(const cocos2d::Data & data, cocos2d::Node * node);
};

}

#endif