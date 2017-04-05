#ifndef COMPONENTS_FONT
#define COMPONENTS_FONT

#include "include.hpp"

namespace Components
{

class Font : public Application::Component
{
public:

	static const std::string EARTH_2073;
	static const float LARGE_SIZE;
	static const float MEDIUM_SIZE;
	static const float SMALL_SIZE;

    void initialize() override;
	std::string get(const std::string & font) const;

private:

	std::unordered_map<std::string, std::string> _fonts;
};

}

#endif