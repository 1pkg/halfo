#include "Over.hpp"

namespace Objects
{

Over::Over()
	: _view(new Views::Over())
{
}

Views::Over *
Over::view() const
{
	return _view.get();
}

}