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

	const float CLEAN_STEP = 10.0f;
	const unsigned int COMBO_PROOF = 2;
	const unsigned int SCALE_LIMIT = 5;

	Kit(Act * act);
	~Kit();
	void update(float delta) override;
	void attach(std::unique_ptr<Objects::Figure> figure);
    Objects::Figure * find(cocos2d::PhysicsBody * body);
	void increase();
	void reset();

private:

	void clean();
	bool contact(cocos2d::PhysicsContact & contact);
	unsigned int _scale, _combo, _result;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _lpool, _rpool;
	cocos2d::Node * _edge;
	cocos2d::Label * _score, * _multiply;
	cocos2d::EventListenerPhysicsContact * _sensor;
	Act * _act;
};

}

#endif