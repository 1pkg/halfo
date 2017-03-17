#ifndef UI_BUTTON
#define UI_BUTTON

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Ui
{

class Button : public Application::View
{
public:

	Button(std::string title, bool primary);
	~Button();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::Vec2 getPosition() const;
	void setPosition(cocos2d::Vec2 position);
	std::function<void()> click;

private:

	cocos2d::ui::Button * _button;
};

}

#endif