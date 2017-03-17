#ifndef OBJECTS_HAMMER
#define OBJECTS_HAMMER

#include "include.hpp"
#include "Views/Hammer.hpp"

namespace Objects
{

class Hammer : public Application::Object
{
public:

	Hammer();
	Views::Hammer * view() const override;
	void upward();
	void downward();

private:

	std::unique_ptr<Views::Hammer> _view;
};

}

#endif