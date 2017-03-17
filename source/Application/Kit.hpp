#ifndef APPLICATION_KIT
#define APPLICATION_KIT

#include "Wrapper.hpp"

namespace Application
{

class Kit : public Wrapper
{
public:

	virtual void update(float delta) {}
};

}

#endif