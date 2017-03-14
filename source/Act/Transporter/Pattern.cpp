#include "Pattern.hpp"

namespace Act
{

namespace Transporter
{

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

}