#ifndef OBJECTS_PLATFORM
#define OBJECTS_PLATFORM

#include "include.hpp"
#include "Views/Object/Platform.hpp"

namespace Objects
{

class Platform : public Application::Object
{
public:

	Platform();
	Views::Object::Platform * view() const override;
	void run(const std::string & action) override;

private:

	std::unique_ptr<Views::Object::Platform> _view;
};

}

#endif