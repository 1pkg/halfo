#ifndef MASTER
#define MASTER

#include "Application/Wrapper.hpp"
#include "Application/Component.hpp"
#include <cocos2d.h>

class Master : public Application::Wrapper, public cocos2d::Application
{
public:

	static const std::string SCENE_MENU;
	static const std::string SCENE_PLAY;
	static const std::string SCENE_SETTINGS;
	static const std::string SCENE_OVER;
	static const std::string SCENE_EXIT;

    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
	void initGLContextAttrs() override;

	static Master & instance();
	template<typename TComponent>
	TComponent & get();
	cocos2d::Scheduler * sheduler() const;
	void scene(const std::string & scene);

private:

	void initialize();
	void finitialize();
	std::unordered_map<std::string, std::unique_ptr<::Application::Component>> _components;
};

template<typename TComponent>
TComponent &
Master::get()
{
	static TComponent & component = *dynamic_cast<TComponent *>(_components.at(typeid(TComponent).name()).get());
	return component;
}

#endif