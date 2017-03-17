#ifndef COMPONENTS_STORAGE
#define COMPONENTS_STORAGE

#include "include.hpp"

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