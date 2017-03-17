#ifndef SCENES_SETTINGS
#define SCENES_SETTINGS

#include "include.hpp"
#include "Ui/Label.hpp"

namespace Scenes
{

class Settings : public Application::Wrapper, public cocos2d::LayerColor
{
public:

	static Settings * create();
	Settings();

private:

	std::unique_ptr<Ui::Label> _info;
};

}
#endif
