#include "Resource.hpp"
#include "include.hpp"

namespace Components
{

void
Resource::initialize()
{
}

const cocos2d::Data &
Resource::get(const std::string & resource)
{
#ifdef RESOURCE_DEBUG
	std::string alias = map(resource);
#else
	std::string alias = resource;
#endif
	if (_resources.find(alias) == _resources.end())
	{
		cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(alias);
#ifdef RESOURCE_DEBUG
		data = Master::instance().get<Components::Crypto>("crypto").decrypt(data);
#endif
		_resources.insert(std::pair<std::string, cocos2d::Data>(alias, data));
	}
	return _resources.at(alias);
}

std::string
Resource::map(const std::string & resource) const
{
	return resource;
}

}