#ifndef COMPONENTS_FILE
#define COMPONENTS_FILE

#include "include.hpp"

namespace Components
{

class File : public Application::Component
{
public:

	void initialize() override;
	void finitialize() override;
	std::string application() const;
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

private:

	std::vector<std::string> _files;
};

}

#endif