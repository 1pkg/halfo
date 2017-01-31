#ifndef TRANSPORTER_PATTERN
#define TRANSPORTER_PATTERN

#include <cocos2d.h>

namespace Transporter
{

template <std::size_t _size>
class Pattern : protected entity
{
public:

	cocos2d::Vec2 at(std::size_t position) const;
	cocos2d::Vec2 operator[](std::size_t position) const;
	const cocos2d::Vec2 * data() const;
	std::size_t size() const;

protected:

	Pattern(std::array<cocos2d::Vec2, _size> pattern);

private:

	std::array<cocos2d::Vec2, _size> _pattern;
};

template <std::size_t _size>
cocos2d::Vec2
Pattern<_size>::at(std::size_t position) const
{
	return _pattern.at(position);
}

template <std::size_t _size>
cocos2d::Vec2
Pattern<_size>::operator[](std::size_t position) const
{
	return _pattern.at(position);
}

template <std::size_t _size>
const cocos2d::Vec2 *
Pattern<_size>::data() const
{
	return _pattern.data();
}

template <std::size_t _size>
std::size_t
Pattern<_size>::size() const
{
	return _pattern.size();
}

template<std::size_t _size>
Pattern<_size>::Pattern(std::array<cocos2d::Vec2, _size> pattern)
	: _pattern(pattern)
{}

using triangle = Pattern<3>;
using quadrangle = Pattern<4>;
using pentagon = Pattern<5>;
using hexagon = Pattern<6>;
using heptagon = Pattern<7>;
using octagon = Pattern<8>;

}

#endif