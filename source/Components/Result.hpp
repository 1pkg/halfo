#ifndef COMPONENTS_RESULT
#define COMPONENTS_RESULT

namespace Components
{

class Result
{
public:

	Result();
	Result(unsigned int score, unsigned int time);
	unsigned int score() const;
	unsigned int time() const;
	unsigned int integral() const;
	bool empty() const;
	bool operator<(const Result & result) const;

private:

	unsigned int _score, _time, _integral;
};

}

#endif