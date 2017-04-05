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
		std::string alias = replace(origin, Resource::Extension[(unsigned int)Resource::Type::SPRITEFRAME], "");

		std::string cache = Master::instance().get<File>().cache(data);
		_spriteFrames.insert(std::pair<std::string, std::string>(alias, cache));
		cocos2d::SpriteFrame * spriteFrame = cocos2d::SpriteFrame::create(cache, cocos2d::Rect(cocos2d::Vec2::ZERO, COMMON_TEXTURE_SIZE));
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, alias);
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