#ifndef OBJECTS_ANVIL
#define OBJECTS_ANVIL

#include "include.hpp"
#include "Views/Anvil.hpp"

namespace Objects
{

class Anvil : public Application::Object
{
public:

	Anvil();
	Views::Anvil * view() const override;

private:

	std::unique_ptr<Views::Anvil> _view;
};

}

#endif