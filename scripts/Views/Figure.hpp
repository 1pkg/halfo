#ifndef VIEWS_FIGURE
#define VIEWS_FIGURE

#include "Application\View.hpp"
#include <cocos2d.h>

namespace Views
{

class Figure : public Application::View
{
public:

	Figure(
		std::vector<cocos2d::Vec2> pattern,
		cocos2d::Color4F color,
		cocos2d::PhysicsMaterial material,
		bool hollow
	);
	~Figure();
	void setHollow(bool hollow);
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;
	cocos2d::Vec2 getPosition() const;
	void setPosition(cocos2d::Vec2 position);

private:

	cocos2d::DrawNode * _node;
};

}

#endif