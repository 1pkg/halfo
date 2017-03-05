#include "Master.hpp"
#include "Scenes/Act.hpp"
#include "Scenes/Over.hpp"
#include "Components/Metric.hpp"
#include "Components/Setting.hpp"
#include "Components/Statistic.hpp"
#include "Components/Storage.hpp"
#include "Components/Resource.hpp"

bool
Master::applicationDidFinishLaunching()
{
    if(!cocos2d::Director::getInstance()->getOpenGLView())
		cocos2d::Director::getInstance()->setOpenGLView(cocos2d::GLViewImpl::create("halfo"));
	cocos2d::Director::getInstance()->setDisplayStats(true);
    cocos2d::Director::getInstance()->setAnimationInterval(1.0f / 30.0f);

	components();
	change("Act");
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
    cocos2d::GLView::setGLContextAttrs(GLContextAttrs{8, 8, 8, 8, 24, 8});
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

const Components::Metric &
Master::metric() const
{
	static Components::Metric & metric = *dynamic_cast<Components::Metric *>(_components.at("metric").get());
	return metric;
}

Components::Setting &
Master::setting() const
{
	static Components::Setting & setting = *dynamic_cast<Components::Setting *>(_components.at("setting").get());
	return setting;
}

Components::Statistic &
Master::statistic() const
{
	static Components::Statistic & statistic = *dynamic_cast<Components::Statistic *>(_components.at("statistic").get());
	return statistic;
}

Components::Resource &
Master::resource() const
{
	static Components::Resource & resource = *dynamic_cast<Components::Resource *>(_components.at("resource").get());
	return resource;
}

void
Master::change(const std::string & scene)
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
}

void
Master::end()
{
	(*dynamic_cast<Components::Storage *>(_components.at("storage").get())).flush();
	cocos2d::Director::getInstance()->end();
}

void
Master::components()
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
	for (std::vector<std::pair<std::string, std::unique_ptr<::Application::Component>>>::iterator it = components.begin(); it != components.end(); ++it)
	{
		it->second->initialize();
		_components.insert(std::pair<std::string, std::unique_ptr<::Application::Component>>(it->first, std::move(it->second)));
	}
}