#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "Application/Component.hpp"
#include "Audio.hpp"
#include "Font.hpp"
#include <cocos2d.h>

namespace Components
{

class Resource : public Application::Component
{
public:

	enum class Type {TEXTURE = 1, BODY, AUDIO, FONT};
	void initialize() override;
	const cocos2d::Data & get(const std::string & resource, Type type);

private:

	friend Audio;
	friend Font;
	struct typehash
	{
		std::size_t operator() (const std::pair<std::string, Type> & pair) const
		{
			return std::hash<std::string>{}(pair.first) ^ std::hash<Type>{}(pair.second);
		}
	};
	cocos2d::Data fetch(const std::string & resource, Type type);
	std::vector<std::tuple<std::string, Type, std::string, std::string>> unserialize(const cocos2d::Data & data);
	std::string hash(const cocos2d::Data & resource);
	std::string hashpad(const std::string & hash);
	std::string hashtrim(const std::string & hash);
	std::unordered_map<std::pair<std::string, Type>, cocos2d::Data, typehash> _resources;
};

}

#endif