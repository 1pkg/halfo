#ifndef OBJECTS_FIGURE
#define OBJECTS_FIGURE

#include "include.hpp"
#include "Views/Object/Figure.hpp"

namespace Objects
{

class Figure : public Application::Object
{
public:

	Figure(const cocos2d::Polygon & pattern, float angle = 0.0f, bool hollow = true);
	Views::Object::Figure * view() const override;
	const std::vector<cocos2d::Vec2> & pattern() const;
	void fill();

private:

	std::vector<cocos2d::Vec2> _pattern;
	bool _hollow;
	std::unique_ptr<Views::Object::Figure> _view;
};

}

#endif