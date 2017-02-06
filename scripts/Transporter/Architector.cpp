#include "Architector.hpp"
#include "Objects/Figure.hpp"
#include "Application/Metric.hpp"

namespace Transporter
{

std::vector<
	std::pair<std::string, unsigned int>
>
Architector::figures =
{
	std::pair<std::string, unsigned int>("triangle", 50),
	std::pair<std::string, unsigned int>("quadrangle", 50),
	std::pair<std::string, unsigned int>("pentagon", 30),
	std::pair<std::string, unsigned int>("hexagon", 30)
};

Architector::Architector()
	: _patterns(PATTERNS_CAPACITY),
	_side(false)
{
	unsigned int limit = 0;
	for (const std::pair<std::string, unsigned int> & data : figures)
		limit += data.second;

	for (size_t i = 0; i < PATTERNS_CAPACITY;)
	{
		std::string figure = choseFigure(cocos2d::RandomHelper::random_int<unsigned int>(0, limit));
		std::unique_ptr<Pattern> pattern = Pattern::create(figure);
		std::unique_ptr<Objects::Figure> object(
			new Objects::Figure(
				pattern->data(),
				pattern->size(),
				cocos2d::Color4F::GREEN,
				cocos2d::PHYSICSBODY_MATERIAL_DEFAULT
			)
		);
		if (object->area() < LIMIT_AREA)
			continue;

		_patterns[i] =
			std::pair<std::unique_ptr<Pattern>, unsigned int>(
				std::move(pattern),
				cocos2d::RandomHelper::random_int<unsigned int>(1, 10)
			);
		++i;
	}
}

std::unique_ptr<Objects::Figure>
Architector::provide()
{
	unsigned int limit = 0;
	for (const std::pair<std::unique_ptr<Pattern>, unsigned int> & data : _patterns)
		limit += data.second;

	Pattern * pattern = chosePattern(cocos2d::RandomHelper::random_int<unsigned int>(0, limit));
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
	figure->view()->body()->setAngularVelocity(
		cocos2d::RandomHelper::random_real<float>(
			Application::Metric::instance().absolute(ANGULAR_SPEED_LIMIT.first),
			Application::Metric::instance().absolute(ANGULAR_SPEED_LIMIT.second)
		)
	);
	figure->view()->setPosition(Application::Metric::instance().spawn(_side));
	_side = !_side;
	return figure;
}

void
Architector::refresh()
{
	unsigned int limit = 0;
	for (const std::pair<std::string, unsigned int> & data : figures)
		limit += data.second;

	std::random_shuffle(_patterns.begin(), _patterns.end());
	for (size_t i = 0; i < REFRESH_DEPTH; ++i)
		_patterns.pop_back();
	for (size_t i = 0; i < REFRESH_DEPTH;)
	{
		std::string figure = choseFigure(cocos2d::RandomHelper::random_int<unsigned int>(0, limit));
		std::unique_ptr<Pattern> pattern = Pattern::create(figure);
		std::unique_ptr<Objects::Figure> object(
			new Objects::Figure(
				pattern->data(),
				pattern->size(),
				cocos2d::Color4F::GREEN,
				cocos2d::PHYSICSBODY_MATERIAL_DEFAULT
			)
		);
		if (object->area() < LIMIT_AREA)
			continue;

		_patterns.push_back(
			std::pair<std::unique_ptr<Pattern>, unsigned int>(
				std::move(Pattern::create(figure)),
				cocos2d::RandomHelper::random_int<unsigned int>(1, 10)
			)
		);
		++i;
	}
}

std::string
Architector::choseFigure(unsigned int roll) const
{
	unsigned int current = 0;
	for (const std::pair<std::string, unsigned int> & data : figures)
	{
		if (current <= roll && current + data.second >= roll)
			return data.first;
		else
			current += data.second;
	}
	return "";
}

Pattern *
Architector::chosePattern(unsigned int roll) const
{
	unsigned int current = 0;
	for (const std::pair<std::unique_ptr<Pattern>, unsigned int> & data : _patterns)
	{
		if (current <= roll && current + data.second >= roll)
			return data.first.get();
		else
			current += data.second;
	}
	return nullptr;
}

}