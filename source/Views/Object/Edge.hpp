#ifndef VIEWS_OBJECT_EDGE
#define VIEWS_OBJECT_EDGE

#include "include.hpp"

namespace Views
{

namespace Object
{

class Edge : public Application::Views::Object
{
public:

	Edge();

private:

	cocos2d::DrawNode * _draw;
};

}

}

#endif