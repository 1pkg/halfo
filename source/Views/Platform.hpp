#ifndef VIEWS_PLATFORM
#define VIEWS_PLATFORM

#include "include.hpp"

namespace Views
{

class Platform : public Application::View
{
public:

	Platform();
	~Platform();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;
	void run(cocos2d::Action * action);

private:

	cocos2d::DrawNode * _node;
};

}

#endif