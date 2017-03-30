#include "constants.hpp"
#include "File.hpp"
#include "Crypto.hpp"
#include "Setting.hpp"
#include "Deploy.hpp"

namespace Components
{

void
Deploy::initialize()
{
	if (Master::instance().get<Setting>().get(Setting::FLAG_DEPLOY_FINISHED) == FLAG_NON)
	{
		Master::instance().get<File>().directory(Master::instance().get<File>().root());
		Master::instance().get<File>().directory(Master::instance().get<File>().assets());
		Master::instance().get<File>().directory(Master::instance().get<File>().storage());
		Master::instance().get<File>().directory(Master::instance().get<File>().cache());
		std::vector<std::string> assets;
		cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().application() + "deploy.list");
		Master::instance().get<File>().remove(Master::instance().get<File>().application() + "deploy.list");
		std::stringstream stream(std::string((char*)data.getBytes(), (char*)data.getBytes() + data.getSize()));
		std::string temp;
		while (std::getline(stream, temp))
			assets.push_back(temp);
		for (const std::string & asset : assets)
			Master::instance().get<File>().move(Master::instance().get<File>().application() + asset, Master::instance().get<File>().assets() + asset);
		Master::instance().get<Setting>().set(Setting::FLAG_DEPLOY_FINISHED, FLAG_DONE);
	}
}

}