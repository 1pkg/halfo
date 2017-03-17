#ifndef COMPONENTS_DEPLOY
#define COMPONENTS_DEPLOY

#include "include.hpp"

namespace Components
{

class Deploy : public Application::Component
{
public:

    void initialize() override;
};

}

#endif