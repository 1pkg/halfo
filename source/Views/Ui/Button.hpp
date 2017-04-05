#ifndef VIEWS_UI_BUTTON
#define VIEWS_UI_BUTTON

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Views
{

namespace Ui
{

class Button : public Application::View
{
public:

	Button(const std::string & icon, const std::string & title, std::function<void()> click);
	cocos2d::Node * node() const override;

private:

	cocos2d::ui::Layout * _layout;
};

}

}

#endif