#ifndef COMPONENTS_STORAGE
#define COMPONENTS_STORAGE

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class Storage : public Application::Component
{
public:

	void initialize() override;
	void flush() const;
	void pull();

private:

	cocos2d::Data serialize() const;
	bool unserialize(const cocos2d::Data & buffer);
	std::string _path;
};

}

#endif