#ifndef VIEWS_OBJECT_PLATFORM
#define VIEWS_OBJECT_PLATFORM

#include "include.hpp"

namespace Views
{

namespace Object
{

class Platform : public Application::Views::Object
{
public:

	Platform();

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif