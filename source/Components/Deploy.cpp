#include "include.hpp"
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
		Master::instance().get<File>().move(Master::instance().get<File>().application() + "rc" + TRUE_FILE_EXTENSION, Master::instance().get<File>().storage() + "rc" + TRUE_FILE_EXTENSION);
		std::vector<std::string> assets;
		cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().application() + "sts" + TRUE_FILE_EXTENSION);
		data = Master::instance().get<Crypto>().decrypt(data, CRYPTO_STORAGE_BLOCK);
		std::stringstream stream(std::string((char*)data.getBytes(), (char*)data.getBytes() + data.getSize()));
		std::string temp;
		while (std::getline(stream, temp))
			assets.push_back(temp);
		Master::instance().get<File>().move(Master::instance().get<File>().application() + "sts" + TRUE_FILE_EXTENSION, Master::instance().get<File>().storage() + "sts" + TRUE_FILE_EXTENSION);
		for (const std::string & asset : assets)
			Master::instance().get<File>().move(Master::instance().get<File>().application() + asset + TRUE_FILE_EXTENSION, Master::instance().get<File>().assets() + asset + TRUE_FILE_EXTENSION);
		Master::instance().get<Setting>().set(Setting::FLAG_DEPLOY_FINISHED, FLAG_DONE);
	}
}

}