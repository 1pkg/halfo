#include "Main.hpp"
#include "Scenes/Act.hpp"
#include "Components/Metric.hpp"

namespace Application
{

const Main &
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

	_metric = new Components::Metric(
		cocos2d::Director::getInstance()->getVisibleSize(),
		cocos2d::Director::getInstance()->getVisibleOrigin()
	);


    cocos2d::Director::getInstance()->setDisplayStats(true);
    cocos2d::Director::getInstance()->setAnimationInterval(1.0f / 30.0f);
    cocos2d::Director::getInstance()->runWithScene(Scenes::Act::instantiate());

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

const Components::Metric &
Main::metric() const
{
	return *_metric;
}

}