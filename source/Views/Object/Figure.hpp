#ifndef VIEWS_OBJECT_FIGURE
#define VIEWS_OBJECT_FIGURE

#include "include.hpp"

namespace Views
{

namespace Object
{

class Figure : public Application::View
{
public:

	Figure(const cocos2d::Polygon & pattern, float angle, bool hollow);
	~Figure();
	cocos2d::Node * node() const override;

private:

	cocos2d::Sprite * _sprite;
	cocos2d::ClippingNode * _clipper;
	cocos2d::DrawNode * _stencil;
};

}

}

#endif