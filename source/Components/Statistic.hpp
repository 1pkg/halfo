#ifndef COMPONENTS_STATISTIC
#define COMPONENTS_STATISTIC

#include "include.hpp"
#include "constants.hpp"
#include "functions.hpp"

namespace Components
{

class Statistic : public Application::Component
{
public:

	static const std::string TOTAL_SLICES_STATISTIC;
	static const std::string TOTAL_TIME_STATISTIC;
	static const std::string TOTAL_MASS_STATISTIC;
	static const std::string TOTAL_GAMES_STATISTIC;

	void initialize() override;
	const std::array<Result, STATISTIC_TABLE_SIZE> & table() const;
	unsigned int total(std::string key) const;
	void update(const Result & result);

private:

	friend class Storage;
	std::array<Result, STATISTIC_TABLE_SIZE> _table;
	std::unordered_map<std::string, unsigned int> _totals;
};

}

#endif