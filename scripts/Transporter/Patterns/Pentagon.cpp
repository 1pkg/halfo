#include "Pentagon.hpp"
#include "Application/Metric.hpp"

namespace Transporter
{

namespace Patterns
{

Pentagon::Pentagon()
	: Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				Application::Metric::instance().constraint().width * cocos2d::RandomHelper::random_real<float>(-0.4f, -0.1f),
				Application::Metric::instance().constraint().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			),
			cocos2d::Vec2(
				Application::Metric::instance().constraint().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.2f),
				Application::Metric::instance().constraint().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				Application::Metric::instance().constraint().width * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f),
				Application::Metric::instance().constraint().height * cocos2d::RandomHelper::random_real<float>(0.0f, 0.5f)
			),
			cocos2d::Vec2(
				Application::Metric::instance().constraint().width * cocos2d::RandomHelper::random_real<float>(0.2f, 0.5f),
				Application::Metric::instance().constraint().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				Application::Metric::instance().constraint().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.4f),
				Application::Metric::instance().constraint().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			)
		}
	)
{
}


}

}