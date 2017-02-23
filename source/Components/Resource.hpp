#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "File.hpp"
#include <unordered_map>

namespace Components
{

class Resource : public File
{
public:

	Resource();
	void flush() const override;
	void pull() override;
	cocos2d::Data resource(const std::string & alias) const;

protected:

	std::string path() const override;
	cocos2d::Data serialize() const override;
	bool unserialize(const  cocos2d::Data & buffer) override;
	void default() override;

private:

	std::unordered_map<
		std::string,
		std::tuple<
			std::string,
			std::string
		>
	> _resources;
};

}

#endif