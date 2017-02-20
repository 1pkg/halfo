#ifndef COMPONENTS_RESOURCE
#define COMPONENTS_RESOURCE

#include "File.hpp"
#include "Buffer.hpp"
#include <unordered_map>

namespace Components
{

class Resource : public File
{
public:

	std::string path() const override;
	void flush() const override;
	void fetch() override;

	Resource();
	~Resource();

	Buffer resource(const std::string & alias) const;

private:

	struct Rsc
	{
		std::string path;
		std::string hash;
	};

	void write() const;
	void read();
	void default();
	std::unordered_map<
		std::string,
		Rsc
	> _resources;

};

}

#endif