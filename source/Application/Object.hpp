#ifndef APPLICATION_OBJECT
#define APPLICATION_OBJECT

#include "Wrapper.hpp"
#include <string>

namespace Application
{

class View;
class Object : public Wrapper
{
public:

	virtual void run(const std::string & action);
	virtual View * view() const;
};

}

#endif