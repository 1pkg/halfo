#ifndef CLEANER_KIT
#define CLEANER_KIT

#include "include.hpp"

namespace Scenes{class Act;}
namespace Objects{class Figure;}
namespace Cleaner
{

class Kit : public Application::Kit
{
public:

	Kit(Scenes::Act * act);
	~Kit();
	void update(float delta) override;
	void attach(std::unique_ptr<Objects::Figure> figure);
    Objects::Figure * find(cocos2d::PhysicsBody * body) const;
	void increase();
	void reset();

private:

	const float
		EDGE_STEP = 30.0f,
		EDGE_STEP_TIME = 1.0f;
	const unsigned int
		COMBO_LIMIT = 12,
		COMBO_PROOF = 3,
		SCALE_KOEFICIENT = 2;
	const std::pair<unsigned int, unsigned int>
		FIGURE_BURN_LIMIT = std::pair<unsigned int, unsigned int>(1, 3);
	const std::string FONT_NAME = "font.ttf";
	const float FONT_SIZE = 32.0f;
	const float DELTA = 0.01f;
	const float INSPECTION_TIME = 2.0f;

	unsigned int scale() const;
	void clean();
	void inspection() const;
	bool contact(cocos2d::PhysicsContact & contact) const;
	unsigned int _combo, _result;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _lpool, _rpool;
	cocos2d::DrawNode * _platfrom, * _over;
	cocos2d::Label * _score;
	cocos2d::EventListenerPhysicsContact * _sensor;
	Scenes::Act * _act;
};

}

#endif