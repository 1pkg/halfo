#ifndef FUNCTIONS
#define FUNCTIONS

#include <cocos2d.h>

template <typename T>
std::string to_string(T value)
{
	std::ostringstream stream;
	stream << value ;
	return stream.str() ;
}

std::string replace(const std::string & string, const std::string & search, const std::string & replace);

std::string hash(const cocos2d::Data & data);

struct Result
{
	Result();
	Result(unsigned int slices, unsigned int time, unsigned int mass);
	bool operator<(const Result & result) const;
	bool empty() const;
	unsigned int slices, time, mass;
};

#endif