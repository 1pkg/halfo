#ifndef OBJECTS_FIGURE
#define OBJECTS_FIGURE

#include "include.hpp"
#include "Views/Figure.hpp"

namespace Objects
{

class Hammer;
class Figure : public Application::Object
{
public:

	Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		bool hollow = true
	);
	Views::Figure * view() const override;
	float area() const;
	bool intersect(const std::array<cocos2d::Vec2, 2> & line) const;
	std::pair<
		std::unique_ptr<Figure>,
		std::unique_ptr<Figure>
	> slice(const std::array<cocos2d::Vec2, 2> & line) const;
	void fill();

private:

	const float SLICE_DELTA = 0.001f;

	std::vector<cocos2d::Vec2>
		rotate(const std::vector<cocos2d::Vec2> & vector) const;
	std::vector<cocos2d::Vec2> _pattern;
	bool _hollow;
	std::unique_ptr<Views::Figure> _view;
};

}

#endif