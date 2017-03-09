#ifndef COMPONENTS_FILE
#define COMPONENTS_FILE

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class File : public Application::Component
{
public:

	void initialize() override;
	void finitialize() override;
	cocos2d::Data read(const std::string & from) const;
	std::string write(const cocos2d::Data & data, const std::string & to = "");
	bool exist(const std::string & from) const;
	void remove(const std::string & from);
	void move(const std::string & from, const std::string & to);

private:

	std::string unique(std::size_t size) const;
	std::vector<std::string> _files;
};

}

#endif