#ifndef VIEWS_FIGURE
#define VIEWS_FIGURE

#include "include.hpp"

namespace Views
{

class Figure : public Application::View
{
public:

	Figure(
		const cocos2d::Vec2 * pattern,
		std::size_t size,
		cocos2d::Color4F color,
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

	const float LINE_WIDHT = 1.0f;
	const float LINEAR_VELOCITY_LIMIT = 500.0f;
	const float ANGULAR_VELOCITY_LIMIT = 5.0f;

	cocos2d::DrawNode * _node;
};

}

#endif