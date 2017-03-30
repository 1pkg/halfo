#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "include.hpp"
#include "functions.hpp"

namespace Components
{

class Resource : public Application::Component
{
public:

	enum class Type{SPRITEFRAME, BODY, AUDIO, FONT};
	static const char * Extension[];

	void initialize() override;
	const cocos2d::Data & get(const std::string & name, Type type, unsigned int number = 0);
	void walk(Type type, std::function<bool(const std::string &, const cocos2d::Data &)> callback);
	void walk(const std::string & name, std::function<bool(const std::string &, const cocos2d::Data &)> callback);

private:

	std::unordered_map<std::string, cocos2d::Data> _resources;
};

}

#endif