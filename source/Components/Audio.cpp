#include "include.hpp"
#include "Audio.hpp"
#include <SimpleAudioEngine.h>

namespace Components
{

void
Audio::initialize()
{
	for (std::pair<std::pair<std::string, Resource::Type>, cocos2d::Data> resource : Master::instance().get<Components::Resource>("resource")._resources)
		if (resource.first.second == Resource::Type::AUDIO)
		{
			std::string file = create(resource.second);
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(file.data());
			_files.insert(std::pair<std::string, std::string>(resource.first.first, file));
		}
}

void
Audio::finitialize()
{
	for (std::pair<std::string, std::string> file : _files)
		cocos2d::FileUtils::getInstance()->removeFile(file.second);
}

unsigned int
Audio::play(const std::string & alias) const
{
	return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(_files.at(alias).data());
}

void
Audio::stop(unsigned int identifier) const
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(identifier);
}

void
Audio::pause(unsigned int identifier) const
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(identifier);
}

void
Audio::resume(unsigned int identifier) const
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(identifier);
}

std::string
Audio::create(const cocos2d::Data & data) const
{
	static const char CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string name;
    for (unsigned i = 0; i < 0x10; ++i)
       name += CHARS[cocos2d::RandomHelper::random_int<unsigned int>(0, (sizeof(CHARS) - 1))];
	std::string path = cocos2d::FileUtils::getInstance()->getWritablePath() + name + ".wav";
	cocos2d::FileUtils::getInstance()->writeDataToFile(data, path);
	return path;
}

}