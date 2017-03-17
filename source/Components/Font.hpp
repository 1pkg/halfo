#ifndef COMPONENTS_FONT
#define COMPONENTS_FONT

#include "include.hpp"

namespace Components
{

class Font : public Application::Component
{
public:

    void initialize() override;
	std::string get() const;

private:

	std::string _font;
};

}

#endif