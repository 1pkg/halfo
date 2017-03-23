#ifndef VIEWS_OBJECT_ANVIL
#define VIEWS_OBJECT_ANVIL

#include "include.hpp"

namespace Views
{

namespace Object
{

class Anvil : public Application::Views::Object
{
public:

	Anvil();

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif