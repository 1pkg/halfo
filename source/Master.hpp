#ifndef MASTER
#define MASTER

#include "Application/Wrapper.hpp"
#include "Components/Metric.hpp"
#include "Components/Setting.hpp"
#include "Components/Statistic.hpp"
#include "Components/Storage.hpp"
#include "Components/Resource.hpp"
#include "Components/Crypto.hpp"
#include "Components/Texture.hpp"
#include <cocos2d.h>
#include <unordered_map>

class Master : public Application::Wrapper, public cocos2d::Application
{
public:

    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
	void initGLContextAttrs() override;

	static Master & instance();
	template<typename TComponent>
	TComponent & get(const std::string name);
	cocos2d::Scheduler * sheduler() const;
	void scene(const std::string & scene);

private:

	void components();
	std::unordered_map<std::string, std::unique_ptr<::Application::Component>> _components;
};

template<typename TComponent>
TComponent &
Master::get(const std::string name)
{
	static TComponent & component = *dynamic_cast<TComponent *>(_components.at(name).get());
	return component;
}

#endif