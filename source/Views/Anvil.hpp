#ifndef VIEWS_ANVIL
#define VIEWS_ANVIL

#include "include.hpp"

namespace Views
{

class Anvil : public Application::View
{
public:

	Anvil();
	~Anvil();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;

private:

	cocos2d::DrawNode * _draw;
};

}

#endif