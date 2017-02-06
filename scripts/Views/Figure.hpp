#ifndef VIEWS_FIGURE
#define VIEWS_FIGURE

#include "Application/View.hpp"
#include <cocos2d.h>

namespace Views
{

class Figure : public Application::View
{
public:

	const float LINE_WIDHT = 3.0f;
	const float LINEAR_VELOCITY_LIMIT = 500.0f;
	const float ANGULAR_VELOCITY_LIMIT = 5.0f;

	Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		cocos2d::Color4F color,
		cocos2d::PhysicsMaterial material,
		bool hollow
	);
	~Figure();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;
	cocos2d::Vec2 getPosition() const;
	void setPosition(cocos2d::Vec2 position);
	float getRotation() const;
	void setRotation(float angle) const;
	void setHollow(bool hollow);

private:

	cocos2d::DrawNode * _node;
};

}

#endif