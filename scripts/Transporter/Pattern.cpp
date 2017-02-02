#include "Pattern.hpp"
#include "Patterns/Triangle.hpp"
#include "Patterns/Quadrangle.hpp"
#include "Patterns/Pentagon.hpp"

namespace Transporter
{

std::vector<std::string>
Pattern::names =
{
	"triangle",
//	"quadrangle",
//	"pentagon"
};

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