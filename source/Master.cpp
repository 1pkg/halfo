#include "Components/Metric.hpp"
#include "Components/File.hpp"
#include "Components/Setting.hpp"
#include "Components/Statistic.hpp"
#include "Components/Storage.hpp"
#include "Components/Deploy.hpp"
#include "Components/Resource.hpp"
#include "Components/Crypto.hpp"
#include "Components/SpriteFrame.hpp"
#include "Components/Body.hpp"
#include "Components/Audio.hpp"
#include "Components/Font.hpp"
#include "Components/Share.hpp"
#include "Components/Notification.hpp"
#include "Components/Analytic.hpp"
#include "Components/Ad.hpp"
#include "Components/Purchase.hpp"
#include "Components/Architector.hpp"
#include "Components/Triangulator.hpp"
#include "Components/Splitter.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Play.hpp"
#include "Scenes/Over.hpp"
#include "Master.hpp"

const std::string Master::SCENE_MENU = "menu";
const std::string Master::SCENE_PLAY = "play";
const std::string Master::SCENE_OVER = "over";
const std::string Master::SCENE_EXIT = "exit";

bool
Master::applicationDidFinishLaunching()
{
    if(!cocos2d::Director::getInstance()->getOpenGLView())
		cocos2d::Director::getInstance()->setOpenGLView(cocos2d::GLViewImpl::create("halfo"));
	cocos2d::Director::getInstance()->setDisplayStats(true);
    cocos2d::Director::getInstance()->setAnimationInterval(1.0f / 30.0f);

	initialize();
	scene(SCENE_MENU);
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
	static std::unique_ptr<::Application::Scene> ptr;
	if (scene == SCENE_MENU)
	{
		ptr.reset(new Scenes::Menu());
		return cocos2d::Director::getInstance()->replaceScene(*ptr);
	}
	
	if (scene == SCENE_PLAY)
	{
		ptr.reset(new Scenes::Play());
		return cocos2d::Director::getInstance()->replaceScene(*ptr);
	}

	if (scene == SCENE_OVER)
	{
		ptr.reset(new Scenes::Over());
		return cocos2d::Director::getInstance()->replaceScene(*ptr);
	}

	if (scene == SCENE_EXIT)
	{
		finitialize();
		return cocos2d::Director::getInstance()->end();
	}
}

void
Master::initialize()
{
	using namespace Components;
	std::vector<std::pair<std::string, std::unique_ptr<::Application::Component>>> components;
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Metric).name(), std::move(std::unique_ptr<Metric>(new Metric()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(File).name(), std::move(std::unique_ptr<File>(new File()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Crypto).name(), std::move(std::unique_ptr<Crypto>(new Crypto()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Setting).name(), std::move(std::unique_ptr<Setting>(new Setting()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Statistic).name(), std::move(std::unique_ptr<Statistic>(new Statistic()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Storage).name(), std::move(std::unique_ptr<Storage>(new Storage()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Deploy).name(), std::move(std::unique_ptr<Deploy>(new Deploy()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Resource).name(),std::move(std::unique_ptr<Resource>(new Resource()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(SpriteFrame).name(), std::move(std::unique_ptr<SpriteFrame>(new SpriteFrame()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Body).name(), std::move(std::unique_ptr<Body>(new Body()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Audio).name(), std::move(std::unique_ptr<Audio>(new Audio()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Font).name(), std::move(std::unique_ptr<Font>(new Font()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Share).name(), std::move(std::unique_ptr<Share>(new Share()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Notification).name(), std::move(std::unique_ptr<Notification>(new Notification()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Analytic).name(), std::move(std::unique_ptr<Analytic>(new Analytic()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Ad).name(), std::move(std::unique_ptr<Ad>(new Ad()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Purchase).name(), std::move(std::unique_ptr<Purchase>(new Purchase()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Architector).name(), std::move(std::unique_ptr<Architector>(new Architector()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Triangulator).name(), std::move(std::unique_ptr<Triangulator>(new Triangulator()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Splitter).name(), std::move(std::unique_ptr<Splitter>(new Splitter()))));
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