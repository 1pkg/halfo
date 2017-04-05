#ifndef VIEWS_OBJECT_PLATFORM
#define VIEWS_OBJECT_PLATFORM

#include "include.hpp"

namespace Views
{

namespace Object
{

class Platform : public Application::View
{
public:

	Platform();
	cocos2d::Node * node() const override;

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif