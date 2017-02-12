#ifndef APPLICATION_PATTERN
#define APPLICATION_PATTERN

#include "Wrapper.hpp"
#include <cocos2d.h>

namespace Application
{

class Pattern : public Wrapper
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