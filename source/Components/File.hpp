#ifndef COMPONENTS_FILE
#define COMPONENTS_FILE

#include "Application/Component.hpp"
#include <cocos2d.h>

namespace Components
{

class File : public Application::Component
{
public:

	void finitialize() override;
	std::string root() const;
	std::string assets() const;
	std::string storage() const;
	std::string cache() const;
	bool exist(const std::string & path) const;
	cocos2d::Data read(const std::string & path) const;
	void write(const cocos2d::Data & data, const std::string & path) const;
	std::string cache(const cocos2d::Data & data);
	void directory(const std::string & path) const;
	void remove(const std::string & path) const;
	void copy(const std::string & from, const std::string & to) const;
	void move(const std::string & from, const std::string & to) const;
	std::vector<std::string> list(const std::string & path) const;

private:

	std::string unique(std::size_t size) const;
	std::vector<std::string> _files;
};

}

#endif