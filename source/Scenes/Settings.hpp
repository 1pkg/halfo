#ifndef SCENES_SETTINGS
#define SCENES_SETTINGS

#include "include.hpp"

namespace Scenes
{

class Settings : public Application::Scene
{
public:

	Settings();

private:

	std::unique_ptr<Views::Ui::Label> _info, _path;
};

}
#endif
