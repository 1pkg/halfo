#include "components.hpp"
#include "Panel.hpp"

namespace Views
{

namespace Ui
{

Panel::Panel()
{
	_layout = cocos2d::ui::Layout::create();
}

cocos2d::Node *
Panel::node() const
{
	return _layout;
}

void
Panel::attach(Application::View & ui) const
{
	return _layout->addChild(ui.node());
}

}

}