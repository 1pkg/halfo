#ifndef OBJECTS_OVER
#define OBJECTS_OVER

#include "include.hpp"
#include "Views/Object/Over.hpp"

namespace Objects
{

class Over : public Application::Object
{
public:

	Over();
	Views::Object::Over * view() const override;

private:

	std::unique_ptr<Views::Object::Over> _view;
};

}

#endif