#ifndef OBJECTS_FIGURE
#define OBJECTS_FIGURE

#include "Application/Object.hpp"
#include "Views/Figure.hpp"
#include <cocos2d.h>

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
		cocos2d::PhysicsMaterial material,
		bool hollow = true
	);
	Views::Figure * view() const override;
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
	cocos2d::PhysicsMaterial _material;
	bool _hollow;
	std::unique_ptr<Views::Figure> _view;
};

}

#endif