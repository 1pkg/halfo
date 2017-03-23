#ifndef APPLICATION_OBJECT
#define APPLICATION_OBJECT

#include "Wrapper.hpp"
#include "View.hpp"

namespace Application
{

class Object : public Wrapper
{
public:

	virtual void run(const std::string & action) {}
	virtual Views::Object * view() const {return nullptr;}
};

}

#endif