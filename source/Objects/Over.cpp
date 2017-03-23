#include "Over.hpp"

namespace Objects
{

Over::Over()
	: _view(new Views::Object::Over())
{
}

Views::Object::Over *
Over::view() const
{
	return _view.get();
}

}