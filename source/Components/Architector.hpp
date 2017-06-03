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
};

}

#endif