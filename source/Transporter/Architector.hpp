#ifndef TRANSPORTER_ARCHITECTOR
#define TRANSPORTER_ARCHITECTOR

#include "include.hpp"

class Act;
namespace Objects{class Figure;}
namespace Transporter
{

class Architector : public Application::Wrapper
{
public:

	Architector();
	std::unique_ptr<Objects::Figure> provide();
	void refresh();
	void increase();
	void reset();

private:

	const size_t
		PATTERNS_CAPACITY = 32,
		REFRESH_DEPTH = 6;
	const std::pair<float, float>
		LINEAR_SPEED_LIMIT = std::pair<float, float>(100.0f, 300.0f),
		ANGULAR_SPEED_LIMIT = std::pair<float, float>(0.5f, 1.0f);
	const float LIMIT_AREA = 100.0f;
	const unsigned int
		LINEAR_SPEED_SCALE_LIMIT = 5,
		ANGULAR_SPEED_SCALE_LIMIT = 2;

	const static std::vector<
		std::pair<std::string, unsigned int>
	> FIGURES;

	std::string choseFigure(unsigned int roll) const;
	Application::Pattern * chosePattern(unsigned int roll) const;
	bool _side;
	unsigned int _linearSpeedScale, _angularSpeedScale;
	std::vector<
		std::pair<std::unique_ptr<Application::Pattern>, unsigned int>
	> _patterns;
};

}

#endif