#include "Quadrangle.hpp"

namespace Transporter
{

namespace Patterns
{

Quadrangle::Quadrangle()
	: Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.5f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.1f)
			)
		}
	)
{
}

}

}