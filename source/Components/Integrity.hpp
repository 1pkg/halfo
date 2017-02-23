#ifndef COMPONENTS_INTEGRITY
#define COMPONENTS_INTEGRITY

#include "File.hpp"

namespace Components
{

class Integrity : public File
{
public:

	Integrity();

	const std::string & storage() const;
	const std::string & resource() const;

	void storage(const std::string & storage);
	void resource(const std::string & resource);

protected:

	std::string path() const override;
	cocos2d::Data serialize() const override;
	bool unserialize(const cocos2d::Data & buffer) override;

private:

	std::string _storage, _resource, _self;

};

}

#endif