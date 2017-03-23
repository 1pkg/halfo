#ifndef OBJECTS_HAMMER
#define OBJECTS_HAMMER

#include "include.hpp"
#include "Views/Object/Hammer.hpp"

namespace Objects
{

class Hammer : public Application::Object
{
public:

	Hammer();
	Views::Object::Hammer * view() const override;
	void run(const std::string & action) override;

private:

	std::unique_ptr<Views::Object::Hammer> _view;
};

}

#endif