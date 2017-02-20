#ifndef COMPONENTS_INTEGRITY
#define COMPONENTS_INTEGRITY

#include "File.hpp"

namespace Components
{

class Integrity : public File
{
public:

	std::string path() const override;
	void flush() const override;
	void fetch() override;

	Integrity();
	~Integrity();

	const std::string & storage() const;
	const std::string & resource() const;

	void storage(const std::string & storage);
	void resource(const std::string & resource);

private:

	void write() const;
	void read();
	std::string _storage, _resource;

};

}

#endif