#ifndef SCENES_OVER
#define SCENES_OVER

#include "Application/Wrapper.hpp"
#include <cocos2d.h>
#include <ui/CocosGUI.h>

namespace Scenes
{

class Over : public Application::Wrapper, public cocos2d::LayerColor
{
public:

    static cocos2d::Scene * instantiate();

	Over();
	~Over();
	static Over * create();

private:

	cocos2d::ui::Button * _restart, * _exit;
	cocos2d::Label * _label;
};

}
#endif
