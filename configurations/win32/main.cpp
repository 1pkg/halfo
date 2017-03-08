#include "main.hpp"
#include "Master.hpp"
#include <cocos2d.h>

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    Master master;
    return cocos2d::Application::getInstance()->run();
}