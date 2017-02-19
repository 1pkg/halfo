#ifndef APPLICATION_MAIN
#define APPLICATION_MAIN

#include "Wrapper.hpp"
#include <cocos2d.h>

namespace Components{class Metric;}
namespace Application
{

class Act;
class Main : public Wrapper, public cocos2d::Application
{
public:

	static const Main & instance();

    void initGLContextAttrs() override;
    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;

	const Components::Metric & metric() const;

private:
	
	Components::Metric * _metric;
};

}

#endif