#ifndef APPLICATION_KIT
#define APPLICATION_KIT

#include "Wrapper.hpp"
#include <functional>

namespace Application
{

class Object;
class Kit : public Wrapper
{
public:

	virtual void update(float delta);
	virtual void walk(std::function<bool(const Object *)> callback);
};

}

#endif