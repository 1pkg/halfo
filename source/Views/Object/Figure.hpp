#ifndef VIEWS_OBJECT_FIGURE
#define VIEWS_OBJECT_FIGURE

#include "include.hpp"

namespace Views
{

namespace Object
{

class Figure : public Application::Views::Object
{
public:

	Figure(const cocos2d::Vec2 * pattern, std::size_t size, float angle, bool hollow);

private:

	cocos2d::Sprite * _sprite;
	cocos2d::ClippingNode * _clipper;
	cocos2d::DrawNode * _stencil;
};

}

}

#endif