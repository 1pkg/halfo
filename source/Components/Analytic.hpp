#ifndef COMPONENTS_ANALYTIC
#define COMPONENTS_ANALYTIC

#include "include.hpp"

namespace Components
{

class Analytic : public Application::Component
{
public:

    void initialize() override;
	void track(const std::string & category, const std::string & action, const std::string & label, int value);
};

}

#endif