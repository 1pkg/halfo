#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "include.hpp"
#include "functions.hpp"

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
	std::unordered_map<std::pair<std::string, Type>, cocos2d::Data, unorderedhash> _resources;
};

}

#endif