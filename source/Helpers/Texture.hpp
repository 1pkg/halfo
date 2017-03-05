#ifndef HELPERS_TEXTURE
#define HELPERS_TEXTURE

#include <cocos2d.h>

namespace Helpers
{

class Texture
{
public:

	static Texture & intance();
	cocos2d::Texture2D * get(const std::string & alias, const cocos2d::Data & data);

private:

	Texture();
	std::unordered_map<std::string, std::unique_ptr<cocos2d::Image>> _images;
};

}

#endif