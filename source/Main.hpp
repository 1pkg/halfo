#ifndef MASTER
#define MASTER

#include "Application/Wrapper.hpp"
#include "Components/Metric.hpp"
#include "Components/Integrity.hpp"
#include "Components/Storage.hpp"
#include "Components/Resource.hpp"
#include <cocos2d.h>

class Master : public Application::Wrapper, public cocos2d::Application
{
public:

	static Master & instance();

    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
	void initGLContextAttrs() override;

	cocos2d::Scheduler * sheduler() const;
	const Components::Metric & metric() const;
	const Components::Resource & resource() const;
	Components::Storage & storage() const;
	Components::Integrity & integrity() const;

	void change(const std::string & scene);

private:
	
	std::unique_ptr<Components::Metric> _metric;
	std::unique_ptr<Components::Integrity> _integrity;
	std::unique_ptr<Components::Storage> _storage;
	std::unique_ptr<Components::Resource> _resource;
};

#endif