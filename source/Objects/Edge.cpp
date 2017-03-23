#include "Edge.hpp"

namespace Objects
{

Edge::Edge()
	: _view(new Views::Object::Edge())
{
}

Views::Object::Edge *
Edge::view() const
{
	return _view.get();
}

}