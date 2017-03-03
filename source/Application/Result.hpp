#ifndef APPLICATION_RESULT
#define APPLICATION_RESULT

namespace Application
{

struct Result
{
	unsigned int
		score,
		seconds,
		integral;
	Result(
		unsigned int score,
		unsigned int seconds,
		unsigned int integral
	);
	Result();
	bool operator<(const Result & result);
};

}

#endif