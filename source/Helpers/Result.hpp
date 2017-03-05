#ifndef HELPERS_RESULT
#define HELPERS_RESULT

#include <string>

namespace Helpers
{

class Result
{
public:

	Result();
	Result(unsigned int score, unsigned int time);
	unsigned int slice() const;
	unsigned int time() const;
	unsigned int total() const;
	bool empty() const;
	std::string toString() const;
	bool operator<(const Result & result) const;

private:

	unsigned int _slice, _time, _total;
};

}

#endif