#ifndef TRANSPORTER_ARCHITECTOR
#define TRANSPORTER_ARCHITECTOR

#include "include.hpp"
#include "Pattern.hpp"

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

	const size_t
		PATTERNS_CAPACITY = 32,
		REFRESH_DEPTH = 6;
	const std::pair<float, float>
		LINEAR_SPEED_LIMIT = std::pair<float, float>(100.0f, 300.0f),
		ANGULAR_SPEED_LIMIT = std::pair<float, float>(0.5f, 1.0f);
	const float LIMIT_AREA = 100.0f;

	void fill(unsigned int count);
	std::unique_ptr<Pattern> roll() const;
	bool _side;
	std::vector<
		std::pair<std::unique_ptr<Pattern>, unsigned int>
	> _patterns;
};

}

#endif