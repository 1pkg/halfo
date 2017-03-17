#ifndef UI_CHECKBOX
#define UI_CHECKBOX

#include "include.hpp"
#include <ui/CocosGUI.h>

namespace Ui
{

class Checkbox : public Application::View
{
public:

	Checkbox(std::string title);
	~Checkbox();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::Vec2 getPosition() const;
	void setPosition(cocos2d::Vec2 position);
	bool state();
	std::function<void(bool)> change;

private:

	cocos2d::ui::CheckBox * _checkbox;
	cocos2d::Label * _label;
};

}

#endif