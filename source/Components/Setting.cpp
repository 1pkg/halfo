#include "Setting.hpp"

namespace Components
{

void
Setting::initialize()
{
	_settings.insert(
		std::pair<std::string, std::string>(FIGURE_SKIN, "deault")
	);
	_settings.insert(
		std::pair<std::string, std::string>(HAMMER_SKIN, "deault")
	);
}

bool
Setting::has(const std::string & setting) const
{
	return _settings.find(setting) != _settings.end();
}

const std::string &
Setting::value(const std::string & setting) const
{
	return _settings.find(setting)->second;
}

void
Setting::change(const std::string & setting, const std::string & value)
{
	_settings.find(setting)->second = value;
}

}