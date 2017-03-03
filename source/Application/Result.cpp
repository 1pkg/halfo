#include "Result.hpp"

namespace Application
{

Result::Result(
	unsigned int score,
	unsigned int seconds,
	unsigned int integral
)
{
	this->score = score,
	this->seconds = seconds,
	this->integral = integral;
}

Result::Result()
{
}

bool
Result::operator<(const Result & result)
{
	return
		integral < result.integral ||
		(integral == result.integral && score < result.score);
}

}