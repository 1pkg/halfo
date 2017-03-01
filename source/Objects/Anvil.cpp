#include "Anvil.hpp"

namespace Objects
{

Anvil::Anvil()
	: _view(new Views::Anvil())
{
}

Views::Anvil *
Anvil::view() const
{
	return _view.get();
}

}