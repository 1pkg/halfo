#ifndef OBJECTS_OVER
#define OBJECTS_OVER

#include "include.hpp"
#include "Views/Over.hpp"

namespace Objects
{

class Over : public Application::Object
{
public:

	Over();
	Views::Over * view() const override;

private:

	std::unique_ptr<Views::Over> _view;
};

}

#endif