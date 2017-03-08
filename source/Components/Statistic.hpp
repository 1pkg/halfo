#ifndef COMPONENTS_STATISTIC
#define COMPONENTS_STATISTIC

#include "Application/Component.hpp"
#include <array>
#include <unordered_map>

namespace Components
{

class Statistic : public Application::Component
{
public:

	static const std::string TOTAL_SLICE;
	static const std::string TOTAL_TIME;
	static const std::string TOTAL_GAME;

	static const std::size_t TABLE_SIZE = 10;
	void initialize() override;
	std::array<std::tuple<unsigned int, unsigned int, unsigned int>, TABLE_SIZE> table() const;
	unsigned int total(std::string key) const;
	void update(unsigned int slice, unsigned int time);

private:

	friend class Storage;
	std::array<std::tuple<unsigned int, unsigned int, unsigned int>, TABLE_SIZE> _table;
	std::unordered_map<std::string, unsigned int> _totals;
};

}

#endif