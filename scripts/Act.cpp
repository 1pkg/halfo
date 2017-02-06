#include "Act.hpp"

cocos2d::Scene *
Act::scene()
{
    cocos2d::Scene * scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0.0f, -100.0f));
    Act * layer = Act::create();
    scene->addChild(layer);
    return scene;
}

bool
Act::init()
{
	cocos2d::LayerColor::initWithColor(cocos2d::Color4B::GRAY);
	_transpoter.reset(new Transporter::Kit(this));
	_slicer.reset(new Slicer::Kit(this));
	_cleaner.reset(new Cleaner::Kit(this));
	schedule(schedule_selector(Act::update), 1.0f / 30.0f);
	return true;
}

Transporter::Kit *
Act::transpoter() const
{
	return _transpoter.get();
}

Slicer::Kit *
Act::slicer() const
{
	return _slicer.get();
}

Cleaner::Kit *
Act::cleaner() const
{
	return _cleaner.get();
}

void
Act::update(float dt)
{
	_transpoter->update(dt);
	_slicer->update(dt);
	_cleaner->update(dt);
}

