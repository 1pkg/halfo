#include "Pattern.hpp"
#include "Patterns/Triangle.hpp"
#include "Patterns/Quadrangle.hpp"
#include "Patterns/Pentagon.hpp"
#include "Patterns/Hexagon.hpp"
#include "Patterns/Heptagon.hpp"
#include "Patterns/Octagon.hpp"
#include "Patterns/Enneagon.hpp"
#include "Patterns/Decagon.hpp"

namespace Application
{

std::unique_ptr<Pattern>
Pattern::create(const std::string & name)
{
	using namespace Patterns;

	if (name == "triangle")
		return std::unique_ptr<Pattern>(new Triangle());

	if (name == "quadrangle")
		return std::unique_ptr<Pattern>(new Quadrangle());

	if (name == "pentagon")
		return std::unique_ptr<Pattern>(new Pentagon());

	if (name == "hexagon")
		return std::unique_ptr<Pattern>(new Hexagon());

	if (name == "heptagon")
		return std::unique_ptr<Pattern>(new Heptagon());

	if (name == "octagon")
		return std::unique_ptr<Pattern>(new Octagon());

	if (name == "enneagon")
		return std::unique_ptr<Pattern>(new Enneagon());

	if (name == "decagon")
		return std::unique_ptr<Pattern>(new Decagon());

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