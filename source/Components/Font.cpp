#include "include.hpp"
#include "Font.hpp"

namespace Components
{

void
Font::initialize()
{
	cocos2d::Data data = Master::instance().get<Resource>()._resources.at(std::pair<std::string, Resource::Type>("font", Resource::Type::FONT));
	_path = Master::instance().get<File>().write(data);
}

std::string
Font::get() const
{
	return _path;
}

}