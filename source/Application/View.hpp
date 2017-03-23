#ifndef APPLICATION_VIEW
#define APPLICATION_VIEW

#include "Wrapper.hpp"
#include "Scene.hpp"
#include <cocos2d.h>

namespace Application
{

template<bool UI>
class View : public Wrapper
{
public:

	View(cocos2d::Node * node) : _node(node) {}
	~View() override {if(_node)_node->removeFromParentAndCleanup(true);}
	virtual void attach(Scene * scene) {if(_node && !_node->getParent())scene->add(_node, UI);}
	virtual cocos2d::Vec2 getPosition() const {return _node ? _node->getPosition() : cocos2d::Vec2::ZERO;}
	virtual void setPosition(cocos2d::Vec2 position) {if(_node)_node->setPosition(position);}
	virtual float getRotation() const {return _node ? _node->getRotation() : 0.0f;}
	virtual void setRotation(float angle) const {if(_node)_node->setRotation(angle);}

protected:

	cocos2d::Node * _node;
};

namespace Views
{

class Object : public View<false>
{
public:

	Object() : View<false>(nullptr) {}
	virtual cocos2d::PhysicsBody * body() const {return _node ? _node->getPhysicsBody() : nullptr;}
	virtual void run(cocos2d::Action * action) {if(_node)_node->runAction(action);}
};

class Ui : public View<true>
{
public:

	Ui() : View<true>(nullptr) {}
};

}

}

#endif