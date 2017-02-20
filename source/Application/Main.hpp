#ifndef APPLICATION_MAIN
#define APPLICATION_MAIN

#include "Wrapper.hpp"
#include "Components/Metric.hpp"
#include "Components/Storage.hpp"
#include "Components/Resource.hpp"
#include "Components/Integrity.hpp"
#include <cocos2d.h>

namespace Application
{

class Act;
class Main : public Wrapper, public cocos2d::Application
{
public:

	static Main & instance();

    void initGLContextAttrs() override;
    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;

	void act();
	void over();
	void end();

	cocos2d::Scheduler * sheduler() const;
	const Components::Metric & metric() const;
	Components::Storage & storage() const;
	const Components::Resource & resource() const;
	Components::Integrity & integrity() const;

private:
	
	std::unique_ptr<Components::Metric> _metric;
	std::unique_ptr<Components::Integrity> _integrity;
	std::unique_ptr<Components::Storage> _storage;
	std::unique_ptr<Components::Resource> _resource;
};

}

#endif