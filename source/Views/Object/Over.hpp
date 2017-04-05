#ifndef VIEWS_OBJECT_OVER
#define VIEWS_OBJECT_OVER

#include "include.hpp"

namespace Views
{

namespace Object
{

class Over : public Application::View
{
public:

	Over();
	cocos2d::Node * node() const override;

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif