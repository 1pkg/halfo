#ifndef SCENES_OVER
#define SCENES_OVER

#include "include.hpp"

namespace Scenes
{

class Over : public Application::Scene
{
public:

	Over();

private:

	std::unique_ptr<Views::Ui::Button> _play, _menu, _exit;
	std::unique_ptr<Views::Ui::Label> _result;
};

}
#endif
