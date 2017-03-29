#ifndef COMPONENTS_PURCHASE
#define COMPONENTS_PURCHASE

#include "include.hpp"

namespace Components
{

class Purchase : public Application::Component
{
public:

    void initialize() override;
	void purchase(const std::string & item);
};

}

#endif