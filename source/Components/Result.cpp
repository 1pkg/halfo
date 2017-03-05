#include "Result.hpp"

namespace Components
{

Result::Result()
	: _score(0),
	_time(0),
	_integral(0)
	
{
}

Result::Result(unsigned int score, unsigned int time)
	: _score(score),
	_time(time),
	_integral(score + time)
	
{
}

unsigned int
Result::score() const
{
	return _score;
}

unsigned int
Result::time() const
{
	return _time;
}

unsigned int
Result::integral() const
{
	return _integral;
}

bool
Result::empty() const
{
	return _integral != 0 && _score != 0 && _time != 0;
}

bool
Result::operator<(const Result & result) const
{
	return _integral < result._integral;
}

}