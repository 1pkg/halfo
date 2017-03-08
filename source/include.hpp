#ifndef INCLUDE
#define INCLUDE

#include "Application/Wrapper.hpp"
#include "Application/Kit.hpp"
#include "Application/Object.hpp"
#include "Application/View.hpp"
#include "Application/Component.hpp"

#include "Components/Metric.hpp"
#include "Components/Setting.hpp"
#include "Components/Statistic.hpp"
#include "Components/Resource.hpp"

#include "Master.hpp"
#include <cocos2d.h>

#include <memory>
#include <array>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define DEFAULT_PHYSICS_MASK 0xFFFFFFFF
#define RESOURCE_DEBUG

template <typename T>
std::string to_string(T value)
{
	std::ostringstream stream;
	stream << value ;
	return stream.str() ;
}

#endif