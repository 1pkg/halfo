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
	act->initWithColor(cocos2d::Color4B::GRAY);
	act->setScale(0.7f);
	scene->addChild(act);

	act->_transpoter.reset(new Transporter::Kit(act));
	act->_slicer.reset(new Slicer::Kit(act));
	act->_cleaner.reset(new Cleaner::Kit(act));

	act->schedule(schedule_selector(Act::update), 1.0f / 30.0f);

    return scene;
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
Act::over()
{
	unschedule(schedule_selector(Act::update));
}

void
Act::update(float dt)
{
	_transpoter->update(dt);
	_slicer->update(dt);
	_cleaner->update(dt);
}

}