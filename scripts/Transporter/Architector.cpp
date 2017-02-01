#include "Architector.hpp"
#include "Objects/Figure.hpp"
#include "Application/Metric.hpp"

namespace Transporter
{

Architector::Architector()
	: _patterns(PATTERNS_CAPACITY),
	_side(false)
{
	for (size_t i = 0; i < PATTERNS_CAPACITY; ++i)
		_patterns[i] =
			std::pair<std::unique_ptr<Pattern>, unsigned int>(
				std::move(
					Pattern::create(
						Pattern::names[cocos2d::RandomHelper::random_int<std::size_t>(0, Pattern::names.size() - 1)]
					)
				),
				cocos2d::RandomHelper::random_int<unsigned int>(1, 10)
			);
}

std::unique_ptr<Objects::Figure>
Architector::provide()
{
	unsigned int limit = 0;
	for (const std::pair<std::unique_ptr<Pattern>, unsigned int> & data : _patterns)
		limit += data.second;

	Pattern * pattern = chose(cocos2d::RandomHelper::random_int<unsigned int>(0, limit));
	std::unique_ptr<Objects::Figure> figure(
		new Objects::Figure(
			pattern->data(),
			pattern->size(),
			cocos2d::Color4F::GREEN,
			cocos2d::PHYSICSBODY_MATERIAL_DEFAULT
		)
	);
	figure->view()->body()->setVelocity(
		cocos2d::Vec2(
			(_side ? -1 : 1) * cocos2d::RandomHelper::random_real<float>(
				Application::Metric::instance().absolute(LINEAR_SPEED_LIMIT.first),
				Application::Metric::instance().absolute(LINEAR_SPEED_LIMIT.second)
			),
			0.0f
		)
	);
	//figure->view()->body()->setAngularVelocity(
	//	cocos2d::RandomHelper::random_real<float>(
	//		Application::Metric::instance().absolute(ANGULAR_SPEED_LIMIT.first),
	//		Application::Metric::instance().absolute(ANGULAR_SPEED_LIMIT.second)
	//	)
	//);
	figure->view()->setPosition(Application::Metric::instance().spawn(_side));
	_side = !_side;
	return figure;
}

void
Architector::refresh()
{
	std::random_shuffle(_patterns.begin(), _patterns.end());
	for (size_t i = 0; i < REFRESH_DEPTH; ++i)
		_patterns.pop_back();
	for (size_t i = 0; i < REFRESH_DEPTH; ++i)
		_patterns.push_back(
			std::pair<std::unique_ptr<Pattern>, unsigned int>(
				std::move(
					Pattern::create(
						Pattern::names[cocos2d::RandomHelper::random_int<std::size_t>(0, Pattern::names.size() - 1)]
					)
				),
				cocos2d::RandomHelper::random_int<unsigned int>(1, 10)
			)
		);
}

Pattern *
Architector::chose(unsigned int roll) const
{
	unsigned int current = 0;
	for (const std::pair<std::unique_ptr<Pattern>, unsigned int> & data : _patterns)
	{
		if (current < roll && current + data.second >= roll)
			return data.first.get();
		else
			current += data.second;
	}
	return nullptr;
}

}