#ifndef COMPONENTS_AD
#define COMPONENTS_AD

#include "include.hpp"

namespace Components
{

class Ad : public Application::Component
{
public:

    void initialize() override;
	void ad(const std::string & unit, const std::string & place);
	void placement(const std::string & placement);
};

}

#endif