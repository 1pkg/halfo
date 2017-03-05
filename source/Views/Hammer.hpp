#ifndef VIEWS_HAMMER
#define VIEWS_HAMMER

#include "include.hpp"

namespace Views
{

class Hammer : public Application::View
{
public:

	Hammer();
	~Hammer();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;
	void run(cocos2d::Action * action);

private:

	cocos2d::Sprite * _node;
	cocos2d::Image * _image;
};

}

#endif