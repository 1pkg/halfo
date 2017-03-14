#include "include.hpp"
#include "Font.hpp"

namespace Components
{

void
Font::initialize()
{
	std::function<bool(const std::string &, const cocos2d::Data &)> callback =
	[this](const std::string & origin, const cocos2d::Data & data)
	{
		_font = Master::instance().get<File>().cache(data);
		return false;
	};
	Master::instance().get<Components::Resource>().walk(Resource::Type::FONT, callback);
}

std::string
Font::get() const
{
	return _font;
}

}