#include "Setting.hpp"

namespace Components
{

const std::string Setting::PARAMETER_FIGURE_RESOURCE = "figure";
const std::string Setting::PARAMETER_HAMMER_RESOURCE = "hammer";
const std::string Setting::DONE_DISABLE_ADDS = "disable-adds";
const std::string Setting::DONE_DEPLOY = "deploy";

void
Setting::initialize()
{
	_settings.insert(std::pair<std::string, std::string>(PARAMETER_FIGURE_RESOURCE, "figure-deault"));
	_settings.insert(std::pair<std::string, std::string>(PARAMETER_HAMMER_RESOURCE, "hammer-deault"));
	_settings.insert(std::pair<std::string, std::string>(DONE_DISABLE_ADDS, "non"));
	_settings.insert(std::pair<std::string, std::string>(DONE_DEPLOY, "non"));
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