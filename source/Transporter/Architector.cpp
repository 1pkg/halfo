#include "Architector.hpp"
#include "Objects/Figure.hpp"

namespace Transporter
{

const std::vector<
	std::pair<std::string, unsigned int>
>
Architector::FIGURES =
{
	std::pair<std::string, unsigned int>("triangle", 50),
	std::pair<std::string, unsigned int>("quadrangle", 50),
	std::pair<std::string, unsigned int>("pentagon", 30),
	std::pair<std::string, unsigned int>("hexagon", 30)
	//std::pair<std::string, unsigned int>("heptagon", 20)
	//std::pair<std::string, unsigned int>("octagon", 20),
	//std::pair<std::string, unsigned int>("enneagon", 10),
	//std::pair<std::string, unsigned int>("decagon", 10)
};

Architector::Architector()
	: _linearSpeedScale(0), _angularSpeedScale(0),
	_patterns(PATTERNS_CAPACITY),
	_side(false)
{
	unsigned int limit = 0;
	for (const std::pair<std::string, unsigned int> & data : FIGURES)
		limit += data.second;

	for (size_t i = 0; i < PATTERNS_CAPACITY;)
	{
		std::string figure =
			choseFigure(
				cocos2d::RandomHelper::random_int<
					unsigned int
				>(0, limit)
			);
		std::unique_ptr<Application::Pattern> pattern =
			Application::Pattern::create(figure);
		std::unique_ptr<Objects::Figure> object(
			new Objects::Figure(
				pattern->data(),
				pattern->size()
			)
		);
		if (
			object->area() <
			Application::Main::instance().metric().absolute(
				Application::Main::instance().metric().absolute(
					LIMIT_AREA
				)
			)
		)
			continue;

		_patterns[i] =
			std::pair<std::unique_ptr<Application::Pattern>, unsigned int>(
				std::move(pattern),
				cocos2d::RandomHelper::random_int<
					unsigned int
				>(1, 10)
			);
		++i;
	}
}

std::unique_ptr<Objects::Figure>
Architector::provide()
{
	unsigned int limit = 0;
	for (const std::pair<std::unique_ptr<Application::Pattern>, unsigned int> & data : _patterns)
		limit += data.second;

	Application::Pattern * pattern =
		chosePattern(
			cocos2d::RandomHelper::random_int<
				unsigned int
			>(0, limit)
		);
	std::unique_ptr<Objects::Figure> figure(
		new Objects::Figure(
			pattern->data(),
			pattern->size()
		)
	);
	figure->view()->body()->setVelocity(
		cocos2d::Vec2(
			(_side ? -1 : 1) * cocos2d::RandomHelper::random_real<float>(
				Application::Main::instance().metric().absolute(LINEAR_SPEED_LIMIT.first),
				Application::Main::instance().metric().absolute(LINEAR_SPEED_LIMIT.second)
			) * (1 + _linearSpeedScale),
			0.0f
		)
	);
	figure->view()->body()->setAngularVelocity(
		cocos2d::RandomHelper::random_real<float>(
			Application::Main::instance().metric().absolute(ANGULAR_SPEED_LIMIT.first),
			Application::Main::instance().metric().absolute(ANGULAR_SPEED_LIMIT.second)
		) * (1 + _angularSpeedScale)
	);
	figure->view()->setPosition(Application::Main::instance().metric().spawn(_side));
	_side = !_side;
	return figure;
}

void
Architector::refresh()
{
	unsigned int limit = 0;
	for (const std::pair<std::string, unsigned int> & data : FIGURES)
		limit += data.second;

	std::random_shuffle(_patterns.begin(), _patterns.end());
	for (size_t i = 0; i < REFRESH_DEPTH; ++i)
		_patterns.pop_back();
	for (size_t i = 0; i < REFRESH_DEPTH;)
	{
		std::string figure =
			choseFigure(
				cocos2d::RandomHelper::random_int<
					unsigned int
				>(0, limit)
			);
		std::unique_ptr<Application::Pattern> pattern =
			Application::Pattern::create(figure);
		std::unique_ptr<Objects::Figure> object(
			new Objects::Figure(
				pattern->data(),
				pattern->size()
			)
		);
		if (
			object->area() <
			Application::Main::instance().metric().absolute(
				Application::Main::instance().metric().absolute(
					LIMIT_AREA
				)
			)
		)
			continue;

		_patterns.push_back(
			std::pair<std::unique_ptr<Application::Pattern>, unsigned int>(
				std::move(Application::Pattern::create(figure)),
				cocos2d::RandomHelper::random_int<unsigned int>(1, 10)
			)
		);
		++i;
	}
}

void
Architector::increase()
{
	_linearSpeedScale =
		_linearSpeedScale < LINEAR_SPEED_SCALE_LIMIT ? _linearSpeedScale + 1 : LINEAR_SPEED_SCALE_LIMIT;
	_angularSpeedScale =
		_angularSpeedScale < ANGULAR_SPEED_SCALE_LIMIT ? _angularSpeedScale + 1 : ANGULAR_SPEED_SCALE_LIMIT;
}

void
Architector::reset()
{
	_linearSpeedScale =
		_linearSpeedScale < 2 ? 0 : _linearSpeedScale - 2;
	_angularSpeedScale =
		_angularSpeedScale < 1 ? 0 : _angularSpeedScale - 1;
}

std::string
Architector::choseFigure(unsigned int roll) const
{
	unsigned int current = 0;
	for (const std::pair<std::string, unsigned int> & data : FIGURES)
	{
		if (current <= roll && current + data.second >= roll)
			return data.first;
		else
			current += data.second;
	}
	return "";
}

Application::Pattern *
Architector::chosePattern(unsigned int roll) const
{
	unsigned int current = 0;
	for (const std::pair<std::unique_ptr<Application::Pattern>, unsigned int> & data : _patterns)
	{
		if (current <= roll && current + data.second >= roll)
			return data.first.get();
		else
			current += data.second;
	}
	return nullptr;
}

}