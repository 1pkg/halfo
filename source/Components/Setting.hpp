#ifndef COMPONENTS_SETTING
#define COMPONENTS_SETTING

#include "Application/Component.hpp"
#include <unordered_map>

namespace Components
{

class Setting : public Application::Component
{
public:

	const std::string FIGURE_SKIN = "figure-skin";
	const std::string HAMMER_SKIN = "hammer-skin";

	void initialize() override;
	bool has(const std::string & setting) const;
	const std::string & value(const std::string & setting) const;
	void change(const std::string & setting, const std::string & value);

private:

	friend class Storage;
	std::unordered_map<
		std::string,
		std::string
	> _settings;
};

}

#endif