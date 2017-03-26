#ifndef COMPONENTS_SHARE
#define COMPONENTS_SHARE

#include "include.hpp"

namespace Components
{

class Share : public Application::Component
{
public:

    void initialize() override;
	void share(const std::string & platform) const;
};

}

#endif