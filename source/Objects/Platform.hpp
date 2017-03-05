#ifndef OBJECTS_PLATFORM
#define OBJECTS_PLATFORM

#include "include.hpp"
#include "Views/Platform.hpp"

namespace Objects
{

class Platform : public Application::Object
{
public:

	Platform();
	Views::Platform * view() const override;
	void upward();
	void downward();

private:

	const float EDGE_STEP = 30.0f, EDGE_STEP_TIME = 1.0f;
	std::unique_ptr<Views::Platform> _view;
};

}

#endif