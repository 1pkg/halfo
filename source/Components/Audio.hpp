#ifndef COMPONENTS_AUDIO
#define COMPONENTS_AUDIO

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class Audio : public Application::Component
{
public:

    void initialize() override;
	unsigned int play(const std::string & alias) const;
	void stop(unsigned int identifier) const;
	void pause(unsigned int identifier) const;
	void resume(unsigned int identifier) const;

private:

	std::unordered_map<std::string, std::string> _cache;
};

}

#endif