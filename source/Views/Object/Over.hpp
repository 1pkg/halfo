#ifndef VIEWS_OBJECT_OVER
#define VIEWS_OBJECT_OVER

#include "include.hpp"

namespace Views
{

namespace Object
{

class Over : public Application::Views::Object
{
public:

	Over();

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif