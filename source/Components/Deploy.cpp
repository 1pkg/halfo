#include "include.hpp"
#include "Deploy.hpp"

namespace Components
{

void
Deploy::initialize()
{
	if (Master::instance().get<Setting>().get(Setting::DONE_DEPLOY) == "non")
	{
		Master::instance().get<File>().directory(Master::instance().get<File>().root() + "/halfo");
		Master::instance().get<File>().directory(Master::instance().get<File>().assets());
		Master::instance().get<File>().directory(Master::instance().get<File>().storage());
		Master::instance().get<File>().directory(Master::instance().get<File>().cache());
		std::vector<std::string> assets;
#ifdef RESOURCE_DEBUG
		cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().root() + "/assets.dpl");
		Master::instance().get<File>().remove(Master::instance().get<File>().root() + "/assets.dpl");
		std::stringstream stream((char*)data.getBytes());
		std::string file;
		while (std::getline(stream, file))
			assets.push_back(file.substr(0x0, 0x13));
		Master::instance().get<File>().move(Master::instance().get<File>().root() + "/rc.ev", Master::instance().get<File>().storage() + "/rc.ev");
#else
		assets = {
			"figure-deault.png",
			"hammer-deault.png",
			"hammer-deault.json",
			"hammer-deault.wav",
			"hammer-deault1.wav",
			"font.ttf"
		};
#endif
		for (const std::string & asset : assets)
			Master::instance().get<File>().move(Master::instance().get<File>().root()  + "/" + asset, Master::instance().get<File>().assets() + "/" + asset);
		Master::instance().get<Setting>().set(Setting::DONE_DEPLOY, "done");
	}
}

}