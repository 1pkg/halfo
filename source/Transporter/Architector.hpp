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

private:

	const size_t PATTERNS_CAPACITY = 32;
	const size_t REFRESH_DEPTH = 6;
	const float LIMIT_AREA = 100.0f;
	const std::pair<float, float> LINEAR_SPEED_LIMIT = std::pair<float, float>(100.0f, 1000.0f);
	const std::pair<float, float> ANGULAR_SPEED_LIMIT = std::pair<float, float>(1.0f, 3.0f);

	const static std::vector<
		std::pair<std::string, unsigned int>
	> FIGURES;

	std::string choseFigure(unsigned int roll) const;
	Application::Pattern * chosePattern(unsigned int roll) const;
	bool _side;
	std::vector<
		std::pair<std::unique_ptr<Application::Pattern>, unsigned int>
	> _patterns;
};

}

#endif