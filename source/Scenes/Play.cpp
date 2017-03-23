#include "components.hpp"
#include "Play.hpp"

namespace Scenes
{

Play::Play()
	: Application::Scene(cocos2d::Scene::createWithPhysics()),
	_transpoter(new Transporter::Kit(this)),
	_slicer(new Slicer::Kit(this)),
	_cleaner(new Cleaner::Kit(this))
{
	_scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	_scene->getPhysicsWorld()->setGravity(Master::instance().get<Components::Metric>().absolute(GRAVITY_FORCE));
	_play->setScale(0.7f);
	_scene->schedule(std::bind(&Play::update, this, std::placeholders::_1), UPDATE_TIME, "Scenes::Play::update");
}

Play::~Play()
{
	_scene->unschedule("Scenes::Play::update");
}

Transporter::Kit *
Play::transpoter() const
{
	return _transpoter.get();
}

Slicer::Kit *
Play::slicer() const
{
	return _slicer.get();
}

Cleaner::Kit *
Play::cleaner() const
{
	return _cleaner.get();
}

void
Play::update(float delta)
{
	_transpoter->update(delta);
	_slicer->update(delta);
	_cleaner->update(delta);
}

}