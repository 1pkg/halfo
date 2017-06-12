#ifndef COMPONENTS_TRIANGULATOR
#define COMPONENTS_TRIANGULATOR

#include "include.hpp"

namespace Components
{

class Triangulator : public Application::Component
{
public:

	std::vector<cocos2d::Triangle> triangulate(const cocos2d::Polygon & polygon) const;
};

}

#endif