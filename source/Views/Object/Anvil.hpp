#ifndef VIEWS_OBJECT_ANVIL
#define VIEWS_OBJECT_ANVIL

#include "include.hpp"

namespace Views
{

namespace Object
{

class Anvil : public Application::View
{
public:

	Anvil();
	cocos2d::Node * node() const override;

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif