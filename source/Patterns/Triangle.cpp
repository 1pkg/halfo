#include "Triangle.hpp"

namespace Patterns
{

Triangle::Triangle()
	: Application::Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				 Application::Metric::instance().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.2f),
				 Application::Metric::instance().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, 0.0f)
			),
			cocos2d::Vec2(
				 Application::Metric::instance().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, 0.5f),
				 Application::Metric::instance().spawn().height * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f)
			),
			cocos2d::Vec2(
				 Application::Metric::instance().spawn().width * cocos2d::RandomHelper::random_real<float>(0.2f, 0.5f),
				 Application::Metric::instance().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, 0.0f)
			)
		}
	)
{
}

}