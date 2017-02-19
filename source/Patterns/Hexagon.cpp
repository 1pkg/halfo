#include "Hexagon.hpp"

namespace Patterns
{

Hexagon::Hexagon()
	: Application::Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.3f, -0.1f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.5f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.3f, -0.1f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.3f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.5f, 0.5f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.3f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			)
		}
	)
{
}

}