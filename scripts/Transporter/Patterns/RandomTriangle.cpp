#include "RandomTriangle.hpp"
#include "Application/Metric.hpp"

namespace Transporter
{

namespace Patterns
{

RandomTriangle::RandomTriangle()
	: Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				Application::Metric::instance().absolute(cocos2d::RandomHelper::random_real<float>(0.0f, 50.0f)),
				Application::Metric::instance().absolute(cocos2d::RandomHelper::random_real<float>(0.0f, 50.0f))
			),
			cocos2d::Vec2(
				Application::Metric::instance().absolute(cocos2d::RandomHelper::random_real<float>(70.0f, 100.0f)),
				Application::Metric::instance().absolute(cocos2d::RandomHelper::random_real<float>(70.0f, 100.0f))
			),
			cocos2d::Vec2(
				Application::Metric::instance().absolute(cocos2d::RandomHelper::random_real<float>(120.0f, 150.0f)),
				Application::Metric::instance().absolute(cocos2d::RandomHelper::random_real<float>(0.0f, 50.0f))
			)
		}
	)
{
}


}

}