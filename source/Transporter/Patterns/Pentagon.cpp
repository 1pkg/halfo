#include "Pentagon.hpp"

namespace Transporter
{

namespace Patterns
{

Pentagon::Pentagon()
	: Pattern(
		std::vector<cocos2d::Vec2>{
			cocos2d::Vec2(
				 Master::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.4f, -0.1f),
				 Master::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			),
			cocos2d::Vec2(
				 Master::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.2f),
				 Master::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				 Master::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f),
				 Master::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(0.0f, 0.5f)
			),
			cocos2d::Vec2(
				 Master::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.2f, 0.5f),
				 Master::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.2f, 0.2f)
			),
			cocos2d::Vec2(
				 Master::instance().metric().spawn().width * cocos2d::RandomHelper::random_real<float>(0.1f, 0.4f),
				 Master::instance().metric().spawn().height * cocos2d::RandomHelper::random_real<float>(-0.5f, -0.3f)
			)
		}
	)
{
}

}

}