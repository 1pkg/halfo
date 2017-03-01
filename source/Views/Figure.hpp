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
		bool hollow
	);
	~Figure();
	void attach(cocos2d::Layer * layer) override;
	cocos2d::PhysicsBody * body() const;
	cocos2d::Vec2 getPosition() const;
	void setPosition(cocos2d::Vec2 position);
	float getRotation() const;
	void setRotation(float angle) const;

private:

	cocos2d::DrawNode * _node;
};

}

#endif