#ifndef OBJECTS_FIGURE
#define OBJECTS_FIGURE

#include "Application/Object.hpp"
#include <cocos2d.h>

namespace Views{class Figure;}

namespace Objects
{

class Figure : public Application::Object
{
public:

	Figure(
		std::vector<cocos2d::Vec2> pattern,
		cocos2d::Color4F color,
		cocos2d::PhysicsMaterial material,
		bool hollow = true
	);
	Application::View * render() override;
	Views::Figure * view() const;
	bool intersect(std::pair<cocos2d::Vec2, cocos2d::Vec2> line) const;
	std::pair<
		std::unique_ptr<Figure>,
		std::unique_ptr<Figure>
	> slice(std::pair<cocos2d::Vec2, cocos2d::Vec2> line) const;
	void fill();

private:

	std::vector<cocos2d::Vec2> _pattern;
	cocos2d::Color4F _color;
	cocos2d::PhysicsMaterial _material;
	bool _hollow;
	std::unique_ptr<Views::Figure> _view;
};

}

#endif