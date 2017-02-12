#include "Main.hpp"
#include "Act.hpp"

namespace Application
{

void
Main::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

bool
Main::applicationDidFinishLaunching()
{
    cocos2d::Director * director = cocos2d::Director::getInstance();
    if(!director->getOpenGLView())
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		director->setOpenGLView(
			cocos2d::GLViewImpl::createWithRect("shredder", cocos2d::Rect(0, 0, 800, 480))
		);
#else
		director->setOpenGLView(
			cocos2d::GLViewImpl::create("")
		);
#endif
    }
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 30.0f);
    director->runWithScene(Act::scene());
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

}