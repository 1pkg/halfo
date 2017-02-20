#ifndef COMPONENTS_FILE
#define COMPONENTS_FILE

#include "Application\Wrapper.hpp"
#include <string>

namespace Components
{

class File : public Application::Wrapper
{
public:

	virtual std::string path() const = 0;
	virtual void flush() const = 0;
	virtual void fetch() = 0;
	std::string hash(const std::string & file) const;

private:

	const std::size_t LIMIT = 128;
	const std::size_t STEP = 4;

	std::string pad(const std::string & hash) const;
	std::string trim(const std::string & hash) const;
};

}

#endif