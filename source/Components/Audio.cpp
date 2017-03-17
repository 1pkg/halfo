#include "File.hpp"
#include "Resource.hpp"
#include "Audio.hpp"
#include <SimpleAudioEngine.h>

namespace Components
{

void
Audio::initialize()
{
	std::function<bool(const std::string &, const cocos2d::Data &)> callback =
	[this](const std::string & origin, const cocos2d::Data & data)
	{
		std::string audio = Master::instance().get<File>().cache(data);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(audio.data());
		_audios.insert(std::pair<std::string, std::string>(origin, audio));
		return true;
	};
	Master::instance().get<Components::Resource>().walk(Resource::Type::AUDIO, callback);
}

unsigned int
Audio::play(const std::string & audio) const
{
	std::unordered_map<std::string, std::string>::const_iterator it = _audios.find(audio);
	if (it == _audios.end())
		return 0;

	return CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(it->second.data());
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