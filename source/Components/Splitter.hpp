#ifndef COMPONENTS_SPLITTER
#define COMPONENTS_SPLITTER

#include "include.hpp"

namespace Objects
{
	class Figure;
}

namespace Components
{

class Splitter : public Application::Component
{
public:

	std::vector<std::unique_ptr<Objects::Figure>> split(const Objects::Figure * figure, const cocos2d::Line & line);

private:

	static cocos2d::Polygon rotate(const cocos2d::Polygon & vector, float angle);
};

}

#endif