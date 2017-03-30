#ifndef COMPONENTS_FONT
#define COMPONENTS_FONT

#include "include.hpp"

namespace Components
{

class Font : public Application::Component
{
public:

    void initialize() override;
	std::string get(const std::string & font) const;

private:

	std::unordered_map<std::string, std::string> _fonts;
};

}

#endif