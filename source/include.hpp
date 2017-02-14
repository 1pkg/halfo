#ifndef INCLUDE
#define INCLUDE

#include "Application/Kit.hpp"
#include "Application/Object.hpp"
#include "Application/View.hpp"
#include "Application/Pattern.hpp"
#include "Application/Metric.hpp"
#include <cocos2d.h>

#define DEFAULT_PHYSICS_MASK 0xFFFFFFFF

template <typename T>
std::string
toString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

#endif