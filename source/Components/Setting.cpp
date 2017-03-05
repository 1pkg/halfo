#include "Setting.hpp"

namespace Components
{

const std::string Setting::FIGURE_SKIN = "figure-skin";
const std::string Setting::HAMMER_SKIN = "hammer-skin";
const std::string Setting::DISABLE_ADDS = "disable-adds";

void
Setting::initialize()
{
	_settings.insert(std::pair<std::string, std::string>(FIGURE_SKIN, "figure-skin-deault"));
	_settings.insert(std::pair<std::string, std::string>(HAMMER_SKIN, "hammer-skin-deault"));
	_settings.insert(std::pair<std::string, std::string>(DISABLE_ADDS, "disable"));
}

const std::string &
Setting::get(const std::string & setting) const
{
	return _settings.find(setting)->second;
}

void
Setting::set(const std::string & setting, const std::string & value)
{
	_settings.find(setting)->second = value;
}

}