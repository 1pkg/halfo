#ifndef VIEWS_OBJECT_BLADE
#define VIEWS_OBJECT_BLADE

#include "include.hpp"

namespace Views
{

namespace Object
{

class Blade : public Application::View
{
public:

	Blade();
	cocos2d::Node * node() const override;

private:

	cocos2d::Sprite * _sprite;
};

}

}

#endif