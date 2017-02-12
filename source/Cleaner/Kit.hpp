#ifndef CLEANER_KIT
#define CLEANER_KIT

#include "include.hpp"

namespace Application{class Act;}
namespace Objects{class Figure;}
namespace Cleaner
{

class Kit : public Application::Kit
{
public:

	Kit(Application::Act * act);
	~Kit();
	void update(float delta) override;
	void attach(std::unique_ptr<Objects::Figure> figure);
    Objects::Figure * find(cocos2d::PhysicsBody * body);
	void increase();
	void reset();

private:

	const float EDGE_STEP = 10.0f;
	const float EDGE_STEP_TIME = 0.5f;
	const unsigned int COMBO_PROOF = 2;
	const unsigned int SCALE_LIMIT = 5;
	const std::string FONT_NAME = "sexy.ttf";
	const float FONT_SIZE = 32.0f;

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
	Application::Act * _act;
};

}

#endif