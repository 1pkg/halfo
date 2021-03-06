#ifndef APPLICATION_COMPONENT
#define APPLICATION_COMPONENT

#include "Wrapper.hpp"

namespace Application
{

class Component : public Wrapper
{
public:

	virtual void initialize();
	virtual void finitialize();
};

}

#endif