#ifndef VIEWS_OBJECT_HAMMER
#define VIEWS_OBJECT_HAMMER

#include "include.hpp"

namespace Views
{

namespace Object
{

class Hammer : public Application::Views::Object
{
public:

	Hammer();

private:

	cocos2d::Sprite * _sprite;
};

}

}

#endif