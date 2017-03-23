#include "Anvil.hpp"

namespace Objects
{

Anvil::Anvil()
	: _view(new Views::Object::Anvil())
{
}

Views::Object::Anvil *
Anvil::view() const
{
	return _view.get();
}

}