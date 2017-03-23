#ifndef PLAY_TRANSPORTER_PATTERN
#define PLAY_TRANSPORTER_PATTERN

#include "Application/Wrapper.hpp"
#include <cocos2d.h>

namespace Play
{

namespace Transporter
{

class Pattern : public Application::Wrapper
{
public:

	const cocos2d::Vec2 * data() const;
	std::size_t size() const;

protected:

	Pattern(const std::vector<cocos2d::Vec2> & pattern);

private:

	std::vector<cocos2d::Vec2> _pattern;
};

}

}

#endif