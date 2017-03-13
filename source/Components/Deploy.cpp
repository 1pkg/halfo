#include "include.hpp"
#include "Deploy.hpp"

namespace Components
{

void
Deploy::initialize()
{
	if (Master::instance().get<Setting>().get(Setting::DONE_DEPLOY) == "non")
	{
		Master::instance().get<File>().directory(Master::instance().get<File>().root());
		Master::instance().get<File>().directory(Master::instance().get<File>().assets());
		Master::instance().get<File>().directory(Master::instance().get<File>().storage());
		Master::instance().get<File>().directory(Master::instance().get<File>().cache());
		Master::instance().get<File>().move(Master::instance().get<File>().application() + "rc.ev", Master::instance().get<File>().storage() + "rc.ev");
		std::vector<std::string> assets;
		cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().application() + "sts.ev");
		std::stringstream stream(std::string((char*)data.getBytes(), (char*)data.getBytes() + data.getSize()));
		std::string temp;
		while (std::getline(stream, temp))
			assets.push_back(temp);
		Master::instance().get<File>().remove(Master::instance().get<File>().application() + "sts.ev");
		for (const std::string & asset : assets)
			Master::instance().get<File>().move(Master::instance().get<File>().application() + asset, Master::instance().get<File>().assets() + asset);
		Master::instance().get<Setting>().set(Setting::DONE_DEPLOY, "done");
	}
}

}