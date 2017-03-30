#ifndef COMPONENTS_BODY
#define COMPONENTS_BODY

#include "include.hpp"

namespace Components
{

class Body : public Application::Component
{
public:

	void initialize() override;
	cocos2d::PhysicsBody * get(const std::string & body, cocos2d::Node * node);

private:

	std::unordered_map<std::string, std::string> _bodies;
};

}

#endif