#include "constants.hpp"
#include "File.hpp"
#include "Resource.hpp"
#include "SpriteFrame.hpp"

namespace Components
{

void
SpriteFrame::initialize()
{
	std::function<bool(const std::string &, const cocos2d::Data &)> callback =
	[this](const std::string & origin, const cocos2d::Data & data)
	{
		std::string spriteFrame = Master::instance().get<File>().cache(data);
		_spriteFrames.insert(std::pair<std::string, std::string>(replace(origin, Resource::Extension[(unsigned int)Resource::Type::SPRITEFRAME], ""), spriteFrame));
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(cocos2d::SpriteFrame::create(spriteFrame, cocos2d::Rect(cocos2d::Vec2::ZERO, COMMON_TEXTURE_SIZE)), replace(origin, Resource::Extension[(unsigned int)Resource::Type::SPRITEFRAME], ""));
		return true;
	};
	Master::instance().get<Components::Resource>().walk(Resource::Type::SPRITEFRAME, callback);
}

cocos2d::SpriteFrame *
SpriteFrame::get(const std::string & spriteFrame)
{
	std::unordered_map<std::string, std::string>::const_iterator it = _spriteFrames.find(spriteFrame);
	if (it == _spriteFrames.end())
		return nullptr;

	return cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrame);
}

}