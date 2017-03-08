#include "Master.hpp"
#include "Scenes/Act.hpp"
#include "Scenes/Over.hpp"

bool
Master::applicationDidFinishLaunching()
{
    if(!cocos2d::Director::getInstance()->getOpenGLView())
		cocos2d::Director::getInstance()->setOpenGLView(cocos2d::GLViewImpl::create("halfo"));
	cocos2d::Director::getInstance()->setDisplayStats(true);
    cocos2d::Director::getInstance()->setAnimationInterval(1.0f / 30.0f);
	cocos2d::FileUtils::getInstance()->addSearchPath("assets");

	initialize();
	scene("Act");
    return true;
}

void
Master::applicationDidEnterBackground()
{
    cocos2d::Director::getInstance()->stopAnimation();
}

void
Master::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
}

void
Master::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

Master &
Master::instance()
{
	static Master & master = *dynamic_cast<Master *>(cocos2d::Application::getInstance());
	return master;
}

cocos2d::Scheduler *
Master::sheduler() const
{
	return cocos2d::Director::getInstance()->getScheduler();
}

void
Master::scene(const std::string & scene)
{
	
	if (scene == "Act")
	{
		cocos2d::Director::getInstance()->replaceScene(Scenes::Act::instantiate());
		return;
	}

	if (scene == "Over")
	{
		cocos2d::Director::getInstance()->replaceScene(Scenes::Over::instantiate());
		return;
	}

	if (scene == "Exit")
	{
		finitialize();
		cocos2d::Director::getInstance()->end();
		return;
	}
}

void
Master::initialize()
{
	std::vector<std::pair<std::string, std::unique_ptr<::Application::Component>>> components;
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"metric",
			std::move(std::unique_ptr<Components::Metric>(new Components::Metric(cocos2d::Director::getInstance()->getVisibleSize(), cocos2d::Director::getInstance()->getVisibleOrigin())))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"crypto",
			std::move(std::unique_ptr<Components::Crypto>(new Components::Crypto()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"setting",
			std::move(std::unique_ptr<Components::Setting>(new Components::Setting()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"statistic",
			std::move(std::unique_ptr<Components::Statistic>(new Components::Statistic()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"resource",
			std::move(std::unique_ptr<Components::Resource>(new Components::Resource()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"storage",
			std::move(std::unique_ptr<Components::Storage>(new Components::Storage()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"texture",
			std::move(std::unique_ptr<Components::Texture>(new Components::Texture()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"body",
			std::move(std::unique_ptr<Components::Body>(new Components::Body()))
		)
	);
	components.push_back(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"audio",
			std::move(std::unique_ptr<Components::Audio>(new Components::Audio()))
		)
	);
	for (std::vector<std::pair<std::string, std::unique_ptr<::Application::Component>>>::iterator it = components.begin(); it != components.end(); ++it)
	{
		it->second->initialize();
		_components.insert(std::pair<std::string, std::unique_ptr<::Application::Component>>(it->first, std::move(it->second)));
	}
}

void
Master::finitialize()
{
	for (std::unordered_map<std::string, std::unique_ptr<::Application::Component>>::iterator it = _components.begin(); it != _components.end(); ++it)
		it->second->finitialize();
}