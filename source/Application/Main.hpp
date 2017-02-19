#ifndef APPLICATION_MAIN
#define APPLICATION_MAIN

#include "Wrapper.hpp"
#include "Components/Metric.hpp"
#include "Components/LocalStorage.hpp"
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

	const Components::Metric & metric() const;
	Components::LocalStorage & localStorage() const;

private:
	
	std::unique_ptr<Components::Metric> _metric;
	std::unique_ptr<Components::LocalStorage> _localStorage;
};

}

#endif