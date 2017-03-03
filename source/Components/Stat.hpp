#ifndef COMPONENTS_STAT
#define COMPONENTS_STAT

#include "Application/Component.hpp"
#include <vector>

namespace Components
{

class Stat : public Application::Component
{
public:

	void initialize() override;
	unsigned int total(std::size_t position);

private:

	friend class Storage;
	unsigned int _total;
};

}

#endif