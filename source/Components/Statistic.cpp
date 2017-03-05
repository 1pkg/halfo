#include "Statistic.hpp"
#include <algorithm>

namespace Components
{

const std::string
Statistic::TOTAL_SCORE = "total-score";
const std::string
Statistic::TOTAL_TIME = "total-time";
const std::string
Statistic::TOTAL_GAME = "total-game";

void
Statistic::initialize()
{
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_SCORE, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_TIME, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_GAME, 0));
}

std::array<
	Result,
	Statistic::TABLE_SIZE
>
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
Statistic::update(unsigned int score, unsigned int time)
{
	_totals.at(TOTAL_SCORE) += score;
	_totals.at(TOTAL_TIME) += time;
	++_totals.at(TOTAL_GAME);
	Result current(score, time);
	for (Result & result : _table)
		if (result < current)
		{
			result = current;
			break;
		}
}

}