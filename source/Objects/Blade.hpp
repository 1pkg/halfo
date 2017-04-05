#ifndef OBJECTS_BLADE
#define OBJECTS_BLADE

#include "include.hpp"
#include "Views/Object/Blade.hpp"

namespace Objects
{

class Blade : public Application::Object
{
public:

	Blade();
	Views::Object::Blade * view() const override;
	void run(const std::string & action) override;

private:

	std::unique_ptr<Views::Object::Blade> _view;
};

}

#endif