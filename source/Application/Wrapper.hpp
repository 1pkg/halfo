#ifndef APPLICATION_WRAPPER
#define APPLICATION_WRAPPER

namespace Application
{

class Wrapper
{
public:

	virtual ~Wrapper() = default;
	Wrapper() = default;
	Wrapper(const Wrapper &) = delete;
    Wrapper& operator=(const Wrapper &) = delete;
};

}

#endif