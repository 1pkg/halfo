#include "constants.hpp"
#include "resources.rc"
#include "File.hpp"
#include "Crypto.hpp"
#include "Resource.hpp"

namespace Components
{

const char *
Resource::Extension[] = {".png", ".json", ".wav", ".ttf"};

void
Resource::initialize()
{
	for (std::unordered_map<std::string, std::pair<std::string, std::string>>::const_iterator it = RESOURCES.begin(); it != RESOURCES.end(); ++it)
	{
		cocos2d::Data data = Master::instance().get<File>().read(Master::instance().get<File>().assets() + it->second.first);
		data = Master::instance().get<Crypto>().decrypt(data, CRYPTO_RESOURCE_BLOCK);
		if (hash(data) == it->second.second)
			_resources.insert(std::pair<std::string, cocos2d::Data>(it->first, data));
	}
}

const cocos2d::Data &
Resource::get(const std::string & name, Type type, unsigned int number)
{
	static cocos2d::Data data;
	std::string key = name + to_string(number) + Extension[(unsigned int)type];
	std::unordered_map<std::string, cocos2d::Data>::const_iterator it = _resources.find(key);
	if (it != _resources.end())
		return it->second;

	return data;
}

void
Resource::walk(Type type, std::function<bool(const std::string &, const cocos2d::Data &)> callback)
{
	for(std::unordered_map<std::string, cocos2d::Data>::const_iterator it = _resources.begin(); it != _resources.end(); ++it)
		if (it->first.find(Extension[(unsigned int)type]) != std::string::npos)
			if(!callback(it->first, it->second))
				return;
}

void
Resource::walk(const std::string & name, std::function<bool(const std::string &, const cocos2d::Data &)> callback)
{
	for(std::unordered_map<std::string, cocos2d::Data>::const_iterator it = _resources.begin(); it != _resources.end(); ++it)
		if (it->first.find(name) == 0)
			if(!callback(it->first, it->second))
				return;
}

}