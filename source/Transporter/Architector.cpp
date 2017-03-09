#include "Architector.hpp"
#include "Objects/Figure.hpp"
#include "Patterns/Triangle.hpp"
#include "Patterns/Quadrangle.hpp"
#include "Patterns/Pentagon.hpp"
#include "Patterns/Octagon.hpp"

namespace Transporter
{

Architector::Architector()
	: _patterns(PATTERNS_CAPACITY),
	_side(false)
{
	fill(PATTERNS_CAPACITY);
}

std::unique_ptr<Objects::Figure>
Architector::provide()
{
	Pattern * pattern = nullptr;
	unsigned int limit = 0;
	for (const std::pair<std::unique_ptr<Pattern>, unsigned int> & data : _patterns)
		limit += data.second;
	unsigned int roll = cocos2d::RandomHelper::random_int<unsigned int>(0, limit);
	unsigned int current = 0;
	for (const std::pair<std::unique_ptr<Pattern>, unsigned int> & data : _patterns)
	{
		if (current <= roll && current + data.second >= roll)
		{
			pattern = data.first.get();
			break;
		}
		else
			current += data.second;
	}
	std::unique_ptr<Objects::Figure> figure(new Objects::Figure(pattern->data(), pattern->size()));
	figure->view()->body()->setVelocity(
		cocos2d::Vec2(
			(_side ? -1 : 1) * cocos2d::RandomHelper::random_real<float>(
				Master::instance().get<Components::Metric>().absolute(LINEAR_SPEED_LIMIT.first),
				Master::instance().get<Components::Metric>().absolute(LINEAR_SPEED_LIMIT.second)
			),
			0.0f
		)
	);
	figure->view()->body()->setAngularVelocity(
		cocos2d::RandomHelper::random_real<float>(
			Master::instance().get<Components::Metric>().absolute(ANGULAR_SPEED_LIMIT.first),
			Master::instance().get<Components::Metric>().absolute(ANGULAR_SPEED_LIMIT.second)
		)
	);
	figure->view()->setPosition(Master::instance().get<Components::Metric>().spawn(_side));
	_side = !_side;
	return figure;
}

void
Architector::refresh()
{
	std::random_shuffle(_patterns.begin(), _patterns.end());
	for (size_t i = 0; i < REFRESH_DEPTH; ++i)
		_patterns.pop_back();
	fill(REFRESH_DEPTH);
}

void
Architector::fill(unsigned int count)
{
	for (size_t i = 0; i < count;)
	{
		std::unique_ptr<Pattern> pattern = roll();
		std::unique_ptr<Objects::Figure> object(new Objects::Figure(pattern->data(), pattern->size()));
		if (object->area() < Master::instance().get<Components::Metric>().absolute2(LIMIT_AREA))
			continue;

		_patterns[i] = std::pair<std::unique_ptr<Pattern>, unsigned int>(std::move(pattern), cocos2d::RandomHelper::random_int<unsigned int>(1, 10));
		++i;
	}
}

std::unique_ptr<Pattern>
Architector::roll() const
{
	using namespace Patterns;
	unsigned int roll = cocos2d::RandomHelper::random_int<unsigned int>(0, 3);
	switch (roll)
	{
		case 0:
			return std::move(std::unique_ptr<Pattern>(new Triangle()));

		case 1:
			return std::move(std::unique_ptr<Pattern>(new Quadrangle()));

		case 2:
			return std::move(std::unique_ptr<Pattern>(new Pentagon()));

		case 3:
			return std::move(std::unique_ptr<Pattern>(new Octagon()));

		default:
			return nullptr;
	}
}

}