#ifndef COMPONENTS_SETTING
#define COMPONENTS_SETTING

#include "include.hpp"

namespace Components
{

class Setting : public Application::Component
{
public:

	static const std::string PARAMETER_FIGURE_RESOURCE;
	static const std::string PARAMETER_BLADE_RESOURCE;
	static const std::string FLAG_ADDS_DISABLED;
	static const std::string FLAG_DEPLOY_FINISHED;

	void initialize() override;
	const std::string & get(const std::string & setting) const;
	void set(const std::string & setting, const std::string & value);

private:

	friend class Storage;
	std::unordered_map<std::string, std::string> _settings;
};

}

#endif