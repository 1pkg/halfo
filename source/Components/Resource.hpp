#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Resource : public Application::Component
{
public:

	enum class Type {TEXTURE = 1, BODY, AUDIO, FONT};

	void initialize() override;
	const cocos2d::Data & get(const std::string & resource, Type type);
	void walk(Type type, std::function<bool(const std::string &, const cocos2d::Data &)> callback);

private:

	void unserialize(const cocos2d::Data & data);
	std::unordered_map<std::string, std::vector<std::pair<Type, cocos2d::Data>>> _resources;
};

}

#endif