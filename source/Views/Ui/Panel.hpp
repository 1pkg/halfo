#ifndef VIEWS_UI_PANEL
#define VIEWS_UI_PANEL

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Views
{

namespace Ui
{

class Panel : public Application::View
{
public:

	Panel();
	cocos2d::Node * node() const override;
	void attach(Application::View & ui) const;

private:

	cocos2d::ui::Layout * _layout;
};

}

}

#endif