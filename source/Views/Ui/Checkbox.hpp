#ifndef VIEWS_UI_CHECKBOX
#define VIEWS_UI_CHECKBOX

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Views
{

namespace Ui
{

class Checkbox : public Application::Views::Ui
{
public:

	Checkbox(std::string title, bool state);
	std::function<void(bool)> change;

private:

	 cocos2d::ui::Layout * _layout;
};

}

}

#endif