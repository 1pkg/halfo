#ifndef APPLICATION_VIEW
#define APPLICATION_VIEW

#include "Wrapper.hpp"

namespace cocos2d
{
	class Vec2;
	class Size;
	class Node;
	class PhysicsBody;
	class Action;
}

namespace Application
{

class Scene;
class View : public Wrapper
{
public:

	virtual cocos2d::Node * node() const;
	virtual void attach(Scene * scene);
	virtual void run(cocos2d::Action * action);
	virtual cocos2d::PhysicsBody * body() const;
	virtual cocos2d::Vec2 getPosition() const;
	virtual void setPosition(cocos2d::Vec2 position);
	virtual float getRotation() const;
	virtual void setRotation(float angle);
	virtual cocos2d::Size getContentSize() const;
	virtual void setContentSize(cocos2d::Size size);
	virtual void setScale(float scale);
};

}

#endif