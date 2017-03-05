#ifndef COMPONENTS_STATISTIC
#define COMPONENTS_STATISTIC

#include "Application/Component.hpp"
#include "Result.hpp"
#include <array>
#include <unordered_map>

namespace Components
{

class Statistic : public Application::Component
{
public:

	static const std::string TOTAL_SCORE;
	static const std::string TOTAL_TIME;
	static const std::string TOTAL_GAME;

	static const std::size_t TABLE_SIZE = 10;

	void initialize() override;
	std::array<
		Result,
		TABLE_SIZE
	> table() const;
	unsigned int total(std::string key) const;
	void update(unsigned int score, unsigned int time);

private:

	friend class Storage;
	std::array<
		Result,
		TABLE_SIZE
	> _table;
	std::unordered_map<
		std::string,
		unsigned int
	> _totals;
};

}

#endif