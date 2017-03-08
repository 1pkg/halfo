#ifndef COMPONENTS_TEXTURE
#define COMPONENTS_TEXTURE

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class Texture : public Application::Component
{
public:

	void initialize() override;
	cocos2d::Texture2D * get(const std::string & alias, const cocos2d::Data & data);

private:

	std::unordered_map<std::string, std::unique_ptr<cocos2d::Image>> _images;
};

}

#endif