#ifndef APPLICATION_OBJECT
#define APPLICATION_OBJECT

#include "Wrapper.hpp"

namespace Application
{

class View;
class Object : public Wrapper
{
public:

	virtual View * view() const {return nullptr;}
};

}

#endif