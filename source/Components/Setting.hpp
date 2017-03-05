#ifndef COMPONENTS_SETTING
#define COMPONENTS_SETTING

#include "Application/Component.hpp"
#include <unordered_map>

namespace Components
{

class Setting : public Application::Component
{
public:

	static const std::string FIGURE_SKIN;
	static const std::string HAMMER_SKIN;
	static const std::string DISABLE_ADDS;

	void initialize() override;
	const std::string & get(const std::string & setting) const;
	void set(const std::string & setting, const std::string & value);

private:

	friend class Storage;
	std::unordered_map<std::string, std::string> _settings;
};

}

#endif