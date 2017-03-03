#include "Result.hpp"
#include <algorithm>

namespace Components
{

void
Result::initialize()
{
	_results.clear();
}

std::size_t
Result::size() const
{
	return _results.size();
}

const Application::Result &
Result::at(std::size_t position) const
{
	return _results.at(position);
}

void
Result::update(const Application::Result & result)
{
	_results.push_back(result);
	std::sort(_results.begin(), _results.end());
	if (_results.size() > RESULTS_LIMIT)
		_results.pop_back();
}

}