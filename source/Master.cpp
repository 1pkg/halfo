#include "Master.hpp"
#include "Scenes/Act.hpp"
#include "Scenes/Over.hpp"
#include "Components/Metric.hpp"
#include "Components/Feature.hpp"
#include "Components/Setting.hpp"
#include "Components/Result.hpp"
#include "Components/Stat.hpp"
#include "Components/Storage.hpp"

bool
Master::applicationDidFinishLaunching()
{
    if(!cocos2d::Director::getInstance()->getOpenGLView())
		cocos2d::Director::getInstance()->setOpenGLView(
			cocos2d::GLViewImpl::create("halfo")
		);
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
	static Master & master =
		*dynamic_cast<Master *>(cocos2d::Application::getInstance());
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
	static Components::Metric & metric =
		*dynamic_cast<Components::Metric *>(_components.at("metric").get());
	return metric;
}

Components::Feature &
Master::feature() const
{
	static Components::Feature & feature =
		*dynamic_cast<Components::Feature *>(_components.at("feature").get());
	return feature;
}

Components::Setting &
Master::setting() const
{
	static Components::Setting & setting =
		*dynamic_cast<Components::Setting *>(_components.at("setting").get());
	return setting;
}

Components::Result &
Master::result() const
{
	static Components::Result & result =
		*dynamic_cast<Components::Result *>(_components.at("result").get());
	return result;
}

Components::Stat &
Master::stat() const
{
	static Components::Stat & stat =
		*dynamic_cast<Components::Stat *>(_components.at("stat").get());
	return stat;
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
	(*dynamic_cast<Components::Storage *>(_components.at("stat").get())).flush();
	cocos2d::Director::getInstance()->end();
}

void
Master::components()
{
	_components.insert(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"feature",
			std::move(std::unique_ptr<Components::Feature>(new Components::Feature()))
		)
	);
	_components.insert(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"setting",
			std::move(std::unique_ptr<Components::Setting>(new Components::Setting()))
		)
	);
	_components.insert(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"result",
			std::move(std::unique_ptr<Components::Result>(new Components::Result()))
		)
	);
	_components.insert(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"stat",
			std::move(std::unique_ptr<Components::Stat>(new Components::Stat()))
		)
	);
	for (std::unordered_map<std::string, std::unique_ptr<::Application::Component>>::iterator it = _components.begin(); it != _components.end(); ++it)
		it->second->initialize();

	std::unique_ptr<Components::Metric> metric(
		new Components::Metric(
			cocos2d::Director::getInstance()->getVisibleSize(),
			cocos2d::Director::getInstance()->getVisibleOrigin()
		)
	);
	metric->initialize();
	_components.insert(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"metric",
			std::move(metric)
		)
	);
	std::unique_ptr<Components::Storage> storage(
		new Components::Storage()
	);
	storage->initialize();
	storage->pull();
	_components.insert(
		std::pair<std::string, std::unique_ptr<::Application::Component>>(
			"storage",
			std::move(storage)
		)
	);
}