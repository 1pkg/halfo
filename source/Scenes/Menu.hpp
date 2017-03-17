#ifndef SCENES_MENU
#define SCENES_MENU

#include "include.hpp"
#include "Ui/Button.hpp"

namespace Scenes
{

class Menu : public Application::Wrapper, public cocos2d::LayerColor
{
public:

	static Menu * create();
	Menu();

private:

	std::unique_ptr<Ui::Button> _play, _score, _purchape, _settings, _credits;
};

}
#endif
