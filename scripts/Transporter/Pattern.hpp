#ifndef TRANSPORTER_PATTERN
#define TRANSPORTER_PATTERN

#include "Application/Wrapper.hpp"
#include <cocos2d.h>

namespace Transporter
{

class Pattern : public Application::Wrapper
{
public:

	static std::unique_ptr<Pattern> create(const std::string & name);
	const cocos2d::Vec2 * data() const;
	std::size_t size() const;

protected:

	Pattern(const std::vector<cocos2d::Vec2> & pattern);

private:

	std::vector<cocos2d::Vec2> _pattern;
};

}

#endif