#ifndef COMPONENTS_STATISTIC
#define COMPONENTS_STATISTIC

#include "Application/Component.hpp"
#include <cocos2d.h>
#include <array>

namespace Components
{

class Statistic : public Application::Component
{
public:

	static const std::string TOTAL_SLICES_STATISTIC;
	static const std::string TOTAL_TIME_STATISTIC;
	static const std::string TOTAL_MASS_STATISTIC;
	static const std::string TOTAL_GAMES_STATISTIC;

	struct Result
	{
		Result();
		Result(unsigned int slices, unsigned int time, unsigned int mass);
		bool operator<(const Result & result) const;
		unsigned int slices, time, mass;
	};

	void initialize() override;
	const std::array<Result, 0xA> & table() const;
	unsigned int total(std::string key) const;
	void update(const Result & result);

private:

	friend class Storage;
	std::array<Result, 0xA> _table;
	std::unordered_map<std::string, unsigned int> _totals;
};

}

#endif