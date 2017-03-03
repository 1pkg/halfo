#ifndef MASTER
#define MASTER

#include "Application/Wrapper.hpp"
#include "Application/Component.hpp"
#include <cocos2d.h>
#include <unordered_map>

namespace Components {class Metric; class Feature; class Setting; class Result; class Storage; class Stat;}
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
	Components::Feature & feature() const;
	Components::Setting & setting() const;
	Components::Result & result() const;
	Components::Stat & stat() const;

	void change(const std::string & scene);
	void end();

private:

	void components();
	
	std::unordered_map<
		std::string,
		std::unique_ptr<::Application::Component>
	> _components;
};

#endif