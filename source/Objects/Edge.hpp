#ifndef OBJECTS_EDGE
#define OBJECTS_EDGE

#include "include.hpp"
#include "Views/Edge.hpp"

namespace Objects
{

class Edge : public Application::Object
{
public:

	Edge();
	Views::Edge * view() const override;

private:

	std::unique_ptr<Views::Edge> _view;
};

}

#endif