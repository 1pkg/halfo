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

	float STEP = 10.0f;

	Kit(Act * act);
	~Kit();
	void update(float delta) override;
	void attach(std::unique_ptr<Objects::Figure> figure);
	void grow();
	void drop();

private:

	float _limit;
	float _current;
	unsigned int _combo;
	std::vector<std::unique_ptr<Objects::Figure>> _pool;
	cocos2d::Node * _node;
	Act * _act;
};

}

#endif