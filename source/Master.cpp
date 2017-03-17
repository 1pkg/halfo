#include "Components/Metric.hpp"
#include "Components/File.hpp"
#include "Components/Setting.hpp"
#include "Components/Statistic.hpp"
#include "Components/Storage.hpp"
#include "Components/Deploy.hpp"
#include "Components/Resource.hpp"
#include "Components/Crypto.hpp"
#include "Components/Texture.hpp"
#include "Components/Body.hpp"
#include "Components/Audio.hpp"
#include "Components/Font.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Act.hpp"
#include "Scenes/Settings.hpp"
#include "Scenes/Over.hpp"
#include "Master.hpp"

const std::string Master::SCENE_MENU = "menu";
const std::string Master::SCENE_ACT = "act";
const std::string Master::SCENE_SETTINGS = "settings";
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
	if (scene == SCENE_MENU)
	{
		cocos2d::Scene * scene = cocos2d::Scene::create();
		scene->addChild(Scenes::Menu::create());
		return cocos2d::Director::getInstance()->replaceScene(scene);
	}
	
	if (scene == SCENE_ACT)
	{
		cocos2d::Scene * scene = cocos2d::Scene::createWithPhysics();
		scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);
		scene->getPhysicsWorld()->setGravity(Master::instance().get<Components::Metric>().absolute(GRAVITY_FORCE));
		scene->addChild(Scenes::Act::create());
		return cocos2d::Director::getInstance()->replaceScene(scene);
	}

	if (scene == SCENE_SETTINGS)
	{
		cocos2d::Scene * scene = cocos2d::Scene::create();
		scene->addChild(Scenes::Settings::create());
		return cocos2d::Director::getInstance()->replaceScene(scene);
	}

	if (scene == SCENE_OVER)
	{
		cocos2d::Scene * scene = cocos2d::Scene::create();
		scene->addChild(Scenes::Over::create());
		return cocos2d::Director::getInstance()->replaceScene(scene);
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
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Texture).name(), std::move(std::unique_ptr<Texture>(new Texture()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Body).name(), std::move(std::unique_ptr<Body>(new Body()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Audio).name(), std::move(std::unique_ptr<Audio>(new Audio()))));
	components.push_back(std::pair<std::string, std::unique_ptr<::Application::Component>>(typeid(Font).name(), std::move(std::unique_ptr<Font>(new Font()))));
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