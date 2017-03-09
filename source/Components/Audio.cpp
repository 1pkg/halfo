#include "include.hpp"
#include "Audio.hpp"
#include <SimpleAudioEngine.h>

namespace Components
{

void
Audio::initialize()
{
	for (std::pair<std::pair<std::string, Resource::Type>, cocos2d::Data> resource : Master::instance().get<Components::Resource>()._resources)
		if (resource.first.second == Resource::Type::AUDIO)
		{
			std::string audio = Master::instance().get<File>().write(resource.second);
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(audio.data());
			_files.insert(std::pair<std::string, std::string>(resource.first.first, audio));
		}
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

}