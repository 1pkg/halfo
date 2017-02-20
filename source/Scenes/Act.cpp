#include "Act.hpp"

namespace Scenes
{

cocos2d::Scene *
Act::instantiate()
{
    cocos2d::Scene * scene = cocos2d::Scene::createWithPhysics();
	Act * act = Act::create();
	scene->addChild(act);
	scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(
		Application::Main::instance().metric().absolute(act->GRAVITY)
	);
    return scene;
}

Act *
Act::create()
{
    Act * act = new (std::nothrow) Act();
    if (act && act->initWithColor(cocos2d::Color4B::GRAY))
        act->autorelease();
    else
        CC_SAFE_DELETE(act);
    return act;
}

Act::Act()
	: _transpoter(new Transporter::Kit(this)),
	_slicer(new Slicer::Kit(this)),
	_cleaner(new Cleaner::Kit(this))
{
	setScale(0.7f);

	schedule(
		schedule_selector(Act::update),
		UPDATE_TIME
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
Act::update(float delta)
{
	_transpoter->update(delta);
	_slicer->update(delta);
	_cleaner->update(delta);
}

}