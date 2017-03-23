#ifndef OBJECTS_EDGE
#define OBJECTS_EDGE

#include "include.hpp"
#include "Views/Object/Edge.hpp"

namespace Objects
{

class Edge : public Application::Object
{
public:

	Edge();
	Views::Object::Edge * view() const override;

private:

	std::unique_ptr<Views::Object::Edge> _view;
};

}

#endif