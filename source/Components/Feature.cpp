#include "Feature.hpp"

namespace Components
{

void
Feature::initialize()
{
	_features.insert(
		std::pair<std::string, bool>(DISABLE_ADDS, false)
	);
}

bool
Feature::has(const std::string & feature) const
{
	return _features.find(feature) != _features.end();
}

bool
Feature::value(const std::string & feature) const
{
	return _features.find(feature)->second;
}

void
Feature::change(const std::string & feature, bool value)
{
	_features.find(feature)->second = value;
}

}