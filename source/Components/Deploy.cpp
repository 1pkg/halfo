#include "include.hpp"
#include "Deploy.hpp"

namespace Components
{

void
Deploy::initialize()
{
	if (Master::instance().get<Setting>().get(Setting::DEPLOY_DONE) == "false")
	{
		Master::instance().get<File>().move("rc.ev", "rc.ev");
		Master::instance().get<Setting>().set(Setting::DEPLOY_DONE, "true");
	}
}

}