#ifndef APPLICATION_MAIN
#define APPLICATION_MAIN

#include "include.hpp"

namespace Application
{

class Main : private cocos2d::Application
{
public:

    void initGLContextAttrs() override;
    bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;
};

}

#endif