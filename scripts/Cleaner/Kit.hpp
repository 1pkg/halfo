#ifndef CLEANER_KIT
#define CLEANER_KIT

#include "Application/Kit.hpp"
#include <cocos2d.h>

class Act;
namespace Objects{class Figure;}
namespace Cleaner
{

class Kit : public Application::Kit
{
public:

	Kit(Act * act);
	~Kit();
	void update(float delta) override;

private:

	Act * _act;
};

}

#endif