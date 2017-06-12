#ifndef COMPONENTS_ARCHITECTOR
#define COMPONENTS_ARCHITECTOR

#include "include.hpp"

namespace Objects
{
	class Figure;
}

namespace Components
{

class Architector : public Application::Component
{
public:

	std::unique_ptr<Objects::Figure> provide();

private:

	static cocos2d::Polygon generate(const cocos2d::Size & boundary);
};

}

#endif