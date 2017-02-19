#include "Quadrangle.hpp"

namespace Patterns
{

Quadrangle::Quadrangle()
	: Application::Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f)
			),
			cocos2d::Vec2(
				 Application::Main::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f),
				 Application::Main::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f)
			)
		}
	)
{
}

}