#include "Act.h"
#include "Transporter/Kit.hpp"

cocos2d::Scene* Act::scene()
{
    cocos2d::Scene * scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0.0f, -100.0f));
    Act * layer = Act::create();
    scene->addChild(layer);
    return scene;
}

bool Act::init()
{
	cocos2d::LayerColor::initWithColor(cocos2d::Color4B::GRAY);
	_contours.reset(new Transporter::Kit(this));
	schedule(schedule_selector(Act::updater), 1.0f / 30.0f);
	return true;
}

void
Act::updater(float dt)
{
	_contours->update(dt);
}

