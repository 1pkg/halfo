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
	std::string rsc = "D:/proj/shredder/assets/" + resource + ".png";
	if (_resources.find(rsc) == _resources.end())
		_resources.insert(
			std::pair<std::string, cocos2d::Data>(
				rsc,
				cocos2d::FileUtils::getInstance()->getDataFromFile("D:/proj/shredder/assets/" + resource + ".png")
			)
		);

	return _resources.at(rsc);
}

}