#include "Main.hpp"
#include "Scenes/Act.hpp"
#include "Scenes/Over.hpp"

namespace Application
{

Main &
Main::instance()
{
	return *dynamic_cast<Main *>(cocos2d::Application::getInstance());
}

void
Main::initGLContextAttrs()
{
    cocos2d::GLView::setGLContextAttrs(GLContextAttrs{8, 8, 8, 8, 24, 8});
}

bool
Main::applicationDidFinishLaunching()
{
    if(!cocos2d::Director::getInstance()->getOpenGLView())
		cocos2d::Director::getInstance()->setOpenGLView(
			cocos2d::GLViewImpl::create("halfo")
		);
	cocos2d::Director::getInstance()->setDisplayStats(true);
    cocos2d::Director::getInstance()->setAnimationInterval(1.0f / 30.0f);

	_metric.reset(
		new Components::Metric(
			cocos2d::Director::getInstance()->getVisibleSize(),
			cocos2d::Director::getInstance()->getVisibleOrigin()
		)
	);
	_integrity.reset(
		new Components::Integrity()
	);
	_storage.reset(
		new Components::Storage()
	);
	_resource.reset(
		new Components::Resource()
	);
	_integrity->pull();
	_storage->pull();
	_resource->pull();

    act();
    return true;
}

void
Main::applicationDidEnterBackground()
{
    cocos2d::Director::getInstance()->stopAnimation();
}

void
Main::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
}

void
Main::act()
{
	cocos2d::Director::getInstance()->replaceScene(Scenes::Act::instantiate());
}

void
Main::over()
{
	cocos2d::Director::getInstance()->replaceScene(Scenes::Over::instantiate());
}

void
Main::end()
{
	_storage->flush();
	_resource->flush();
	_integrity->flush();

	cocos2d::Director::getInstance()->end();
}

cocos2d::Scheduler *
Main::sheduler() const
{
	return cocos2d::Director::getInstance()->getScheduler();
}

const Components::Metric &
Main::metric() const
{
	return *_metric;
}

Components::Storage &
Main::storage() const
{
	return *_storage;
}

const Components::Resource &
Main::resource() const
{
	return *_resource;
}

Components::Integrity &
Main::integrity() const
{
	return *_integrity;
}

}