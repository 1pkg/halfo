#include "components.hpp"
#include "Architector.hpp"
#include "Objects/Figure.hpp"

namespace Components
{

std::unique_ptr<Objects::Figure>
Architector::provide()
{
	static bool side = true;
	std::vector<cocos2d::Vec2> pattern{
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
	};
	std::unique_ptr<Objects::Figure> figure(new Objects::Figure(pattern.data(), pattern.size()));
	figure->view()->body()->setVelocity(
		cocos2d::Vec2(
			(side ? -1 : 1) * cocos2d::RandomHelper::random_real<float>(
				Master::instance().get<Components::Metric>().absolute(100.0f),
				Master::instance().get<Components::Metric>().absolute(300.0f)
			),
			0.0f
		)
	);
	figure->view()->body()->setAngularVelocity(
		cocos2d::RandomHelper::random_real<float>(
			Master::instance().get<Components::Metric>().absolute(0.5f),
			Master::instance().get<Components::Metric>().absolute(1.0f)
		)
	);
	figure->view()->setPosition(Master::instance().get<Components::Metric>().spawn(side));
	side = !side;
	return figure;
}

}