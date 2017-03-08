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

std::array<std::tuple<unsigned int, unsigned int, unsigned int>, Statistic::TABLE_SIZE>
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
Statistic::update(unsigned int slice, unsigned int time)
{
	_totals.at(TOTAL_SLICE) += slice;
	_totals.at(TOTAL_TIME) += time;
	++_totals.at(TOTAL_GAME);
	unsigned total = slice + time;
	for (std::tuple<unsigned int, unsigned int, unsigned int> & row : _table)
		if (std::get<2>(row) < total)
		{
			row = std::tuple<unsigned int, unsigned int, unsigned int>(slice, time, total);
			break;
		}
}

}