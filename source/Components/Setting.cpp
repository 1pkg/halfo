#include "constants.hpp"
#include "Setting.hpp"

namespace Components
{

const std::string Setting::PARAMETER_FIGURE_RESOURCE = "figure";
const std::string Setting::PARAMETER_HAMMER_RESOURCE = "hammer";
const std::string Setting::FLAG_ADDS_DISABLED = "adds-disables";
const std::string Setting::FLAG_DEPLOY_FINISHED = "deploy-finished";

void
Setting::initialize()
{
	_settings.insert(std::pair<std::string, std::string>(PARAMETER_FIGURE_RESOURCE, "figure-deault"));
	_settings.insert(std::pair<std::string, std::string>(PARAMETER_HAMMER_RESOURCE, "hammer-deault"));
	_settings.insert(std::pair<std::string, std::string>(FLAG_ADDS_DISABLED, FLAG_NON));
	_settings.insert(std::pair<std::string, std::string>(FLAG_DEPLOY_FINISHED, FLAG_NON));
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