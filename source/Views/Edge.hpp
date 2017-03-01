#ifndef VIEWS_EDGE
#define VIEWS_EDGE

#include "include.hpp"

namespace Views
{

class Edge : public Application::View
{
public:

	Edge();
	~Edge();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;

private:

	cocos2d::DrawNode * _node;
};

}

#endif