#ifndef COMPONENTS_DEPLOY
#define COMPONENTS_DEPLOY

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Deploy : public Application::Component
{
public:

    void initialize() override;
};

}

#endif