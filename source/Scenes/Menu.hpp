#ifndef SCENES_MENU
#define SCENES_MENU

#include "include.hpp"

namespace Scenes
{

class Menu : public Application::Scene
{
public:

	Menu();

private:

	std::unique_ptr<Views::Ui::Button> _play, _score, _purchape, _settings, _credits;
};

}
#endif
