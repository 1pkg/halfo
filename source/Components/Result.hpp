#ifndef COMPONENTS_RESULT
#define COMPONENTS_RESULT

#include "Application/Component.hpp"
#include "Application/Result.hpp"
#include <vector>

namespace Components
{

class Result : public Application::Component
{
public:

	void initialize() override;
	std::size_t size() const;
	const Application::Result & at(std::size_t position) const;
	void update(const Application::Result & result);

private:

	friend class Storage;
	const unsigned int RESULTS_LIMIT = 100;
	std::vector<Application::Result> _results;
};

}

#endif