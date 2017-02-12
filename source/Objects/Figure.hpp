#ifndef OBJECTS_FIGURE
#define OBJECTS_FIGURE

#include "include.hpp"
#include "Views/Figure.hpp"

namespace Objects
{

class Figure : public Application::Object
{
public:

	const float DELTA = 0.001f;

	Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		cocos2d::Color4F color,
		bool hollow = true
	);
	Views::Figure * view() const override;
	float area() const;
	bool intersect(const std::pair<cocos2d::Vec2, cocos2d::Vec2> & line) const;
	std::pair<
		std::unique_ptr<Figure>,
		std::unique_ptr<Figure>
	> slice(const std::pair<cocos2d::Vec2, cocos2d::Vec2> & line) const;
	void fill();

private:

	std::vector<cocos2d::Vec2>
		rotate(const std::vector<cocos2d::Vec2> & vector) const;
	std::vector<cocos2d::Vec2> _pattern;
	cocos2d::Color4F _color;
	bool _hollow;
	std::unique_ptr<Views::Figure> _view;
};

}

#endif