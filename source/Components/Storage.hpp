#ifndef COMPONENTS_STORAGE
#define COMPONENTS_STORAGE

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Storage : public Application::Component
{
public:

	void initialize() override;
	void finitialize() override;

private:

	cocos2d::Data serialize() const;
	bool unserialize(const cocos2d::Data & data);
};

}

#endif