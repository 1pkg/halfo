#ifndef FUNCTIONS
#define FUNCTIONS

#include <cocos2d.h>
#include <array>
namespace cocos2d
{
	typedef std::pair<Vec2, Vec2> Line;
	typedef std::vector<Vec2> Polygon;
	typedef std::array<cocos2d::Vec2, 3> Triangle;
}

template <typename T>
std::string to_string(T value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

template <>
std::string to_string(cocos2d::Vec2 value);
template <>
std::string to_string(cocos2d::Line value);
template <>
std::string to_string(cocos2d::Polygon value);

std::string replace(const std::string & string, const std::string & search, const std::string & replace);

std::string hash(const cocos2d::Data & data);

float area(const cocos2d::Polygon & polygon);

struct Result
{
	Result();
	Result(unsigned int slices, unsigned int time, unsigned int mass);
	bool operator<(const Result & result) const;
	bool empty() const;
	unsigned int slices, time, mass;
};

#endif