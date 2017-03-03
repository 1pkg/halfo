#ifndef COMPONENTS_FEATURE
#define COMPONENTS_FEATURE

#include "Application/Component.hpp"
#include <unordered_map>

namespace Components
{

class Feature : public Application::Component
{
public:

	const std::string DISABLE_ADDS = "disable-adds";

	void initialize() override;
	bool has(const std::string & feature) const;
	bool value(const std::string & feature) const;
	void change(const std::string & feature, bool value);

private:

	friend class Storage;
	std::unordered_map<
		std::string,
		bool
	> _features;
};

}

#endif