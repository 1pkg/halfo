#ifndef SCENES_OVER
#define SCENES_OVER

#include "include.hpp"
#include "Ui/Button.hpp"
#include "Ui/Label.hpp"

namespace Scenes
{

class Over : public Application::Wrapper, public cocos2d::LayerColor
{
public:

	static Over * create();
	Over();

private:

	std::unique_ptr<Ui::Button> _play, _menu, _exit;
	std::unique_ptr<Ui::Label> _result;
};

}
#endif
