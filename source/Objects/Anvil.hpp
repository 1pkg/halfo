#ifndef OBJECTS_ANVIL
#define OBJECTS_ANVIL

#include "include.hpp"
#include "Views/Object/Anvil.hpp"

namespace Objects
{

class Anvil : public Application::Object
{
public:

	Anvil();
	Views::Object::Anvil * view() const override;

private:

	std::unique_ptr<Views::Object::Anvil> _view;
};

}

#endif