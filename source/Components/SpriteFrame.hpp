#ifndef COMPONENTS_SPRITEFRAME
#define COMPONENTS_SPRITEFRAME

#include "include.hpp"

namespace Components
{

class SpriteFrame : public Application::Component
{
public:

	void initialize() override;
	cocos2d::SpriteFrame * get(const std::string & spriteFrame);

private:

	std::unordered_map<std::string, std::string> _spriteFrames;
};

}

#endif