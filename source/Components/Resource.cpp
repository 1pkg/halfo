#include "Resource.hpp"

namespace Components
{

void
Resource::initialize()
{
}

const cocos2d::Data &
Resource::get(const std::string & resource)
{
	if (_resources.find(resource) == _resources.end())
	{
		cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(resource + ".png");
		_resources.insert(std::pair<std::string, cocos2d::Data>(resource, data));
	}
	return _resources.at(resource);
}

}