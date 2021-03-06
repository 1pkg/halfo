#include "File.hpp"
#include "Resource.hpp"
#include "Font.hpp"

namespace Components
{

const std::string Font::EARTH_2073 = "earth-2073";
const float Font::LARGE_SIZE = 48.0f;
const float Font::MEDIUM_SIZE = 32.0f;
const float Font::SMALL_SIZE = 24.0f;

void
Font::initialize()
{
	std::function<bool(const std::string &, const cocos2d::Data &)> callback =
	[this](const std::string & origin, const cocos2d::Data & data)
	{
		std::string font = Master::instance().get<File>().cache(data);
		_fonts.insert(std::pair<std::string, std::string>(replace(origin, Resource::Extension[(unsigned int)Resource::Type::FONT], ""), font));
		return true;
	};
	Master::instance().get<Resource>().walk(Resource::Type::FONT, callback);
}

std::string
Font::get(const std::string & font) const
{
	std::unordered_map<std::string, std::string>::const_iterator it = _fonts.find(font);
	if (it == _fonts.end())
		return "";

	return it->second;
}

}