#include "Stat.hpp"

namespace Components
{

void
Stat::initialize()
{
	_total = 0;
}

unsigned int
Stat::total(std::size_t position)
{
	return _total;
}

}