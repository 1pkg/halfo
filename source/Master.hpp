#ifndef MASTER
#define MASTER

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
#include <cocos2d.h>

class Master : public Application::Wrapper, public cocos2d::Application
{
public:

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