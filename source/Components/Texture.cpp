#include "Texture.hpp"

namespace Components
{

cocos2d::Texture2D *
Texture::get(const cocos2d::Data & data, const std::string & alias)
{
	cocos2d::Texture2D * texture = cocos2d::Director::getInstance()->getTextureCache()->getTextureForKey(alias);
	if (texture)
		return texture;

	cocos2d::Image * image = _images.find(alias) != _images.end() ? _images.at(alias).get() : nullptr;
	if (!image)
	{
		image = new cocos2d::Image();
		image->initWithImageData(data.getBytes(), data.getSize());
		_images.insert(std::pair<std::string, std::unique_ptr<cocos2d::Image>>(alias, std::move(std::unique_ptr<cocos2d::Image>(image))));
	}
	texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(image, alias);
	return texture;
}

}