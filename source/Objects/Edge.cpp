#include "Edge.hpp"

namespace Objects
{

Edge::Edge()
	: _view(new Views::Edge())
{
}

Views::Edge *
Edge::view() const
{
	return _view.get();
}

}