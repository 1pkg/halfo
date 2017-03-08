#include "include.hpp"
#include "Result.hpp"

namespace Helpers
{

Result::Result()
	: _slice(0),
	_time(0),
	_total(0)
	
{
}

Result::Result(unsigned int score, unsigned int time)
	: _slice(score),
	_time(time),
	_total(score + time)
	
{
}

unsigned int
Result::slice() const
{
	return _slice;
}

unsigned int
Result::time() const
{
	return _time;
}

unsigned int
Result::total() const
{
	return _total;
}

bool
Result::empty() const
{
	return _total != 0 && _slice != 0 && _time != 0;
}

std::string
Result::toString() const
{
	if (empty())
		return "";

	return "" + to_string(_total) + "" + to_string(_slice) + "" + to_string(_time);
}

bool
Result::operator<(const Result & result) const
{
	return _total < result._total;
}

}