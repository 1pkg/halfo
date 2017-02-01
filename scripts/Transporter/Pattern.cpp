#include "Pattern.hpp"
#include "Patterns/RandomTriangle.hpp"

namespace Transporter
{

std::array<std::string, 1> Pattern::names =
	{
		"random-triangle"
	};

std::unique_ptr<Pattern>
Pattern::create(const std::string & name)
{
	using namespace Patterns;
	if (name == "random-triangle")
		return std::unique_ptr<Pattern>(new RandomTriangle());

	return nullptr;
}

const cocos2d::Vec2 *
Pattern::data() const
{
	return _pattern.data();
}

std::size_t
Pattern::size() const
{
	return _pattern.size();
}

Pattern::Pattern(const std::vector<cocos2d::Vec2> & pattern)
	: _pattern(pattern)
{
}

}