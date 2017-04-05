#ifndef VIEWS_OBJECT_EDGE
#define VIEWS_OBJECT_EDGE

#include "include.hpp"

namespace Views
{

namespace Object
{

class Edge : public Application::View
{
public:

	Edge();
	cocos2d::Node * node() const override;

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif