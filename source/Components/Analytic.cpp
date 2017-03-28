#include "constants.hpp"
#include "Analytic.hpp"
#include <plugins/Sdkbox.hpp>
#include <plugins/PluginGoogleAnalytics.hpp>

namespace Components
{

void
Analytic::initialize()
{
	sdkbox::PluginGoogleAnalytics::init();
}

void
Analytic::track(const std::string & category, const std::string & action, const std::string & label, int value)
{
	sdkbox::PluginGoogleAnalytics::logEvent(category, action, label, value);
}

}