#ifndef VIEWS_UI_BUTTON
#define VIEWS_UI_BUTTON

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Views
{

namespace Ui
{

class Button : public Application::Views::Ui
{
public:

	Button(std::string title, bool primary);
	std::function<void()> click;

private:

	cocos2d::ui::Button * _button;
};

}

}

#endif