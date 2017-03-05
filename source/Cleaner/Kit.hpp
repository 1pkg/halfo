#ifndef CLEANER_KIT
#define CLEANER_KIT

#include "include.hpp"

namespace Scenes{class Act;}
namespace Objects{class Figure; class Platform; class Over;}
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

	const unsigned int COMBO_LIMIT = 12, COMBO_PROOF = 3, SCALE_KOEFICIENT = 2;
	const std::pair<unsigned int, unsigned int> FIGURE_CLEAN_LIMIT = std::pair<unsigned int, unsigned int>(1, 3);
	const float REST_SPEAD_DELTA = 0.01f;
	const float INSPECTION_TIME = 0.5f;

	unsigned int scale() const;
	void clean();
	void inspection(float delta);
	bool contact(cocos2d::PhysicsContact & contact) const;
	unsigned int _combo, _result, _time;
	cocos2d::Label * _score;
	std::unordered_map<
		cocos2d::PhysicsBody *,
		std::unique_ptr<Objects::Figure>
	> _pool;
	std::unique_ptr<Objects::Platform> _platform;
	std::unique_ptr<Objects::Over> _over;
	cocos2d::EventListenerPhysicsContact * _sensor;
	Scenes::Act * _act;
};

}

#endif