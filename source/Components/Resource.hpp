#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class Resource : public Application::Component
{
public:

	void initialize() override;
	const cocos2d::Data & get(const std::string & resource);

private:

	friend class Storage;
	std::unordered_map<
		std::string,
		cocos2d::Data
	> _resources;
};

}

#endif