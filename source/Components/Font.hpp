#ifndef COMPONENTS_FONT
#define COMPONENTS_FONT

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class Font : public Application::Component
{
public:

    void initialize() override;
	std::string get() const;

private:

	std::string _cache;
};

}

#endif