#include "components.hpp"
#include "Octagon.hpp"

namespace Play
{

namespace Transporter
{

namespace Patterns
{

Octagon::Octagon()
	: Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.1f, 0.1f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(0.4f, 0.5f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				 Master::instance().get<Components::Metric>().spawn().width * cocos2d::RandomHelper::random_real<float>(0.3f, 0.5f),
				 Master::instance().get<Components::Metric>().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			)
		}
	)
{
}

}

}

}