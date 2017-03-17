#include "Statistic.hpp"

namespace Components
{

const std::string Statistic::TOTAL_SLICES_STATISTIC = "slices";
const std::string Statistic::TOTAL_TIME_STATISTIC = "time";
const std::string Statistic::TOTAL_MASS_STATISTIC = "mass";
const std::string Statistic::TOTAL_GAMES_STATISTIC = "games";

void
Statistic::initialize()
{
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_SLICES_STATISTIC, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_TIME_STATISTIC, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_MASS_STATISTIC, 0));
	_totals.insert(std::pair<std::string, unsigned int>(TOTAL_GAMES_STATISTIC, 0));
}

const std::array<Statistic::Result, STATISTIC_TABLE_SIZE> &
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
Statistic::update(const Result & result)
{
	_totals.at(TOTAL_SLICES_STATISTIC) += result.slices;
	_totals.at(TOTAL_TIME_STATISTIC) += result.time;
	_totals.at(TOTAL_MASS_STATISTIC) += result.mass;
	++_totals.at(TOTAL_GAMES_STATISTIC);

	if (_table[STATISTIC_TABLE_SIZE - 1] < result)
	{
		_table[STATISTIC_TABLE_SIZE - 1] = result;
		std::sort(_table.begin(), _table.end());
	}
}

Statistic::Result::Result()
{
	this->slices = this->time = this->mass = 0;
}

Statistic::Result::Result(unsigned int slices, unsigned int time, unsigned int mass)
{
	this->slices = slices;
	this->time = time;
	this->mass = mass;
}

bool
Statistic::Result::operator<(const Result & result) const
{
	return slices < result.slices;
}

}