#include "Act.hpp"

namespace Scenes
{

cocos2d::Scene *
Act::instantiate()
{
    cocos2d::Scene * scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0.0f, -100.0f));
	Act * act = new Act();
	act->autorelease();
	scene->addChild(act);
    return scene;
}

Act::Act()
	: _time(0),
	_transpoter(new Transporter::Kit(this)),
	_slicer(new Slicer::Kit(this)),
	_cleaner(new Cleaner::Kit(this))
{
	initWithColor(cocos2d::Color4B::GRAY);
	setScale(0.7f);

	_time = 0;
	schedule(
		schedule_selector(Act::update),
		1.0f / 30.0f
	);
}

Act::~Act()
{
	unschedule(
		schedule_selector(Act::update)
	);
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
	static float time = 0.0f;
	time += dt;
	_time = (unsigned int) time;

	_transpoter->update(dt);
	_slicer->update(dt);
	_cleaner->update(dt);
}

}