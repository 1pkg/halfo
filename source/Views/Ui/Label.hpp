#ifndef VIEWS_UI_LABEL
#define VIEWS_UI_LABEL

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Views
{

namespace Ui
{

class Label : public Application::View
{
public:

	Label(const std::string & text);
	cocos2d::Node * node() const override;

private:

	cocos2d::ui::Layout * _layout;
};

}

}

#endif