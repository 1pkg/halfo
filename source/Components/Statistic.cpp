#include "Statistic.hpp"

namespace Components
{

const std::string Statistic::TOTAL_SLICE = "total-slice";
const std::string Statistic::TOTAL_TIME = "total-time";
const std::string Statistic::TOTAL_GAME = "total-game";

void
Statistic::initialize()
{
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_SLICE, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_TIME, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_GAME, 0));
}

std::array<Helpers::Result, Statistic::TABLE_SIZE>
Statistic::table() const
{
	return _table;
}

unsigned int
Statistic::total(std::string key) const
{
	return _totals.at(key);
}

void
Statistic::update(const Helpers::Result & result)
{
	_totals.at(TOTAL_SLICE) += result.slice();
	_totals.at(TOTAL_TIME) += result.time();
	++_totals.at(TOTAL_GAME);
	for (Helpers::Result & row : _table)
		if (row < result)
		{
			row = result;
			break;
		}
}

}