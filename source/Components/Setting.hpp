#ifndef COMPONENTS_SETTING
#define COMPONENTS_SETTING

#include "Application/Component.hpp"
#include <unordered_map>

namespace Components
{

class Setting : public Application::Component
{
public:

	static const std::string PARAMETER_FIGURE_RESOURCE;
	static const std::string PARAMETER_HAMMER_RESOURCE;
	static const std::string DONE_DISABLE_ADDS;
	static const std::string DONE_DEPLOY;

	void initialize() override;
	const std::string & get(const std::string & setting) const;
	void set(const std::string & setting, const std::string & value);

private:

	friend class Storage;
	std::unordered_map<std::string, std::string> _settings;
};

}

#endif