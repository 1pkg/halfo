#ifndef VIEWS_UI_SEPARATOR
#define VIEWS_UI_SEPARATOR

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Views
{

namespace Ui
{

class Separator : public Application::View
{
public:

	Separator(cocos2d::Vec2 first, cocos2d::Vec2 second);
	cocos2d::Node * node() const override;

private:

	cocos2d::ui::Layout * _layout;
};

}

}

#endif