#ifndef MASTER
#define MASTER

#include "Application/Wrapper.hpp"
#include "Application/Component.hpp"
#include <cocos2d.h>
#include <unordered_map>

namespace Components
{
	class Metric;
	class Setting;
	class Storage;
	class Statistic;
	class Resource;
}
class Master : public Application::Wrapper, public cocos2d::Application
{
public:

    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
	void initGLContextAttrs() override;

	static Master & instance();

	cocos2d::Scheduler * sheduler() const;
	const Components::Metric & metric() const;
	Components::Setting & setting() const;
	Components::Statistic & statistic() const;
	Components::Resource & resource() const;

	void change(const std::string & scene);
	void end();

private:

	void components();
	std::unordered_map<std::string, std::unique_ptr<::Application::Component>> _components;
};

#endif